
const {read} = require('jsgui3-gfx').ta_math;

const {read_2x2_rect, read_1x2_rect, read_2x1_rect, read_merged_vfpx_24bipp, read_merged_vfpx, get_instance} = read;

module.exports = {
    read_2x2_rect: read_2x2_rect,
    read_1x2_rect: read_1x2_rect,
    read_2x1_rect: read_2x1_rect,
    read_merged_vfpx_24bipp: read_merged_vfpx_24bipp,
    read_merged_vfpx: read_merged_vfpx,
    get_instance: get_instance
}