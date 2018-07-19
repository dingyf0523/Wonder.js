let convertToGameObjectIndexData =
    (
      {scenes, nodes, meshes, cameras, materials, extras, extensions}: GLTFType.gltf,
    )
    : WDType.gameObjectIndices => {
  let transformGameObjectIndexData =
    ConvertComponentIndexDataSystem.convertToTransformGameObjectIndexData(
      nodes,
    );
  {
    transformGameObjectIndexData,
    childrenTransformIndexData:
      ConvertChildrenDataSystem.convertToChildrenTransformIndexData(
        transformGameObjectIndexData,
        nodes,
      ),
    basicCameraViewGameObjectIndexData:
      ConvertComponentIndexDataSystem.convertToBasicCameraViewGameObjectIndexData(
        nodes,
      ),
    perspectiveCameraProjectionGameObjectIndexData:
      ConvertComponentIndexDataSystem.convertToPerspectiveCameraProjectionGameObjectIndexData(
        nodes,
        cameras,
      ),
    arcballCameraControllerGameObjectIndexData:
      ConvertComponentIndexDataSystem.convertToArcballCameraControllerGameObjectIndexData(
        nodes,
      ),
    lightMaterialGameObjectIndexData:
      ConvertComponentIndexDataSystem.convertToLightMaterialGameObjectIndexData(
        nodes,
        meshes,
        materials,
      ),
    customGeometryGameObjectIndexData:
      ConvertComponentIndexDataSystem.convertToGeometryGameObjectIndexData(
        nodes,
      ),
    directionLightGameObjectIndexData:
      ConvertComponentIndexDataSystem.convertToLightGameObjectIndexData(
        "directional",
        nodes,
        extensions,
      ),
    pointLightGameObjectIndexData:
      ConvertComponentIndexDataSystem.convertToLightGameObjectIndexData(
        "point",
        nodes,
        extensions,
      ),
  };
};