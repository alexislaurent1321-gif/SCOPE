#version 330 core
layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec3 vertNormal;
layout (location = 2) in vec2 vertUV;

out vec3 position; 
out vec3 normal;

out vec2 UV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(vertPosition, 1.0);
    position = vec3(model * vec4(vertPosition, 1.0));
    normal = mat3(transpose(inverse(model))) * vertNormal;
    UV = vertUV;  
} 