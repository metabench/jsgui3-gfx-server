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

const load_save = async() => {
    const pb = await Pixel_Buffer.load('../source_images/Erte Ale Volcano.jpg');

    //(path, size_or_opts)
    //const pb = await Server_Pixel_Buffer.load('./source_images/Swiss Alps.jpg');
    //await pb.save('./source_images/saved-Swiss Alps.jpg');

    await gfx.save_pixel_buffer('./output/test_load_save-erte_ale.jpg', pb, {
        format: 'jpg'
    });
    //pb.color_whole(124);
    //await gfx.save_pixel_buffer('./source_images/Swiss Alps.jpg', pb, {
    //    format: 'jpg'
    //});
}

if (require.main === module) {
    (async() => {
        // Set file paths here...?

        let res = await load_save();
        console.log('res load_save', res);
    })();
}
