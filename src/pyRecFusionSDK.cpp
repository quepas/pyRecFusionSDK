#include <nanobind/nanobind.h>

int add(int a, int b) { return a + b; }

NB_MODULE(_pyRecFusionSDK_impl, m) {
  m.def("hello", []() { return "Hello world!"; });
  m.def("add", &add);
}
