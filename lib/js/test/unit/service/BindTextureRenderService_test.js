'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Sinon = require("wonder-bs-sinon/lib/js/src/sinon.js");
var Sinon$1 = require("sinon");
var Wonder_jest = require("wonder-bs-jest/lib/js/src/wonder_jest.js");
var TestTool$Wonderjs = require("../../tool/TestTool.js");
var CreateStateMainService$Wonderjs = require("../../../src/service/state/main/state/CreateStateMainService.js");
var BindTextureRenderService$Wonderjs = require("../../../src/service/state/render/texture/BindTextureRenderService.js");

describe("BindTextureRenderService", (function () {
        var sandbox = Sinon.getSandboxDefaultVal(/* () */0);
        var state = /* record */[/* contents */CreateStateMainService$Wonderjs.createState(/* () */0)];
        beforeEach((function () {
                sandbox[0] = Sinon$1.sandbox.create();
                state[0] = TestTool$Wonderjs.init(sandbox, undefined, undefined, /* () */0);
                return /* () */0;
              }));
        afterEach((function () {
                return Curry._1(Sinon.restoreSandbox, sandbox[0]);
              }));
        describe("contract check", (function () {
                return Wonder_jest.test("unit should >= 0", (function () {
                              return Wonder_jest.Expect[/* toThrowMessage */20]("unit should >= 0", Wonder_jest.Expect[/* expect */0]((function () {
                                                return BindTextureRenderService$Wonderjs.bind(1, -1, 0, 2);
                                              })));
                            }));
              }));
        return /* () */0;
      }));

/*  Not a pure module */
