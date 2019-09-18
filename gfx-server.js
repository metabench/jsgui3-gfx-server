//const gm = require('gm');
// That would mean server side only
// gfx is both for client and server.

// Convolutions on the server.
// Wrap gm
//  Or be able to use it quickly.

// GM_Wrapper
//  Can output a PixelBuffer.
//  Input a pixel buffer too.

// Carry out GM processes on pixel buffer.
//  Would go via bitmap.

//const gm = require('gm');

//var addon = require('bindings')('addon.node')
//console.log('addon', addon);


const convert_svg_to_png = require('convert-svg-to-png').convert;
const sharp = require('sharp');

// clone it...?
//  not using a direct reference?
//   don't want to replace the Pixel_Buffer of what's loaded.



const gfx_core = require('jsgui3-gfx');
const gfx = {};
Object.assign(gfx, gfx_core);


// Means it does not upgrade / override the existing non-server of the module.


// gfx.override?
//  // gfx override the pixel buffer ta math.



const Pixel_Buffer = gfx.Pixel_Buffer;
var bmp = require("bmp-js");
const {
    prom_or_cb
} = require('fnl');

const ta_math = require('./ta-math-server');
//ta_math.override('transform', 'resize_ta_colorspace_24bipp$superpixel', addon.resize_ta_colorspace_24bipp$superpixel$inline$locals$inline);
const {resize_ta_colorspace} = ta_math;

// could stream it.
const fnlfs = require('fnlfs');
const {
    file_type
} = fnlfs;

const {
    extname
} = require('path');

// options
// max size
// reorient

const formats = require('jsgui3-gfx-formats');
const {
    jpeg
} = formats;

class Server_Pixel_Buffer extends Pixel_Buffer {
    constructor(spec) {
        super(spec);
        // just one color object given?
        //  can better handle poly in C++ anyway.
        this.compiled = {
            color_whole: this.compiled_color_whole
        }
    }

    

    new_resized(size) {
        //const source_ta = this.ta;
        //const dest_size = new Int16Array(size);
        const dest = new this.constructor({
            size: size,
            bits_per_pixel: this.bipp
        });
        resize_ta_colorspace(this.ta, this.ta_colorspace, dest.size, dest.ta);
        return dest;
    }

    // and use the accelerated versions of some things...



    // Don't need the width in this case.
    //  In many cases the width is important.

    /*

    compiled_color_whole(color) {
        // Maybe go back to an Args Info function.
        //  Could get that right before wrapping other functions.
        //console.log('[this.ta, this.bits_per_pixel, this.size[0], color]', [this.ta, this.bits_per_pixel, this.size[0], color]);
        //console.log('compiled_color_whole');
        //console.log('this.size', this.size);
        //console.log('JS: color', color);

        const ta_sample = new Uint8Array(32);
        addon.color_whole(this.ta, this.bits_per_pixel, this.size[0], color);
        //console.log('post addon compiled_color_whole');
        //console.log('this.bits_per_pixel', this.bits_per_pixel);
        //addon.color_whole(ta_sample, this.bits_per_pixel, this.size[0], color);
    }

    */
    // Some other functions soon.
    //  Convolution, blurring, sharpening

    // Creating a color image as well.
    //  including rgba.




    toString() {
        return 'Server_Pixel_Buffer';
    }
    async save(path) {
        let ext = extname(path).toLowerCase();
        //console.log('ext', ext);
        if (ext === '.jpeg') ext = '.jpg';
        await gfx.save_pixel_buffer(path, this, {
            format: ext
        });
    }
    async export (opts = {
        format: 'png'
    }) {
        let res = await gfx.export_pixel_buffer(this, opts);
        return res;
    }
}



Server_Pixel_Buffer.load = async (path, size_or_opts) => {
    // determine the format from the path
    let opts;
    if (Array.isArray(size_or_opts)) {
        opts = {
            max_size: size_or_opts,
            reorient: true
        }
    } else {
        opts = size_or_opts || {};
    }
    //console.log('opts', opts);
    const pb = gfx.load_pixel_buffer(path, opts);
    return pb;
}

gfx.Pixel_Buffer = Server_Pixel_Buffer;

const sharp_decode = async (buf, opts = {}) => {
    //console.log('sharp_decode_jpeg');
    const {
        max_size,
        reorient
    } = opts;
    // 
    // .ensureAlpha()
    // Have alpha channel to keep compatibility for the moment.

    // could have a resize / max size capability
    // Number of channels in the image.
    // bytes_per_pixel in pb.

    //console.log('opts', opts);
    let r;

    // Don't want to ensure alpha channel!!!
    //  Look into options.

    if (max_size) {
        //console.log('max_size', max_size);
        if (reorient) {
            r = await sharp(buf).withMetadata().resize(max_size[0], max_size[1], {
                fit: 'inside'
            //}).rotate().ensureAlpha().raw().toBuffer({
            }).rotate().raw().toBuffer({
                resolveWithObject: true
            });
        } else {
            r = await sharp(buf).withMetadata().resize(max_size[0], max_size[1], {
                fit: 'inside'
            //}).ensureAlpha().raw().toBuffer({
            }).raw().toBuffer({
                resolveWithObject: true
            });
        }
    } else {
        if (reorient) {
            r = await sharp(buf).withMetadata().rotate().raw().toBuffer({
                //r = await sharp(buf).withMetadata().ensureAlpha().rotate().raw().toBuffer({
                resolveWithObject: true
            });
        } else {
            r = await sharp(buf).withMetadata().raw().toBuffer({
            //r = await sharp(buf).withMetadata().ensureAlpha().raw().toBuffer({
                resolveWithObject: true
            });
        }
    }
    // size, data
    //console.log('r', r);
    //console.log('r.data.length', r.data.length);
    [r.width, r.height] = [r.info.width, r.info.height];
    //let buf_r     = 
    //console.log('r ', r);
    //console.log('r.info', r.info);

    return r;
}

const decode_jpeg = gfx.decode_jpeg = jpeg.decode;

gfx.export_pixel_buffer = (pb, opts = {
    format: 'jpg',
    quality: 85
}, cb) => prom_or_cb(async (solve, jettison) => {
    // would need to convert a typed array to a buffer

    //console.trace();
    //console.log('pb', pb);
    //console.log('opts', opts);

    //console.log('pb.size', pb.size);
    //console.log('pb.bytes_per_pixel', pb.bytes_per_pixel);

    let buf;
    if (pb.buffer instanceof Uint8Array || pb.buffer instanceof Uint8ClampedArray) {
        buf = Buffer.from(pb.buffer.buffer);
    } else {
        buf = pb.buffer;
    }

    //console.log('***** buf', buf);

    let o_sharp = {
        raw: {
            width: Math.round(pb.size[0]),
            height: Math.round(pb.size[1]),
            channels: pb.bytes_per_pixel
        }
    }
    //console.log('o_sharp', o_sharp);
    //console.log('o_sharp', o_sharp);
    //console.log('pb.bytes_per_pixel', pb.bytes_per_pixel);
    const s = sharp(buf,  o_sharp);
    const quality = opts.quality || 85;
    let {
        format
    } = opts;
    
    opts.format = format = format.toLowerCase().split('.').join('');
    //console.log('1) format', format);

    if (format === 'jpg' || format === 'jpeg') {
        let jpeg = await s.jpeg(opts);
        let obuf = await jpeg.toBuffer();
        //console.log('obuf', obuf);
        solve(obuf);
    } else if (format === 'png') {
        //console.log('pre get png')
        //console.log('opts', opts);
        let png = await s.png(opts);
        //console.log('png', png);
        //console.log('pre png output');
        //console.trace();
        let obuf = await png.toBuffer();
        //console.log('obuf', obuf);
        solve(obuf);
    }
    /* else if (format === 'bmp') {
        let bmp = await s.bmp(opts);
        let obuf = await bmp.toBuffer();
        //console.log('obuf', obuf);

        solve(obuf);
    } */
    else {
        jettison(new Error('Unsupported format'));
    }
});

gfx.save_pixel_buffer = (path, pb, opts = {
    format: 'jpg'
}, cb) => prom_or_cb(async (solve, jettison) => {
    // save to disk
    // 'JPG'
    // get it as a bitmap, using bmp-js, then put it into gm, then save as jpeg
    //  Exporting would need to keep the alpha channel where possible.
    //   Would need to save it in a different format.
    //   Raise an error when trying to save image with an alpha channel as jpeg?


    let buf = await gfx.export_pixel_buffer(pb, opts);
    //console.log('buf', buf);
    //console.log('path', path);
    let res = await fnlfs.save(path, buf);
    solve(res);
}, cb)

gfx.load_pixel_buffer = (buf, opts = {}, cb) => prom_or_cb(async (solve, jettison) => {
    // could we detect the format?


    let path;
    let format = 'jpg';

    // jpeg we want to load into pb at 24bipp.
    let default_bipp = 32;


    if (typeof buf === 'string') {
        path = buf;
        //console.log('path', path);

        let s_path = path.split('.');
        let ext = s_path[s_path.length - 1];
        format = ext;

        buf = await fnlfs.load(path);
    }

    //  metadata reader that can identify an image's format.

    //console.log('load_pixel_buffer');

    /*
    const {
        max_size
    } = opts;
    let reorient = opts.reorient || opts.reOrient || opts.autoOrient || opts.auto_orient || opts.autoorient;

    // Does not work with SVGs.
    //console.log('buf', buf);

    // Could use sharp for this.

    // Depends on the format.

    // sharp_decode_jpeg
    //console.log('pre sharp load jpeg');

    // decode with a maximum size?
    let decoded, o = {};

    if (max_size) {
        o.max_size = max_size;

    } else {
        //decoded = await sharp_decode_jpeg(buf);
    }
    */

    //console.trace();

    //console.log('*** buf', buf);
    //console.log('2) format', format);

    // 

    if (format === 'png') {
        decoded = await sharp_decode(buf, opts);
        //console.log('decoded', decoded);
        default_bipp = 32;
    }

    if (format === 'jpg' || format === 'jpeg') {
        opts.channels = 3;
        decoded = await sharp_decode(buf, opts);
        // but decoded is at 32bipp.
        //  dont want that.

        // convert_ta_32bipp_to_ta_24bipp

        // see how many channels it has.
        // and run convert_ta_32bipp_to_ta_24bipp

        // but the data is a buffer.
        //  a quick way of getting that into a uint8array?
        //  maybe best to read bytes?
        //   or read it 32bit chunk by 32 bit chunk, and zero out the alpha component.
        //    then bit shift it to get the rgb stored in a 32 byte value...
        //     then write it to the appropriate place in the buffer...?
        
        // may be simplest to read and write byte by byte.

        // convert_buf_32bipp_to_ta_24bipp
        //  removes the alpha channel.

        // maybe will use some gfx util.
        //  not server-specific.
        //   still will have node buffer equivalents on the client for the moment I assume.




    






        console.log('decoded', decoded);
        default_bipp = 24;
    }
    if (format === 'svg') {

        // read the svg size.
        console.log('opts', opts);
        console.trace();
        //throw 'stop';

        // Not so ure about limiting the size here

        let size = [1024, 1024];

        decoded = await sharp_decode(await convert_svg_to_png(buf, {
            width: size[0],
            height: size[1]
        }));
        default_bipp = 32;
        //console.log('svg decoded', decoded);
        //throw 'stop';
    }

    //console.log('decoded', decoded);

    // Need to choose number of bits per pixel?
    //  Or have a default?
    //  Load a sensible default depending on the file type.

    let pb = new gfx.Pixel_Buffer({
        'buffer': decoded.data,
        'size': [decoded.width, decoded.height],
        'bits_per_pixel': default_bipp
    });

    //console.log('pb', pb);
    // then if there is a max size, resize that pixel buffer to within that size.
    //console.log('pb.size', pb.size);
    //throw 'stop';
    solve(pb);

}, cb);


const load_decode = async path => {
    //let path;
    let format = 'jpg';
    let decoded;
    if (typeof buf === 'string') {
        path = buf;
        console.log('path', path);
        let s_path = path.split('.');
        let ext = s_path[s_path.length - 1];
        format = ext;
        buf = await fnlfs.load(path);
    }
    if (format === 'png') {
        decoded = await sharp_decode(buf, opts);
        //console.log('decoded', decoded);
    }
    if (format === 'jpg' || format === 'jpeg') {
        decoded = await sharp_decode(buf, opts);
        //console.log('decoded', decoded);
    }
    return decoded;
}

gfx.load_decode = load_decode;

// encode_save
// And does not use a Pixel_Buffer.

// Image data can be represented well in Tensors.
//  Then it will be possible to do convolutions

// Possibly gfx server will be upgraded to use tensor images and convolutions.

gfx.sharp_decode = sharp_decode;

//Server_Pixel_Buffer.override('ta_math', ta_math);



module.exports = gfx;




if (require.main === module) {
    (async () => {
        const fnlfs = require('fnlfs');

        // Specific examples will be much better.
        //  color_whole - very basic C++ algo, wrapped with napi.




        let test_create = async () => {

            /*

            let pb = new Server_Pixel_Buffer({
                bytes_per_pixel: 1,
                size: [800, 600]
            })
            pb.color_whole(124);
            await gfx.save_pixel_buffer('./test_create.jpg', pb, {
                format: 'jpg'
            });

            */

            let pb = new Server_Pixel_Buffer({
                bytes_per_pixel: 3,
                size: [800, 600]
            })

            //pb.compiled_color_whole(new Uint8ClampedArray([0, 0, 0]));
            //pb.compiled_color_whole(new Uint8ClampedArray([10, 10, 10]));


            //pb.compiled_color_whole(new Uint8ClampedArray([2, 8, 32]));
            //pb.compiled_color_whole(new Uint8ClampedArray([100, 150, 225]));
            pb.color_whole(new Uint8ClampedArray([100, 150, 225]));
            await gfx.save_pixel_buffer('./test_create_24bipp.jpg', pb, {
                format: 'jpg'
            });
        }
        await test_create();


        // trace image
        // Load it into a pixel buffer.
        //  Run a convolution on it.
        // process file.

        // Average difference between a pixel and its 

        // Average difference between a pixel and its neighbours
        //  That's a possible way to measure contrasts.


        /*


        let gauss_7_4 = gfx.convolution_kernels.get_gauss(7, 4);
        let gauss_3_2 = gfx.convolution_kernels.get_gauss(3, 2);

        const n_blurs = (pb, n) => {
            for (let c = 0; c < n; c++) {
                pb = pb.apply_square_convolution(gauss_3_2);
            }
            return pb;
            //return 
        }




        let test_file = async (input_path, output_path) => {
            //let buf = await fnlfs.load(input_path);
            let pb_conv = async () => {
                let buf = await fnlfs.load(input_path);

                let pb = await gfx.load_pixel_buffer(buf, {
                    format: 'jpg',
                    max_size: [1024, 1024],
                    //max_size: [8, 8],
                    reorient: true
                });
                //console.log('pb', pb);

                //throw 'stop';


                let lap_gauss_5 = gfx.convolution_kernels.lap_gauss_5;
                //let edges_convolution = gfx.convolution_kernels.edge;
                //console.log('edges_convolution', edges_convolution);

                let pb_lg = n_blurs(pb, 2).apply_square_convolution(lap_gauss_5);
                / *
                pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
                let edges_pb = pb_gblurred.apply_square_convolution(edges_convolution);
                * /

                let gs = pb_lg.to_8bit_greyscale();

                await gfx.save_pixel_buffer(output_path, gs, {
                    format: 'jpg'
                });
            }
            await pb_conv();

            let test2 = async () => {
                let buf = await fnlfs.load(input_path);
                console.log('buf.length', buf.length);

                let log_time = (fn => {
                    let t = Date.now();
                    let res = fn();
                    let d = Date.now() - t;
                    console.log('time taken: ' + d);
                    return res;
                })

                let decoded = log_time(() => decode_jpeg(buf));
                console.log('decoded', decoded);



            }
            //await test2();

            



            // Could try blurring in combination with edge detection.

            //let pb_gblurred = pb.apply_square_convolution(gfx.convolution_kernels.gauss_blur_5_5);
            //let pb_gblurred = pb.apply_square_convolution(gauss_3_2);
            //pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
            //pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
            //pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
            //pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
            //pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
            //pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);


            let test1 = async () => {



                //let pb_gblurred = pb.apply_square_convolution(gauss_3_2);
                //pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
                let pb_lg = n_blurs(pb, 5).apply_square_convolution(lap_gauss_5);
                / *
                pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
                let edges_pb = pb_gblurred.apply_square_convolution(edges_convolution);
                * /

                let gs = pb_lg.to_8bit_greyscale();

                //console.log('edges_pb', edges_pb);
                await gfx.save_pixel_buffer(output_path, gs, {
                    format: 'jpg'
                });
            }
            //await test1();


        }

        */

        /*
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Erte Ale Volcano.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Erte Ale Volcano.jpg')
        //await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Swiss Alps.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Swiss Alps.jpg')
        //await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Swiss_Alps_003_(6815891681).jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Swiss_Alps_003_(6815891681).jpg')
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\city-918523_1920.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-city-918523_1920.jpg');
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\val-trupchen-in-the-swiss-alps.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-val-trupchen-in-the-swiss-alps.jpg');
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\io.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-io.jpg');
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\beach-blur-boardwalk-132037.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-beach-blur-boardwalk-132037.jpg');
        
        */

        /*

        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Swiss Alps.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Swiss Alps.jpg')
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Swiss_Alps_003_(6815891681).jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Swiss_Alps_003_(6815891681).jpg')
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Ultimate-Travel-Guide-to-London.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Ultimate-Travel-Guide-to-London.jpg');

        */

        // Lets try a few operations on pixel buffers
        //  A few painting / rendering operations.

        // Can make some simpler tests to do with creating and counting regions.


        // Ultimate-Travel-Guide-to-London

        // beach-blur-boardwalk-132037.jpg


        // val-trupchen-in-the-swiss-alps.jpg

        // Swiss_Alps_003_(6815891681).jpg
        // Swiss Alps.jpg

        /*
        let traced;

        let trace_all = async () => {
            let res_traces = await trace.full_trace_walk('../../source_files/raw/', '../../source_files/ready/');
            console.log('res_traces', res_traces);
        }
        await trace_all();
        */

    })();

} else {
    //console.log('required as a module');
}


