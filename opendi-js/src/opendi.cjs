module.exports.init = async function(wasmUrl) {
	const { init } = await import('./opendi.mjs')
	return init(wasmUrl)
}
