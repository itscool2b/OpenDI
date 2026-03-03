export interface Weights {
	/** Raw WASM pointer — use with Session API */
	_ptr: number
	/** Copy of the weight data as Float64Array */
	data: Float64Array
	/** Number of weights */
	length: number
	/** Free the underlying malloc'd memory */
	free(): void
}

export interface ForwardResult {
	/** WASM pointer to output array */
	outputPtr: number
	/** WASM pointer to cache (for backward pass), or 0 if softmax/none */
	cachePtr: number
}

export interface BackwardResult {
	/** WASM pointer to weight gradients (n × p) */
	dWeightsPtr: number
	/** WASM pointer to input gradients (m × n) */
	dInputPtr: number
}

export type Activation = 'none' | 'relu' | 'sigmoid' | 'softmax' | number

export interface Session {
	writeArray(arr: ArrayLike<number>): number
	writeI32Array(arr: ArrayLike<number>): number
	readArray(ptr: number, n: number): Float64Array
	/** Copy a JS array into a WASM pointer (e.g. malloc'd weights) */
	copyToPtr(destPtr: number, srcArray: ArrayLike<number>): void

	softmax(inputPtr: number, n: number): number
	vecadd(aPtr: number, bPtr: number, n: number): number
	vecscale(arrPtr: number, scalar: number, n: number): number
	matmul(aPtr: number, bPtr: number, m: number, n: number, p: number): number
	matadd(aPtr: number, bPtr: number, m: number, n: number): number
	matscale(aPtr: number, s: number, m: number, n: number): number
	mattranspose(aPtr: number, m: number, n: number): number

	reluBackward(doutPtr: number, inputPtr: number, n: number): number
	sigmoidBackward(doutPtr: number, outputPtr: number, n: number): number
	softmaxBackward(doutPtr: number, outputPtr: number, n: number): number
	matmulBackwardA(doutPtr: number, bPtr: number, m: number, n: number, p: number): number
	matmulBackwardB(aPtr: number, doutPtr: number, m: number, n: number, p: number): number

	sgdUpdate(weightsPtr: number, gradsPtr: number, lr: number, n: number): number

	normalize(ptr: number, n: number): number
	batchRelu(ptr: number, n: number): number
	batchSigmoid(ptr: number, n: number): number
	batchSoftmax(ptr: number, rows: number, cols: number): number
	batchNormalize(ptr: number, nSamples: number, nFeatures: number): number

	mseBackward(predPtr: number, targetsPtr: number, n: number): number
	crossEntropyBackward(predPtr: number, targetsPtr: number, nSamples: number, nClasses: number): number

	randomUniform(min: number, max: number, n: number): number
	randomNormal(mean: number, std: number, n: number): number

	denseForward(inputPtr: number, weightsPtr: number, m: number, n: number, p: number, activation: Activation): ForwardResult
	denseBackward(doutPtr: number, inputPtr: number, weightsPtr: number, cachePtr: number, m: number, n: number, p: number, activation: Activation): BackwardResult

	mseLoss(predPtr: number, targetsPtr: number, n: number): number
	crossEntropy(predPtr: number, targetsPtr: number, n: number): number
	accuracy(predPtr: number, labelsPtr: number, nSamples: number, nClasses: number): number

	clear(): void
	destroy(): void
}

export interface OpenDI {
	// Primitives
	add(...nums: number[]): number
	subtract(...nums: number[]): number
	multiply(...nums: number[]): number
	divide(...nums: number[]): number
	abs(x: number): number
	min(...nums: number[]): number
	max(...nums: number[]): number
	round(mode: 'floor' | 'ceil', x: number): number
	pow(base: number, exp: number): number

	// Activations
	relu(x: number): number
	sigmoid(x: number): number
	softmax(arr: ArrayLike<number>): Float64Array

	// Vectors
	vecadd(a: ArrayLike<number>, b: ArrayLike<number>): Float64Array
	vecscale(arr: ArrayLike<number>, scalar: number): Float64Array
	veccross(a: ArrayLike<number>, b: ArrayLike<number>): Float64Array
	vecdot(a: ArrayLike<number>, b: ArrayLike<number>): number
	vecnorm(arr: ArrayLike<number>): number

	// Matrices
	matmul(a: ArrayLike<number>, b: ArrayLike<number>, m: number, n: number, p: number): Float64Array
	matadd(a: ArrayLike<number>, b: ArrayLike<number>, m: number, n: number): Float64Array
	matscale(a: ArrayLike<number>, s: number, m: number, n: number): Float64Array
	mattranspose(a: ArrayLike<number>, m: number, n: number): Float64Array

	// Loss
	mseLoss(pred: ArrayLike<number>, targets: ArrayLike<number>): number
	crossEntropy(pred: ArrayLike<number>, targets: ArrayLike<number>): number

	// Backward
	reluBackward(dout: ArrayLike<number>, input: ArrayLike<number>): Float64Array
	sigmoidBackward(dout: ArrayLike<number>, output: ArrayLike<number>): Float64Array
	softmaxBackward(dout: ArrayLike<number>, output: ArrayLike<number>): Float64Array
	matmulBackwardA(dout: ArrayLike<number>, b: ArrayLike<number>, m: number, n: number, p: number): Float64Array
	matmulBackwardB(a: ArrayLike<number>, dout: ArrayLike<number>, m: number, n: number, p: number): Float64Array

	// Optimizer
	sgdUpdate(weights: ArrayLike<number>, grads: ArrayLike<number>, lr: number): Float64Array

	// Random
	randomSeed(seed: number): void
	randomUniform(min: number, max: number, n: number): Float64Array
	randomNormal(mean: number, std: number, n: number): Float64Array

	// Statistics
	normalize(arr: ArrayLike<number>): Float64Array

	// Calculus
	forwarddiff(f: (x: number) => number, x: number, h: number): number
	backwarddiff(f: (x: number) => number, x: number, h: number): number
	centralDifference(f: (x: number) => number, x: number, h: number): number
	secondDerivative(f: (x: number) => number, x: number, h: number): number
	centralNth(f: (x: number) => number, x: number, h: number, n: number): number
	rombergIntegrate(f: (x: number) => number, a: number, b: number, eps: number, kMax: number): number

	// Pipeline
	batchRelu(input: ArrayLike<number>): Float64Array
	batchSigmoid(input: ArrayLike<number>): Float64Array
	batchSoftmax(input: ArrayLike<number>, rows: number, cols: number): Float64Array
	batchNormalize(features: ArrayLike<number>, nSamples: number, nFeatures: number): Float64Array
	mseBackward(pred: ArrayLike<number>, targets: ArrayLike<number>): Float64Array
	crossEntropyBackward(pred: ArrayLike<number>, targets: ArrayLike<number>, nSamples: number, nClasses: number): Float64Array
	accuracy(pred: ArrayLike<number>, labels: ArrayLike<number>, nSamples: number, nClasses: number): number

	// Weights
	initWeights(n: number, mean: number, std: number): Weights

	// Session
	createSession(arenaBytes?: number): Session

	// Constants
	readonly ACTIVATION_NONE: 0
	readonly ACTIVATION_RELU: 1
	readonly ACTIVATION_SIGMOID: 2
	readonly ACTIVATION_SOFTMAX: 3
}

export function init(wasmUrl?: string): Promise<OpenDI>
export default init
