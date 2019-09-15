// Inner C / C++ implementation
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <node_api.h>
#include <assert.h>
#include <stdio.h>
//#include "ta_macros.h"
#include <sstream>
#include <string>
using namespace std;





/*


let resize_ta_colorspace_24bipp$superpixel$inline$locals$inline = (ta_source, source_colorspace, dest_size, opt_ta_dest) => {

    const ta_dest = opt_ta_dest;
    const dest_to_source_ratio = new Float32Array([source_colorspace[0] / dest_size[0], source_colorspace[1] / dest_size[1]]);
    const fpx_area_recip = 1 / (dest_to_source_ratio[0] * dest_to_source_ratio[1]);

    const [fpxw, fpxh] = [source_colorspace[0] / dest_size[0], source_colorspace[1] / dest_size[1]];

    let edge_l, edge_t, edge_r, edge_b;

    let edge_p_l, edge_p_t, edge_p_r, edge_p_b;

    let corner_p_tl, corner_p_tr, corner_p_bl, corner_p_br;

    const fpx_area = dest_to_source_ratio[0] * dest_to_source_ratio[1];


    //  ------------


    //let [width, height, bypp, bypr, bipp, bipr] = source_colorspace;
    const source_bypp = source_colorspace[2];
    const source_bypr = source_colorspace[3];
    
    const source_bipp = source_colorspace[4];
    const dest_colorspace = new Int32Array([dest_size[0], dest_size[1], source_bypp, source_bypp * dest_size[0], source_bipp, source_bipp * dest_size[0]]);

    let fbounds_l, fbounds_t, fbounds_r, fbounds_b;

    let ibounds_l, ibounds_t, ibounds_r, ibounds_b;

    let any_coverage_w, any_coverage_h;

    let total_coverage_l, total_coverage_t, total_coverage_r, total_coverage_b;

    let byi_read;

    let dest_byi = 0;

    const width = dest_colorspace[0], height = dest_colorspace[1];


    // Storing calculated values from the previous x?
    //  Precalculating an array of different variables for all x values.
    //  Then all y values are iterated so no benefit from precalc.
    //   edges etc

    // A lot more could be precalculated and then referenced.

    // Read a set of values from a larger ta for each x?
    //  Or refer to it.
    //  

    // Could make a version of this that does precalculations.


    let x, y;

    let r = 0, g = 0, b = 0;
    let x_inner, y_inner;

    let byi_read_right, byi_read_below, byi_read_below_right;

    let byi_tl, byi_tm, byi_tr;
    let byi_ml, byi_mm, byi_mr;
    let byi_bl, byi_bm, byi_br;

    let end_hmiddle, end_vmiddle;



    // could have next source pixel pos
    //  use it for bounds of the current pixel


    //for (dest_xy[1] = 0; dest_xy[1] < height; dest_xy[1]++) {
    for (y = 0; y < height; y++) {

        // Can optimize with calculations done just using y.


        fbounds_t = y * fpxh;
        fbounds_b = fbounds_t + fpxh;
        //fbounds_b = (fbounds_t = y * fpxh) + fpxh;


        ibounds_t = Math.floor(fbounds_t);
        ibounds_b = Math.ceil(fbounds_b);

        any_coverage_h = ibounds_b - ibounds_t;

        total_coverage_t = Math.ceil(fbounds_t);

        total_coverage_b = Math.floor(fbounds_b);


        //edge_t = total_coverage_t - fbounds_t || 1;
        //edge_b = fbounds_b - total_coverage_b || 1;

        edge_t = total_coverage_t - fbounds_t;
        edge_b = fbounds_b - total_coverage_b;

        if (edge_t === 0) edge_t = 1;
        if (edge_b === 0) edge_b = 1;
        edge_p_t = edge_t / fpx_area;
        edge_p_b = edge_b / fpx_area;

        // Could try incrementing the fbounds...

        fbounds_l = 0;
        fbounds_r = fpxw;


        for (x = 0; x < width; x++) {
            fbounds_l = x * fpxw;
            fbounds_r = (x + 1) * fpxw;
            ibounds_l = Math.floor(fbounds_l);
            ibounds_r = Math.ceil(fbounds_r);
            any_coverage_w = ibounds_r - ibounds_l;
            byi_read = ibounds_l * source_bypp + ibounds_t * source_bypr;
            total_coverage_l = Math.ceil(fbounds_l);
            total_coverage_r = Math.floor(fbounds_r);
            edge_l = total_coverage_l - fbounds_l;
            edge_r = fbounds_r - total_coverage_r;
            if (edge_l === 0) edge_l = 1;
            if (edge_r === 0) edge_r = 1;
            corner_p_tl = edge_l * edge_p_t;
            corner_p_tr = edge_r * edge_p_t;
            corner_p_bl = edge_l * edge_p_b;
            corner_p_br = edge_r * edge_p_b;

            if (any_coverage_w > 3 ||  any_coverage_h > 3) {
                edge_p_l = edge_l / fpx_area;
                    //edge_distances_proportions_of_total[1] = edge_t / fpx_area;
                edge_p_r = edge_r / fpx_area;
                

                byi_tl = byi_read;
                //byi_read = byi_tl;
                
                // Separate loops...
                //  Worth having an inner row loop too.
                
                end_hmiddle = any_coverage_w - 1; end_vmiddle = any_coverage_h - 1;
            
                //const [w, h] = source_i_any_coverage_size;
            
                //console.log('bypr, byi_read, source_i_any_coverage_size', bypr, byi_read, source_i_any_coverage_size);
                //console.log('[edge_distances_proportions_of_total, corner_weights_ltrb, fpx_area_recip]', [edge_distances_proportions_of_total, corner_weights_ltrb, fpx_area_recip]);
                r = g = b = 0;
            
                r += ta_source[byi_read++] * corner_p_tl;
                g += ta_source[byi_read++] * corner_p_tl;
                b += ta_source[byi_read++] * corner_p_tl;
            
                // loop through the middle section of the top row.
            
                //x = 1;
                
            
                for (x_inner = 1; x_inner < end_hmiddle; x_inner++) {
                    r += ta_source[byi_read++] * edge_p_t;
                    g += ta_source[byi_read++] * edge_p_t;
                    b += ta_source[byi_read++] * edge_p_t;
                }
            
                r += ta_source[byi_read++] * corner_p_tr;
                g += ta_source[byi_read++] * corner_p_tr;
                b += ta_source[byi_read++] * corner_p_tr;
            
                // then loop through the v middle rows.
            
                for (y_inner = 1; y_inner < end_vmiddle; y_inner++) {
                    byi_read = byi_tl + y_inner * source_bypr;
            
                    r += ta_source[byi_read++] * edge_p_l;
                    g += ta_source[byi_read++] * edge_p_l;
                    b += ta_source[byi_read++] * edge_p_l;
            
                    for (x_inner = 1; x_inner < end_hmiddle; x_inner++) {
                        r += ta_source[byi_read++] * fpx_area_recip;
                        g += ta_source[byi_read++] * fpx_area_recip;
                        b += ta_source[byi_read++] * fpx_area_recip;
                    }
            
                    r += ta_source[byi_read++] * edge_p_r;
                    g += ta_source[byi_read++] * edge_p_r;
                    b += ta_source[byi_read++] * edge_p_r;
                }
                byi_read = byi_tl + end_vmiddle * source_bypr;
                // then the bottom vrow
                r += ta_source[byi_read++] * corner_p_bl;
                g += ta_source[byi_read++] * corner_p_bl;
                b += ta_source[byi_read++] * corner_p_bl;
                // loop through the middle section of the top row.
                //x = 1;
            
                //const end_hmiddle = w - 1, end_vmiddle = h - 1;
            
                for (x_inner = 1; x_inner < end_hmiddle; x_inner++) {
                    r += ta_source[byi_read++] * edge_p_b;
                    g += ta_source[byi_read++] * edge_p_b;
                    b += ta_source[byi_read++] * edge_p_b;
                }
            
                r += ta_source[byi_read++] * corner_p_br;
                g += ta_source[byi_read++] * corner_p_br;
                b += ta_source[byi_read++] * corner_p_br;
            
                //console.log('[r, g, b]', [r, g, b]);
            
                ta_dest[dest_byi] = Math.round(r);
                ta_dest[dest_byi + 1] = Math.round(g);
                ta_dest[dest_byi + 2] = Math.round(b);
            } else {

                if (any_coverage_w === 2 && any_coverage_h === 2) {

                    
                    //read_2x2_weight_write_24bipp$locals(ta_source, source_bypr, byi_read, 
                    //    corner_p_tl, corner_p_tr, corner_p_bl, corner_p_br,
                    //    opt_ta_dest, dest_byi); 

                        
                        
                    byi_read_right = byi_read + 3;
                    byi_read_below = byi_read + source_bypr;
                    byi_read_below_right = byi_read_below + 3;
                    ta_dest[dest_byi] = corner_p_tl * ta_source[byi_read++] + corner_p_tr * ta_source[byi_read_right++] + corner_p_bl * ta_source[byi_read_below++] + corner_p_br * ta_source[byi_read_below_right++];
                    ta_dest[dest_byi + 1] = corner_p_tl * ta_source[byi_read++] + corner_p_tr * ta_source[byi_read_right++] + corner_p_bl * ta_source[byi_read_below++] + corner_p_br * ta_source[byi_read_below_right++];
                    ta_dest[dest_byi + 2] = corner_p_tl * ta_source[byi_read++] + corner_p_tr * ta_source[byi_read_right++] + corner_p_bl * ta_source[byi_read_below++] + corner_p_br * ta_source[byi_read_below_right++];
                    


                } else {
                    edge_p_l = edge_l / fpx_area;
                    edge_p_r = edge_r / fpx_area;
                    if (any_coverage_w === 2 && any_coverage_h === 3) {


                        byi_tl = byi_read; byi_tr = byi_tl + 3;
                        byi_ml = byi_tl + source_bypr; byi_mr = byi_ml + 3;
                        byi_bl = byi_ml + source_bypr; byi_br = byi_bl + 3;
                    
                        ta_dest[dest_byi] =     ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_br++] * corner_p_br
                    
                    
                        ta_dest[dest_byi + 1] = ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_br++] * corner_p_br
                    
                    
                        ta_dest[dest_byi + 2] = ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_br++] * corner_p_br





                        //read_2x3_weight_write_24bipp(ta_source, source_bypr, byi_read, edge_distances_proportions_of_total, corner_areas_proportions_of_total, opt_ta_dest, dest_byi);
                        ///read_2x3_weight_write_24bipp$locals(ta_source, source_bypr, byi_read, edge_distances_proportions_of_total, corner_areas_proportions_of_total, opt_ta_dest, dest_byi);
                    } else if (any_coverage_w === 3 && any_coverage_h === 2) {

                        byi_tl = byi_read;
                        byi_tm = byi_tl + 3; byi_tr = byi_tm + 3;
                        byi_bl = byi_tm + source_bypr; byi_bm = byi_bl + 3; byi_br = byi_bm + 3;

                        


                        ta_dest[dest_byi] =     ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                            ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br;

                        ta_dest[dest_byi + 1] = ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                            ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br;
                                            
                        ta_dest[dest_byi + 2] = ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                            ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br;
                                            

                    } else if (any_coverage_w === 3 && any_coverage_h === 3) {

                        byi_tl = byi_read; byi_tm = byi_tl + source_bypp; byi_tr = byi_tm + source_bypp;
                        byi_ml = byi_tl + source_bypr; byi_mm = byi_ml + source_bypp; byi_mr = byi_mm + source_bypp;
                        byi_bl = byi_ml + source_bypr; byi_bm = byi_bl + source_bypp; byi_br = byi_bm + source_bypp;
                    
                        // Doing it component by component.
                    
                        ta_dest[dest_byi] =     ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mm++] * fpx_area_recip + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br
                    
                    
                        ta_dest[dest_byi + 1] = ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mm++] * fpx_area_recip + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br
                    
                    
                        ta_dest[dest_byi + 2] = ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mm++] * fpx_area_recip + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br
                    } else {

                        console.trace();
                        throw 'stop';

                        //read_gt3x3_weight_write_24bipp(ta_source, source_bypr, byi_read, source_i_any_coverage_size, edge_distances_proportions_of_total, corner_areas_proportions_of_total, fpx_area_recip, opt_ta_dest, dest_byi);
                    }
                }
            }
            dest_byi += source_bypp;

            //fbounds_l += fpxw; fbounds_r += fpxw;
        }
    }
}

*/
void resize_ta_colorspace_24bipp$superpixel$inline$locals$inline(uint8_t* ta_source, int16_t* source_colorspace, int16_t* dest_size, uint8_t* ta_dest) {
    float const dest_to_source_ratio[2] = {((float)source_colorspace[0] / (float)dest_size[0]), ((float)source_colorspace[1] / (float)dest_size[1])};

    float const fpx_area_recip = 1 / (dest_to_source_ratio[0] * dest_to_source_ratio[1]);

    // const [fpxw, fpxh]
    float const fpxw = dest_to_source_ratio[0];
    float const fpxh = dest_to_source_ratio[1];
    
    float edge_l, edge_t, edge_r, edge_b;

    float edge_p_l, edge_p_t, edge_p_r, edge_p_b;

    float corner_p_tl, corner_p_tr, corner_p_bl, corner_p_br;

    float const fpx_area = dest_to_source_ratio[0] * dest_to_source_ratio[1];


    int16_t const source_bypp = source_colorspace[2];
    int16_t const source_bypr = source_colorspace[3];
    int16_t const source_bipp = source_colorspace[4];


    //const dest_colorspace = new Int32Array([dest_size[0], dest_size[1], source_bypp, source_bypp * dest_size[0], source_bipp, source_bipp * dest_size[0]]);

    float fbounds_l, fbounds_t, fbounds_r, fbounds_b;
    int16_t ibounds_l, ibounds_t, ibounds_r, ibounds_b;
    int16_t any_coverage_w, any_coverage_h;
    int16_t total_coverage_l, total_coverage_t, total_coverage_r, total_coverage_b;
    int32_t byi_read;
    int32_t dest_byi = 0;

    int16_t const width = dest_size[0], height = dest_size[1];
    int16_t x, y;

    float r = 0, g = 0, b = 0;
    int16_t x_inner, y_inner;

    int32_t byi_read_right, byi_read_below, byi_read_below_right;

    int32_t byi_tl, byi_tm, byi_tr;
    int32_t byi_ml, byi_mm, byi_mr;
    int32_t byi_bl, byi_bm, byi_br;

    int16_t end_hmiddle, end_vmiddle;


    for (y = 0; y < height; y++) {

        // Can optimize with calculations done just using y.


        fbounds_t = y * fpxh;
        fbounds_b = fbounds_t + fpxh;
        //fbounds_b = (fbounds_t = y * fpxh) + fpxh;


        ibounds_t = floor(fbounds_t);
        ibounds_b = ceil(fbounds_b);

        any_coverage_h = ibounds_b - ibounds_t;

        total_coverage_t = ceil(fbounds_t);
        total_coverage_b = floor(fbounds_b);


        //edge_t = total_coverage_t - fbounds_t || 1;
        //edge_b = fbounds_b - total_coverage_b || 1;

        edge_t = total_coverage_t - fbounds_t;
        edge_b = fbounds_b - total_coverage_b;

        if (edge_t == 0) edge_t = 1;
        if (edge_b == 0) edge_b = 1;
        edge_p_t = edge_t / fpx_area;
        edge_p_b = edge_b / fpx_area;

        // Could try incrementing the fbounds...

        fbounds_l = 0;
        fbounds_r = fpxw;


        for (x = 0; x < width; x++) {
            fbounds_l = x * fpxw;
            fbounds_r = (x + 1) * fpxw;
            ibounds_l = floor(fbounds_l);
            ibounds_r = ceil(fbounds_r);
            any_coverage_w = ibounds_r - ibounds_l;
            byi_read = ibounds_l * source_bypp + ibounds_t * source_bypr;
            total_coverage_l = ceil(fbounds_l);
            total_coverage_r = floor(fbounds_r);
            edge_l = total_coverage_l - fbounds_l;
            edge_r = fbounds_r - total_coverage_r;
            if (edge_l == 0) edge_l = 1;
            if (edge_r == 0) edge_r = 1;
            corner_p_tl = edge_l * edge_p_t;
            corner_p_tr = edge_r * edge_p_t;
            corner_p_bl = edge_l * edge_p_b;
            corner_p_br = edge_r * edge_p_b;

            if (any_coverage_w > 3 ||  any_coverage_h > 3) {
                edge_p_l = edge_l / fpx_area;
                    //edge_distances_proportions_of_total[1] = edge_t / fpx_area;
                edge_p_r = edge_r / fpx_area;
                byi_tl = byi_read;
                //byi_read = byi_tl;
                
                // Separate loops...
                //  Worth having an inner row loop too.
                
                end_hmiddle = any_coverage_w - 1; end_vmiddle = any_coverage_h - 1;
            
                //const [w, h] = source_i_any_coverage_size;
            
                //console.log('bypr, byi_read, source_i_any_coverage_size', bypr, byi_read, source_i_any_coverage_size);
                //console.log('[edge_distances_proportions_of_total, corner_weights_ltrb, fpx_area_recip]', [edge_distances_proportions_of_total, corner_weights_ltrb, fpx_area_recip]);
                //r = g = b = 0;
            
                r = ta_source[byi_read++] * corner_p_tl;
                g = ta_source[byi_read++] * corner_p_tl;
                b = ta_source[byi_read++] * corner_p_tl;
            
                // loop through the middle section of the top row.
            
                //x = 1;
                
            
                for (x_inner = 1; x_inner < end_hmiddle; x_inner++) {
                    r += ta_source[byi_read++] * edge_p_t;
                    g += ta_source[byi_read++] * edge_p_t;
                    b += ta_source[byi_read++] * edge_p_t;
                }
            
                r += ta_source[byi_read++] * corner_p_tr;
                g += ta_source[byi_read++] * corner_p_tr;
                b += ta_source[byi_read++] * corner_p_tr;
            
                // then loop through the v middle rows.
            
                for (y_inner = 1; y_inner < end_vmiddle; y_inner++) {
                    byi_read = byi_tl + y_inner * source_bypr;
            
                    r += ta_source[byi_read++] * edge_p_l;
                    g += ta_source[byi_read++] * edge_p_l;
                    b += ta_source[byi_read++] * edge_p_l;
            
                    for (x_inner = 1; x_inner < end_hmiddle; x_inner++) {
                        r += ta_source[byi_read++] * fpx_area_recip;
                        g += ta_source[byi_read++] * fpx_area_recip;
                        b += ta_source[byi_read++] * fpx_area_recip;
                    }
            
                    r += ta_source[byi_read++] * edge_p_r;
                    g += ta_source[byi_read++] * edge_p_r;
                    b += ta_source[byi_read++] * edge_p_r;
                }
                byi_read = byi_tl + end_vmiddle * source_bypr;
                // then the bottom vrow
                r += ta_source[byi_read++] * corner_p_bl;
                g += ta_source[byi_read++] * corner_p_bl;
                b += ta_source[byi_read++] * corner_p_bl;
                // loop through the middle section of the top row.
                //x = 1;
            
                //const end_hmiddle = w - 1, end_vmiddle = h - 1;
            
                for (x_inner = 1; x_inner < end_hmiddle; x_inner++) {
                    r += ta_source[byi_read++] * edge_p_b;
                    g += ta_source[byi_read++] * edge_p_b;
                    b += ta_source[byi_read++] * edge_p_b;
                }
            
                r += ta_source[byi_read++] * corner_p_br;
                g += ta_source[byi_read++] * corner_p_br;
                b += ta_source[byi_read++] * corner_p_br;
            
                //console.log('[r, g, b]', [r, g, b]);
            
                //ta_dest[dest_byi] = round(r);
                //ta_dest[dest_byi + 1] = round(g);
                //ta_dest[dest_byi + 2] = round(b);
                ta_dest[dest_byi] = (r);
                ta_dest[dest_byi + 1] = (g);
                ta_dest[dest_byi + 2] = (b);
            } else {

                if (any_coverage_w == 2 && any_coverage_h == 2) {

                    
                    //read_2x2_weight_write_24bipp$locals(ta_source, source_bypr, byi_read, 
                    //    corner_p_tl, corner_p_tr, corner_p_bl, corner_p_br,
                    //    opt_ta_dest, dest_byi); 

                        
                        
                    byi_read_right = byi_read + 3;
                    byi_read_below = byi_read + source_bypr;
                    byi_read_below_right = byi_read_below + 3;
                    ta_dest[dest_byi] = (corner_p_tl * ta_source[byi_read++] + corner_p_tr * ta_source[byi_read_right++] + corner_p_bl * ta_source[byi_read_below++] + corner_p_br * ta_source[byi_read_below_right++]);
                    ta_dest[dest_byi + 1] = (corner_p_tl * ta_source[byi_read++] + corner_p_tr * ta_source[byi_read_right++] + corner_p_bl * ta_source[byi_read_below++] + corner_p_br * ta_source[byi_read_below_right++]);
                    ta_dest[dest_byi + 2] = (corner_p_tl * ta_source[byi_read++] + corner_p_tr * ta_source[byi_read_right++] + corner_p_bl * ta_source[byi_read_below++] + corner_p_br * ta_source[byi_read_below_right++]);
                    


                } else {
                    edge_p_l = edge_l / fpx_area;
                    edge_p_r = edge_r / fpx_area;
                    if (any_coverage_w == 2 && any_coverage_h == 3) {


                        byi_tl = byi_read; byi_tr = byi_tl + 3;
                        byi_ml = byi_tl + source_bypr; byi_mr = byi_ml + 3;
                        byi_bl = byi_ml + source_bypr; byi_br = byi_bl + 3;
                    
                        ta_dest[dest_byi] =     (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_br++] * corner_p_br);
                    
                    
                        ta_dest[dest_byi + 1] = (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_br++] * corner_p_br);
                    
                    
                        ta_dest[dest_byi + 2] = (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_br++] * corner_p_br);





                        //read_2x3_weight_write_24bipp(ta_source, source_bypr, byi_read, edge_distances_proportions_of_total, corner_areas_proportions_of_total, opt_ta_dest, dest_byi);
                        ///read_2x3_weight_write_24bipp$locals(ta_source, source_bypr, byi_read, edge_distances_proportions_of_total, corner_areas_proportions_of_total, opt_ta_dest, dest_byi);
                    } else if (any_coverage_w == 3 && any_coverage_h == 2) {

                        byi_tl = byi_read;
                        byi_tm = byi_tl + 3; byi_tr = byi_tm + 3;
                        byi_bl = byi_tm + source_bypr; byi_bm = byi_bl + 3; byi_br = byi_bm + 3;

                        


                        ta_dest[dest_byi] = (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                            ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br);

                        ta_dest[dest_byi + 1] = (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                            ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br);
                                            
                        ta_dest[dest_byi + 2] = (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                            ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br);
                                            

                    } else if (any_coverage_w == 3 && any_coverage_h == 3) {

                        byi_tl = byi_read; byi_tm = byi_tl + source_bypp; byi_tr = byi_tm + source_bypp;
                        byi_ml = byi_tl + source_bypr; byi_mm = byi_ml + source_bypp; byi_mr = byi_mm + source_bypp;
                        byi_bl = byi_ml + source_bypr; byi_bm = byi_bl + source_bypp; byi_br = byi_bm + source_bypp;
                    
                        // Doing it component by component.
                    
                        ta_dest[dest_byi] =     (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mm++] * fpx_area_recip + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br);
                    
                    
                        ta_dest[dest_byi + 1] = (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mm++] * fpx_area_recip + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br);
                    
                    
                        ta_dest[dest_byi + 2] = (ta_source[byi_tl++] * corner_p_tl + ta_source[byi_tm++] * edge_p_t + ta_source[byi_tr++] * corner_p_tr +
                                                ta_source[byi_ml++] * edge_p_l + ta_source[byi_mm++] * fpx_area_recip + ta_source[byi_mr++] * edge_p_r +
                                                ta_source[byi_bl++] * corner_p_bl + ta_source[byi_bm++] * edge_p_b + ta_source[byi_br++] * corner_p_br);
                    } else {

                        //console.trace();
                        //throw 'stop';

                        //read_gt3x3_weight_write_24bipp(ta_source, source_bypr, byi_read, source_i_any_coverage_size, edge_distances_proportions_of_total, corner_areas_proportions_of_total, fpx_area_recip, opt_ta_dest, dest_byi);
                    }
                }
            }
            dest_byi += source_bypp;

            //fbounds_l += fpxw; fbounds_r += fpxw;
        }
    }
}

napi_value NAPI_resize_ta_colorspace_24bipp$superpixel$inline$locals$inline(napi_env env, napi_callback_info info) {

    // ta_source, source_colorspace, dest_size, opt_ta_dest
    size_t c_args = 4;

    napi_value args[4];
    napi_status status;
    status = napi_get_cb_info(env, info, &c_args, args, nullptr, nullptr);
    assert(status == napi_ok);

    // Then need to read / assign to variables a bunch of different values and typed arrays.




    //printf("Arg count: %d\n", (int)c_args);
    // (ta_source, bypr, byi_read, source_i_any_coverage_size, edge_segment_areas_proportions_of_total, corner_areas_proportions_of_total, fpx_area_recip, ta_dest, byi_write)

    // Args variables:

    napi_typedarray_type tat;
    size_t length_ta_source, length_ta_source_colorspace, length_ta_dest_size, length_ta_dest;
    uint8_t* ta_source;
    uint8_t* ta_dest;
    napi_value arrbuf_ta_source, arrbuf_ta_source_colorspace, arrbuf_ta_dest_size, arrbuf_ta_dest;
    size_t boffset_ta_source, boffset_ta_source_colorspace, boffset_ta_dest_size, boffset_ta_dest;

    //uint32_t byi_read, byi_write;

    // the colorspace typedarray.
    //  int16 I think.

    int16_t* source_colorspace;
    int16_t* dest_size;

    status = napi_get_typedarray_info(env, args[0], &tat, &length_ta_source, (void**) &ta_source, &arrbuf_ta_source, &boffset_ta_source);
    assert(status == napi_ok);

    //printf("args[0] napi_typedarray_type enum Value : %d\n", (int)tat);
    //printf("length_ta_source: %d\n", (int)length_ta_source);
    //printf("boffset_ta_source: %d\n", (int)boffset_ta_source);

    status = napi_get_typedarray_info(env, args[1], &tat, &length_ta_source_colorspace, (void**) &source_colorspace, &arrbuf_ta_source_colorspace, &boffset_ta_source_colorspace);
    assert(status == napi_ok);
    
    status = napi_get_typedarray_info(env, args[2], &tat, &length_ta_dest_size, (void**) &dest_size, &arrbuf_ta_dest_size, &boffset_ta_dest_size);
    assert(status == napi_ok);

    status = napi_get_typedarray_info(env, args[3], &tat, &length_ta_dest, (void**) &ta_dest, &arrbuf_ta_dest, &boffset_ta_dest);
    assert(status == napi_ok);

    // the dest size is also a typed array

    //printf("Pre c++ inner function\n");

    resize_ta_colorspace_24bipp$superpixel$inline$locals$inline(ta_source, source_colorspace, dest_size, ta_dest);
    //printf("Post c++ inner function\n");



    napi_value res;
    napi_get_undefined(env, &res);
    return res;

}





/*

void color_whole(uint8_t* input_ui8s, int num_pixels, uint8_t r, uint8_t g, uint8_t b) {
  for(uint32_t i = 0; i < num_pixels; i++) {
    //ta_data[i] = grey;
    input_ui8s[(i) * 3] = r;
    input_ui8s[(i) * 3 + 1] = g;
    input_ui8s[(i) * 3 + 2] = b;
  }
}


let read_gt3x3_weight_write_24bipp = (ta_source, bypr, byi_read, source_i_any_coverage_size, edge_distances_proportions_of_total, corner_areas_proportions_of_total, fpx_area_recip, ta_dest, dest_byi) => {
    const byi_tl = byi_read;
    byi_read = byi_tl;
    let r = 0, g = 0, b = 0;
    // Separate loops...
    //  Worth having an inner row loop too.
    let x = 0, y = 0;

    const [w, h] = source_i_any_coverage_size;

    r += ta_source[byi_read++] * corner_areas_proportions_of_total[0];
    g += ta_source[byi_read++] * corner_areas_proportions_of_total[0];
    b += ta_source[byi_read++] * corner_areas_proportions_of_total[0];

    // loop through the middle section of the top row.

    //x = 1;

    const end_hmiddle = w - 1, end_vmiddle = h - 1;

    for (x = 1; x < end_hmiddle; x++) {
        r += ta_source[byi_read++] * edge_distances_proportions_of_total[1];
        g += ta_source[byi_read++] * edge_distances_proportions_of_total[1];
        b += ta_source[byi_read++] * edge_distances_proportions_of_total[1];
    }

    r += ta_source[byi_read++] * corner_areas_proportions_of_total[1];
    g += ta_source[byi_read++] * corner_areas_proportions_of_total[1];
    b += ta_source[byi_read++] * corner_areas_proportions_of_total[1];

    // then loop through the v middle rows.

    for (y = 1; y < end_vmiddle; y++) {
        byi_read = byi_tl + y * bypr;

        r += ta_source[byi_read++] * edge_distances_proportions_of_total[0];
        g += ta_source[byi_read++] * edge_distances_proportions_of_total[0];
        b += ta_source[byi_read++] * edge_distances_proportions_of_total[0];

        for (x = 1; x < end_hmiddle; x++) {
            r += ta_source[byi_read++] * fpx_area_recip;
            g += ta_source[byi_read++] * fpx_area_recip;
            b += ta_source[byi_read++] * fpx_area_recip;
        }

        r += ta_source[byi_read++] * edge_distances_proportions_of_total[2];
        g += ta_source[byi_read++] * edge_distances_proportions_of_total[2];
        b += ta_source[byi_read++] * edge_distances_proportions_of_total[2];
    }


    byi_read = byi_tl + end_vmiddle * bypr;
    // then the bottom vrow

    r += ta_source[byi_read++] * corner_areas_proportions_of_total[2];
    g += ta_source[byi_read++] * corner_areas_proportions_of_total[2];
    b += ta_source[byi_read++] * corner_areas_proportions_of_total[2];

    // loop through the middle section of the top row.
    //x = 1;

    //const end_hmiddle = w - 1, end_vmiddle = h - 1;

    for (x = 1; x < end_hmiddle; x++) {
        r += ta_source[byi_read++] * edge_distances_proportions_of_total[3];
        g += ta_source[byi_read++] * edge_distances_proportions_of_total[3];
        b += ta_source[byi_read++] * edge_distances_proportions_of_total[3];
    }

    r += ta_source[byi_read++] * corner_areas_proportions_of_total[3];
    g += ta_source[byi_read++] * corner_areas_proportions_of_total[3];
    b += ta_source[byi_read++] * corner_areas_proportions_of_total[3];


    ta_dest[dest_byi] = Math.round(r);
    ta_dest[dest_byi + 1] = Math.round(g);
    ta_dest[dest_byi + 2] = Math.round(b);
}

(ta_source, bypr, byi_read, source_i_any_coverage_size, edge_segment_areas_proportions_of_total, corner_areas_proportions_of_total, fpx_area_recip, ta_dest, dest_byi)

*/

void read_gt3x3_weight_write_24bipp(uint8_t* ta_source, uint32_t bypr, uint32_t byi_read, 
    int16_t* source_i_any_coverage_size, float* edge_segment_areas_proportions_of_total, float* corner_areas_proportions_of_total, float fpx_area_recip,
    uint8_t* ta_dest, uint32_t byi_write) {

    float r = 0, g = 0, b = 0;

    uint32_t x, y;
    uint32_t w = source_i_any_coverage_size[0];
    uint32_t h = source_i_any_coverage_size[1];

    uint32_t end_hmiddle = w - 1, end_vmiddle = h - 1;

    uint32_t byi_tl = byi_read;

    r += ta_source[byi_read++] * corner_areas_proportions_of_total[0];
    g += ta_source[byi_read++] * corner_areas_proportions_of_total[0];
    b += ta_source[byi_read++] * corner_areas_proportions_of_total[0];

    for (x = 1; x < end_hmiddle; x++) {
        r += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[1];
        g += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[1];
        b += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[1];
    }

    r += ta_source[byi_read++] * corner_areas_proportions_of_total[1];
    g += ta_source[byi_read++] * corner_areas_proportions_of_total[1];
    b += ta_source[byi_read++] * corner_areas_proportions_of_total[1];

    // then loop through the v middle rows.

    for (y = 1; y < end_vmiddle; y++) {
        byi_read = byi_tl + y * bypr;

        r += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[0];
        g += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[0];
        b += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[0];

        for (x = 1; x < end_hmiddle; x++) {
            r += ta_source[byi_read++] * fpx_area_recip;
            g += ta_source[byi_read++] * fpx_area_recip;
            b += ta_source[byi_read++] * fpx_area_recip;
        }

        r += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[2];
        g += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[2];
        b += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[2];
    }


    byi_read = byi_tl + end_vmiddle * bypr;
    // then the bottom vrow

    r += ta_source[byi_read++] * corner_areas_proportions_of_total[2];
    g += ta_source[byi_read++] * corner_areas_proportions_of_total[2];
    b += ta_source[byi_read++] * corner_areas_proportions_of_total[2];

    // loop through the middle section of the top row.
    //x = 1;

    //const end_hmiddle = w - 1, end_vmiddle = h - 1;

    for (x = 1; x < end_hmiddle; x++) {
        r += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[3];
        g += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[3];
        b += ta_source[byi_read++] * edge_segment_areas_proportions_of_total[3];
    }

    r += ta_source[byi_read++] * corner_areas_proportions_of_total[3];
    g += ta_source[byi_read++] * corner_areas_proportions_of_total[3];
    b += ta_source[byi_read++] * corner_areas_proportions_of_total[3];


    ta_dest[byi_write] = round(r);
    ta_dest[byi_write + 1] = round(g);
    ta_dest[byi_write + 2] = round(b);



}



// NAPI function


napi_value NAPI_read_gt3x3_weight_write_24bipp(napi_env env, napi_callback_info info) {
    // Interpret the parameters.
    //  Could be given different numbers of parameters.
    //   eg r, g, b, a as 4 numbers.
    //    a greyscale value
    //    a single rgb / rgba typed array
    size_t c_args = 9;
    // We can still get the args info.
    //  Not so sure how to get the args array / structure when we dont know its length.  

    // May as well use buffer size 4 and prepare for undefined items.
    //const int max_num_args = 9;
    napi_value args[9];
    napi_status status;
    status = napi_get_cb_info(env, info, &c_args, args, nullptr, nullptr);
    assert(status == napi_ok);

    // Then need to read / assign to variables a bunch of different values and typed arrays.




    //printf("Arg count: %d\n", (int)c_args);
    // (ta_source, bypr, byi_read, source_i_any_coverage_size, edge_segment_areas_proportions_of_total, corner_areas_proportions_of_total, fpx_area_recip, ta_dest, byi_write)

    // Args variables:

    napi_typedarray_type tat;
    size_t length_ta_source, length_source_i_any_coverage_size, length_edge_segment_areas_proportions_of_total, length_corner_areas_proportions_of_total, length_ta_dest;
    uint8_t* ta_source;
    napi_value arrbuf_ta_source;
    size_t boffset_ta_source;

    uint32_t bypr, byi_read;
    int16_t* source_i_any_coverage_size;
    napi_value arrbuf_source_any_coverage_size;
    size_t boffset_source_any_coverage_size, boffset_edge_segment_areas_proportions_of_total, boffset_corner_areas_proportions_of_total, boffset_ta_dest;

    float* edge_segment_areas_proportions_of_total;
    float* corner_areas_proportions_of_total;
    float fpx_area_recip;
    uint8_t* ta_dest;
    uint32_t byi_write;


    napi_value arrbuf_wont_use_this, arrbuf_wont_use_this2;

    // Arg 0: ta_source

    

    //printf("pre (ta_source) napi_get_typedarray_info\n");
    status = napi_get_typedarray_info(env, args[0], &tat, &length_ta_source, (void**) &ta_source, &arrbuf_ta_source, &boffset_ta_source);
    assert(status == napi_ok);

    //printf("args[0] napi_typedarray_type enum Value : %d\n", (int)tat);
    //printf("length_ta_source: %d\n", (int)length_ta_source);
    //printf("boffset_ta_source: %d\n", (int)boffset_ta_source);

    // Arg 1: bypr (source)

    status = napi_get_value_uint32(env, args[1], &bypr);
    assert(status == napi_ok);
    //printf("bypr: %d\n", (int)bypr);

    // Arg 2: byi_read

    status = napi_get_value_uint32(env, args[2], &byi_read);
    assert(status == napi_ok);
    //printf("byi_read: %d\n", (int)byi_read);

    // Arg 3: source_i_any_coverage_size
    status = napi_get_typedarray_info(env, args[3], &tat, &length_source_i_any_coverage_size, (void**) &source_i_any_coverage_size, &arrbuf_source_any_coverage_size, &boffset_source_any_coverage_size);
    assert(status == napi_ok);
    //printf("args[3] napi_typedarray_type enum Value : %d\n", (int)tat);
    //printf("length_ta_source: %d\n", (int)length_source_i_any_coverage_size);
    //printf("boffset_ta_source: %d\n", (int)boffset_source_any_coverage_size);

    //printf("source_i_any_coverage_size[0]: %d\n", source_i_any_coverage_size[0]);
    //printf("source_i_any_coverage_size[1]: %d\n", source_i_any_coverage_size[1]);


    // Arg 4: edge_segment_areas_proportions_of_total

    status = napi_get_typedarray_info(env, args[4], &tat, &length_edge_segment_areas_proportions_of_total, (void**) &edge_segment_areas_proportions_of_total, &arrbuf_wont_use_this, &boffset_edge_segment_areas_proportions_of_total);
    assert(status == napi_ok);

    //printf("args[4] napi_typedarray_type enum Value : %d\n", (int)tat);
    //printf("length_edge_segment_areas_proportions_of_total: %d\n", (int)length_edge_segment_areas_proportions_of_total);
    //printf("boffset_edge_segment_areas_proportions_of_total: %d\n", (int)boffset_edge_segment_areas_proportions_of_total);

    //printf("edge_segment_areas_proportions_of_total[0]: %f\n", edge_segment_areas_proportions_of_total[0]);
    //printf("edge_segment_areas_proportions_of_total[1]: %f\n", edge_segment_areas_proportions_of_total[1]);
    //printf("edge_segment_areas_proportions_of_total[2]: %f\n", edge_segment_areas_proportions_of_total[2]);
    //printf("edge_segment_areas_proportions_of_total[3]: %f\n", edge_segment_areas_proportions_of_total[3]);


    // Arg 5: corner_areas_proportions_of_total

    status = napi_get_typedarray_info(env, args[5], &tat, &length_corner_areas_proportions_of_total, (void**) &corner_areas_proportions_of_total, &arrbuf_wont_use_this, &boffset_corner_areas_proportions_of_total);
    assert(status == napi_ok);

    //printf("args[5] napi_typedarray_type enum Value : %d\n", (int)tat);
    //printf("length_corner_areas_proportions_of_total: %d\n", (int)length_corner_areas_proportions_of_total);
    //printf("boffset_corner_areas_proportions_of_total: %d\n", (int)boffset_corner_areas_proportions_of_total);

    //printf("corner_areas_proportions_of_total[0]: %f\n", corner_areas_proportions_of_total[0]);
    //printf("corner_areas_proportions_of_total[1]: %f\n", corner_areas_proportions_of_total[1]);
    //printf("corner_areas_proportions_of_total[2]: %f\n", corner_areas_proportions_of_total[2]);
    //printf("corner_areas_proportions_of_total[3]: %f\n", corner_areas_proportions_of_total[3]);

    // Arg 6: fpx_area_recip

    //napi_get_value_double

    double scratch_double;

    status = napi_get_value_double(env, args[6], (double*)&scratch_double);
    //status = napi_get_value_double(env, args[6], (double*)&fpx_area_recip);
    assert(status == napi_ok);
    fpx_area_recip = (float)scratch_double;
    //printf("fpx_area_recip: %f\n", fpx_area_recip);


    // Arg 7: ta_dest

    status = napi_get_typedarray_info(env, args[7], &tat, &length_ta_dest, (void**) &ta_dest, &arrbuf_wont_use_this2, &boffset_ta_dest);
    assert(status == napi_ok);

    //printf("args[7] napi_typedarray_type enum Value : %d\n", (int)tat);
    //printf("length_ta_dest: %d\n", (int)length_ta_dest);
    //printf("boffset_ta_dest: %d\n", (int)boffset_ta_dest);


    // Arg 8: byi_write

    status = napi_get_value_uint32(env, args[8], &byi_write);
    assert(status == napi_ok);
    //printf("byi_write: %d\n", (int)byi_write);


    //  Then once we have the args in C++land, we run a normal C++ function using them.

    read_gt3x3_weight_write_24bipp(ta_source, bypr, byi_read, source_i_any_coverage_size, edge_segment_areas_proportions_of_total, corner_areas_proportions_of_total, fpx_area_recip, ta_dest, byi_write);

    //printf("Post c++ inner function\n");




    //napi_value res;
    //napi_get_boolean(env, true, &res);
    //printf("Pre napi return true res\n");
    //return res;
    


    napi_value res;
    napi_get_undefined(env, &res);
    return res;



}

// NAPI binding




#endif