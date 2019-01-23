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
const {file_type} = fnlfs;
// options
// max size
// reorient

const formats = require('jsgui3-gfx-formats');
const {
    jpeg
} = formats;
//const  = jpeg.decoder;

const sharp_decode_jpeg = async (buf_jpeg, max_size) => {
    console.log('sharp_decode_jpeg');

    // 

    // .ensureAlpha()

    // Have alpha channel to keep compatibility for the moment.

    // could have a resize / max size capability

    // Number of channels in the image.
    // bytes_per_pixel in pb.

    let r;

    if (max_size) {
        r = await sharp(buf_jpeg).withMetadata().resize(max_size[0], max_size[1], {
            fit: 'inside'
        }).ensureAlpha().raw().toBuffer({
            resolveWithObject: true
        });
    } else {
        r = await sharp(buf_jpeg).withMetadata().ensureAlpha().raw().toBuffer({
            resolveWithObject: true
        });
    }
    
    // size, data
    console.log('r', r);
    console.log('r.data.length', r.data.length);

    [r.width, r.height] = [r.info.width, r.info.height];
    //let buf_r     = 

    console.log('r ', r);

    return r;

}

const decode_jpeg = gfx.decode_jpeg = jpeg.decode;

gfx.export_pixel_buffer = (pb, opts = {
    format: 'jpg',
    quality: 85
}, cb) => prom_or_cb(async (solve, jettison) => {
    const s = sharp(pb.buffer, {
        raw: {
            width: pb.size[0],
            height: pb.size[1],
            channels: pb.bytes_per_pixel
        }
    });
    const quality = opts.quality || 85;
    let {
        format
    } = opts;

    //console.log('format', format);
    format = format.toLowerCase();

    if (format === 'jpg' || format === 'jpeg') {
        let jpeg = await s.jpeg(opts);

        let obuf = await jpeg.toBuffer();
        console.log('obuf', obuf);

        solve(obuf);
    } else if (format === 'png') {
        let png = await s.png(opts);

        let obuf = await png.toBuffer();
        console.log('obuf', obuf);

        solve(obuf);
    } else {
        jettison(new Error('Unsupported format'));
    }








})

/*
gfx._old_export_pixel_buffer = (pb, opts = {
    format: 'jpg'
}, cb) => prom_or_cb(async (solve, jettison) => {
    // save to disk

    // Could try using raw sharp data.

    let format = opts.format.toLowerCase();
    console.log('pb', pb);
    //console.log('data', data);
    let buf2;
    if (pb.bytes_per_pixel === 4) {
        buf2 = Buffer.alloc(pb.buffer.length);
        pb.buffer.copy(buf2);
        const l = buf2.length;
        let i;
        for (i = 0; i < l; i += 4) {
            //buf_res.writeInt32BE(buf_res.readInt32LE(i), i);
            buf2.writeInt32BE(buf2.readInt32LE(i), i);
        }
    } else {
        console.log('pb.bytes_per_pixel', pb.bytes_per_pixel);

        if (pb.bytes_per_pixel === 1) {
            buf2 = Buffer.alloc(pb.buffer.length * 4);
            const l = pb.buffer.length;
            let i;
            for (i = 0; i < l; i += 1) {
                //buf_res.writeInt32BE(buf_res.readInt32LE(i), i);
                buf2.writeUInt8(255, i * 4);
                buf2.writeUInt8(pb.buffer.readUInt8(i), i * 4 + 1);
                buf2.writeUInt8(pb.buffer.readUInt8(i), i * 4 + 2);
                buf2.writeUInt8(pb.buffer.readUInt8(i), i * 4 + 3);
            }
        }
        //throw 'NYI';
    }
    //(() => {

    //})();
    //console.log('buf2.length', buf2.length);
    let bmpData = {
        data: buf2,
        width: pb.size[0],
        height: pb.size[1]
    }
    var bitmap = bmp.encode(bmpData);

    //console.log('bitmap.data', bitmap.data);

    if (format === 'bmp') {
        console.log('format', format);
        solve(bitmap.data);
    }
    //console.log('bitmap', bitmap);
    // Create the gm object using a bitmap

    if (format === 'jpg') {

        let f_call = gm(bitmap.data).quality(95);

        //if (max_size) {
        //    f_call = f_call.resize(max_size[0], max_size[1]);
        //}
        //if (reorient) {
        //    f_call = f_call.autoOrient();
        //}

        f_call.toBuffer(format, function (err, buf_jpg) {

            solve(buf_jpg);
            // Then with the bitmap buffer, we can load it into bmp

            /*
            const bmp_data = bmp.decode(buf_bmp);
            const {
                width,
                height,
                data
            } = bmp_data;
            if (reorient) {
                //this.autoOrient();
            }
            if (max_size) {
                //this.resize(max_size[0], max_size[1]);
                //[width, height] = max_size;
            }
            // Then create the RGBA pixel buffer.
            //  Could do 32 bit read-writes

            console.log('w, h', [width, height]);
            console.log('data.length', data.length);

            // Could do an LE -> BE swap.
            //var bmp_data = bmp.decode(bmpBuffer);

            //let buf_res = Buffer.alloc(l);
            //console.log('buf_res', buf_res);
            console.log('data', data);
            const l = data.length;
            let i;
            for (i = 0; i < l; i += 4) {
                //buf_res.writeInt32BE(buf_res.readInt32LE(i), i);
                data.writeInt32BE(data.readInt32LE(i), i);
            }
            console.log('data', data);
            let pb = new Pixel_Buffer({
                'buffer': data,
                'size': [width, height]
            });
            * /
        });
    }
    // get it as a bitmap, using bmp-js, then put it into gm, then save as jpeg
}, cb);
*/

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

gfx.load_pixel_buffer = (buf, opts, cb) => prom_or_cb(async (solve, jettison) => {

    // could we detect the format?
    //  metadata reader that can identify an image's format.






    console.log('load_pixel_buffer');
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
    let decoded;
    if (max_size) {
        decoded = await sharp_decode_jpeg(buf, max_size);
    } else {
        decoded = await sharp_decode_jpeg(buf);
    }

    //console.log('decoded', decoded);

    let pb = new Pixel_Buffer({
        'buffer': decoded.data,
        'size': [decoded.width, decoded.height]
    });

    // then if there is a max size, resize that pixel buffer to within that size.



    solve(pb);



}, cb);


if (require.main === module) {
    (async () => {
        const fnlfs = require('fnlfs');
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

        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Swiss Alps.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Swiss Alps.jpg')
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Swiss_Alps_003_(6815891681).jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Swiss_Alps_003_(6815891681).jpg')
        await test_file('I:\\code\\js\\jsgui3-gfx-server\\source_images\\Ultimate-Travel-Guide-to-London.jpg', 'I:\\code\\js\\jsgui3-gfx-server\\source_images\\edges-Ultimate-Travel-Guide-to-London.jpg');


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

gfx.sharp_decode_jpeg = sharp_decode_jpeg;

module.exports = gfx;