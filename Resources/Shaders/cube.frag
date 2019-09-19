#version 450 core
//Uniforms
uniform float desiredColor;
uniform sampler2D suppliedTexture;
//Inputs
in vec2 texCoord;

//Outputs

void main(){
    //gl_FragColor = vec4(desiredColor, 0.0f, 0.0f, 1.0f);
    gl_FragColor = texture(suppliedTexture, texCoord);
}