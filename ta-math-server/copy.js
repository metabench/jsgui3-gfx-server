
const {copy} = require('jsgui3-gfx').ta_math;


const {unaligned_copy_rect_1to4bypp, dest_aligned_copy_rect_1to4bypp, copy_rect_to_same_size_24bipp, copy_rect_to_same_size_8bipp, copy_ta_byte_range, get_instance} = copy;
// copy_px_to_ta

module.exports = {
    unaligned_copy_rect_1to4bypp: unaligned_copy_rect_1to4bypp,
    dest_aligned_copy_rect_1to4bypp: dest_aligned_copy_rect_1to4bypp,
    copy_rect_to_same_size_24bipp: copy_rect_to_same_size_24bipp,
    copy_rect_to_same_size_8bipp: copy_rect_to_same_size_8bipp,
    copy_ta_byte_range: copy_ta_byte_range,
    get_instance: get_instance
};