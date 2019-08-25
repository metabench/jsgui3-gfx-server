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

const { PerformanceObserver, performance } = require('perf_hooks');

const obs = new PerformanceObserver((items) => {
  console.log(items.getEntries()[0].duration, 'ms');
  performance.clearMarks();
});
obs.observe({ entryTypes: ['measure'] });

// options
// max size
// reorient

const formats = require('jsgui3-gfx-formats');
const {
    jpeg
} = formats;

const gfx = require('../gfx-server');
const {Pixel_Buffer} = gfx;
//console.log('Pixel_Buffer', Pixel_Buffer);

// create the pixel buffer.
// save it in the output folder.

// Nice, it actually works.


// Greyscale image


const fn_eg_create1 = async() => {
    let pb = new Pixel_Buffer({
        bytes_per_pixel: 1,
        size: [8000, 6000]
    });
    console.log('Object.keys(pb)', Object.keys(pb));
    // pb.meta
    //  will give easier set of info. no buffer.
    // get meta.
    // oext to define an enumerable read only property.
    //  ero?
    performance.mark('A');
    //pb.color_whole(124);
    pb.compiled_color_whole(64);
    // Can try an n-api color_whole
    //  may be worth overriding it?
    //  having a wrapper function? integrating c++ within my function calling mechanism?
    //   side-by-side comparisions would be useful for benchmarking.
    // Not totally overriding makes sense for the moment.

    //pb.compiled_color_whole(124);
    //pb.compiled.color_whole

    performance.mark('B');
    performance.measure('A to B', 'A', 'B');
    await gfx.save_pixel_buffer('./output/create1_a-dark_grey.jpg', pb, {
        format: 'jpg'
    });
    return 'Greyscale dark grey (64) jpg created and saved.'
}

// Blue image
//  Giving the color as an array will likely be more convenient than a typed array in many cases.


const fn_eg_create2 = async() => {
    let pb = new Pixel_Buffer({
        bytes_per_pixel: 3,
        size: [8000, 6000]
    });
    console.log('Object.keys(pb)', Object.keys(pb));
    // pb.meta
    //  will give easier set of info. no buffer.
    // get meta.
    // oext to define an enumerable read only property.
    //  ero?
    performance.mark('A');
    //pb.color_whole(124);
    pb.compiled_color_whole([100, 150, 250]);
    // Can try an n-api color_whole
    //  may be worth overriding it?
    //  having a wrapper function? integrating c++ within my function calling mechanism?
    //   side-by-side comparisions would be useful for benchmarking.
    // Not totally overriding makes sense for the moment.

    //pb.compiled_color_whole(124);
    //pb.compiled.color_whole
    performance.mark('B');
    performance.measure('A to B', 'A', 'B');
    await gfx.save_pixel_buffer('./output/create1_b-rgb_blue.jpg', pb, {
        format: 'jpg'
    });
    return 'Blue (3 bytes per px) jpg created and saved.'
}

const fn_eg_create3 = async() => {
    let pb = new Pixel_Buffer({
        bytes_per_pixel: 4,
        size: [8000, 6000]
    });
    //console.log('Object.keys(pb)', Object.keys(pb));
    // pb.meta
    //  will give easier set of info. no buffer.
    // get meta.
    // oext to define an enumerable read only property.
    //  ero?
    performance.mark('A');
    //pb.color_whole(124);
    pb.compiled_color_whole([100, 150, 250, 64]);
    // Can try an n-api color_whole
    //  may be worth overriding it?
    //  having a wrapper function? integrating c++ within my function calling mechanism?
    //   side-by-side comparisions would be useful for benchmarking.
    // Not totally overriding makes sense for the moment.

    //pb.compiled_color_whole(124);
    //pb.compiled.color_whole
    performance.mark('B');
    performance.measure('A to B', 'A', 'B');
    await gfx.save_pixel_buffer('./output/create1_c-rgba_blue.png', pb, {
        format: 'png'
    });
    return 'Translucent Blue (4 bytes per px) png created and saved.'
    // And it worked! :)
}

// could have a function it runs and returns results...?

if (require.main === module) {
    (async() => {
        // Set file paths here...?

        let res = await fn_eg_create1();
        console.log('res fn_eg_create1', res);

        res = await fn_eg_create2();
        console.log('res fn_eg_create2', res);

        res = await fn_eg_create3();
        console.log('res fn_eg_create3', res);
    })();
}
