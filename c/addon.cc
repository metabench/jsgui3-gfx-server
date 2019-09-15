#include <node_api.h>
#include <assert.h>
#include <stdio.h>
//#include "ta_macros.h"
#include <sstream>
#include <string>

#include "color_whole.h"
#include "transform.h"
using namespace std;

#define DECLARE_NAPI_METHOD(name, func)                          \
  { name, 0, func, 0, 0, 0, napi_default, 0 }


napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  //napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("add", Add);

  // ReadTypedArray
  //status = napi_define_properties(env, exports, 1, &addDescriptor);
  //assert(status == napi_ok);

  // Set_Pixel_Buffer_Single_Color

  // NAPI_resize_ta_colorspace_24bipp$superpixel$inline$locals$inline

  napi_property_descriptor addDescriptor1 = DECLARE_NAPI_METHOD("resize_ta_colorspace_24bipp$superpixel$inline$locals$inline", NAPI_resize_ta_colorspace_24bipp$superpixel$inline$locals$inline);
  status = napi_define_properties(env, exports, 1, &addDescriptor1);
  assert(status == napi_ok);



  napi_property_descriptor addDescriptor2 = DECLARE_NAPI_METHOD("read_gt3x3_weight_write_24bipp", NAPI_read_gt3x3_weight_write_24bipp);
  status = napi_define_properties(env, exports, 1, &addDescriptor2);
  assert(status == napi_ok);

  // Later, could make use of 'this' reference.
  //  Later still, a whole Pixel_Buffer implementation in C++.



  napi_property_descriptor addDescriptor3 = DECLARE_NAPI_METHOD("color_whole", Set_Pixel_Buffer_Single_Color);
  status = napi_define_properties(env, exports, 1, &addDescriptor3);
  assert(status == napi_ok);



  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
