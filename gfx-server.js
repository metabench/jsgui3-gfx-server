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

const convert_svg_to_png = require('convert-svg-to-png').convert;
const sharp = require('sharp');
const gfx = require('jsgui3-gfx');
const {
    Pixel_Buffer
} = gfx;
var bmp = require("bmp-js");
const {
    prom_or_cb
} = require('fnl');

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
//const  = jpeg.decoder;

class Server_Pixel_Buffer extends Pixel_Buffer {
    constructor(spec) {
        super(spec);
    }
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

    console.log('opts', opts);
    let r;

    if (max_size) {
        console.log('max_size', max_size);
        if (reorient) {
            r = await sharp(buf).withMetadata().resize(max_size[0], max_size[1], {
                fit: 'inside'
            }).rotate().ensureAlpha().raw().toBuffer({
                resolveWithObject: true
            });
        } else {
            r = await sharp(buf).withMetadata().resize(max_size[0], max_size[1], {
                fit: 'inside'
            }).ensureAlpha().raw().toBuffer({
                resolveWithObject: true
            });
        }
    } else {
        if (reorient) {
            r = await sharp(buf).withMetadata().ensureAlpha().rotate().raw().toBuffer({
                resolveWithObject: true
            });
        } else {
            r = await sharp(buf).withMetadata().ensureAlpha().raw().toBuffer({
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

    //console.log('pb', pb);
    console.log('opts', opts);

    //console.log('pb.size', pb.size);
    //console.log('pb.bytes_per_pixel', pb.bytes_per_pixel);

    let buf;
    if (pb.buffer instanceof Uint8Array || pb.buffer instanceof Uint8ClampedArray) {
        buf = Buffer.from(pb.buffer.buffer);
    } else {
        buf = pb.buffer;
    }

    console.log('***** buf', buf);

    let o_sharp = {
        raw: {
            width: Math.round(pb.size[0]),
            height: Math.round(pb.size[1]),
            channels: pb.bytes_per_pixel
        }
    }
    console.log('o_sharp', o_sharp);
    //console.log('o_sharp', o_sharp);
    //console.log('pb.bytes_per_pixel', pb.bytes_per_pixel);
    const s = sharp(buf, o_sharp.raw || o_sharp);
    const quality = opts.quality || 85;
    let {
        format
    } = opts;

    
    opts.format = format = format.toLowerCase().split('.').join('');
    console.log('1) format', format);

    if (format === 'jpg' || format === 'jpeg') {
        let jpeg = await s.jpeg(opts);

        let obuf = await jpeg.toBuffer();
        //console.log('obuf', obuf);

        solve(obuf);
    } else if (format === 'png') {
        console.log('pre get png')
        console.log('opts', opts);
        let png = await s.png(opts);
        console.log('png', png);

        console.log('pre png output');
        console.trace();
        let obuf = await png.toBuffer();
        console.log('obuf', obuf);

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


    if (typeof buf === 'string') {
        path = buf;
        console.log('path', path);

        let s_path = path.split('.');
        let ext = s_path[s_path.length - 1];
        format = ext;

        buf = await fnlfs.load(path);
    }

    //  metadata reader that can identify an image's format.

    console.log('load_pixel_buffer');

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

    if (format === 'jpg' || format === 'jpeg') {
        decoded = await sharp_decode(buf, opts);
        //console.log('decoded', decoded);
    }
    if (format === 'svg') {

        // read the svg size.
        console.log('opts', opts);
        console.trace();
        //throw 'stop';

        let size = [1024, 1024];

        decoded = await sharp_decode(await convert_svg_to_png(buf, {
            width: size[0],
            height: size[1]
        }));
        console.log('svg decoded', decoded);

        //throw 'stop';
    }

    let pb = new gfx.Pixel_Buffer({
        'buffer': decoded.data,
        'size': [decoded.width, decoded.height]
    });
    // then if there is a max size, resize that pixel buffer to within that size.
    //console.log('pb.size', pb.size);
    //throw 'stop';
    solve(pb);

}, cb);


if (require.main === module) {
    (async () => {
        const fnlfs = require('fnlfs');




        let test_create = async () => {
            let pb = new Server_Pixel_Buffer({
                bytes_per_pixel: 1,
                size: [800, 600]
            })
            pb.color_whole(124);
            await gfx.save_pixel_buffer('./test_create.jpg', pb, {
                format: 'jpg'
            });


        }
        //await test_create();

        let test_load_save = async () => {

            /*
            let pb = new Pixel_Buffer({
                bytes_per_pixel: 1,
                size: [800, 600]
            })
            */

            const pb = await Server_Pixel_Buffer.load('./source_images/Swiss Alps.jpg');
            await pb.save('./source_images/saved-Swiss Alps.jpg');

            //pb.color_whole(124);
            //await gfx.save_pixel_buffer('./source_images/Swiss Alps.jpg', pb, {
            //    format: 'jpg'
            //});


        }
        await test_load_save();








        // trace image
        // Load it into a pixel buffer.
        //  Run a convolution on it.
        // process file.

        // Average difference between a pixel and its 

        // Average difference between a pixel and its neighbours
        //  That's a possible way to measure contrasts.
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
                /*
                pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
                let edges_pb = pb_gblurred.apply_square_convolution(edges_convolution);
                */

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
                /*
                pb_gblurred = pb_gblurred.apply_square_convolution(gauss_3_2);
                let edges_pb = pb_gblurred.apply_square_convolution(edges_convolution);
                */

                let gs = pb_lg.to_8bit_greyscale();

                //console.log('edges_pb', edges_pb);
                await gfx.save_pixel_buffer(output_path, gs, {
                    format: 'jpg'
                });
            }
            //await test1();


        }

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

gfx.sharp_decode = sharp_decode;

module.exports = gfx;