#include "../../../include/monolish_blas.hpp"
#include "../monolish_internal.hpp"

namespace monolish {
namespace internal {
///////////////////////
//   scalar-vector   //
///////////////////////
// y[i] = a[i] + alpha
void vadd(const size_t N, const float *a, const float alpha, float *y,
          bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] + alpha;
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] + alpha;
    }
  }
  logger.func_out();
}

// y[i] = a[i] - alpha
void vsub(const size_t N, const float *a, const float alpha, float *y,
          bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] - alpha;
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] - alpha;
    }
  }
  logger.func_out();
}

// y[i] = a[i] * alpha
void vmul(const size_t N, const float *a, const float alpha, float *y,
          bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] * alpha;
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] * alpha;
    }
  }
  logger.func_out();
}

// y[i] = a[i] / alpha
void vdiv(const size_t N, const float *a, const float alpha, float *y,
          bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] / alpha;
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] / alpha;
    }
  }
  logger.func_out();
}

///////////////////////
//   vector-vector   //
///////////////////////
// y[i] = a[i] + b[i]
void vadd(const size_t N, const float *a, const float *b, float *y,
          bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] + b[i];
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#if MONOLISH_USE_MKL
    vsAdd(N, a, b, y);
#else
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] + b[i];
    }
#endif
  }
  logger.func_out();
}

// y[i] = a[i] - b[i]
void vsub(const size_t N, const float *a, const float *b, float *y,
          bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] - b[i];
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#if MONOLISH_USE_MKL
    vsSub(N, a, b, y);
#else
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] - b[i];
    }
#endif
  }
  logger.func_out();
}

// y[i] = a[i] * b[i]
void vmul(const size_t N, const float *a, const float *b, float *y,
          bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] * b[i];
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#if MONOLISH_USE_MKL
    vsMul(N, a, b, y);
#else
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] * b[i];
    }
#endif
  }
  logger.func_out();
}

// y[i] = a[i] / b[i]
void vdiv(const size_t N, const float *a, const float *b, float *y,
          bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] / b[i];
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      y[i] = a[i] / b[i];
    }
  }
  logger.func_out();
}

///////////////////////
//   vector utils    //
///////////////////////

// y[i] = a[i]
void vcopy(const size_t N, const float *a, float *y, bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
    cublasHandle_t h;
    internal::check_CUDA(cublasCreate(&h));
#pragma omp target data use_device_ptr(a, y)
    { internal::check_CUDA(cublasScopy(h, N, a, 1, y, 1)); }
    cublasDestroy(h);
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
    cblas_scopy(N, a, 1, y, 1);
  }
  logger.func_out();
}

// y[i] == a[i]
bool vequal(const size_t N, const float *a, const float *y, bool gpu_status) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  bool ans = true;

  if (gpu_status == true) {
#if MONOLISH_USE_GPU
#pragma omp target teams distribute parallel for
    for (size_t i = 0; i < N; i++) {
      if (y[i] != a[i]) {
        ans = false;
      }
    }
#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
      if (y[i] != a[i]) {
        ans = false;
      }
    }
  }
  logger.func_out();
  return ans;
}

} // namespace internal
} // namespace monolish
