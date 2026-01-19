#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <cmath>

enum Projection{PERSPECTIVE, ORTHOGRAPHIC};

// Default values of the camera
namespace cameraDefault {
    inline constexpr glm::vec3 Position{-5.f, 0.f, 0.f};
    inline constexpr glm::vec3 Target{0.f};
    inline constexpr glm::vec3 up(0.f, 1.f, 0.f);

    inline constexpr float fov = 45.0f;
    inline constexpr float aspectRatio = 16.f / 9.f;
    inline constexpr float nearPlane = 0.05f;
    inline constexpr float farPlane  = 100.f;   
}

namespace SCOPE {
    class cameraController;

/**
 * @brief Generic camera class allowing movement within the scene and zooming based on the depth of the object
 */
class Camera
{
public:
    // View
    glm::vec3 Position;         ///< position of the camera
    glm::vec3 Target;           ///< target of the camera

    glm::vec3 up;               ///< unitary vector up to the camera
    glm::vec3 front;            ///< unitary vector between the target and the position
    glm::vec3 right;            ///< unitary vector right to the camera

    glm::vec3 RotationCenter;   ///< rotation center of the camera
    float yaw = 0.f;            ///< horizontal rotation angle
    float pitch = 0.f;          ///< vertical rotation angle

    // Projection
    float nearPlane;            ///< clip near the camera
    float farPlane;             ///< clip far to the camera
    float fov;                  ///< field of view 
    float aspectRatio;          ///< ratio of horizontal size divided by vertical size
    Projection projection = PERSPECTIVE;    ///< projection method


    Camera();

    /**
     * @brief Pan the camera
     * 
     * @param dx displacement on the x axis
     * @param dy displacement on the y axis
     */
    void pan(float dx, float dy); 
    
    /**
     * @brief Rotation around the center of rotation
     * 
     * @param dx displacement on the x axis for the yaw
     * @param dy displacement on the y axis for the pitch
     */
    void rotate(float dx, float dy);    

    /**
     * @brief Zoom at center
     * 
     * @param dz displacement on the z axis by scrolling
     */
    void zoom(float dz);   
    
    /**
     * @brief Zoom to cursor if no object is pointed at
     * 
     * @param dz displacement on the z axis by scrolling
     * @param xpos x position of the cursor in the homogeneous space
     * @param ypos y position of the cursor in the homogeneous space
     */
    void zoom(float dz, float xpos, float ypos);     
    
    /**
     * @brief Zoom to cursor based on the depth of the object pointed to by the cursor
     * 
     * @param dz displacement on the z axis by scrolling
     * @param mouseX x position in the screen space
     * @param mouseY y position in the screen space 
     * @param depth distance between the camera and the fragment pointed by the cursor in the screen space
     * @param viewport viewport params to convert the screen coordinates into homogeneous coordinates
     */
    void zoom(float dz, float mouseX, float mouseY, float depth, const glm::vec4& viewport);   

    /**
     * @brief Return the view matrix
     * 
     * @return view matrix
     */
    glm::mat4 getViewMatrix() const;

    /**
     * @brief Return the projection matrix
     * 
     * @return projection matrix
     */
    glm::mat4 getProjectionMatrix() const;

    

private : 

    /**
     * @brief Update the view matrix after a transformation
     */
    void updateCameraOrientation(); 
};

}

#endif

