#include <RecFusion.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

using std::make_tuple;
namespace nb = nanobind;
using namespace RecFusion;
using namespace nb::literals;

NB_MODULE(_pyRecFusionSDK_impl, m) {
  m.def("init", &RecFusionSDK::init, "log_filename"_a = "");
  m.def("deinit", &RecFusionSDK::deinit);
  m.def("activate", &RecFusionSDK::activate, "key"_a, "code"_a = "");
  m.def("token", &RecFusionSDK::token);
  m.def("major_version", &RecFusionSDK::majorVersion);
  m.def("minor_version", &RecFusionSDK::minorVersion);
  m.def("build_version", &RecFusionSDK::buildVersion);

  // RecFusion/Sensor.h
  // Sensor
  // TODO: no default constructor!
  nb::class_<Sensor>(m, "Sensor")
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
      .def_prop_ro("supports_auto_exposure", &Sensor::supportsAutoExposure);

  // .def(nb::init<>());
  // .def("device_name", &Sensor::deviceName, "name"_a, "len"_a);
  // .def("uuid",
  // SensorManager
  nb::class_<SensorManager>(m, "SensorManager")
      .def(nb::init<>())
      .def("device_count", &SensorManager::deviceCount)
      .def("sensor", &SensorManager::sensor, "id"_a);

  // ReconstructionParams
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
      .def_prop_ro("good", &Reconstruction::good);
  // RecFusion/Common.h
  // ColorImage
  nb::class_<ColorImage>(m, "ColorImage")
      .def(nb::init<int, int, int, unsigned char *>())
      .def_prop_ro("width", &ColorImage::width)
      .def_prop_ro("height", &ColorImage::height)
      .def_prop_ro("channels", &ColorImage::channels);
  // Vec3
  // Mat3
  nb::class_<Mat3>(m, "Mat3")
      .def(nb::init<double*>());
  // Mat4
  nb::class_<Mat4>(m, "Mat4")
      .def(nb::init<double*>());
  // Mesh
  nb::class_<Mesh>(m, "Mesh")
      .def(nb::init<>())
      // static Mesh* create()
      // TODO: this doesn't work :(
      // .def_static("create", "vertex_count"_a, "vertices"_a,
      // "triangle_count"_a,
      //             "triangle_indices"_a, "colors"_a = 0, "normals"_a = 0,
      //             "volume_resolution"_a = 512, &Mesh::create)
      .def("vertex_count", &Mesh::vertexCount)
      .def("triangle_count", &Mesh::triangleCount)
      .def(
          "vertex",
          [](Mesh &mesh, int idx) {
            auto coord = mesh.vertex(idx);
            return make_tuple(coord.x, coord.y, coord.z);
          },
          "idx"_a)
      .def(
          "set_vertex",
          [](Mesh &mesh, int idx, double x, double y, double z) {
            mesh.setVertex(idx, {x, y, z});
          },
          "idx"_a, "x"_a, "y"_a, "z"_a)
      .def(
          "normal",
          [](Mesh &mesh, int idx) {
            auto normal = mesh.normal(idx);
            return make_tuple(normal.x, normal.y, normal.z);
          },
          "idx"_a)
      .def(
          "set_normal",
          [](Mesh &mesh, int idx, double nx, double ny, double nz) {
            mesh.setNormal(idx, {nx, ny, nz});
          },
          "idx"_a, "nx"_a, "ny"_a, "nz"_a)
      .def(
          "color",
          [](Mesh &mesh, int idx) {
            auto color = mesh.color(idx);
            return make_tuple(color.r, color.g, color.b);
          },
          "idx"_a)
      .def(
          "set_color",
          [](Mesh &mesh, int idx, double r, double g, double b) {
            mesh.setNormal(idx, {r, g, b});
          },
          "idx"_a, "r"_a, "g"_a, "b"_a);
  // .def(
  //     "triangle",
  //     [](Mesh &mesh, int idx) {
  //       auto triangle = mesh.triangle(idx);
  //       return make_tuple(triangle.i1, triangle.i2, triangle.i3);
  //     },
  //     "idx"_a);
  // .def("add_triangle");
}
