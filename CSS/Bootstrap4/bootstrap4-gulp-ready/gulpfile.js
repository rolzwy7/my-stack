var
    gulp        = require("gulp"),
    gulp_sass   = require("gulp-sass");


gulp.task("copy_bootstrap_scss", function(){
    return gulp
    .src("node_modules/bootstrap/scss/**/*")
    .pipe(
        gulp.dest("src/bootstrap")
    )
});

gulp.task("copy_bootstrap_js", function(){
    return gulp
    .src("node_modules/bootstrap/dist/js/bootstrap.min.js")
    .pipe(
        gulp.dest("dist/static/js/")
    )
});

gulp.task("sass", ["copy_bootstrap_js", "copy_bootstrap_scss"], function () {
    return gulp
        .src("src/scss/main.scss")
        .pipe(
            gulp_sass({
                outputStyle: "compressed", // nested
                precison: 3,
                errLogToConsole: true
            })
        )
        .pipe(
            gulp.dest("dist/static/css")
        );
});

gulp.task("default", ["sass"], function () {
    gulp.watch("src/scss/**/*", ["sass"]);
});
