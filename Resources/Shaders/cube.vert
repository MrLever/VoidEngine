#version 450 core
precision highp float;

//Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Inputs
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texPos;

//Outputs
out vec2 texCoord;

void main(){
    texCoord = texPos;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}