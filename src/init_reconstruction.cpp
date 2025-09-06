#include <RecFusion.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

void init_reconstruction(nb::module_ &m) {

  nb::class_<ReconstructionParams>(m, "ReconstructionParams")
      .def(nb::init<int>(), "sensors"_a = 1)
      .def_prop_ro("sensors", &ReconstructionParams::sensors)
      .def("set_image_size", &ReconstructionParams::setImageSize,
           "color_width"_a, "color_height"_a, "depth_width"_a, "depth_height"_a,
           "sensor"_a = 0)
      // TODO: imageSize
      .def("set_intrinsics", &ReconstructionParams::setIntrinsics, "K"_a,
           "sensor"_a = 0)
      .def("set_color_intrinsics", &ReconstructionParams::setColorIntrinsics,
           "K"_a, "sensor"_a = 0)
      .def("set_depth_to_color_transformation",
           &ReconstructionParams::setDepthToColorTransformation, "T"_a,
           "sensor"_a = 0);
  // .def("intrinsics
  // Reconstruction
  nb::class_<Reconstruction>(m, "Reconstruction")
      .def(nb::init<ReconstructionParams>())
      .def_prop_ro("good", &Reconstruction::good)
      .def(
          "add_frame2",
          [](Reconstruction &reconstruction, int sensor, DepthImage &imgDepth,
             ColorImage &imgColor) {
            return reconstruction.addFrame(sensor, imgDepth, imgColor);
          },
          "sensor"_a, "img_depth"_a, "img_color"_a)
      .def("add_frame", &Reconstruction::addFrame, "sensor"_a, "img_depth"_a,
           "img_color"_a, "tracking_status"_a = 0, "img_scene"_a = 0, "T"_a = 0,
           "sensor_T"_a = 0, "tracked_t"_a = 0,
           "dont_force_first_frame"_a = false)
      .def("get_mesh", [](Reconstruction &reconstruction) {
        auto mesh = new Mesh();
        reconstruction.getMesh(mesh);
        return mesh;
      });
}
