#include "../../../include/monolish_vml.hpp"
#include "../../internal/monolish_internal.hpp"

namespace monolish {

namespace {
template <typename F1, typename F2, typename F3>
void vvdiv_core(const F1 &a, const F2 &b, F3 &y) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  // err
  assert(util::is_same_size(a, b, y));
  assert(util::is_same_device_mem_stat(a, b, y));

  internal::vdiv(y.size(), a.data(), b.data(), y.data(),
                 y.get_device_mem_stat());

  logger.func_out();
}

} // namespace

namespace vml {
void div(const vector<double> &a, const vector<double> &b, vector<double> &y) {
  vvdiv_core(a, b, y);
}

void div(const vector<float> &a, const vector<float> &b, vector<float> &y) {
  vvdiv_core(a, b, y);
}

} // namespace vml

} // namespace monolish
