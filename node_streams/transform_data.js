var fs = require('fs')
var through = require('through2')
fs.createReadStream(process.argv[2])
    .pipe(toupper())
    .pipe(process.stdout)

function toupper() {
    return through((buf, enc, next)=>{
        next(null, buf.toString().toUpperCase()+"_THROUGH_ADD");
    })
}
