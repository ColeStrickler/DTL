module {
  func.func @kernel() {
    %A = memref.alloc() : memref<4096xf32>
    %B = memref.alloc() : memref<4096xf32>
    %C = memref.alloc() : memref<4096xf32>

    // Producer loop
    affine.for %i = 0 to 4096 {
      %a = affine.load %A[%i] : memref<4096xf32>
      %b = arith.addf %a, %a : f32
      affine.store %b, %B[%i] : memref<4096xf32>
    }

    // Consumer loop (perfect for fusion)
    affine.for %i = 0 to 4096 {
      %b = affine.load %B[%i] : memref<4096xf32>
      %c = arith.mulf %b, %b : f32
      affine.store %c, %C[%i] : memref<4096xf32>
    }

    return
  }
}