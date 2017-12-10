open UidUtils;

open ComponentType;

open StateDataType;

open GameObjectType;

let init = (state: StateDataType.state) =>
  state |> CameraControllerSystem.init |> GeometrySystem.init;

/*  */
let initDataFromState = (state: StateDataType.state) =>
  state |> TransformSystem.initData |> MaterialAdmin.initData |> GeometrySystem.initData;

let update = (elapsed: float, state: StateDataType.state) =>
  state |> CameraControllerSystem.update;

/* todo dispose instance */
let hasSourceInstanceComponent = GameObjectComponentCommon.hasSourceInstanceComponent;

let getSourceInstanceComponent = GameObjectComponentCommon.getSourceInstanceComponent;

let addSourceInstanceComponent = GameObjectComponentCommon.addSourceInstanceComponent;

let hasCameraControllerComponent = GameObjectComponentCommon.hasCameraControllerComponent;

let getCameraControllerComponent = GameObjectComponentCommon.getCameraControllerComponent;

let addCameraControllerComponent = GameObjectComponentCommon.addCameraControllerComponent;

let disposeCameraControllerComponent = (uid: int, component: component, state: StateDataType.state) =>
  GameObjectComponentCommon.disposeCameraControllerComponent(
    uid,
    component,
    CameraControllerSystem.handleDisposeComponent,
    state
  );

let hasTransformComponent = GameObjectComponentCommon.hasTransformComponent;

let getTransformComponent = GameObjectComponentCommon.getTransformComponent;

let unsafeGetTransformComponent = GameObjectComponentCommon.unsafeGetTransformComponent;

let addTransformComponent = GameObjectComponentCommon.addTransformComponent;

let disposeTransformComponent = (uid: int, component: component, state: StateDataType.state) =>
  GameObjectComponentCommon.disposeTransformComponent(
    uid,
    component,
    TransformSystem.handleDisposeComponent,
    state
  );

let hasGeometryComponent = GameObjectComponentCommon.hasGeometryComponent;

let getGeometryComponent = GameObjectComponentCommon.getGeometryComponent;

let unsafeGetGeometryComponent = GameObjectComponentCommon.unsafeGetGeometryComponent;

let addGeometryComponent = GameObjectComponentCommon.addGeometryComponent;

let disposeGeometryComponent = (uid: int, component: component, state: StateDataType.state) =>
  GameObjectComponentCommon.disposeGeometryComponent(
    uid,
    component,
    GeometrySystem.handleDisposeComponent,
    state
  );

let hasMeshRendererComponent = GameObjectComponentCommon.hasMeshRendererComponent;

let getMeshRendererComponent = GameObjectComponentCommon.getMeshRendererComponent;

let addMeshRendererComponent = GameObjectComponentCommon.addMeshRendererComponent;

let disposeMeshRendererComponent = (uid: int, component: component, state: StateDataType.state) =>
  GameObjectComponentCommon.disposeMeshRendererComponent(
    uid,
    component,
    MeshRendererSystem.handleDisposeComponent,
    state
  );

let hasMaterialComponent = GameObjectComponentCommon.hasMaterialComponent;

let getMaterialComponent = GameObjectComponentCommon.getMaterialComponent;

let unsafeGetMaterialComponent = GameObjectComponentCommon.unsafeGetMaterialComponent;

let addMaterialComponent = (uid: int, component: component, state: StateDataType.state) =>
  GameObjectComponentCommon.addMaterialComponent(
    uid,
    component,
    MaterialSystem.handleAddComponent,
    state
  );

let disposeMaterialComponent = (uid: int, component: component, state: StateDataType.state) =>
  GameObjectComponentCommon.disposeMaterialComponent(
    uid,
    component,
    MaterialSystem.handleDisposeComponent,
    state
  );

let create = (state: StateDataType.state) => {
  let (state, uid) = GameObjectCreateCommon.create(state);
  let (state, transform) = TransformSystem.create(state);
  (addTransformComponent(uid, transform, state), uid)
};

let dispose = (uid: int, state: StateDataType.state) => {
  let {disposeCount, disposedUidMap} as data = GameObjectStateCommon.getGameObjectData(state);
  data.disposeCount = succ(disposeCount);
  disposedUidMap |> WonderCommonlib.SparseMapSystem.set(uid, true) |> ignore;
  let state =
    switch (getTransformComponent(uid, state)) {
    | Some(transform) => disposeTransformComponent(uid, transform, state)
    | None => state
    };
  let state =
    switch (getMeshRendererComponent(uid, state)) {
    | Some(meshRenderer) => disposeMeshRendererComponent(uid, meshRenderer, state)
    | None => state
    };
  let state =
    switch (getMaterialComponent(uid, state)) {
    | Some(material) => disposeMaterialComponent(uid, material, state)
    | None => state
    };
  let state =
    switch (getGeometryComponent(uid, state)) {
    | Some(geometry) => disposeGeometryComponent(uid, geometry, state)
    | None => state
    };
  let state =
    switch (getCameraControllerComponent(uid, state)) {
    | Some(cameraController) => disposeCameraControllerComponent(uid, cameraController, state)
    | None => state
    };
  if (MemoryUtils.isDisposeTooMany(data.disposeCount, state)) {
    data.disposeCount = 0;
    CpuMemorySystem.reAllocateGameObject(state)
  } else {
    state
  }
};

let batchDispose = (uidArray: array(int), state: StateDataType.state) => {
  let {disposeCount, disposedUidMap} as data = GameObjectStateCommon.getGameObjectData(state);
  uidArray
  |> WonderCommonlib.ArraySystem.forEach(
       [@bs] ((uid) => disposedUidMap |> WonderCommonlib.SparseMapSystem.set(uid, true) |> ignore)
     );
  data.disposeCount = disposeCount + (uidArray |> Js.Array.length);
  let state =
    state
    |> GameObjectComponentCommon.batchGetMeshRendererComponent(uidArray)
    |> GameObjectComponentCommon.batchDisposeComponent(
         disposedUidMap,
         state,
         MeshRendererSystem.handleBatchDisposeComponent
       )
    |> GameObjectComponentCommon.batchGetTransformComponent(uidArray)
    |> GameObjectComponentCommon.batchDisposeComponent(
         disposedUidMap,
         state,
         TransformSystem.handleBatchDisposeComponent
       )
    |> GameObjectComponentCommon.batchGetMaterialComponent(uidArray)
    |> GameObjectComponentCommon.batchDisposeComponent(
         disposedUidMap,
         state,
         MaterialSystem.handleBatchDisposeComponent
       )
    |> GameObjectComponentCommon.batchGetGeometryComponent(uidArray)
    |> GameObjectComponentCommon.batchDisposeComponent(
         disposedUidMap,
         state,
         GeometrySystem.handleBatchDisposeComponent
       )
    |> GameObjectComponentCommon.batchGetCameraControllerComponent(uidArray)
    |> GameObjectComponentCommon.batchDisposeComponent(
         disposedUidMap,
         state,
         CameraControllerSystem.handleBatchDisposeComponent
       );
  if (MemoryUtils.isDisposeTooMany(data.disposeCount, state)) {
    data.disposeCount = 0;
    CpuMemorySystem.reAllocateGameObject(state)
  } else {
    state
  }
};

/* {
                   cloneChildren:true,
                   cloneGeometry:true
                   ////shareGeometry:false
   } */
let clone = (uid: int, count: int, state: StateDataType.state) => {
  let countRangeArr = ArraySystem.range(0, count - 1);
  let totalClonedGameObjectArr = [||];
  let rec _clone =
          (
            uid: int,
            transform,
            countRangeArr,
            clonedParentTransformArr,
            totalClonedGameObjectArr,
            state: StateDataType.state
          ) => {
    let clonedGameObjectArr = [||];
    let state =
      countRangeArr
      |> ArraySystem.reduceState(
           [@bs]
           (
             (state, _) => {
               let (state, gameObject) = GameObjectCreateCommon.create(state);
               clonedGameObjectArr |> Js.Array.push(gameObject) |> ignore;
               state
             }
           ),
           state
         );
    totalClonedGameObjectArr |> Js.Array.push(clonedGameObjectArr) |> ignore;
    let state =
      switch (getMeshRendererComponent(uid, state)) {
      | Some(meshRenderer) =>
        let (state, clonedMeshRendererArr) =
          GameObjectComponentCommon.cloneMeshRendererComponent(meshRenderer, countRangeArr, state);
        state
        |> GameObjectComponentCommon.batchAddMeshRendererComponentForClone(
             clonedGameObjectArr,
             clonedMeshRendererArr
           )
      | None => state
      };
    let state =
      switch (getGeometryComponent(uid, state)) {
      | Some(geometry) =>
        let (state, clonedGeometryArr) =
          GameObjectComponentCommon.cloneGeometryComponent(geometry, countRangeArr, state);
        state
        |> GameObjectComponentCommon.batchAddGeometryComponentForClone(
             clonedGameObjectArr,
             clonedGeometryArr
           )
      | None => state
      };
    let state =
      switch (getMaterialComponent(uid, state)) {
      | Some(meshRenderer) =>
        let (state, clonedMaterialArr) =
          GameObjectComponentCommon.cloneMaterialComponent(
            meshRenderer,
            countRangeArr,
            MaterialSystem.handleCloneComponent,
            state
          );
        state
        |> GameObjectComponentCommon.batchAddMaterialComponentForClone(
             clonedGameObjectArr,
             clonedMaterialArr,
             MaterialSystem.handleAddComponent
           )
      | None => state
      };
    let state =
      switch (getCameraControllerComponent(uid, state)) {
      | Some(cameraController) =>
        let (state, clonedCameraControllerArr) =
          GameObjectComponentCommon.cloneCameraControllerComponent(
            cameraController,
            countRangeArr,
            state
          );
        state
        |> GameObjectComponentCommon.batchAddCameraControllerComponentForClone(
             clonedGameObjectArr,
             clonedCameraControllerArr
           )
      | None => state
      };
    let (state, clonedTransformArr) =
      GameObjectComponentCommon.cloneTransformComponent(transform, countRangeArr, state);
    /* todo optimize compare: add in each loop? */
    /* let state = */
    state
    |> GameObjectComponentCommon.batchAddTransformComponentForClone(
         clonedGameObjectArr,
         clonedTransformArr
       );
    clonedParentTransformArr
    |> ArraySystem.reduceOneParami(
         [@bs]
         (
           (transformData, clonedParentTransform, i) =>
             transformData
             |> TransformSystem.setParentNotMarkDirty(
                  Some(clonedParentTransform),
                  clonedTransformArr[i]
                )
         ),
         TransformSystem.getData(state)
       )
    |> TransformSystem.unsafeGetChildren(transform)
    |> ArraySystem.reduceState(
         [@bs]
         (
           (state, childTransform) =>
             state
             |> _clone(
                  state |> TransformSystem.getGameObject(childTransform) |> Js.Option.getExn,
                  childTransform,
                  countRangeArr,
                  clonedTransformArr,
                  totalClonedGameObjectArr
                )
         ),
         state
       );
    state
  };
  (
    _clone(
      uid,
      getTransformComponent(uid, state) |> Js.Option.getExn,
      countRangeArr,
      [||],
      totalClonedGameObjectArr,
      state
    ),
    totalClonedGameObjectArr
  )
};

let isAlive = (uid: int, state: StateDataType.state) => {
  let {transformMap, disposedUidMap} = GameObjectStateCommon.getGameObjectData(state);
  disposedUidMap |> WonderCommonlib.SparseMapSystem.has(uid) ?
    false : transformMap |> WonderCommonlib.SparseMapSystem.has(uid) ? true : false
};

let initGameObject = (uid: int, state: StateDataType.state) => {
  let state =
    switch (getGeometryComponent(uid, state)) {
    | Some(geometry) =>
      GeometrySystem.handleInitComponent(
        geometry,
        GeometrySystem.getMappedIndex(geometry, GeometrySystem.getMappedIndexMap(state)),
        state
      )
    | None => state
    };
  let state =
    switch (getMaterialComponent(uid, state)) {
    | Some(material) =>
      MaterialSystem.handleInitComponent([@bs] DeviceManagerSystem.getGl(state), material, state)
    | None => state
    };
  state
};

let initData = () => {
  uid: 0,
  disposeCount: 0,
  disposedUidMap: WonderCommonlib.SparseMapSystem.createEmpty(),
  aliveUidArray: WonderCommonlib.ArraySystem.createEmpty(),
  transformMap: WonderCommonlib.SparseMapSystem.createEmpty(),
  cameraControllerMap: WonderCommonlib.SparseMapSystem.createEmpty(),
  geometryMap: WonderCommonlib.SparseMapSystem.createEmpty(),
  meshRendererMap: WonderCommonlib.SparseMapSystem.createEmpty(),
  materialMap: WonderCommonlib.SparseMapSystem.createEmpty(),
  sourceInstanceMap: WonderCommonlib.SparseMapSystem.createEmpty()
};