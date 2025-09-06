#include <RecFusion.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <string>

namespace nb = nanobind;
using namespace nb::literals;
using namespace RecFusion;
using std::to_string;

void init_recfusionsdk(nb::module_ &m) {
  m.def("init", &RecFusionSDK::init, "log_filename"_a = "",
        "Initialize the SDK");
  m.def("deinit", &RecFusionSDK::deinit, "Deinitialize the SDK");
  m.def("activate", &RecFusionSDK::activate, "key"_a, "code"_a = "");
  m.def("valid_license", &RecFusionSDK::validLicense);
  m.def("token", &RecFusionSDK::token);
  m.def("major_version", &RecFusionSDK::majorVersion);
  m.def("minor_version", &RecFusionSDK::minorVersion);
  m.def("build_version", &RecFusionSDK::buildVersion);
  // New API
  m.def("version", []() {
    return to_string(RecFusionSDK::majorVersion()) + "." +
           to_string(RecFusionSDK::minorVersion()) + "." +
           to_string(RecFusionSDK::buildVersion());
  });
}
