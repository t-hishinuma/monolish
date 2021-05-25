#!/bin/bash
echo "// This code is generated by gen_vector_blas.sh
#include \"../internal/monolish_internal.hpp\"
#include \"allreduce.hpp\"

namespace monolish::mpi {"

echo "
void Comm::Init() {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  assert(MPI_Init(nullptr, nullptr) == MPI_SUCCESS);
  if (comm == 0) {
    comm = MPI_COMM_WORLD;
  }
#endif
  logger.util_out();
}

void Comm::Init(int argc, char **argv) {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  assert(MPI_Init(&argc, &argv) == MPI_SUCCESS);
  if (comm == 0) {
    comm = MPI_COMM_WORLD;
  }
#endif
  logger.util_out();
}

bool Comm::Initialized() const {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  int flag;
  assert(MPI_Initialized(&flag) == MPI_SUCCESS);
  logger.util_out();
  return (flag == 0) ? true : false;
#endif
  logger.util_out();
  return true;
}

void Comm::Finalize() {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  assert(MPI_Finalize() == MPI_SUCCESS);
#endif
  logger.util_out();
}

int Comm::get_rank() const{
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  logger.util_out();
  return rank;
#endif
  logger.util_out();
  return 0;
}

int Comm::get_size() const{
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
#if defined MONOLISH_USE_MPI
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  logger.util_out();
  return size;
#endif
  logger.util_out();
  return 1;
}

void Comm::set_comm(MPI_Comm external_comm) {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);
  comm = external_comm; 
  logger.util_out();
}

"

## allreduce
for type in double float int size_t; do
    echo "$type Comm::Allreduce($type val) const{ return Allreduce_core(val, MPI_SUM, get_comm() );}"
done

echo ""

## allreduce sum
for type in double float int size_t; do
  echo "$type Comm::Allreduce_sum($type val) const{ return Allreduce_core(val, MPI_SUM, get_comm() );}"
done

echo ""

## allreduce prod
for type in double float int size_t; do
  echo "$type Comm::Allreduce_prod($type val) const{ return Allreduce_core(val, MPI_PROD, get_comm() );}"
done

echo ""

## allreduce max
for type in double float int size_t; do
  echo "$type Comm::Allreduce_max($type val) const{ return Allreduce_core(val, MPI_MAX, get_comm() );}"
done

echo ""

## allreduce min
for type in double float int size_t; do
  echo "$type Comm::Allreduce_min($type val) const{ return Allreduce_core(val, MPI_MIN, get_comm() );}"
done

echo ""

echo "
}" 

