import createOpenDI from '../build/opendi.js'

// Activation enum values matching C ActivationType
const ACT = { none: 0, relu: 1, sigmoid: 2, softmax: 3 }

function actEnum(str) {
	if (typeof str === 'number') return str
	const v = ACT[(str || 'none').toLowerCase()]
	if (v === undefined) throw new Error(`Unknown activation: ${str}`)
	return v
}

// ── Heap helpers ──

function writeF64(wasm, arena, arr) {
	const bytes = arr.length * 8
	const ptr = wasm._glue_arena_push(arena, bytes)
	if (!ptr) throw new Error('Arena out of memory')
	const heap = new Float64Array(wasm.wasmMemory.buffer, ptr, arr.length)
	heap.set(arr)
	return ptr
}

function readF64(wasm, ptr, n) {
	const offset = ptr / 8
	return new Float64Array(wasm.wasmMemory.buffer.slice(ptr, ptr + n * 8))
}

function writeI32(wasm, arena, arr) {
	const bytes = arr.length * 4
	const ptr = wasm._glue_arena_push(arena, bytes)
	if (!ptr) throw new Error('Arena out of memory')
	const heap = new Int32Array(wasm.wasmMemory.buffer, ptr, arr.length)
	heap.set(arr)
	return ptr
}

function readI32(wasm, ptr, n) {
	return new Int32Array(wasm.wasmMemory.buffer.slice(ptr, ptr + n * 4))
}

// ── Temp arena pattern ──

function withTempArena(wasm, bytes, fn) {
	const arena = wasm._glue_arena_create(bytes)
	try {
		return fn(arena)
	} finally {
		wasm._glue_arena_destroy(arena)
	}
}

// ── Function pointer helpers for calculus ──
// Cache function pointers to avoid removeFunction bugs in Emscripten.
// Each unique JS function gets one WASM table slot.
const fpCache = new Map()

function withFunctionPointer(wasm, jsFn, cb) {
	let fp = fpCache.get(jsFn)
	if (fp === undefined) {
		fp = wasm.addFunction(jsFn, 'dd')
		fpCache.set(jsFn, fp)
	}
	return cb(fp)
}

// ── Main init ──

export async function init(wasmUrl) {
	const opts = {}
	if (wasmUrl) {
		opts.locateFile = () => wasmUrl
	}
	const wasm = await createOpenDI(opts)

	const api = {}

	// ── Primitives (variadic → array-based via glue) ──

	api.add = (...nums) => {
		const arr = nums.flat()
		return withTempArena(wasm, arr.length * 8 + 64, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			return wasm._glue_add(ptr, arr.length)
		})
	}

	api.subtract = (...nums) => {
		const arr = nums.flat()
		return withTempArena(wasm, arr.length * 8 + 64, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			return wasm._glue_subtract(ptr, arr.length)
		})
	}

	api.multiply = (...nums) => {
		const arr = nums.flat()
		return withTempArena(wasm, arr.length * 8 + 64, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			return wasm._glue_multiply(ptr, arr.length)
		})
	}

	api.divide = (...nums) => {
		const arr = nums.flat()
		return withTempArena(wasm, arr.length * 8 + 64, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			return wasm._glue_divide(ptr, arr.length)
		})
	}

	api.abs = (x) => wasm._absolute(x)

	api.min = (...nums) => {
		const arr = nums.flat()
		return withTempArena(wasm, arr.length * 8 + 64, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			return wasm._glue_min(ptr, arr.length)
		})
	}

	api.max = (...nums) => {
		const arr = nums.flat()
		return withTempArena(wasm, arr.length * 8 + 64, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			return wasm._glue_max(ptr, arr.length)
		})
	}

	api.round = (mode, x) => {
		return withTempArena(wasm, 64, (arena) => {
			const strBytes = wasm.lengthBytesUTF8(mode) + 1
			const strPtr = wasm._glue_arena_push(arena, strBytes)
			wasm.stringToUTF8(mode, strPtr, strBytes)
			return wasm._roundval(strPtr, x)
		})
	}

	api.pow = (base, exp) => wasm._exponents(base, exp)

	// ── Activations ──

	api.relu = (x) => wasm._relu(x)

	api.sigmoid = (x) => wasm._sigmoid(x)

	api.softmax = (arr) => {
		const input = Array.isArray(arr) ? arr : Array.from(arr)
		const n = input.length
		return withTempArena(wasm, n * 8 * 3 + 256, (arena) => {
			const inPtr = writeF64(wasm, arena, input)
			const outPtr = wasm._softmax(arena, inPtr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	// ── Vectors ──

	api.vecadd = (a, b) => {
		const n = a.length
		return withTempArena(wasm, n * 8 * 3 + 256, (arena) => {
			const aPtr = writeF64(wasm, arena, a)
			const bPtr = writeF64(wasm, arena, b)
			const outPtr = wasm._vecadd(arena, aPtr, bPtr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.vecscale = (arr, scalar) => {
		const n = arr.length
		return withTempArena(wasm, n * 8 * 2 + 256, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			const outPtr = wasm._vecscale(arena, ptr, scalar, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.veccross = (a, b) => {
		return withTempArena(wasm, 6 * 8 + 256, (arena) => {
			const aPtr = writeF64(wasm, arena, a)
			const bPtr = writeF64(wasm, arena, b)
			const outPtr = wasm._veccross(arena, aPtr, bPtr)
			return readF64(wasm, outPtr, 3)
		})
	}

	api.vecdot = (a, b) => {
		const n = a.length
		return withTempArena(wasm, n * 8 * 2 + 256, (arena) => {
			const aPtr = writeF64(wasm, arena, a)
			const bPtr = writeF64(wasm, arena, b)
			return wasm._vecdot(aPtr, bPtr, n)
		})
	}

	api.vecnorm = (arr) => {
		const n = arr.length
		return withTempArena(wasm, n * 8 + 256, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			return wasm._vecnorm(ptr, n)
		})
	}

	// ── Matrices ──

	api.matmul = (a, b, m, n, p) => {
		return withTempArena(wasm, (m * n + n * p + m * p) * 8 + 256, (arena) => {
			const aPtr = writeF64(wasm, arena, a)
			const bPtr = writeF64(wasm, arena, b)
			const outPtr = wasm._matmul(arena, aPtr, bPtr, m, n, p)
			return readF64(wasm, outPtr, m * p)
		})
	}

	api.matadd = (a, b, m, n) => {
		return withTempArena(wasm, m * n * 3 * 8 + 256, (arena) => {
			const aPtr = writeF64(wasm, arena, a)
			const bPtr = writeF64(wasm, arena, b)
			const outPtr = wasm._matadd(arena, aPtr, bPtr, m, n)
			return readF64(wasm, outPtr, m * n)
		})
	}

	api.matscale = (a, s, m, n) => {
		return withTempArena(wasm, m * n * 2 * 8 + 256, (arena) => {
			const aPtr = writeF64(wasm, arena, a)
			const outPtr = wasm._matscale(arena, aPtr, s, m, n)
			return readF64(wasm, outPtr, m * n)
		})
	}

	api.mattranspose = (a, m, n) => {
		return withTempArena(wasm, m * n * 2 * 8 + 256, (arena) => {
			const aPtr = writeF64(wasm, arena, a)
			const outPtr = wasm._mattranspose(arena, aPtr, m, n)
			return readF64(wasm, outPtr, n * m)
		})
	}

	// ── Loss ──

	api.mseLoss = (pred, targets) => {
		const n = pred.length
		return withTempArena(wasm, n * 8 * 2 + 256, (arena) => {
			const pPtr = writeF64(wasm, arena, pred)
			const tPtr = writeF64(wasm, arena, targets)
			return wasm._mse_loss(pPtr, tPtr, n)
		})
	}

	api.crossEntropy = (pred, targets) => {
		const n = pred.length
		return withTempArena(wasm, n * 8 * 2 + 256, (arena) => {
			const pPtr = writeF64(wasm, arena, pred)
			const tPtr = writeF64(wasm, arena, targets)
			return wasm._cross_entropy(pPtr, tPtr, n)
		})
	}

	// ── Backward ──

	api.reluBackward = (dout, input) => {
		const n = dout.length
		return withTempArena(wasm, n * 8 * 3 + 256, (arena) => {
			const dPtr = writeF64(wasm, arena, dout)
			const iPtr = writeF64(wasm, arena, input)
			const outPtr = wasm._relu_backward(arena, dPtr, iPtr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.sigmoidBackward = (dout, output) => {
		const n = dout.length
		return withTempArena(wasm, n * 8 * 3 + 256, (arena) => {
			const dPtr = writeF64(wasm, arena, dout)
			const oPtr = writeF64(wasm, arena, output)
			const outPtr = wasm._sigmoid_backward(arena, dPtr, oPtr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.softmaxBackward = (dout, output) => {
		const n = dout.length
		return withTempArena(wasm, n * 8 * 3 + 256, (arena) => {
			const dPtr = writeF64(wasm, arena, dout)
			const oPtr = writeF64(wasm, arena, output)
			const outPtr = wasm._softmax_backward(arena, dPtr, oPtr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.matmulBackwardA = (dout, b, m, n, p) => {
		return withTempArena(wasm, (m * p + n * p + m * n) * 8 + 256, (arena) => {
			const dPtr = writeF64(wasm, arena, dout)
			const bPtr = writeF64(wasm, arena, b)
			const outPtr = wasm._matmul_backward_a(arena, dPtr, bPtr, m, n, p)
			return readF64(wasm, outPtr, m * n)
		})
	}

	api.matmulBackwardB = (a, dout, m, n, p) => {
		return withTempArena(wasm, (m * n + m * p + n * p) * 8 + 256, (arena) => {
			const aPtr = writeF64(wasm, arena, a)
			const dPtr = writeF64(wasm, arena, dout)
			const outPtr = wasm._matmul_backward_b(arena, aPtr, dPtr, m, n, p)
			return readF64(wasm, outPtr, n * p)
		})
	}

	// ── Optimizer ──

	api.sgdUpdate = (weights, grads, lr) => {
		const n = weights.length
		return withTempArena(wasm, n * 8 * 3 + 256, (arena) => {
			const wPtr = writeF64(wasm, arena, weights)
			const gPtr = writeF64(wasm, arena, grads)
			const outPtr = wasm._sgd_update(arena, wPtr, gPtr, lr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	// ── Random ──

	api.randomSeed = (seed) => wasm._random_seed(seed)

	api.randomUniform = (min, max, n) => {
		return withTempArena(wasm, n * 8 + 256, (arena) => {
			const outPtr = wasm._random_uniform(arena, min, max, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.randomNormal = (mean, std, n) => {
		return withTempArena(wasm, n * 8 + 256, (arena) => {
			const outPtr = wasm._random_normal(arena, mean, std, n)
			return readF64(wasm, outPtr, n)
		})
	}

	// ── Statistics ──

	api.normalize = (arr) => {
		const n = arr.length
		return withTempArena(wasm, n * 8 * 2 + 256, (arena) => {
			const ptr = writeF64(wasm, arena, arr)
			const outPtr = wasm._normalize(arena, ptr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	// ── Calculus (function pointer based) ──

	api.forwarddiff = (f, x, h) => {
		return withFunctionPointer(wasm, f, (fp) => {
			return wasm._forwarddiff(fp, x, h)
		})
	}

	api.backwarddiff = (f, x, h) => {
		return withFunctionPointer(wasm, f, (fp) => {
			return wasm._backwarddiff(fp, x, h)
		})
	}

	api.centralDifference = (f, x, h) => {
		return withFunctionPointer(wasm, f, (fp) => {
			return wasm._central_difference(fp, x, h)
		})
	}

	api.secondDerivative = (f, x, h) => {
		return withFunctionPointer(wasm, f, (fp) => {
			return wasm._secondderivative(fp, x, h)
		})
	}

	api.centralNth = (f, x, h, n) => {
		return withFunctionPointer(wasm, f, (fp) => {
			return wasm._centralnth(fp, x, h, n)
		})
	}

	api.rombergIntegrate = (f, a, b, eps, kMax) => {
		return withFunctionPointer(wasm, f, (fp) => {
			return wasm._romberg_integrate(fp, a, b, eps, kMax)
		})
	}

	// ── Pipeline (batch operations) ──

	api.batchRelu = (input) => {
		const n = input.length
		return withTempArena(wasm, n * 8 * 2 + 256, (arena) => {
			const ptr = writeF64(wasm, arena, input)
			const outPtr = wasm._batch_relu(arena, ptr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.batchSigmoid = (input) => {
		const n = input.length
		return withTempArena(wasm, n * 8 * 2 + 256, (arena) => {
			const ptr = writeF64(wasm, arena, input)
			const outPtr = wasm._batch_sigmoid(arena, ptr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.batchSoftmax = (input, rows, cols) => {
		return withTempArena(wasm, rows * cols * 8 * 2 + 256, (arena) => {
			const ptr = writeF64(wasm, arena, input)
			const outPtr = wasm._batch_softmax(arena, ptr, rows, cols)
			return readF64(wasm, outPtr, rows * cols)
		})
	}

	api.batchNormalize = (features, nSamples, nFeatures) => {
		return withTempArena(wasm, nSamples * nFeatures * 8 * 2 + 256, (arena) => {
			const ptr = writeF64(wasm, arena, features)
			const outPtr = wasm._batch_normalize(arena, ptr, nSamples, nFeatures)
			return readF64(wasm, outPtr, nSamples * nFeatures)
		})
	}

	api.mseBackward = (pred, targets) => {
		const n = pred.length
		return withTempArena(wasm, n * 8 * 3 + 256, (arena) => {
			const pPtr = writeF64(wasm, arena, pred)
			const tPtr = writeF64(wasm, arena, targets)
			const outPtr = wasm._mse_backward(arena, pPtr, tPtr, n)
			return readF64(wasm, outPtr, n)
		})
	}

	api.crossEntropyBackward = (pred, targets, nSamples, nClasses) => {
		const total = nSamples * nClasses
		return withTempArena(wasm, total * 8 * 3 + 256, (arena) => {
			const pPtr = writeF64(wasm, arena, pred)
			const tPtr = writeF64(wasm, arena, targets)
			const outPtr = wasm._cross_entropy_backward(arena, pPtr, tPtr, nSamples, nClasses)
			return readF64(wasm, outPtr, total)
		})
	}

	api.accuracy = (pred, labels, nSamples, nClasses) => {
		return withTempArena(wasm, nSamples * nClasses * 8 + nSamples * 4 + 256, (arena) => {
			const pPtr = writeF64(wasm, arena, pred)
			const lPtr = writeI32(wasm, arena, labels)
			return wasm._accuracy(pPtr, lPtr, nSamples, nClasses)
		})
	}

	// ── Weights (uses malloc, not arena) ──

	api.initWeights = (n, mean, std) => {
		const ptr = wasm._init_weights(n, mean, std)
		const data = readF64(wasm, ptr, n)
		return {
			_ptr: ptr,
			data,
			length: n,
			free() { wasm._glue_free(ptr) }
		}
	}

	// ── Session API (pointer-level control for training loops) ──

	api.createSession = (arenaBytes) => {
		const arena = wasm._glue_arena_create(arenaBytes || 65536)
		const session = {}

		session.writeArray = (arr) => writeF64(wasm, arena, arr)
		session.writeI32Array = (arr) => writeI32(wasm, arena, arr)
		session.readArray = (ptr, n) => readF64(wasm, ptr, n)

		session.copyToPtr = (destPtr, srcArray) => {
			const heap = new Float64Array(wasm.wasmMemory.buffer, destPtr, srcArray.length)
			heap.set(srcArray)
		}

		session.softmax = (inputPtr, n) => {
			return wasm._softmax(arena, inputPtr, n)
		}

		session.vecadd = (aPtr, bPtr, n) => {
			return wasm._vecadd(arena, aPtr, bPtr, n)
		}

		session.vecscale = (arrPtr, scalar, n) => {
			return wasm._vecscale(arena, arrPtr, scalar, n)
		}

		session.matmul = (aPtr, bPtr, m, n, p) => {
			return wasm._matmul(arena, aPtr, bPtr, m, n, p)
		}

		session.matadd = (aPtr, bPtr, m, n) => {
			return wasm._matadd(arena, aPtr, bPtr, m, n)
		}

		session.matscale = (aPtr, s, m, n) => {
			return wasm._matscale(arena, aPtr, s, m, n)
		}

		session.mattranspose = (aPtr, m, n) => {
			return wasm._mattranspose(arena, aPtr, m, n)
		}

		session.reluBackward = (doutPtr, inputPtr, n) => {
			return wasm._relu_backward(arena, doutPtr, inputPtr, n)
		}

		session.sigmoidBackward = (doutPtr, outputPtr, n) => {
			return wasm._sigmoid_backward(arena, doutPtr, outputPtr, n)
		}

		session.softmaxBackward = (doutPtr, outputPtr, n) => {
			return wasm._softmax_backward(arena, doutPtr, outputPtr, n)
		}

		session.matmulBackwardA = (doutPtr, bPtr, m, n, p) => {
			return wasm._matmul_backward_a(arena, doutPtr, bPtr, m, n, p)
		}

		session.matmulBackwardB = (aPtr, doutPtr, m, n, p) => {
			return wasm._matmul_backward_b(arena, aPtr, doutPtr, m, n, p)
		}

		session.sgdUpdate = (weightsPtr, gradsPtr, lr, n) => {
			return wasm._sgd_update(arena, weightsPtr, gradsPtr, lr, n)
		}

		session.normalize = (ptr, n) => {
			return wasm._normalize(arena, ptr, n)
		}

		session.batchRelu = (ptr, n) => {
			return wasm._batch_relu(arena, ptr, n)
		}

		session.batchSigmoid = (ptr, n) => {
			return wasm._batch_sigmoid(arena, ptr, n)
		}

		session.batchSoftmax = (ptr, rows, cols) => {
			return wasm._batch_softmax(arena, ptr, rows, cols)
		}

		session.batchNormalize = (ptr, nSamples, nFeatures) => {
			return wasm._batch_normalize(arena, ptr, nSamples, nFeatures)
		}

		session.mseBackward = (predPtr, targetsPtr, n) => {
			return wasm._mse_backward(arena, predPtr, targetsPtr, n)
		}

		session.crossEntropyBackward = (predPtr, targetsPtr, nSamples, nClasses) => {
			return wasm._cross_entropy_backward(arena, predPtr, targetsPtr, nSamples, nClasses)
		}

		session.randomUniform = (min, max, n) => {
			return wasm._random_uniform(arena, min, max, n)
		}

		session.randomNormal = (mean, std, n) => {
			return wasm._random_normal(arena, mean, std, n)
		}

		session.denseForward = (inputPtr, weightsPtr, m, n, p, activation) => {
			const act = actEnum(activation)
			const outPtr = wasm._glue_dense_forward(arena, inputPtr, weightsPtr, m, n, p, act)
			const cachePtr = wasm._glue_get_cache_ptr()
			return { outputPtr: outPtr, cachePtr }
		}

		session.denseBackward = (doutPtr, inputPtr, weightsPtr, cachePtr, m, n, p, activation) => {
			const act = actEnum(activation)
			wasm._glue_dense_backward(arena, doutPtr, inputPtr, weightsPtr, cachePtr, m, n, p, act)
			return {
				dWeightsPtr: wasm._glue_get_dw_ptr(),
				dInputPtr: wasm._glue_get_di_ptr()
			}
		}

		session.mseLoss = (predPtr, targetsPtr, n) => {
			return wasm._mse_loss(predPtr, targetsPtr, n)
		}

		session.crossEntropy = (predPtr, targetsPtr, n) => {
			return wasm._cross_entropy(predPtr, targetsPtr, n)
		}

		session.accuracy = (predPtr, labelsPtr, nSamples, nClasses) => {
			return wasm._accuracy(predPtr, labelsPtr, nSamples, nClasses)
		}

		session.clear = () => wasm._glue_arena_clear(arena)

		session.destroy = () => wasm._glue_arena_destroy(arena)

		return session
	}

	// ── Expose constants ──
	api.ACTIVATION_NONE = 0
	api.ACTIVATION_RELU = 1
	api.ACTIVATION_SIGMOID = 2
	api.ACTIVATION_SOFTMAX = 3

	return api
}

export default init
