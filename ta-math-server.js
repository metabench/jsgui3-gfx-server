//const {ta_math} = require('jsgui3-gfx');

const copy = require('./ta-math-server/copy');
const info = require('./ta-math-server/info');
const read = require('./ta-math-server/read');
const transform = require('./ta-math-server/transform');
const write = require('./ta-math-server/write');

    
const {copy_rect_to_same_size_8bipp, copy_rect_to_same_size_24bipp, copy_ta_byte_range, unaligned_copy_rect_1to4bypp, unaligned_copy_rect_1bypp_to_3bypp,
    dest_aligned_copy_rect_1to4bypp} = copy;
const {overlapping_bounds} = info;
const {fill_solid_rect_by_bounds} = write;
const {read_1x2_rect, read_2x1_rect, read_2x2_rect, read_px} = read;



const {resize_ta_colorspace} = transform;

const ta_math_server = {
    overlapping_bounds: overlapping_bounds,
    copy_rect_to_same_size_8bipp: copy_rect_to_same_size_8bipp,
    copy_rect_to_same_size_24bipp: copy_rect_to_same_size_24bipp,
    copy_ta_byte_range: copy_ta_byte_range,
    unaligned_copy_rect_1to4bypp: unaligned_copy_rect_1to4bypp,
    unaligned_copy_rect_1bypp_to_3bypp: unaligned_copy_rect_1bypp_to_3bypp,
    dest_aligned_copy_rect_1to4bypp: dest_aligned_copy_rect_1to4bypp,
    fill_solid_rect_by_bounds: fill_solid_rect_by_bounds,
    read_1x2_rect: read_1x2_rect,
    read_2x1_rect: read_2x1_rect,
    read_2x2_rect: read_2x2_rect,
    read_px: read_px,
    read_pixel: read_px,
    resize_ta_colorspace: resize_ta_colorspace//,
    //override: override,
    //get_instance: get_instance
}

module.exports = ta_math_server;