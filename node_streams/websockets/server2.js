var http = require('http')
var fs = require('fs')

var http_server = http.createServer((req, res) => {
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
http_server.listen(5000)

const WebSocket = require('ws');
// const redis = require('redis');

// Configuration: adapt to your environment
// const REDIS_SERVER = "redis://localhost:6379";
// const WEB_SOCKET_PORT = 3000;

// Connect to Redis and subscribe to "app:notifications" channel
// var redisClient = redis.createClient(REDIS_SERVER);
// redisClient.subscribe('app:notifications');

// Create & Start the WebSocket server
const wss = new WebSocket.Server({ port: 5001 });

// Register event for client connection
wss.on('connection', (ws) => {
    ws.send("Test 1\n");
    ws.send("Test 2\n");
    ws.send("Test 3\n");
    ws.on('message', function incoming(data) {
        console.log(data);
    });
    // redisClient.on('message', function (channel, message) {
    //     console.log(message);
    //     ws.send(message);
    // })
});



console.log("WSOCK Server is listening on localhost:5000");
console.log("WebSocket server started at ws://locahost:5001");