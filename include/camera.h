#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <cmath>

enum Projection{PERSPECTIVE, ORTHOGRAPHIC};

// Valeurs par défaut de la caméra
namespace cameraDefault {
    inline constexpr glm::vec3 Position{-5.f, 0.f, 0.f};
    inline constexpr glm::vec3 Target{0.f};
    inline constexpr glm::vec3 up(0.f, 1.f, 0.f);

    inline constexpr float fov = 45.0f;
    inline constexpr float aspectRatio = 16.f / 9.f;
    inline constexpr float nearPlane = 0.05f;
    inline constexpr float farPlane  = 100.f;
}

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Vue
    glm::vec3 Position;
    glm::vec3 Target;

    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;

    glm::vec3 RotationCenter;
    float yaw = 0.f;
    float pitch = 0.f;

    float xDisplacement;
    float yDisplacement;

    // Projection
    float nearPlane;
    float farPlane;
    float fov;
    float aspectRatio;

    Camera();
    
    float getRadius() const;  // distance entre la caméra et son centre de rotation

    void pan(float dx, float dy);       
    void rotate(float dx, float dy);    

    void zoom(float dz);                                                                        // zoom au centre de l'image
    void zoom(float dz, float xpos, float ypos);                                                // zoom au curseur dans le vide
    void zoom(float dz, float mouseX, float mouseY, float depth, const glm::vec4& viewport);    // zoom au curseur sur un mesh

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    Projection projection = PERSPECTIVE;
    
private : 
    void updateCameraOrientation(); // recalcul de la base de vue
};

#endif

