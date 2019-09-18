#version 450 core
//Uniforms

//Inputs
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texPos;

//Outputs
out vec2 texCoord;

void main(){
    gl_Position = vec4(aPos, 1.0);
}