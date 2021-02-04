#include "../../monolish_internal.hpp"
#include "../monolish_lapack_double.hpp"
#ifndef MONOLISH_USE_MKL
#include "../lapack.h"
#endif

#include <vector>

namespace monolish {

// double
int internal::lapack::getrf(matrix::Dense<double> &A, std::vector<int> &ipiv) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  if(ipiv.size() != std::min(A.get_row(), A.get_col())){
    logger.func_out();
    std::runtime_error("lapack::getrf, ipiv size error");
  }

  int info = 0;
  const int M = (int)A.get_row();
  const int N = (int)A.get_col();
  double *Ad = A.val.data();
  int *ipivd = ipiv.data();
  int ipivl = ipiv.size();

  if (A.get_device_mem_stat()) {
#if MONOLISH_USE_GPU
    cudaDeviceSynchronize();
    cusolverDnHandle_t h;
    internal::check_CUDA(cusolverDnCreate(&h));
    int lwork = -1;

#pragma omp target data use_device_ptr(Ad)
    {
      internal::check_CUDA(cusolverDnDgetrf_bufferSize(h, M, N, Ad, M, &lwork));
    }

#pragma omp target enter data map(to : ipivd [0:ipivl])
    monolish::vector<double> work(lwork);
    work.send();
    double *workd = work.data();

#pragma omp target data use_device_ptr(Ad, ipivd, workd)
    {
      internal::check_CUDA(
          cusolverDnDgetrf(h, M, N, Ad, M, workd, ipivd, &info));
    }

    // free
    work.recv();
    cusolverDnDestroy(h);

#else
    throw std::runtime_error(
        "error USE_GPU is false, but get_device_mem_stat() == true");
#endif
  } else {
    dgetrf_(&M, &N, Ad, &M, ipivd, &info);
  }

  logger.func_out();
  return info;
}

} // namespace monolish
