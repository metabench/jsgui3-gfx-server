#ifndef COLOR_WHOLE_H
#define COLOR_WHOLE_H

#include <node_api.h>
#include <assert.h>
#include <stdio.h>
//#include "ta_macros.h"
#include <sstream>
#include <string>
using namespace std;




// Would be best to have a non-napi function
//  Void, I assume, does the internal work.


void color_whole(uint8_t* input_ui8s, uint num_pixels, uint8_t r, uint8_t g, uint8_t b) {
  for(uint32_t i = 0; i < num_pixels; i++) {
    //ta_data[i] = grey;
    input_ui8s[(i) * 3] = r;
    input_ui8s[(i) * 3 + 1] = g;
    input_ui8s[(i) * 3 + 2] = b;
  }
}



napi_value Set_Pixel_Buffer_Single_Color(napi_env env, napi_callback_info info) {
  // Interpret the parameters.
  //  Could be given different numbers of parameters.
  //   eg r, g, b, a as 4 numbers.
  //    a greyscale value
  //    a single rgb / rgba typed array
  size_t c_args = 7;
  // We can still get the args info.
  //  Not so sure how to get the args array / structure when we dont know its length.  

  // May as well use buffer size 4 and prepare for undefined items.
  const int max_num_args = 7;
  napi_value args[7];
  napi_status status;
  status = napi_get_cb_info(env, info, &c_args, args, nullptr, nullptr);
  assert(status == napi_ok);

  // Likely need the bit depth in the function call as well.
  //  Possibly read an options object?
  //  Probably faster to directly pass needed variables.

  // bits_per_pixel
  // width
  //  color as 1 or more params.

  // Could find / make and use a C++ color class.
  //  Maybe much more OO would work well in C++ regarding optimization. Worth a try.

  // Function to read bipp and w args
  //  and then do the rest.

  uint32_t bits_per_pixel, width;
  uint8_t grey, red, green, blue, alpha;

  // Also do this at 32 bpp with an alpha channel.

  // the image typed array.
  //  lets take that as a param too.
  //  1st param!

  // Can we declare the image array here, of unknown length?
  //  Then we get the array, need to set the pointer?
  //  Probably best to have a function that returns the array as c++ uint8 uint8_t

  printf("Arg count: %d\n", (int)c_args);
  

  if (c_args == 1) {
    // throw a JS error? unexpected args count
    printf("Will error - requires 4, 6 or 7 args.\n");
  }
  if (c_args == 2) {
    printf("Will error - requires 4, 6 or 7 args.\n");
  }
  if (c_args == 3) {
    printf("Will error - requires 4, 6 or 7 args.\n");
    /*
    status = napi_get_value_int32(env, args[0], &bits_per_pixel);
    assert(status == napi_ok);
    status = napi_get_value_int32(env, args[1], &width);
    assert(status == napi_ok);
    */
  }
  if (c_args == 4) {
    // Invalid arg count?
    //printf("Will error - requires 3, 5 or 6 args.\n");
    //Read_Bipp_W(&env, args, &bits_per_pixel, &width);
    // read / assign the image typed array as the first parameter.
    //  separate function?
    // typed array is first param?
    // Get the type of that param.
    //  Is it a double?
    // ta, bpp, width, color
    // see what the arg type is.
    double d_read;
    napi_valuetype t_arg;
    // see if its a typed array first?
    status = napi_typeof(env, args[0], &t_arg);
    //printf("t_arg 0: %d\n", t_arg);
    //printf("status: %d\n", status);
    assert(status == napi_ok);

    // check if arg 0 is a typed array... it should be.
    napi_typedarray_type tat;
    size_t ta_length;
    void* ta_data;
    napi_value arrbuf;
    size_t boffset;

    //printf("pre napi_get_typedarray_info\n");
    napi_get_typedarray_info(env, args[0], &tat, &ta_length, &ta_data, &arrbuf, &boffset);
    //printf("post napi_get_typedarray_info\n");

    //printf("napi_typedarray_type enum Value : %d\n", (int)tat);
    //printf("length: %d\n", (int)ta_length);
    //printf("offset: %d\n", (int)boffset);
    uint8_t* input_ui8s = ((uint8_t*)(ta_data) + boffset);
    // get the ta array.
    
    status = napi_typeof(env, args[1], &t_arg);
    assert(status == napi_ok);
    //printf("t_arg 1: %d\n", t_arg);
    // Not sure why its not getting the value double here....
    //napi_get_value_uint32
    status = napi_get_value_uint32(env, args[1], &bits_per_pixel);
    //status = napi_get_value_double(env, args[1], &d_read);
    //printf("post napi_get_value_uint32\n");
    // need to convert to int to print it properly?!
    assert(status == napi_ok);
    //printf("bits_per_pixel: %d\n", (int)bits_per_pixel);

    // the width of the image too....
    status = napi_typeof(env, args[2], &t_arg);
    assert(status == napi_ok);
    //printf("t_arg 2: %d\n", t_arg);

    status = napi_get_value_uint32(env, args[2], &width);
    assert(status == napi_ok);
    //printf("width: %d\n", (int)width);

    //Read_Img_TA(&env, args);
    //printf("pre Read_Bipp_W");
    //Read_Bipp_W(&env, args, bits_per_pixel, width);
    //printf("post Read_Bipp_W");
    // Read the color as one value...?
    // See if we were given an array or typed array for the color.
    //  detect type of arg 2.

    bool p0_is_ta;
    napi_is_typedarray(env, args[2], &p0_is_ta);

    // Check the typed array type...? Must be uint8 or clamped uint8

    bool color_is_ta;
    status = napi_is_typedarray(env, args[3], &color_is_ta);
    //printf("color_is_ta: %d\n", color_is_ta);

    if (color_is_ta) {
      printf("Color arg is a typed array.\n");

      napi_typedarray_type tat;
      size_t length;
      uint8_t* data;
      napi_value arrbuf;
      size_t boffset;

      printf("pre (color arg) napi_get_typedarray_info\n");
      napi_get_typedarray_info(env, args[3], &tat, &length, (void**) &data, &arrbuf, &boffset);

      // Need to or better to refer to &arrbuf?




      printf("post (color arg) napi_get_typedarray_info\n");

      printf("napi_typedarray_type enum Value : %d\n", (int)tat);
      printf("length: %d\n", (int)length);
      printf("offset: %d\n", (int)boffset);

      // Check typed array type?
      //  For the moment assume it contains uint8s which are 1 byte each of course.
      // Then read color components from it.

      if (length == 3) {
        red = data[0];
        green = data[1];
        blue = data[2];
      } else if (length == 4) {
        red = data[0];
        green = data[1];
        blue = data[2];
        alpha = data[3];
      } else {
        //throw Napi::Error::New(env, "Example exception");
        //Napi::Error::New(env, "Example exception").ThrowAsJavaScriptException();
        napi_throw_error(env, "", "Typed array must have 3 or 4 items representing rgb or rgba.");
        //return;
      }

      if (length == 3) {
        printf("red: %d\n", red);
        printf("green: %d\n", green);
        printf("blue: %d\n", blue);

        // Best to run a looping arg outside of this NAPI function.
        uint32_t num_pixels = ta_length / 3;
        printf("num_pixels %d\n", (int)num_pixels);

        color_whole(input_ui8s, num_pixels, red, green, blue);

      } else if (length == 4) {
        printf("red: %d\n", red);
        printf("green: %d\n", green);
        printf("blue: %d\n", blue);
        printf("alpha: %d\n", alpha);
      }
    } else {
      printf("Color arg is not a typed array (but that's OK).\n");
      // is the color a normal array?
      //  Accessing the underlying ta data will probably be highest performance.
      //   No need to use napi to create the ta values???
      // See if it's a normal array / get the arg info, check for array or number.
      napi_valuetype valuetype_color_arg;
      status = napi_typeof(env, args[3], &valuetype_color_arg);
      assert(status == napi_ok);
      printf("valuetype_color_arg (arg 3): %d\n", valuetype_color_arg);
      int32_t rnum;
      if (valuetype_color_arg == napi_number) {
        // read the greyscale value.
        status = napi_get_value_int32(env, args[3], &rnum);
        assert(status == napi_ok);
        grey = (uint8_t)rnum;
        //printf("grey: %d\n", grey);
        // Call the greyscale recolor function.
        //  Didn't actually need the width, bpp? Many functions will need them as standard.
        // let's process the array here....

        // Better to call a more pure / non-node C++ function.
        //  Will be a better programming pattern.
        //  Want to have NAPI C++ functions call simple C++ functions.
        //   


        if (bits_per_pixel == 8) {
          for(uint i = 0; i < ta_length; i++) {
            //ta_data[i] = grey;
            input_ui8s[i] = grey;
          }
        }
      } else if (valuetype_color_arg == napi_object) {
        // an object - is it an array
        bool color_is_array;
        status = napi_is_array(env, args[3], &color_is_array);
        printf("color_is_array %d\n", (int)color_is_array);

        if (color_is_array) {
          // look at the length of the array
          uint32_t i, length;
          status = napi_get_array_length(env, args[3], &length);
          printf("color array length %d\n", (int)length);
          if (bits_per_pixel == 24) {
            // red, green, blue are the 3 entries in the array.
            //  Then will assign the values accordingly, moving through the data array.
            //  Not using a pixel struct for the moment.
            //uint32_t i;
            napi_value e;
            //napi_number n;
            double dn;
            //status = napi_get_value_uint32(env, args[3], 0, &e);
            status = napi_get_element(env, args[3], 0, &e);
            status = napi_get_value_double(env, e, &dn);
            assert(status == napi_ok);
            red = (uint8_t)dn;

            status = napi_get_element(env, args[3], 1, &e);
            status = napi_get_value_double(env, e, &dn);
            assert(status == napi_ok);
            green = (uint8_t)dn;

            status = napi_get_element(env, args[3], 2, &e);
            status = napi_get_value_double(env, e, &dn);
            assert(status == napi_ok);
            blue = (uint8_t)dn;

            printf("red %d\n", (int)red);
            printf("green %d\n", (int)green);
            printf("blue %d\n", (int)blue);
            // Then go through the array, but with an increment of three....
            uint32_t num_pixels = ta_length / 3;
            printf("num_pixels %d\n", (int)num_pixels);
            // then go through each pixel setting the color...


            // Would be better to call another function.

            for(uint32_t i = 0; i < num_pixels; i++) {
              //ta_data[i] = grey;
              input_ui8s[(i) * 3] = red;
              input_ui8s[(i) * 3 + 1] = green;
              input_ui8s[(i) * 3 + 2] = blue;
            }

          } else if (bits_per_pixel == 32) {
            napi_value e;
            double dn;
            status = napi_get_element(env, args[3], 0, &e);
            status = napi_get_value_double(env, e, &dn);
            assert(status == napi_ok);
            red = (uint8_t)dn;

            status = napi_get_element(env, args[3], 1, &e);
            status = napi_get_value_double(env, e, &dn);
            assert(status == napi_ok);
            green = (uint8_t)dn;

            status = napi_get_element(env, args[3], 2, &e);
            status = napi_get_value_double(env, e, &dn);
            assert(status == napi_ok);
            blue = (uint8_t)dn;

            status = napi_get_element(env, args[3], 3, &e);
            status = napi_get_value_double(env, e, &dn);
            assert(status == napi_ok);
            alpha = (uint8_t)dn;

            printf("red %d\n", (int)red);
            printf("green %d\n", (int)green);
            printf("blue %d\n", (int)blue);
            printf("alpha %d\n", (int)alpha);
            // Then go through the array, but with an increment of three....
            uint32_t num_pixels = ta_length / 4;
            printf("num_pixels %d\n", (int)num_pixels);


            // Again, would be better to call a separate C++ function.

            // write_color_whole(num_pixels, r, g, b, a);



            for(uint i = 0; i < num_pixels; i++) {
              //ta_data[i] = grey;
              input_ui8s[(i) * 4] = red;
              input_ui8s[(i) * 4 + 1] = green;
              input_ui8s[(i) * 4 + 2] = blue;
              input_ui8s[(i) * 4 + 3] = alpha;
            }
          }


          /*
          uint32_t i, length;
          status = napi_get_array_length(env, args[0], &length);
          for (i = 0; i < length; i++)
          {
            napi_value e;
            status = napi_get_element(env, args[0], i, &e);
            status = napi_set_element(env, ret, i, e);
          }
          */

         


        }

      }
      // arrays having a value_type?


    }


  }
  if (c_args == 5) {
    // rgb as separate numbers as params.
    //  probably reading from the typed array will be fastest but its hard to predict without benchmarks.

    //Read_Bipp_W(&env, args, &bits_per_pixel, &width);

    printf("Will error - requires 4, 6 or 7 args.\n");

    // args 3, 4, 5 as rgb. must all be numbers, and fit within uint8_t.

    // read the js number values into these uint8 local values.






  }
  if (c_args == 6) {
    //Read_Bipp_W(&env, args, bits_per_pixel, width);


    // args 3, 4, 5 as rgba. must all be numbers, and fit within uint8_t.

  }
  if (c_args == 7) {
    //Read_Bipp_W(env, args, &bits_per_pixel, &width);


    // args 3, 4, 5 as rgba. must all be numbers, and fit within uint8_t.

  }

  //printf("Bits per pixel: %d\n", (int)bits_per_pixel);
  //printf("Image width: %d\n", (int)width);

  // Will check if the bpp given matches the color we have been given.
  //  Then when the arguments are prepared / ready, we call a (polymorphic?) c++ function.


  // Return true to say its complete for the moment.
  ///  may help chaining in js with if (a(...) && b(...) etc).
  
  napi_value res;
  napi_get_boolean(env, true, &res);
  return res;

}

#endif