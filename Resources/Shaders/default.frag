#version 450 core
#define MAX_DIR_LIGHTS 8 
#define MAX_PT_LIGHTS 32

//Structs
struct DirectionalLight {
    vec3 direction;
    vec4 color;
    float intensity;
};

struct PointLight {
    vec3 position;
    vec4 color;
    float intensity;
};

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
    int numDirLights;
    DirectionalLight directionalLights[MAX_DIR_LIGHTS];
    int numPtLights;
    PointLight pointLights[MAX_PT_LIGHTS];
} lightData;

uniform vec3 viewPosition;

//Inputs
in vec2 texCoord;
in vec3 normal;
in vec3 fragmentPosition;

//Outputs
out vec4 fragColor;

vec4 GetBaseColor(){
    return material.base_diffuse + texture(material.texture_diffuse1, texCoord);
}

vec4 CalcAmbient(){
    return 
        lightData.ambientStrength * lightData.ambientColor * GetBaseColor();
}

vec4 CalcDirectionalLight(DirectionalLight light){
    vec3 lightDir   = normalize(-light.direction);
    vec3 viewDir    = normalize(viewPosition - fragmentPosition);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diffuseIntensity = max(dot(normal, lightDir), 0.0);

    float specularIntensity = pow(max(dot(normal, halfwayDir), 0.0), 128);

    vec4 diffuse = 
        light.color * diffuseIntensity * GetBaseColor();

    vec4 specular = vec4(1,1,1,1) * specularIntensity;

    return diffuse + specular;
}

vec4 CalcPointLight(PointLight light){
    vec3 lightDir   = normalize(light.position - fragmentPosition);
    vec3 viewDir    = normalize(viewPosition - fragmentPosition);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diffuseIntensity = max(dot(normal, lightDir), 0.0);

    float specularIntensity = pow(max(dot(normal, halfwayDir), 0.0), 128);

    vec4 diffuse = 
        light.color * diffuseIntensity * GetBaseColor();

    vec4 specular = vec4(1,1,1,1) * specularIntensity;

    return diffuse + specular;
}

void main(){
    vec4 color = CalcAmbient();

    for(int i = 0; i < lightData.numDirLights; i++){
        color += CalcDirectionalLight(lightData.directionalLights[i]);
    } 

    fragColor = color;
}