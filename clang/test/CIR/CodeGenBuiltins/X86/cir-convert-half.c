// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -target-feature +avx512fp16 -target-feature +avx512bf16 -fclangir -emit-cir %s -o - | FileCheck %s --check-prefix=CIR
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -target-feature +avx512fp16 -target-feature +avx512bf16 -emit-llvm %s -o - | FileCheck %s --check-prefix=LLVM
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -target-feature +avx512fp16 -target-feature +avx512bf16 -emit-llvm %s -o - | FileCheck %s --check-prefix=OGCG

// REQUIRES: avx512fp16
// REQUIRES: avx512bf16

#include <stdint.h>
#ifndef __bf16
typedef uint16_t __bf16;
#endif

typedef float __m512 __attribute__((__vector_size__(64), __aligned__(64)));
typedef float __m256 __attribute__((__vector_size__(32), __aligned__(32)));
typedef float __m128 __attribute__((__vector_size__(16), __aligned__(16)));
typedef int __mmask16;
typedef int __mmask8;
typedef short __m256i __attribute__((__vector_size__(32), __aligned__(32)));
typedef short __m128i __attribute__((__vector_size__(16), __aligned__(16)));

// CIR-LABEL: test_vcvtph2ps512_mask
// CIR: cir.call_llvm_intrinsic "x86.avx512.mask.vcvtph2ps.512"
// LLVM-LABEL: test_vcvtph2ps512_mask
// OGCG-LABEL: test_vcvtph2ps512_mask
__m512 test_vcvtph2ps512_mask(__m256i a, __m512 src, __mmask16 k) {
  return __builtin_ia32_vcvtph2ps512_mask(a, src, k, 4);
}

// CIR-LABEL: test_vcvtph2ps256_mask
// CIR: cir.call_llvm_intrinsic "x86.avx512.mask.vcvtph2ps.256"
// LLVM-LABEL: test_vcvtph2ps256_mask
// OGCG-LABEL: test_vcvtph2ps256_mask
__m256 test_vcvtph2ps256_mask(__m128i a, __m256 src, __mmask8 k) {
  return __builtin_ia32_vcvtph2ps256_mask(a, src, k);
}

// CIR-LABEL: test_vcvtph2ps_mask
// CIR: cir.call_llvm_intrinsic "x86.avx512.mask.vcvtph2ps.128"
// LLVM-LABEL: test_vcvtph2ps_mask
// OGCG-LABEL: test_vcvtph2ps_mask
__m128 test_vcvtph2ps_mask(__m128i a, __m128 src, __mmask8 k) {
  return __builtin_ia32_vcvtph2ps_mask(a, src, k);
}

// CIR-LABEL: test_cvtneps2bf16_512_mask
// CIR: cir.call_llvm_intrinsic "x86.avx512bf16.cvtneps2bf16.512"
// LLVM-LABEL: test_cvtneps2bf16_512_mask
// OGCG-LABEL: test_cvtneps2bf16_512_mask
__bf16 test_cvtneps2bf16_512_mask(__m512 a, __bf16 w, __mmask16 u) {
  return __builtin_ia32_cvtneps2bf16_512_mask(a, w, u);
}

// CIR-LABEL: test_cvtneps2bf16_256_mask
// CIR: cir.call_llvm_intrinsic "x86.avx512bf16.cvtneps2bf16.256"
// LLVM-LABEL: test_cvtneps2bf16_256_mask
// OGCG-LABEL: test_cvtneps2bf16_256_mask
__bf16 test_cvtneps2bf16_256_mask(__m256 a, __bf16 w, __mmask8 u) {
  return __builtin_ia32_cvtneps2bf16_256_mask(a, w, u);
}

// CIR-LABEL: test_cvtneps2bf16_128_mask
// CIR: cir.call_llvm_intrinsic "x86.avx512bf16.mask.cvtneps2bf16.128"
// LLVM-LABEL: test_cvtneps2bf16_128_mask
// OGCG-LABEL: test_cvtneps2bf16_128_mask
__bf16 test_cvtneps2bf16_128_mask(__m128 a, __bf16 w, __mmask8 u) {
  return __builtin_ia32_cvtneps2bf16_128_mask(a, w, u);
}
