// #include "material.h"

// void Material::bind(const Shader& shader) const
// {
//     // Upload couleurs (si pas de texture)
//     shader.setVec3("material.diffuseColor", diffuseColor);
//     shader.setVec3("material.specularColor", specularColor);
//     shader.setFloat("material.shininess", shininess);

//     //
//     // --- DIFFUSE TEXTURE ---
//     //
//     if (diffuseTexture) {
//         diffuseTexture->bind(0);
//         shader.setInt("material.hasDiffuseTex", 1);
//         shader.setInt("material.diffuseTex", 0);
//     } else {
//         shader.setInt("material.hasDiffuseTex", 0);
//     }

//     //
//     // --- SPECULAR TEXTURE ---
//     //
//     if (specularTexture) {
//         specularTexture->bind(1);
//         shader.setInt("material.hasSpecularTex", 1);
//         shader.setInt("material.specularTex", 1);
//     } else {
//         shader.setInt("material.hasSpecularTex", 0);
//     }
// }

