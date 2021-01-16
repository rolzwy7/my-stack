var http = require('http')
var through = require('through2')
var fs = require('fs')

var server = http.createServer((req, res) => {
    if (req.method == "GET") {
        if (req.url == "/") {
            res.setHeader('content-type', 'text/html')
            fs.createReadStream("./public/index.html").pipe(res)
        }
        if (req.url == "/bundle.js") {
            res.setHeader('content-type', 'text/javascript')
            fs.createReadStream("./public/bundle.js").pipe(res)
        }
    }
});
server.listen(5000)

var wsock = require('websocket-stream')
wsock.createServer({ server: server }, function (stream) {
    stream.pipe(loud()).pipe(stream)
})


function loud() {
    return through(function (buf, enc, next) {
        next(null, buf.toString().toUpperCase())
    })
}

// setInterval(() => {
// }, 1000);

console.log("WSOCK Server is listening on localhost:5000");