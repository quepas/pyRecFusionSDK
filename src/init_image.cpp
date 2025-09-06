#include <RecFusion.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

void init_image(nb::module_ &m) {
  // RecFusion/Common.h
  // ColorImage
  nb::class_<ColorImage>(m, "_ColorImage")
      .def("__init__",
           [](ColorImage *img,
              const nb::ndarray<unsigned char, nb::shape<-1, -1, 3>> &array) {
             // NOTE: in numpy, row/height is the first dimension (0)
             new (img) ColorImage(array.shape(1), array.shape(0),
                                  array.shape(2), array.data());
           })
      .def_prop_ro("width", &ColorImage::width)
      .def_prop_ro("height", &ColorImage::height)
      .def(
          "to_image",
          [](ColorImage &img_color, const char *filename, int compression = 3) {
            PngIO::writeImage(filename, img_color.data(), img_color.width(),
                              img_color.height(), 3, 0, compression);
          },
          "filename"_a, "compression"_a = 3)
      .def_prop_rw(
          "data",
          [](ColorImage &img) {
            return nb::ndarray<nb::numpy, unsigned char, nb::ndim<3>>(
                img.data(), {(size_t)img.height(), (size_t)img.width(), 3});
          },
          [](ColorImage &img,
             const nb::ndarray<unsigned char, nb::shape<-1, -1, 3>> &array) {
            if (array.shape(0) != img.height()) {
              throw std::invalid_argument(
                  "The size of the first dimension (height) "
                  "must be the same as previously allocated");
            }
            if (array.shape(1) != img.width()) {
              throw std::invalid_argument(
                  "The size of the second dimension (width) "
                  "must be the same as previously allocated");
            }
            int idx = 0;
            for (int row = 0; row < img.height(); ++row) {
              for (int col = 0; col < img.width(); ++col) {
                img.data()[idx++] = array(row, col, 0);
                img.data()[idx++] = array(row, col, 1);
                img.data()[idx++] = array(row, col, 2);
              }
            }
          });

  nb::class_<DepthImage>(m, "_DepthImage")
      .def("__init__",
           [](DepthImage *img, const nb::ndarray<float, nb::ndim<2>> &array) {
             new (img) DepthImage(array.shape(1), array.shape(0), array.data());
           })
      .def_prop_ro("width", &DepthImage::width)
      .def_prop_ro("height", &DepthImage::height)
      .def(
          "to_image",
          [](DepthImage &img_depth, const char *filename, int compression = 3) {
            PngIO::writeImage(filename, img_depth.data(), img_depth.width(),
                              img_depth.height(), 1, compression);
          },
          "filename"_a, "compression"_a = 3)
      .def_prop_rw(
          "data",
          [](DepthImage &img) {
            return nb::ndarray<nb::numpy, float, nb::ndim<2>>(
                img.data(), {(size_t)img.height(), (size_t)img.width()});
          },
          [](DepthImage &img, const nb::ndarray<float, nb::ndim<2>> &array) {
            if (array.shape(0) != img.height()) {
              throw std::invalid_argument(
                  "The size of the first dimension (height)"
                  "must be the same as previously allocated");
            }
            if (array.shape(1) != img.width()) {
              throw std::invalid_argument(
                  "The size of the second dimension (width)"
                  "must be the same as previously allocated");
            }
            int idx = 0;
            for (int row = 0; row < img.height(); ++row) {
              for (int col = 0; col < img.width(); ++col) {
                img.data()[idx++] = array(row, col);
              }
            }
          });
}
