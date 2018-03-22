// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

import * as Curry                                           from "../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as GetComponentGameObjectService$Wonderjs          from "../../../record/gameObject/GetComponentGameObjectService.js";
import * as CloneComponentGameObjectMainService$Wonderjs    from "./CloneComponentGameObjectMainService.js";
import * as BatchAddGameObjectComponentMainService$Wonderjs from "./BatchAddGameObjectComponentMainService.js";

function _clone(param, param$1, state) {
  var component = param[1];
  if (component) {
    var match = Curry._3(param$1[0], component[0], param[2], state);
    return Curry._3(param$1[1], param[3], match[1], state);
  } else {
    return state;
  }
}

function _cloneComponentExceptTransform(param, isShareMaterial, state) {
  var gameObjectRecord = state[/* gameObjectRecord */10];
  var clonedGameObjectArr = param[2];
  var countRangeArr = param[1];
  var uid = param[0];
  return _clone(/* tuple */[
              uid,
              GetComponentGameObjectService$Wonderjs.getPointLightComponent(uid, gameObjectRecord),
              countRangeArr,
              clonedGameObjectArr
            ], /* tuple */[
              CloneComponentGameObjectMainService$Wonderjs.clonePointLightComponent,
              BatchAddGameObjectComponentMainService$Wonderjs.batchAddPointLightComponentForClone
            ], _clone(/* tuple */[
                  uid,
                  GetComponentGameObjectService$Wonderjs.getDirectionLightComponent(uid, gameObjectRecord),
                  countRangeArr,
                  clonedGameObjectArr
                ], /* tuple */[
                  CloneComponentGameObjectMainService$Wonderjs.cloneDirectionLightComponent,
                  BatchAddGameObjectComponentMainService$Wonderjs.batchAddDirectionLightComponentForClone
                ], _clone(/* tuple */[
                      uid,
                      GetComponentGameObjectService$Wonderjs.getAmbientLightComponent(uid, gameObjectRecord),
                      countRangeArr,
                      clonedGameObjectArr
                    ], /* tuple */[
                      CloneComponentGameObjectMainService$Wonderjs.cloneAmbientLightComponent,
                      BatchAddGameObjectComponentMainService$Wonderjs.batchAddAmbientLightComponentForClone
                    ], _clone(/* tuple */[
                          uid,
                          GetComponentGameObjectService$Wonderjs.getLightMaterialComponent(uid, gameObjectRecord),
                          countRangeArr,
                          clonedGameObjectArr
                        ], /* tuple */[
                          (function (param, param$1, param$2) {
                              return CloneComponentGameObjectMainService$Wonderjs.cloneLightMaterialComponent(isShareMaterial, param, param$1, param$2);
                            }),
                          (function (param, param$1, param$2) {
                              return BatchAddGameObjectComponentMainService$Wonderjs.batchAddLightMaterialComponentForClone(isShareMaterial, param, param$1, param$2);
                            })
                        ], _clone(/* tuple */[
                              uid,
                              GetComponentGameObjectService$Wonderjs.getBasicMaterialComponent(uid, gameObjectRecord),
                              countRangeArr,
                              clonedGameObjectArr
                            ], /* tuple */[
                              (function (param, param$1, param$2) {
                                  return CloneComponentGameObjectMainService$Wonderjs.cloneBasicMaterialComponent(isShareMaterial, param, param$1, param$2);
                                }),
                              (function (param, param$1, param$2) {
                                  return BatchAddGameObjectComponentMainService$Wonderjs.batchAddBasicMaterialComponentForClone(isShareMaterial, param, param$1, param$2);
                                })
                            ], _clone(/* tuple */[
                                  uid,
                                  GetComponentGameObjectService$Wonderjs.getBoxGeometryComponent(uid, gameObjectRecord),
                                  countRangeArr,
                                  clonedGameObjectArr
                                ], /* tuple */[
                                  CloneComponentGameObjectMainService$Wonderjs.cloneBoxGeometryComponent,
                                  BatchAddGameObjectComponentMainService$Wonderjs.batchAddBoxGeometryComponentForClone
                                ], _clone(/* tuple */[
                                      uid,
                                      GetComponentGameObjectService$Wonderjs.getMeshRendererComponent(uid, gameObjectRecord),
                                      countRangeArr,
                                      clonedGameObjectArr
                                    ], /* tuple */[
                                      CloneComponentGameObjectMainService$Wonderjs.cloneMeshRendererComponent,
                                      BatchAddGameObjectComponentMainService$Wonderjs.batchAddMeshRendererComponentForClone
                                    ], _clone(/* tuple */[
                                          uid,
                                          GetComponentGameObjectService$Wonderjs.getPerspectiveCameraProjectionComponent(uid, gameObjectRecord),
                                          countRangeArr,
                                          clonedGameObjectArr
                                        ], /* tuple */[
                                          CloneComponentGameObjectMainService$Wonderjs.clonePerspectiveCameraProjectionComponent,
                                          BatchAddGameObjectComponentMainService$Wonderjs.batchAddPerspectiveCameraProjectionComponentForClone
                                        ], _clone(/* tuple */[
                                              uid,
                                              GetComponentGameObjectService$Wonderjs.getBasicCameraViewComponent(uid, gameObjectRecord),
                                              countRangeArr,
                                              clonedGameObjectArr
                                            ], /* tuple */[
                                              CloneComponentGameObjectMainService$Wonderjs.cloneBasicCameraViewComponent,
                                              BatchAddGameObjectComponentMainService$Wonderjs.batchAddBasicCameraViewComponentForClone
                                            ], state)))))))));
}

function clone(param, isShareMaterial, state) {
  var clonedGameObjectArr = param[3];
  var countRangeArr = param[2];
  var match = CloneComponentGameObjectMainService$Wonderjs.cloneTransformComponent(param[1], countRangeArr, _cloneComponentExceptTransform(/* tuple */[
            param[0],
            countRangeArr,
            clonedGameObjectArr
          ], isShareMaterial, state));
  var clonedTransformArr = match[1];
  return /* tuple */[
          BatchAddGameObjectComponentMainService$Wonderjs.batchAddTransformComponentForClone(clonedGameObjectArr, clonedTransformArr, match[0]),
          clonedTransformArr
        ];
}

export {
  _clone                         ,
  _cloneComponentExceptTransform ,
  clone                          ,
  
}
/* GetComponentGameObjectService-Wonderjs Not a pure module */