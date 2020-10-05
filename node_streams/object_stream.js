var through = require('through2')
var size = 0
process.stdin
    .pipe(through({objectMode: true}, write_1))
    .pipe(through({objectMode: true}, write_2, end))


function write_1(buf, enc, next) {
    next(null, {length: buf.length, total: size += buf.length})
}

function write_2(obj, enc, next) {
    console.log('obj=', obj);
    next()
}


function end() {
    console.log("end of pipe");
}