#include <RecFusion.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/optional.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

void init_calibration(nb::module_ &m) {
  nb::class_<Calibration>(m, "Calibration")
      .def(nb::init<>())
      .def("init", &Calibration::init, "num_sensors"_a)
      .def("set_marker", &Calibration::setMarker, "marked_id"_a,
           "marker_size"_a, "marker_t"_a = nb::none())
      .def("set_image", &Calibration::setImage, "sensor"_a, "img_depth"_a,
           "img_color"_a, "depth_k"_a, "color_k"_a,
           "depth_to_color_t"_a = nb::none())
      .def("calibrate", &Calibration::calibrate)
      .def(
          "get_transformation",
          [](Calibration &calibration, int sensor) -> std::optional<Mat4 *> {
            auto T = new Mat4();
            if (calibration.getTransformation(sensor, *T)) {
              return T;
            } else {
              return {};
            }
          },
          "sensor"_a)
      .def_static("get_marker_pose", &Calibration::getMarkerPose, "marker_id"_a,
                  "marker_size"_a, "img_color"_a, "color_k"_a, "t"_a);
}
