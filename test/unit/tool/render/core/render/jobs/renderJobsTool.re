let initWithRenderConfig = () =>
  TestTool.initWithRenderConfig(
    ~bufferConfig=
      Js.Nullable.return({
        "transformDataBufferCount": Js.Nullable.undefined,
        "geometryPointDataBufferCount": Js.Nullable.return(1000),
        "basicMaterialDataBufferCount": Js.Nullable.undefined
      }),
    ~renderConfig=
      RenderConfigTool.buildRenderConfig(
        ~renderSetting={|
    {
    "platform": "pc",
    "browser": [
        {
            "name": "chrome",
            "version": "newest"
        },
        {
            "name": "firefox",
            "version": "newest"
        }
    ],
    "backend": {
        "name": "webgl1"
    },
    "init_pipeline": "simple_basic_render",
    "render_pipeline": "simple_basic_render"
}
|},
        ()
      ),
    ()
  );

let prepareGameObject = (sandbox, state) => {
  open GameObject;
  open BasicMaterial;
  open BoxGeometry;
  open MeshRenderer;
  open Sinon;
  let (state, material) = createBasicMaterial(state);
  let (state, geometry) = BoxGeometryTool.createBoxGeometry(state);
  let (state, meshRenderer) = createMeshRenderer(state);
  let (state, gameObject) = state |> createGameObject;
  let state =
    state
    |> addGameObjectMaterialComponent(gameObject, material)
    |> addGameObjectGeometryComponent(gameObject, geometry)
    |> addGameObjectMeshRendererComponent(gameObject, meshRenderer);
  (state, gameObject, geometry, material, meshRenderer)
};

let initSystemAndRender = (state: StateDataType.state) =>
  state |> DirectorTool.initSystem |> WebGLRenderSystem.init;

let updateSystem = (state: StateDataType.state) => state |> DirectorTool.updateSystem;

let setFakeGl = (sandbox, state: StateDataType.state) =>
  state |> FakeGlTool.setFakeGl(FakeGlTool.buildFakeGl(~sandbox, ()));

let buildConfigData = (~flags=[||], ~shader="", ()) => (flags, shader);