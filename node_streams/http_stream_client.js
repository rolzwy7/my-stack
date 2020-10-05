var http = require('http')

method = process.argv[2]
console.log("Method :", method);
var req = http.request({method: "GET", host: 'localhost', url: '/', port:5000}, (res)=>{
    console.log(res.statusCode);
    res.pipe(process.stdout)
})

if(method === "GET") {
    req.end()
} else {
    req.end('Hello\n')
}