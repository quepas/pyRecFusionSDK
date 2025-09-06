#include <RecFusion.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>
#include <nanobind/trampoline.h>

using std::string, std::make_tuple, std::vector;
namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

struct PySensorListener : public SensorListener {
  NB_TRAMPOLINE(SensorListener, 1);

  void onSensorData(const ColorImage &colorImg,
                    const DepthImage &depthImg) override {
    NB_OVERRIDE_PURE(onSensorData, colorImg, depthImg);
  }
};

void init_sensor(nb::module_ &m) {
  // RecFusion/Sensor.h
  // Sensor
  nb::class_<Sensor>(m, "Sensor")
      .def_prop_ro("device_name",
                   [](Sensor &sensor) {
                     char buffer[256];
                     auto result = sensor.deviceName(buffer, 256);
                     if (result == -2)
                       return string("buffer_too_small");
                     if (result == -1)
                       return string("sensor_manager_non_existing");
                     return string(buffer, result);
                   })
      .def_prop_ro("uuid",
                   [](Sensor &sensor) {
                     char buffer[256];
                     auto result = sensor.uuid(buffer, 256);
                     if (result == -2)
                       return string("buffer_too_small");
                     if (result == -1)
                       return string("sensor_manager_non_existing");
                     return string(buffer, result);
                   })
      .def("depth_format_count", &Sensor::depthFormatCount)
      .def("color_format_count", &Sensor::colorFormatCount)
      .def("depth_format", &Sensor::depthFormat, "id"_a)
      .def("color_format", &Sensor::colorFormat, "id"_a)
      .def("open", &Sensor::open, "color_width"_a = 640, "color_height"_a = 480,
           "depth_width"_a = 640, "depth_height"_a = 480, "max_fps"_a = 30)
      .def("close", &Sensor::close)
      .def("start", &Sensor::start)
      .def("stop", &Sensor::stop)
      .def_prop_ro("is_open", &Sensor::isOpen)
      .def_prop_ro("depth_width", &Sensor::depthWidth)
      .def_prop_ro("depth_height", &Sensor::depthHeight)
      .def_prop_ro("color_width", &Sensor::colorWidth)
      .def_prop_ro("color_height", &Sensor::colorHeight)
      .def_prop_ro("depth_intrinsics", &Sensor::depthIntrinsics)
      .def_prop_ro("color_intrinsics", &Sensor::colorIntrinsics)
      .def_prop_ro("depth_to_color_transformation",
                   &Sensor::depthToColorTransformation)
      .def_prop_ro("supports_color", &Sensor::supportsColor)
      .def("set_laser_state", &Sensor::setLaserState)
      .def_prop_ro("supports_auto_white_balance",
                   &Sensor::supportsAutoWhiteBalance)
      .def_prop_ro("supports_auto_exposure", &Sensor::supportsAutoExposure)
      .def(
          "add_listener",
          [](Sensor &sensor, SensorListener &listener) {
            sensor.addListener(&listener);
          },
          "listener"_a)
      .def("remove_listener", &Sensor::removeListener, "listener"_a)
      .def("read_image", &Sensor::readImage, "img_depth"_a, "img_color"_a,
           "timeout"_a = 2000)
      // New API
      .def_prop_ro("image_size",
                   [](Sensor &sensor) {
                     return make_tuple(
                         sensor.colorWidth(), sensor.colorHeight(),
                         sensor.depthWidth(), sensor.depthHeight());
                   })
      .def_prop_ro("depth_formats",
                   [](Sensor &sensor) {
                     vector<Sensor::Format> formats;
                     for (int i = 0; i < sensor.depthFormatCount(); ++i) {
                       formats.emplace_back(sensor.depthFormat(i));
                     }
                     return formats;
                   })
      .def_prop_ro("color_formats", [](Sensor &sensor) {
        vector<Sensor::Format> formats;
        for (int i = 0; i < sensor.colorFormatCount(); ++i) {
          formats.emplace_back(sensor.colorFormat(i));
        }
        return formats;
      });

  nb::class_<Sensor::Format>(m, "_SensorFormat")
      // .def(nb::init<>())
      .def_ro("width", &Sensor::Format::width)
      .def_ro("height", &Sensor::Format::height)
      .def_ro("fps", &Sensor::Format::fps);
  // New API
  // .def("__repr__", [](Sensor::Format &format) {
  //   return to_string(format.width) + "x" + to_string(format.height) + "@"
  //   +
  //          to_string(format.fps) + "fps";
  // });

  nb::class_<SensorListener, PySensorListener>(m, "SensorListener")
      .def(nb::init<>())
      .def("on_sensor_data", &SensorListener::onSensorData);
}
