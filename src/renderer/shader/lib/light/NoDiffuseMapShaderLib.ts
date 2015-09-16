/// <reference path="../../../../definitions.d.ts"/>
module dy{
    export class NoDiffuseMapShaderLib extends ShaderLib{
        private static _instance = null;

        public static getInstance() {
            if (this._instance === null) {
                this._instance = new this();
                this._instance.initWhenCreate();
            }
            return this._instance;
        }

        public sendShaderVariables(program: Program, quadCmd:QuadCommand, material:LightMaterial){
            program.sendUniformData("u_diffuse", VariableType.FLOAT_3, material.color.toVector3());
        }

        protected setShaderDefinition(){
            this.addUniformVariable(["u_diffuse"]);

            this.fsSourceHead = ShaderChunk.noDiffuseMap_head_fragment;
        }
    }
}

