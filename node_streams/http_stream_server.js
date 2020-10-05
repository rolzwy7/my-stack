var http = require('http')
var fs = require('fs')
var PORT = 5000
var server = http.createServer((req, res)=>{
    if(req.method === "POST") {
        console.log("Server got POST");
        req.pipe(process.stdout)
        req.once('end', ()=>{
            res.end('ok\n')
        })
    }
    if(req.method === "GET") {
        console.log("Server got GET");
        res.setHeader('content-type', 'text/plain')
        fs.createReadStream('file.txt').pipe(res)
    }
})

server.listen(PORT)
console.log(`[*] HTTP server listening at 127.0.0.1:${PORT}`)