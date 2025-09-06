#include <RecFusion.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

void init_rfsrecorder(nb::module_ &m) {
  nb::class_<RFSRecorder>(m, "RFSRecorder")
      .def(nb::init<const char *>())
      .def("init", &RFSRecorder::init, "color_width"_a, "color_height"_a,
           "depth_width"_a, "depth_height"_a, "depth_k"_a,
           "color_k"_a = nb::none(), "depth_to_color_t"_a = nb::none())
      .def("cleanup", &RFSRecorder::cleanup)
      .def("start", &RFSRecorder::start)
      .def("stop", &RFSRecorder::stop)
      .def("add_frame", &RFSRecorder::addFrame, "img_depth"_a, "img_color"_a)
      // New API
      .def("init_from_sensor", [](RFSRecorder &recorder, Sensor &sensor) {
        recorder.init(sensor.colorWidth(), sensor.colorHeight(),
                      sensor.depthWidth(), sensor.depthHeight(),
                      sensor.depthIntrinsics());
      });
}
