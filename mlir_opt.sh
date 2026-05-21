#!/bin/bash
# run-opt.sh - Quick affine optimization runner

set -e

if [ -z "$1" ]; then
    echo "Usage: $0 \"pass1,pass2,...\""
    echo ""
    echo "Examples:"
    echo "  $0 \"affine-loop-tile{tile-size=256}\""
    echo "  $0 \"affine-loop-tile{tile-size=512},affine-loop-unroll{unroll-factor=4}\""
    echo "  $0 \"affine-loop-normalize,affine-scalar-replacement\""
    exit 1
fi

OPTS="$1"

echo "Running: $OPTS"
echo "========================================"

mlir-opt test.mlir \
  --pass-pipeline="builtin.module(func.func(${OPTS}))" \
  --mlir-print-op-generic=false \
  -o optimized.mlir

echo "Done! Output written to optimized.mlir"