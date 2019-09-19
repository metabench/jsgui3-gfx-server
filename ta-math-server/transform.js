

const {transform} = require('jsgui3-gfx').ta_math;
const {resize_ta_colorspace_24bipp$subpixel} = transform;
const addon = require('bindings')('addon.node')
//console.log('addon', addon);
//throw 'stop';
//const {resize_ta_colorspace_24bipp} = addon;


// resize_ta_colorspace_24bipp$subpixel$inline

const resize_ta_colorspace_24bipp$subpixel$inline = addon.resize_ta_colorspace_24bipp$subpixel$inline;


const resize_ta_colorspace_24bipp$superpixel = addon.resize_ta_colorspace_24bipp$superpixel$inline$locals$inline;

const resize_ta_colorspace_24bipp = (ta_source, source_colorspace, dest_size, opt_ta_dest) => {

    // Simplified this function.
    //  Seems like a small perf cost with the extra function calls used.
    //   Could optimize - not setting any weights when its 1x1, not doing the measurements.

    // C++ versions of the functions that run in here would be of use.
    //  May also be better to use functions for single pixel , 2x1 etc read-merge-write operations.
    //   Would make this function significantly shorter overall, and act more as a function dispatcher.

    //const dest_colorspace = new Int32Array([dest_size[0], dest_size[1], bypp, bypp * dest_size[0], bipp, bipp * dest_size[0]]);
    
    // floating point location in source
    const dest_to_source_ratio = new Float32Array([source_colorspace[0] / dest_size[0], source_colorspace[1] / dest_size[1]]);

    if (dest_to_source_ratio[0] < 1 && dest_to_source_ratio[1] < 1) {
        return resize_ta_colorspace_24bipp$subpixel$inline(ta_source, source_colorspace, dest_size, opt_ta_dest);

    } else if (dest_to_source_ratio[0] > 1 && dest_to_source_ratio[1] > 1) {
        return resize_ta_colorspace_24bipp$superpixel(ta_source, source_colorspace, dest_size, opt_ta_dest);
    } else {
        return resize_ta_colorspace_24bipp$general(ta_source, source_colorspace, dest_size, opt_ta_dest);
    }
}



const resize_ta_colorspace = (ta_source, source_colorspace, dest_size, opt_ta_dest) => {

    //const [width, height, bypp, bypr, bipp, bipr] = source_colorspace;
    //const bypp = source_colorspace[2];
    const bipp = source_colorspace[4];

    if (bipp === 1) {
        console.trace(); throw 'NYI';
    } else if (bipp === 8) {
        console.trace(); throw 'NYI';
    } else if (bipp === 24) {
        return resize_ta_colorspace_24bipp(ta_source, source_colorspace, dest_size, opt_ta_dest);
        //return read_merged_vfpx_24bipp(ta_source, colorspace, vfpx)
    } else if (bipp === 32) {
        console.trace(); throw 'NYI';
    } else {
        console.trace();
        throw 'unsupported bipp: ' + bipp;
    }
}


//const {resize_ta_colorspace, resize_ta_colorspace_24bipp} = transform;


module.exports = {
    resize_ta_colorspace: resize_ta_colorspace,
    resize_ta_colorspace_24bipp: resize_ta_colorspace_24bipp
}


