const cookieSession = require('express-session')
var cookieParser = require('cookie-parser')
const express = require('express')

const fs = require('fs')
const path = require('path');
const { start } = require('repl');

const app = express()
const video_path = path.join('videos', 'video2.mp4')
PORT = 80

// app.use(cookieSession({
//     name: 'stream_session',
//     secret: 'secret_string',
//     domain: '127.0.0.1',
//     httpOnly: true,
//     maxAge: 24 * 60 * 60 * 1000, // 24h
//     resave: true,
//     sameSite: 'lax',
//     saveUninitialized: true,
//     // genid: function(req) {
//     //     return genuuid() // use UUIDs for session IDs
//     // },
//   }))
// app.use(cookieParser())


function getChunks(range, file_size) {
    const parts = range.replace(/bytes=/, '').split('-')
    const chunkStart = parseInt(parts[0], 10)
    const chunkEnd = parts[1] ? parseInt(parts[1], 10) : file_size - 1;
    const chunkSize = (chunkEnd - chunkStart) + 1
    return {chunkStart, chunkEnd, chunkSize}
}

function getVideoResponse(req, res, l_video_path) {
    const file_stat = fs.statSync(l_video_path)
    const file_size = file_stat.size
    const content_range = req.headers.range
    if(content_range) {
        console.log("Requested :", content_range);
        const {chunkStart, chunkEnd, chunkSize} = getChunks(content_range, file_size);
        const file = fs.createReadStream(l_video_path, { start: chunkStart, end: chunkEnd })
        res.writeHead(206, {
            'Accept-Ranges': `bytes`,
            'Content-Range': `bytes ${chunkStart}-${chunkEnd}/${file_size}`,
            'Content-Length': `${chunkSize}`,
            'Content-Type': `video/mp4`,
        })
        file.pipe(res);
    } else {
        const file = fs.createReadStream('stream_error.txt')
        res.writeHead(500, {
            'Content-Type': 'text/plain'
        })
        file.pipe(res);
    }
    // } else {
    //     res.writeHead(200, {
    //         'Content-Length': `${file_size}`,
    //         'Content-Type': 'video/mp4',
    //     })
    //     fs.createReadStream(video_path).pipe(res)
    // }
}

app.get('/', function (req, res) {
    // req.session.views++
    const file = fs.createReadStream('index.html')
    res.writeHead(200, {
        'Content-Type': 'text/html'
    });
    file.pipe(res);
})

app.get('/player', function (req, res) {
    const file = fs.createReadStream('player.html')
    res.writeHead(200, {
        'Content-Type': 'text/html'
    });
    file.pipe(res);
})

app.get('/stream', function (req, res) {
    // console.dir(req.headers)
    // console.dir(req.cookies.stream_session)
    // console.dir(req.query)
    // console.dir(req.query.token)
    // console.dir(req.query.unknown)
    // console.dir(req.session)
    // if(req.query.token === undefined || req.query.token !== "token123" ) {
    //     const file = fs.createReadStream('access_denied.txt')
    //     res.writeHead(500, {
    //         'Content-Type': 'text/plain'
    //     })
    //     file.pipe(res);
    // } else {
    //     getVideoResponse(req, res, video_path)
    // }
    getVideoResponse(req, res, video_path)
})

 
app.listen(PORT)
console.log(`[*] Server started at localhost:${PORT}`);