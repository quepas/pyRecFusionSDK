#include <RecFusion.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

void init_vector(nb::module_ &m) {
  // Vec3
  nb::class_<Vec3>(m, "_Vec3")
      .def(nb::init<double, double, double>(), "x"_a, "y"_a, "z"_a)
      .def_prop_rw(
          "x", [](Vec3 &vec) { return vec[0]; },
          [](Vec3 &vec, double value) { vec[0] = value; })
      .def_prop_rw(
          "y", [](Vec3 &vec) { return vec[1]; },
          [](Vec3 &vec, double value) { vec[1] = value; })
      .def_prop_rw(
          "z", [](Vec3 &vec) { return vec[2]; },
          [](Vec3 &vec, double value) { vec[2] = value; });
  // Vec3i
  nb::class_<Vec3i>(m, "_Vec3i")
      .def(nb::init<int, int, int>(), "x"_a, "y"_a, "z"_a)
      .def_prop_rw(
          "x", [](Vec3i &vec) { return vec[0]; },
          [](Vec3i &vec, int value) { vec[0] = value; })
      .def_prop_rw(
          "y", [](Vec3i &vec) { return vec[1]; },
          [](Vec3i &vec, int value) { vec[1] = value; })
      .def_prop_rw(
          "z", [](Vec3i &vec) { return vec[2]; },
          [](Vec3i &vec, int value) { vec[2] = value; });
}
