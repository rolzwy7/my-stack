var net = require('net')
var PORT = 5005
net.createServer((stream)=>{
    stream
        .pipe(net.connect(5000, 'localhost'))
        .pipe(stream)
}).listen(PORT)
console.log(`[*] Proxy is listening on 127.0.0.1:${PORT}`);