
#include <RecFusion.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

void init_rfsplayback(nb::module_ &m) {
  nb::class_<RFSPlayback>(m, "RFSPlayback")
      .def(nb::init<>())
      .def("open", &RFSPlayback::open, "filename"_a)
      .def("close", &RFSPlayback::close)
      .def_prop_ro("frame_count", &RFSPlayback::frameCount)
      .def("read_image", &RFSPlayback::readImage, "frame"_a, "img_depth"_a,
           "img_color"_a)
      .def_prop_ro("color_width", &RFSPlayback::colorWidth)
      .def_prop_ro("color_height", &RFSPlayback::colorHeight)
      .def_prop_ro("depth_width", &RFSPlayback::depthWidth)
      .def_prop_ro("depth_height", &RFSPlayback::depthHeight)
      .def_prop_ro("intrinsics", &RFSPlayback::intrinsics)
      .def_prop_ro("color_intrinsics", &RFSPlayback::colorIntrinsics)
      .def_prop_ro("depth_to_color_t", &RFSPlayback::depthToColorT)
      // New API
      // Alias to intrinsics() method; there is already a specific name like
      // this in Sensor::depthInstrinsics
      .def_prop_ro("depth_intrinsics", &RFSPlayback::intrinsics)
      //
      .def_prop_ro("depth_to_color_transformation",
                   &RFSPlayback::depthToColorT);
}
