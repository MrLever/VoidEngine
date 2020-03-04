#version 450 core
//Uniforms
uniform struct Material {
    vec4 base_diffuse;
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
} material;

uniform struct LightingData {
    float ambientStrength;
    vec4 ambientColor;
} lightData;

//Inputs
in vec2 texCoord;

//Outputs
out vec4 fragColor;

void main(){
    //Calculate diffuse color
    //vec4 diffuse = texture(material.texture_diffuse1, texCoord);
    //vec4 diffuse = vec4(0.5, 0.5, 0.5, 1);
    vec4 diffuse = 
        material.base_diffuse + 
        texture(material.texture_diffuse1, texCoord);;

    fragColor = diffuse * lightData.ambientStrength * lightData.ambientColor;
}