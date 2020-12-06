#include <iostream>
#include <typeinfo>
#include <omp.h>

#ifdef MONOLISH_USE_MKL
#include <mkl.h>
#else
#include <cblas.h>
#endif

#ifdef MONOLISH_USE_GPU
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include "cusparse.h"
#endif

#ifdef MONOLISH_USE_AVX
#include <immintrin.h>
#define SIMD_FUNC(NAME) _mm256_##NAME
using Sreg = __m256;
using Dreg = __m256d;
#endif

namespace monolish {
  namespace internal {

#ifdef MONOLISH_USE_GPU
    auto checkError = [](auto result, auto func, auto file, auto line) {
      if (result) {
        fprintf(stderr, "CUDA error at %s:%d code=%d(%s) \"%s\" \n", file, line,
            static_cast<unsigned int>(result),
            cudaGetErrorName((cudaError_t)result), func);
        // cudaDeviceReset();
        exit(EXIT_FAILURE);
      }
    };
#define check_CUDA(val) checkError((val), #val, __FILE__, __LINE__)
#endif

    void vadd(const size_t N, const double* a, const double* b, double* y, bool gpu_status);
    void vsub(const size_t N, const double* a, const double* b, double* y, bool gpu_status);
    void vmul(const size_t N, const double* a, const double* b, double* y, bool gpu_status);
    void vdiv(const size_t N, const double* a, const double* b, double* y, bool gpu_status);

    void vadd(const size_t N, const float* a, const float* b, float* y, bool gpu_status);
    void vsub(const size_t N, const float* a, const float* b, float* y, bool gpu_status);
    void vmul(const size_t N, const float* a, const float* b, float* y, bool gpu_status);
    void vdiv(const size_t N, const float* a, const float* b, float* y, bool gpu_status);
  }
} // namespace monolish
