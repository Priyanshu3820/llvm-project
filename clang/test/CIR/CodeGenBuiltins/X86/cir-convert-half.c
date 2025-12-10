// Test X86-specific convert_half builtins

// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -target-feature +avx512fp16 -target-feature +avx512bf16 -fclangir -emit-cir %s -o %t.cir
// RUN: FileCheck --check-prefix=CIR --input-file=%t.cir %s
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -target-feature +avx512fp16 -target-feature +avx512bf16 -fclangir -emit-llvm %s -o %t-cir.ll
// RUN: FileCheck --check-prefix=LLVM --input-file=%t-cir.ll %s
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -target-feature +avx512fp16 -target-feature +avx512bf16 -emit-llvm %s -o %t.ll
// RUN: FileCheck --check-prefix=OGCG --input-file=%t.ll %s

typedef float __m512 __attribute__((__vector_size__(64), __aligned__(64)));
typedef float __m256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef float __m128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef int __m256i __attribute__((__vector_size__(32), __aligned__(32)));
typedef int __m128i __attribute__((__vector_size__(16), __aligned__(16)));
typedef int __mmask16;
typedef unsigned char __mmask8;
typedef __bf16 __m256bh __attribute__((__vector_size__(32), __aligned__(32)));
typedef __bf16 __m128bh __attribute__((__vector_size__(16), __aligned__(16)));

// Test __builtin_ia32_vcvtph2ps512_mask
__m512 test_vcvtph2ps512_mask(__m256i a, __m512 src, __mmask16 k) {
  return __builtin_ia32_vcvtph2ps512_mask(a, src, k);
}
// CIR-LABEL: cir.func {{.*}}@test_vcvtph2ps512_mask
// CIR: cir.call @llvm.x86.avx512.mask.vcvtph2ps.512
// LLVM-LABEL: define {{.*}} @test_vcvtph2ps512_mask
// LLVM: call <16 x float> @llvm.x86.avx512.mask.vcvtph2ps.512
// OGCG-LABEL: define {{.*}} @test_vcvtph2ps512_mask
// OGCG: call <16 x float> @llvm.x86.avx512.mask.vcvtph2ps.512

// Test __builtin_ia32_vcvtph2ps256_mask
__m256 test_vcvtph2ps256_mask(__m128i a, __m256 src, __mmask8 k) {
  return __builtin_ia32_vcvtph2ps256_mask(a, src, k);
}
// CIR-LABEL: cir.func {{.*}}@test_vcvtph2ps256_mask
// CIR: cir.call @llvm.x86.avx512.mask.vcvtph2ps.256
// LLVM-LABEL: define {{.*}} @test_vcvtph2ps256_mask
// LLVM: call <8 x float> @llvm.x86.avx512.mask.vcvtph2ps.256
// OGCG-LABEL: define {{.*}} @test_vcvtph2ps256_mask
// OGCG: call <8 x float> @llvm.x86.avx512.mask.vcvtph2ps.256

// Test __builtin_ia32_vcvtph2ps_mask
__m128 test_vcvtph2ps_mask(__m128i a, __m128 src, __mmask8 k) {
  return __builtin_ia32_vcvtph2ps_mask(a, src, k);
}
// CIR-LABEL: cir.func {{.*}}@test_vcvtph2ps_mask
// CIR: cir.call @llvm.x86.avx512.mask.vcvtph2ps.128
// LLVM-LABEL: define {{.*}} @test_vcvtph2ps_mask
// LLVM: call <4 x float> @llvm.x86.avx512.mask.vcvtph2ps.128
// OGCG-LABEL: define {{.*}} @test_vcvtph2ps_mask
// OGCG: call <4 x float> @llvm.x86.avx512.mask.vcvtph2ps.128

// Test __builtin_ia32_cvtneps2bf16_512_mask
__m256bh test_cvtneps2bf16_512_mask(__m512 a, __m256bh w, __mmask16 u) {
  return __builtin_ia32_cvtneps2bf16_512_mask(a, w, u);
}
// CIR-LABEL: cir.func {{.*}}@test_cvtneps2bf16_512_mask
// CIR: cir.call @llvm.x86.avx512bf16.cvtneps2bf16.512
// LLVM-LABEL: define {{.*}} @test_cvtneps2bf16_512_mask
// LLVM: call <32 x bfloat> @llvm.x86.avx512bf16.cvtneps2bf16.512
// OGCG-LABEL: define {{.*}} @test_cvtneps2bf16_512_mask
// OGCG: call <32 x bfloat> @llvm.x86.avx512bf16.cvtneps2bf16.512

// Test __builtin_ia32_cvtneps2bf16_256_mask
__m128bh test_cvtneps2bf16_256_mask(__m256 a, __m128bh w, __mmask8 u) {
  return __builtin_ia32_cvtneps2bf16_256_mask(a, w, u);
}
// CIR-LABEL: cir.func {{.*}}@test_cvtneps2bf16_256_mask
// CIR: cir.call @llvm.x86.avx512bf16.cvtneps2bf16.256
// LLVM-LABEL: define {{.*}} @test_cvtneps2bf16_256_mask
// LLVM: call <16 x bfloat> @llvm.x86.avx512bf16.cvtneps2bf16.256
// OGCG-LABEL: define {{.*}} @test_cvtneps2bf16_256_mask
// OGCG: call <16 x bfloat> @llvm.x86.avx512bf16.cvtneps2bf16.256

// Test __builtin_ia32_cvtneps2bf16_128_mask
__m128bh test_cvtneps2bf16_128_mask(__m128 a, __m128bh w, __mmask8 u) {
  return __builtin_ia32_cvtneps2bf16_128_mask(a, w, u);
}
// CIR-LABEL: cir.func {{.*}}@test_cvtneps2bf16_128_mask
// CIR: cir.call @llvm.x86.avx512bf16.mask.cvtneps2bf16.128
// LLVM-LABEL: define {{.*}} @test_cvtneps2bf16_128_mask
// LLVM: call <8 x bfloat> @llvm.x86.avx512bf16.mask.cvtneps2bf16.128
// OGCG-LABEL: define {{.*}} @test_cvtneps2bf16_128_mask
// OGCG: call <8 x bfloat> @llvm.x86.avx512bf16.mask.cvtneps2bf16.128