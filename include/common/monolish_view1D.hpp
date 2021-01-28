/**
 * @autor RICOS Co. Ltd.
 * @file monolish_view1D.h
 * @brief declare view 1D class
 * @date 2019
 **/

#pragma once
#include "./monolish_logger.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <omp.h>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include <memory>

#if defined USE_MPI
#include <mpi.h>
#endif

namespace monolish {
  template <typename Float> class vector;

  namespace matrix {
    template <typename Float> class Dense;
    template <typename Float> class CRS;
    template <typename Float> class LinearOperator;
  }

/**
 * @brief 1D view class
 * @note
 * - Multi-threading: true
 * - GPU acceleration: true
 */
template <typename TYPE>
  class view1D {
    private:

      TYPE& target;
      size_t first;
      size_t last;
      size_t size;
      mutable bool gpu_status = false;

    public:
      view1D(TYPE& x, size_t start, size_t end):target(x){
        first = start;
        last = end;
        size = last - first; 
      }

      void resize(size_t ){
        first = start;
        last = end;
        size = last - first; 
        
      }
      size_t get_size(){ return size;}

      size_t get_device_mem_stat(){ return target.get_device_mem_stat();}

      auto* data();

      void print_all();

      auto& operator[](size_t i);
  };

} // namespace monolish
