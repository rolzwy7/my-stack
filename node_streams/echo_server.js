var net = require('net')
var PORT = 5000
net.createServer((stream) => {
    stream.pipe(stream);
}).listen(PORT)
console.log(`[*] Echo server started at 127.0.0.1:${PORT}`);