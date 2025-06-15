#include <RecFusion.h>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace RecFusion;

NB_MODULE(_pyRecFusionSDK_impl, m) {
  m.def("major_version", &RecFusionSDK::majorVersion);
  m.def("minor_version", &RecFusionSDK::minorVersion);
  m.def("build_version", &RecFusionSDK::buildVersion);
}
