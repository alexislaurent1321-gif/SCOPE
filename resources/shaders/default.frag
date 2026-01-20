
#version 330 core
#define MAX_SIZE 16

// Material structure
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
}; 
uniform Material material;

// Directional light structure
struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform int nbDirLights;
uniform DirLight dirLights[MAX_SIZE];

// Point light structure
struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform int nbPointLights;
uniform PointLight pointLights[MAX_SIZE];


//--------------------------------------
// Inputs / Outputs
//--------------------------------------

uniform bool illuminated; // Whether lighting is enabled
uniform vec3 viewPos; // Camera position

// vertex datas
in vec3 normal;     
in vec3 position; 
in vec2 UV;

out vec4 fragColor; 


// Function prototypes
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir); 



//--------------------------------------
// Main function
//--------------------------------------

void main()
{
    if(!illuminated) {
        fragColor = texture(material.diffuse, UV);
        return;
    }
    
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - position);

    vec3 result = vec3(0.);

    for(int i = 0; i < nbDirLights; i++)
        result += calcDirLight(dirLights[i], norm, viewDir);

    for(int i = 0; i < nbPointLights; i++)
        result += calcPointLight(pointLights[i], norm, position, viewDir);       

    fragColor = vec4(result, 1.0);
}



//--------------------------------------
// Light calculations
//--------------------------------------  

// Calculates the color when using a directional light.
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
   
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, UV));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, UV));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));
    
    return (ambient + diffuse + specular);
} 


// Calculates the color when using a point light.
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
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
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, UV));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, UV));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
} 