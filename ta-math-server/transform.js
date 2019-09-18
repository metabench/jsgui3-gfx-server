

const {transform} = require('jsgui3-gfx').ta_math;

const addon = require('bindings')('addon.node')
//console.log('addon', addon);

//throw 'stop';
//const {resize_ta_colorspace_24bipp} = addon;

const resize_ta_colorspace_24bipp = addon.resize_ta_colorspace_24bipp$superpixel$inline$locals$inline;

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


