module {
  func.func @kernel() {
    %alloc = memref.alloc() : memref<1xf32>
    %alloc_0 = memref.alloc() : memref<4096xf32>
    %alloc_1 = memref.alloc() : memref<4096xf32>
    affine.for %arg0 = 0 to 4096 {
      %0 = affine.load %alloc_0[%arg0] : memref<4096xf32>
      %1 = arith.addf %0, %0 : f32
      affine.store %1, %alloc[0] : memref<1xf32>
      %2 = affine.load %alloc[0] : memref<1xf32>
      %3 = arith.mulf %2, %2 : f32
      affine.store %3, %alloc_1[%arg0] : memref<4096xf32>
    }
    return
  }
}

