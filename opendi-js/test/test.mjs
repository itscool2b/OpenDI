import { init } from '../src/opendi.mjs'

let passed = 0
let failed = 0

function check(name, got, expected, eps = 1e-6) {
	if (typeof expected === 'number') {
		if (Math.abs(got - expected) < eps) {
			passed++
		} else {
			failed++
			console.error(`  FAIL: ${name} — got ${got}, expected ${expected}`)
		}
	} else {
		// array comparison
		const a = Array.from(got)
		const b = Array.from(expected)
		if (a.length !== b.length) {
			failed++
			console.error(`  FAIL: ${name} — length ${a.length} vs ${b.length}`)
			return
		}
		let ok = true
		for (let i = 0; i < a.length; i++) {
			if (Math.abs(a[i] - b[i]) > eps) {
				ok = false
				break
			}
		}
		if (ok) {
			passed++
		} else {
			failed++
			console.error(`  FAIL: ${name} — got [${a}], expected [${b}]`)
		}
	}
}

async function run() {
	const o = await init()

	console.log('=== Primitives ===')
	check('add(1,2,3)', o.add(1, 2, 3), 6)
	check('add(10,20)', o.add(10, 20), 30)
	check('subtract(10,3)', o.subtract(10, 3), 7)
	check('multiply(2,3,4)', o.multiply(2, 3, 4), 24)
	check('divide(100,5,2)', o.divide(100, 5, 2), 10)
	check('abs(-5)', o.abs(-5), 5)
	check('min(3,1,2)', o.min(3, 1, 2), 1)
	check('max(3,1,2)', o.max(3, 1, 2), 3)
	check('round floor 3.7', o.round('floor', 3.7), 3)
	check('round ceil 3.2', o.round('ceil', 3.2), 4)
	check('pow(2, 10)', o.pow(2, 10), 1024)

	console.log('=== Activations ===')
	check('relu(5)', o.relu(5), 5)
	check('relu(-5)', o.relu(-5), 0)
	check('sigmoid(0)', o.sigmoid(0), 0.5)

	const sm = o.softmax([1, 2, 3])
	check('softmax sum', sm[0] + sm[1] + sm[2], 1.0, 1e-5)
	check('softmax order', sm[2] > sm[1] && sm[1] > sm[0] ? 1 : 0, 1)

	console.log('=== Vectors ===')
	const va = o.vecadd([1, 2, 3], [4, 5, 6])
	check('vecadd', va, [5, 7, 9])

	const vs = o.vecscale([1, 2, 3], 2)
	check('vecscale', vs, [2, 4, 6])

	const vc = o.veccross([1, 0, 0], [0, 1, 0])
	check('veccross', vc, [0, 0, 1])

	check('vecdot', o.vecdot([1, 2, 3], [4, 5, 6]), 32)
	check('vecnorm', o.vecnorm([3, 4]), 5)

	console.log('=== Matrices ===')
	const mm = o.matmul([1, 2, 3, 4], [5, 6, 7, 8], 2, 2, 2)
	check('matmul', mm, [19, 22, 43, 50])

	const ma = o.matadd([1, 2, 3, 4], [10, 20, 30, 40], 2, 2)
	check('matadd', ma, [11, 22, 33, 44])

	const ms = o.matscale([1, 2, 3, 4], 3, 2, 2)
	check('matscale', ms, [3, 6, 9, 12])

	const mt = o.mattranspose([1, 2, 3, 4, 5, 6], 2, 3)
	check('mattranspose', mt, [1, 4, 2, 5, 3, 6])

	console.log('=== Loss ===')
	const mseVal = o.mseLoss([1, 2, 3], [1, 2, 3])
	check('mse_loss perfect', mseVal, 0)

	const mseVal2 = o.mseLoss([1, 0], [0, 1])
	check('mse_loss', mseVal2, 1.0)

	console.log('=== Backward ===')
	const rb = o.reluBackward([1, 1, 1], [5, -3, 0.1])
	check('relu_backward', rb, [1, 0, 1])

	console.log('=== Optimizer ===')
	const updated = o.sgdUpdate([1, 2, 3], [0.1, 0.2, 0.3], 1.0)
	check('sgd_update', updated, [0.9, 1.8, 2.7])

	console.log('=== Random ===')
	o.randomSeed(42)
	const ru = o.randomUniform(0, 1, 5)
	check('random_uniform length', ru.length, 5)
	let inRange = true
	for (let i = 0; i < 5; i++) {
		if (ru[i] < 0 || ru[i] > 1) inRange = false
	}
	check('random_uniform range', inRange ? 1 : 0, 1)

	const rn = o.randomNormal(0, 1, 5)
	check('random_normal length', rn.length, 5)

	console.log('=== Statistics ===')
	const norm = o.normalize([2, 4, 4, 4, 5, 5, 7, 9])
	check('normalize mean ~0', norm.reduce((a, b) => a + b) / norm.length, 0, 1e-5)

	console.log('=== Calculus ===')
	const fd = o.forwarddiff(x => x * x, 3, 0.0001)
	check('forwarddiff x^2 at 3', fd, 6.0, 0.01)

	const bd = o.backwarddiff(x => x * x, 3, 0.0001)
	check('backwarddiff x^2 at 3', bd, 6.0, 0.01)

	const cd = o.centralDifference(x => x * x, 3, 0.0001)
	check('central_difference x^2 at 3', cd, 6.0, 1e-4)

	const sd = o.secondDerivative(x => x * x, 3, 0.001)
	check('secondderivative x^2', sd, 2.0, 0.1)

	const ri = o.rombergIntegrate(x => x * x, 0, 1, 1e-8, 10)
	check('romberg x^2 [0,1]', ri, 1.0 / 3.0, 1e-5)

	console.log('=== Pipeline ===')
	const br = o.batchRelu([-1, 2, -3, 4])
	check('batch_relu', br, [0, 2, 0, 4])

	const bs = o.batchSigmoid([0, 0])
	check('batch_sigmoid', bs, [0.5, 0.5])

	const bn = o.batchNormalize([1, 2, 3, 4, 5, 6], 3, 2)
	check('batch_normalize length', bn.length, 6)

	console.log('=== Weights ===')
	o.randomSeed(42)
	const w = o.initWeights(10, 0.0, 0.1)
	check('initWeights length', w.data.length, 10)
	check('initWeights has ptr', w._ptr > 0 ? 1 : 0, 1)
	w.free()

	console.log('=== Session API ===')
	{
		const session = o.createSession(8192)

		// Basic session operations
		const aPtr = session.writeArray([1, 2, 3])
		const bPtr = session.writeArray([4, 5, 6])
		const sumPtr = session.vecadd(aPtr, bPtr, 3)
		const result = session.readArray(sumPtr, 3)
		check('session vecadd', result, [5, 7, 9])

		const mmPtr = session.matmul(
			session.writeArray([1, 2, 3, 4]),
			session.writeArray([5, 6, 7, 8]),
			2, 2, 2
		)
		check('session matmul', session.readArray(mmPtr, 4), [19, 22, 43, 50])

		session.clear()

		// After clear, write new data and do more work
		const cPtr = session.writeArray([0, 0, 0, 0])
		const sigPtr = session.batchSigmoid(cPtr, 4)
		check('session batch_sigmoid', session.readArray(sigPtr, 4), [0.5, 0.5, 0.5, 0.5])

		session.destroy()
	}

	console.log('=== Session Training Loop ===')
	{
		o.randomSeed(42)

		// Linearly separable: feature > 0.5 → class 1
		const nSamples = 4
		const nFeatures = 1
		const features = [0.1, 0.3, 0.7, 0.9]
		const targets = [0, 0, 1, 1]

		const weights = o.initWeights(nFeatures, 0.0, 0.1)

		const session = o.createSession(65536)
		let lastLoss = Infinity

		for (let epoch = 0; epoch < 200; epoch++) {
			const featPtr = session.writeArray(features)
			const targPtr = session.writeArray(targets)

			const fwd = session.denseForward(featPtr, weights._ptr, nSamples, nFeatures, 1, 'sigmoid')
			lastLoss = session.mseLoss(fwd.outputPtr, targPtr, nSamples)

			const dLoss = session.mseBackward(fwd.outputPtr, targPtr, nSamples)
			const grad = session.denseBackward(dLoss, featPtr, weights._ptr, fwd.cachePtr, nSamples, nFeatures, 1, 'sigmoid')

			const newWPtr = session.sgdUpdate(weights._ptr, grad.dWeightsPtr, 1.0, nFeatures)
			const newWData = session.readArray(newWPtr, nFeatures)

			// Copy updated weights back to the malloc'd pointer
			session.copyToPtr(weights._ptr, newWData)

			session.clear()
		}

		check('training loss decreased', lastLoss < 0.3 ? 1 : 0, 1)

		session.destroy()
		weights.free()
	}

	console.log('')
	console.log(`=== Results: ${passed} passed, ${failed} failed ===`)
	process.exit(failed > 0 ? 1 : 0)
}

run().catch(e => {
	console.error(e)
	process.exit(1)
})
