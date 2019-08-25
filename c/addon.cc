#include <node_api.h>
#include <assert.h>
#include <stdio.h>
//#include "ta_macros.h"
#include <sstream>
#include <string>
#include "color_whole.h"
#include "z_read_typed_array.h"
using namespace std;

/*
  Will later use accelerated thresholding and set_pixel.
  Maybe C++ overhead will make set_pixel too slow?
  Maybe not.

*/

// Maybe back to test addons
//  To do with reading parameters
//  Displaying info about the parameters.

// Would be interesting to have an addon that returns a single function.
//  Maybe less important?

/*
template <typename T>
std::string toString (T arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str ();
}
*/

// read the input value / values.
//  wrap a polymorphic function.
//  separate out napi code from the computational functions.
//   hungarian notation compilation.
//   Translating JavaScript Polymorphism to C++ Polymorphism.

// The internal C / C++ function to carry out the task.
//  Consider Hungarian notation JS subset => C/C++ compilation and creation of bindings automatically.

// General Cased Poly wrapper?
//  Decodes it / gets references for the various parameters given to it?
//  Consider patterns in C++ that make use of polymorphism and / or generics.

// Polymorphism for recieving numeric information
/*
void Read_Bipp_W(napi_env *env, napi_value args[], int32_t& bits_per_pixel, int32_t& width) {
  // recieves (pointer to?) unsized array.
  //  a napi_value is itself an 'opaque pointer'.
  printf("Read_Bipp_W\n");
  napi_status status;

  // bpp already a reference here?

  // Worth looking at the value type?
  //  will be js number

  // get it to a local temp double

  double d_bpp, d_w;

  printf("pre napi_get_value_double\n");

  status = napi_get_value_double(*env, args[1], &d_bpp);
  printf("post napi_get_value_double\n");
  printf("d_bpp: %d\n", (int)d_bpp);
  assert(status == napi_ok);
  status = napi_get_value_double(*env, args[2], &d_w);
  assert(status == napi_ok);

  printf("d_bpp: %d\n", d_bpp);
  printf("d_w: %d\n", d_w);

}
*/

// and will return by reference the length of the array.
/*

uint8_t* Read_TA(napi_env* env, napi_value *args[], size_t* length) {
  // its arg 0.
  // typed array checks, referencing...

  bool arg_0_is_ta;
  napi_is_typedarray(*env, *args[0], &arg_0_is_ta);
  if (arg_0_is_ta) {
    printf("arg 0 is a Typed Array.\n");

    // read the typed array.
    //  reference an array from it's data.

    napi_typedarray_type tat;
    //size_t length;
    void** data;
    napi_value arrbuf;
    size_t boffset;

    printf("pre (Read_TA) napi_get_typedarray_info\n");
    napi_get_typedarray_info(*env, *args[0], &tat, length, data, &arrbuf, &boffset);
    printf("post (Read_TA) napi_get_typedarray_info\n");

    printf("post (color arg) napi_get_typedarray_info\n");
    printf("napi_typedarray_type enum Value : %d\n", (int)tat);
    printf("length: %d\n", (int)length);
    printf("offset: %d\n", (int)boffset);

    // needs to be a uint8 typed array of some sort.

  } else {
    printf("Will error - arg 0 must be a Typed Array.\n");
    //  error prevents need for return statement? C++ error territory here, keeping this part of the code not using N-API or referring to its structures in any way.
    throw "arg err";

    // return empty array?
  }
  // return some sort of array by default?

}
*/


//napi_value set_pixel_buffer_single_color
// prefix it with WNAPI from Wrap N-API?
//  Would make sense.

// Of course need to give it the image ta.
//  Though it could get a whole load of params from referring to this.
//  

// Later will have better inner processing functions in other files.

//void Greyscale_Set_Color()

/*
  N-API object to standard C object converter functions.
*/

// Will be nice to put in / reorganise into a single C++ file.

// color_whole
// whole_color
//  rect_color


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



/*


napi_value Add(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 2;
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 2) {
    napi_throw_type_error(env, nullptr, "Wrong number of arguments");
    return nullptr;
  }

  printf("hello\n");

  

  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);

  //printf(status);

  napi_valuetype valuetype1;
  status = napi_typeof(env, args[1], &valuetype1);
  assert(status == napi_ok);

  if (valuetype0 != napi_number || valuetype1 != napi_number) {
    napi_throw_type_error(env, nullptr, "Wrong arguments");
    return nullptr;
  }

  double value0;
  status = napi_get_value_double(env, args[0], &value0);
  assert(status == napi_ok);

  double value1;
  status = napi_get_value_double(env, args[1], &value1);
  assert(status == napi_ok);

  napi_value sum;
  status = napi_create_double(env, value0 + value1, &sum);
  assert(status == napi_ok);

  // Could return a new typedarray instead.

  //  And try to put the values into that typed array.
  //  Do so other things in between.

  int * foo;
  foo = new int [5];
  //printf(foo);

  // Can put this into a node typed array.
  //  Or create the typed array around the pointer.
  //   And don't deallocate the memory at this stage.
  
  // #define NAPI_GET_UINT8_ARRAY(typedarray, arr, byte_len, arr_len)

  / *
    create any type of napi typedarray from a C pointer
    NAPI_CREATE_TYPEDARRAY(c_type, ?_t* arr, size_t byte_len, size_t arr_len, napi_typedarray_type typedarray_type, napi_value* typedarray);
    [in] c_type: type of the c pointer
    [in] arr: C arr pointer
    [in] byte_len: the length of the C array in bytes
    [in] arr_len: the number of items of the C array
    [in] typedarray_type: napi_typedarray_type
    [out] typedarray: napi_value for the new typed array
    NOTE: assuming that byte_offset is 0
  * /

  //printf("the int size: " + toString(sizeof(int)).c_str());
  //printf(sizeof(int));
  printf("int size is: ");
  printf("%zu", sizeof(int));
  printf("\n");

  //NAPI_CREATE_UINT8_ARRAY(int, foo, sizeof(int) * 5, 5)
  napi_value res;

  for ( int i = 0; i < 5; i++ ) {
    //printf("(p + " << i << ") : ");
    //printf(to_chars(foo[i]));
    //printf(toString(i).c_str());
    printf("%zu", i);
    foo[i] = i;

    //cout << *(p + i) << endl;
  }
  printf("\n");
  NAPI_CREATE_INT32_ARRAY(foo, sizeof(int) * 5, 5, &res);

  //delete[] foo;
  return res;
}
*/

#define DECLARE_NAPI_METHOD(name, func)                          \
  { name, 0, func, 0, 0, 0, napi_default, 0 }


napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  //napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("add", Add);

  // ReadTypedArray
  //status = napi_define_properties(env, exports, 1, &addDescriptor);
  //assert(status == napi_ok);

  // Set_Pixel_Buffer_Single_Color



  napi_property_descriptor addDescriptor2 = DECLARE_NAPI_METHOD("read_typed_array", ReadTypedArray);
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
