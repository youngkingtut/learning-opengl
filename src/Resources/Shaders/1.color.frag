#version 330 core

#define NR_POINT_LIGHTS 4

out vec4 FragColor;

uniform vec3 viewPosition;

uniform struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
} material;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} directionalLight;

in vec2 TextureCoordinate;
in vec3 FragPosition;
in vec3 Normal;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPosition - FragPosition);
    vec3 result = vec3(0.0);

    // phase 1: Directional lighting
    result = CalculateDirectionalLight(directionalLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalculatePointLight(pointLights[i], norm, FragPosition, viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TextureCoordinate));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TextureCoordinate));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextureCoordinate));
    return (ambient + diffuse + specular);
}


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TextureCoordinate));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TextureCoordinate));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextureCoordinate));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
