#ifndef READ_TYPED_ARRAY_H
#define READ_TYPED_ARRAY_H

#include <node_api.h>
#include <assert.h>
#include <stdio.h>
//#include "ta_macros.h"
#include <sstream>
#include <string>
using namespace std;


napi_value ReadTypedArray(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value args[1];

  // But it's not a callback function.
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  //assert(status == napi_ok);
  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);
  //printf(valuetype0);

  // individual checks? case?

  printf("ReadTypedArray\n");
  //printf(valuetype0);

  printf("My enum Value : %d\n", (int)valuetype0);

  // napi_get_typedarray_info

  bool ista;
  napi_is_typedarray(env, args[0], &ista);
  // could be an array buffer?

  //printf(ista);#
  printf("is typed array: ");
  printf("%s", ista ? "true" : "false");
  printf("\n");

  // Worth doing some more mapi object inspection.

  if (ista) {
    napi_typedarray_type tat;
    size_t length;
    void** data;
    napi_value arrbuf;
    size_t boffset;

    printf("pre napi_get_typedarray_info\n");
    napi_get_typedarray_info(env, args[0], &tat, &length, data, &arrbuf, &boffset);
    printf("post napi_get_typedarray_info\n");

    printf("napi_typedarray_type enum Value : %d\n", (int)tat);
    printf("length: %d\n", (int)length);
    printf("offset: %d\n", (int)boffset);

    // Can use the direct data reference now.
    //  Should do that with some fun image processing algorithms.

    // would be nice to iterate through the array.
    //  look up the typed array type.

    // Could use this as an outline for functions that use / modify a typed array.
    //  And modify-in-place functions will return null
    //  And be marked as such.
    
    // Could use some kind(s) of generics to process the arrays?
    //  Nice to keep some things in place
    //  And nice to make reference to existing data structures
    //   Could do a lot of optimised operations without having to recreate result objects.

    //napi_typedarray_type::

    switch(tat) {
      case napi_uint8_array :
          printf("Uint8Array");
          break;
      case napi_uint16_array :
          printf("Uint16Array");
          break;
      case napi_uint32_array :
          printf("Uint32Array");
          break; //optional
      case napi_float32_array :
          printf("Float32Array");
          break; //optional
      case napi_float64_array :
          printf("Float64Array");
          break; //optional
      //case constant-expression  :
      //    statement(s);
      //    break; //optional
      
      // you can have any number of case statements.
      //default : //Optional
      //    statement(s);
    }
    printf("\n");
    // then can look into the specific typed array types.
    //  some functions will require or be able to make use of different typed array types and underlying data.

    // Worth using this for a few image processing algorithms ported from JavaScript.
  }

  //printf("pre napi_get_typedarray_info\n");

  //napi_get_typedarray_info(env, args[0], &tat, &length, NULL, &arrbuf, &boffset);
  //printf("post napi_get_typedarray_info");

  if (valuetype0 == napi_number) {
    printf("Have been given a number\n");
  }
/*
  static Boolean Napi::Boolean::New	(	napi_env 	env,
  bool 	value 
)	
*/
  napi_value res;
  //res = napi_get_value_bool;
  napi_get_boolean(env, true, &res);
  return res;
}

#endif