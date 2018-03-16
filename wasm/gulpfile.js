var gulp = require('gulp');
var ghPages = require('gulp-gh-pages');
var del = require('del');

gulp.task('clean', function(){
    return del(['./dist']);
})
gulp.task('pack', function() {
    return gulp.src([
        "./index.html",
        "./custom.css",
        "./index.js",
        "./opencc_bindings.*"
    ]).pipe(gulp.dest('./dist'))
});

gulp.task('deploy', gulp.series(
    'clean',
    'pack',
    function() {
    return gulp.src("./dist/**/*")
        .pipe(ghPages({
            branch: 'gh-pages',
            remoteUrl: 'https://github.com/ztl8702/OpenCC-wasm.git'
        }))
    })
);