#include <RecFusion.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

void init_matrix(nb::module_ &m) {
  // Mat3
  nb::class_<Mat3>(m, "_Mat3")
      .def("__init__",
           [](Mat3 *t, const nb::ndarray<double, nb::shape<3, 3>> &array) {
             new (t) Mat3(array.data());
           })
      .def_prop_rw(
          "data",
          [](Mat3 &matrix) {
            return nb::ndarray<nb::numpy, double, nb::shape<3, 3>>(
                matrix.data());
          },
          [](Mat3 &matrix, const nb::ndarray<double, nb::shape<3, 3>> &array) {
            for (int r = 0; r < 3; ++r) {
              for (int c = 0; c < 3; ++c) {
                matrix(r, c) = array(r, c);
              }
            }
          })
      .def("__matmul__", [](Mat3 &self, Mat3 &other) { return self * other; });
  // Mat4
  nb::class_<Mat4>(m, "_Mat4")
      .def("__init__",
           [](Mat4 *t, const nb::ndarray<double, nb::shape<4, 4>> &array) {
             new (t) Mat4(array.data());
           })
      .def_prop_rw(
          "data",
          [](Mat4 &matrix) {
            return nb::ndarray<nb::numpy, double, nb::shape<4, 4>>(
                matrix.data());
          },
          [](Mat4 &matrix, const nb::ndarray<double, nb::shape<4, 4>> &array) {
            for (int r = 0; r < 4; ++r) {
              for (int c = 0; c < 4; ++c) {
                matrix(r, c) = array(r, c);
              }
            }
          })
      .def("__matmul__", [](Mat4 &self, Mat4 &other) { return self * other; })
      .def("inverse", &Mat4::inverse)
      .def_static("from_euler", &Mat4::fromEuler, "rx"_a, "ry"_a, "rz"_a);
}
