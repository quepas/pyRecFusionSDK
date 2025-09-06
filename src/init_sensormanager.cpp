#include <RecFusion.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

using std::vector;
namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;

void init_sensormanager(nb::module_ &m) {
  nb::class_<SensorManager>(m, "SensorManager")
      .def(nb::init<>())
      .def_prop_ro("device_count", &SensorManager::deviceCount)
      .def("sensor", &SensorManager::sensor, "id"_a, nb::rv_policy::reference)
      // New API
      .def_prop_ro("all",
                   [](SensorManager &manager) {
                     vector<Sensor *> sensors;
                     for (int i = 0; i < manager.deviceCount(); ++i) {
                       sensors.emplace_back(manager.sensor(i));
                     }
                     return sensors;
                   })
      .def(
          "open_all",
          [](SensorManager &manager, int colorWidth, int colorHeight,
             int depthWidth, int depthHeight, double maxFps) {
            vector<Sensor *> sensors;
            for (int i = 0; i < manager.deviceCount(); ++i) {
              auto sensor = manager.sensor(i);
              if (sensor->open(colorWidth, colorHeight, depthWidth, depthHeight,
                               maxFps)) {
                sensors.emplace_back(sensor);
              }
            }
            return sensors;
          },
          "color_width"_a = 640, "color_height"_a = 480, "depth_width"_a = 640,
          "depth_height"_a = 480, "max_fps"_a = 30, nb::rv_policy::reference)
      .def(
          "open_any",
          [](SensorManager &manager, int colorWidth, int colorHeight,
             int depthWidth, int depthHeight, double maxFps) -> Sensor * {
            if (manager.deviceCount() > 0) {
              auto sensor = manager.sensor(0);
              if (sensor->open(colorWidth, colorHeight, depthWidth, depthHeight,
                               maxFps)) {
                return sensor;
              }
            }
            return nullptr;
          },
          "color_width"_a = 640, "color_height"_a = 480, "depth_width"_a = 640,
          "depth_height"_a = 480, "max_fps"_a = 30, nb::rv_policy::reference);
}
