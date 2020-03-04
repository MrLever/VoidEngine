#version 450 core
#define MAX_DIR_LIGHTS 8 
#define MAX_PT_LIGHTS 32

//Uniforms
uniform struct Material {
    vec4 base_diffuse;
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
} material;

struct DirectionalLight {
    vec3 direction;
    vec4 color;
    float intensity;
};

struct PointLight {
    vec3 location;
    vec4 color;
    float intensity;
};

uniform struct LightingData {
    float ambientStrength;
    vec4 ambientColor;
    int numDirLights;
    DirectionalLight directionalLights[MAX_DIR_LIGHTS];
} lightData;

//Inputs
in vec2 texCoord;
in vec3 normal;

//Outputs
out vec4 fragColor;

vec4 CalcAmbient(){
    return 
        lightData.ambientStrength * lightData.ambientColor * 
        (material.base_diffuse + texture(material.texture_diffuse1, texCoord));
}

vec4 CalcDirectionalLight(DirectionalLight light){
    vec3 lightDir = normalize(-light.direction);
    float diffuseIntensity = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float specularIntensity = 0 /*pow(max(dot(viewDir, reflectDir), 0.0), 10)*/;

    vec4 diffuse = 
        light.color * diffuseIntensity * material.base_diffuse;

    //vec4 specular = vec4(1,1,1,1) * specularIntensity;

    return diffuse /*+ specular*/;
}

void main(){
    vec4 color = CalcAmbient();

    for(int i = 0; i < lightData.numDirLights; i++){
        color += CalcDirectionalLight(lightData.directionalLights[i]);
    }    

    fragColor = color;
}