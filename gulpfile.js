var gulp = require("gulp");
var gulpSync = require("gulp-sync")(gulp);

require("./build/gulp_task/clean/clean");
require("./build/gulp_task/compress/compress");
require("./build/gulp_task/compile/parseTsconfigFilesGlob");
require("./build/gulp_task/compile/removeTsconfigFiles");
require("./build/gulp_task/compile/compileTs");
require("./build/gulp_task/compile/combineInnerLib");
require("./build/gulp_task/compile/addBanner");

require("./build/gulp_task/createDefinitionFile/index");
require("./build/gulp_task/createInnerFile/index");

require("./build/gulp_task/test/test");

gulp.task("build", gulpSync.sync(["clean", "createInnerFile", "parseTsconfigFilesGlob", "compileDTS", "compileTs", "compileTsDebug", "combineInnerLib", "compress", "addBanner", "removeTsconfigFiles"]));


gulp.task("testAll", gulpSync.sync(["build", "testSingleRunByKarma", "renderTest"]));


var tsFilePaths = ["src/*.ts", "src/**/*.ts"];
var glslFilePaths = ["src/renderer/shader/chunk/glsl/**/*.glsl", "src/lib/**/*.glsl"];

gulp.task("watch", function(){
    var totalPaths = tsFilePaths.concat(glslFilePaths);

    gulp.watch(totalPaths, gulpSync.sync(["createShaderChunk", "parseTsconfigFilesGlob", "compileTsDebug", "removeTsconfigFiles"]));
});


