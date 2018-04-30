// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var SettingTool$Wonderjs            = require("../../../../../tool/service/setting/SettingTool.js");
var MainStateTool$Wonderjs          = require("../../../../../tool/service/state/MainStateTool.js");
var StateDataMain$Wonderjs          = require("../../../../../../src/service/state/main/data/StateDataMain.js");
var WorkerJobTool$Wonderjs          = require("../../../../../tool/service/workerJob/WorkerJobTool.js");
var RenderConfigTool$Wonderjs       = require("../../../../../tool/service/renderConfig/RenderConfigTool.js");
var SettingWorkerTool$Wonderjs      = require("../../../tool/SettingWorkerTool.js");
var IsDebugMainService$Wonderjs     = require("../../../../../../src/service/state/main/state/IsDebugMainService.js");
var CreateStateMainService$Wonderjs = require("../../../../../../src/service/state/main/state/CreateStateMainService.js");

function initWithJobConfig(_, $staropt$star, $staropt$star$1, $staropt$star$2, $staropt$star$3, $staropt$star$4, $staropt$star$5, $staropt$star$6, _$1) {
  var isDebug = $staropt$star ? $staropt$star[0] : "true";
  var canvasId = $staropt$star$1 ? $staropt$star$1[0] : /* None */0;
  var useHardwareInstance = $staropt$star$2 ? $staropt$star$2[0] : "true";
  var context = $staropt$star$3 ? $staropt$star$3[0] : "\n        {\n        \"alpha\": true,\n        \"depth\": true,\n        \"stencil\": false,\n        \"antialias\": true,\n        \"premultiplied_alpha\": true,\n        \"preserve_drawing_buffer\": false\n        }\n               ";
  var workerJobRecord = $staropt$star$4 ? $staropt$star$4[0] : WorkerJobTool$Wonderjs.buildWorkerJobConfig(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0);
  var renderConfigRecord = $staropt$star$5 ? $staropt$star$5[0] : RenderConfigTool$Wonderjs.buildRenderConfig(/* None */0, /* None */0, /* () */0);
  var buffer = $staropt$star$6 ? $staropt$star$6[0] : SettingTool$Wonderjs.buildBufferConfigStr(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0);
  var state = CreateStateMainService$Wonderjs.createState(/* () */0);
  var newrecord = state.slice();
  var init = state[/* workerDetectRecord */35];
  newrecord[/* workerDetectRecord */35] = /* record */[
    /* isSupportSharedArrayBuffer */init[/* isSupportSharedArrayBuffer */0],
    /* isSupportRenderWorkerAndSharedArrayBuffer : true */1
  ];
  return MainStateTool$Wonderjs.setState(RenderConfigTool$Wonderjs.create(renderConfigRecord, WorkerJobTool$Wonderjs.create(workerJobRecord, SettingWorkerTool$Wonderjs.createStateAndSetToStateData(/* Some */[newrecord], /* Some */[isDebug], /* Some */[canvasId], /* Some */[context], /* Some */[useHardwareInstance], /* Some */["true"], /* Some */[buffer], /* () */0))));
}

function openContractCheck() {
  IsDebugMainService$Wonderjs.setIsDebug(StateDataMain$Wonderjs.stateData, /* true */1);
  return /* () */0;
}

function closeContractCheck() {
  IsDebugMainService$Wonderjs.setIsDebug(StateDataMain$Wonderjs.stateData, /* false */0);
  return /* () */0;
}

exports.initWithJobConfig  = initWithJobConfig;
exports.openContractCheck  = openContractCheck;
exports.closeContractCheck = closeContractCheck;
/* SettingTool-Wonderjs Not a pure module */