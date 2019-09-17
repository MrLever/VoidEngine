#version 450 core
//Uniforms
uniform float desiredColor;

//Inputs

//Outputs
out vec4 FragColor;

void main(){
    //FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    FragColor = vec4(desiredColor, 0.0f, 0.0f, 1.0f);
}