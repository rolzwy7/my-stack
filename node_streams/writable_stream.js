var fs = require('fs')

var w = fs.createWriteStream('dump.txt')
w.on('finish', function() {
    console.log("Stream finished");
});
w.write("Hi! from writable stream\n");
w.end()