var path        = require('path');
var express     = require("express");
var body_parser = require('body-parser');
var app         = express();
app.engine('ejs', require('express-ejs-extend'));
app.use('/static', express.static("dist/static",
    {
      dotfiles: 'ignore',
      etag: false,
      extensions: ['png', 'jpg', 'pdf', 'doc', 'docx', 'mp4', 'webm', 'css', 'js'],
      index: false,
      maxAge: '1d',
      redirect: false,
      setHeaders: function (res, path, stat) {
        res.set('x-timestamp', Date.now())
      }
    }
));
app.use(body_parser.urlencoded({extended: false}));
app.use(body_parser.json());
app.set("view engine", "ejs");
app.set("views", path.join(__dirname, "dist", "views"));
// ADD NEW ROUTES
app.get("/", function(req, res){
    var timestamp = + new Date();
    var TS = "?ts=" + timestamp;
    return res.render("test",{
            "refreshScript":process.env.BROWSER_REFRESH_URL,
            "TS": TS
        });
});
// ADD NEW ROUTES
app.listen(
    8080,
    "127.0.0.1", () => {
    var hostnamePort = "127.0.0.1:8080";
    console.log("[+] Server started at " + hostnamePort);

    if (process.send) {
         process.send({event:'online',url:'http://'+hostnamePort+'/'});
    }

});
