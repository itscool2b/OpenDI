#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PKG_DIR="$(dirname "$SCRIPT_DIR")"
ROOT_DIR="$(dirname "$PKG_DIR")"

SRC_DIR="$ROOT_DIR/src"
INCLUDE_DIR="$ROOT_DIR/include"
BUILD_DIR="$PKG_DIR/build"
GLUE="$PKG_DIR/src/glue.c"

mkdir -p "$BUILD_DIR"

# Collect all .c files, excluding visuals/ and elementary/
SOURCES=$(find "$SRC_DIR" -name '*.c' \
	! -path '*/visuals/*' \
	! -path '*/elementary/*')

EXPORTS=$(cat "$SCRIPT_DIR/exports.json")

emcc \
	$SOURCES \
	"$GLUE" \
	-I"$INCLUDE_DIR" \
	-o "$BUILD_DIR/opendi.js" \
	-s MODULARIZE=1 \
	-s EXPORT_ES6=1 \
	-s EXPORTED_FUNCTIONS="$EXPORTS" \
	-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap","addFunction","removeFunction","getValue","setValue","UTF8ToString","stringToUTF8","lengthBytesUTF8","wasmMemory"]' \
	-s ALLOW_TABLE_GROWTH=1 \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s FILESYSTEM=0 \
	-s ENVIRONMENT='web,node' \
	-s EXPORT_NAME='createOpenDI' \
	-O2 \
	-lm

echo "Build complete: $BUILD_DIR/opendi.js + $BUILD_DIR/opendi.wasm"
