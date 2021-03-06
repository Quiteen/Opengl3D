#ifndef VIEW_H
#define VIEW_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#ifdef VIEW_STATIC
static glm::vec3 rotateAroundAxis(glm::vec3 v, glm::vec3 axis, float angle)
{
    axis = glm::normalize(axis);
    glm::mat3 transform;

    transform[0][0] = axis.x * axis.x * (1 - cosf(angle)) + cosf(angle);
    transform[1][0] = axis.x * axis.y * (1 - cosf(angle)) + axis.z * sinf(angle);
    transform[2][0] = axis.x * axis.z * (1 - cosf(angle)) - axis.y * sinf(angle);

    transform[0][1] = axis.x * axis.y * (1 - cosf(angle)) - axis.z * sinf(angle);
    transform[1][1] = axis.y * axis.y * (1 - cosf(angle)) + cosf(angle);
    transform[2][1] = axis.z * axis.y * (1 - cosf(angle)) + axis.x * sinf(angle);

    transform[0][2] = axis.x * axis.z * (1 - cosf(angle)) + axis.y * sinf(angle);
    transform[1][2] = axis.y * axis.z * (1 - cosf(angle)) - axis.x * sinf(angle);
    transform[2][2] = axis.z * axis.z * (1 - cosf(angle)) + cosf(angle);

    return transform * v;
}
#else
extern glm::vec3 rotateAroundAxis(glm::vec3 v, glm::vec3 axis, float angle);
#endif



class View
{
 public:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 origin;
    float zoom;
    float zoomSensitivity;
    float mouseSensitivity;

    View(glm::vec3 eye = glm::vec3(0.0f, 0.0f, 1.0f),
         glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
        : origin(glm::vec3(0,0,0)), zoom(45.0f), zoomSensitivity(1.0f), mouseSensitivity(0.2f)
    {
        this->eye = eye;
        this->center = center;
        this->up = up;
        right = glm::cross(up, glm::normalize(eye-center));
    }

    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(eye+origin, center+origin, up);
    }

    void moveOnLeftRight(float offset)
    {
        offset *= mouseSensitivity;
        origin += glm::vec3(offset * right.x / glm::length(right),
                            offset * right.y / glm::length(right),
                            offset * right.z / glm::length(right));
    }

    void moveOnUpDown(float offset)
    {
        offset *= mouseSensitivity;
        origin += glm::vec3(offset * up.x / glm::length(up),
                            offset * up.y / glm::length(up),
                            offset * up.z / glm::length(up));
    }

    void moveOnFrontBack(float offset)
    {
        offset *= mouseSensitivity;
        glm::vec3 front = eye - center;
        origin += glm::vec3(offset * front.x / glm::length(front),
                            offset * front.y / glm::length(front),
                            offset * front.z / glm::length(front));
    }

    void rotateAroundRight(float angle)
    {
        angle = glm::radians(angle * mouseSensitivity);
        eye = rotateAroundAxis(eye, right, angle);
        up = rotateAroundAxis(up, right, angle);
    }

    void rotateAroundUp(float angle)
    {
        angle = glm::radians(angle * mouseSensitivity);
        eye = rotateAroundAxis(eye, up, angle);
        right = rotateAroundAxis(right, up, angle);
    }

    void rotateAroundEye(float angle)
    {
        angle = glm::radians(angle * mouseSensitivity);
        up = rotateAroundAxis(up, eye, angle);
        right = rotateAroundAxis(right, eye, angle);
    }

    void rotateAroundX(float angle)
    {
        angle = glm::radians(angle * mouseSensitivity);
        float newy = cosf(angle) * eye.y - sin(angle) * eye.z;
        float newz = cosf(angle) * eye.z + sin(angle) * eye.y;
        eye = glm::vec3(eye.x, newy, newz);
        newy = cosf(angle) * up.y - sin(angle) * up.z;
        newz = cosf(angle) * up.z + sin(angle) * up.y;
        up = glm::vec3(up.x, newy, newz);
    }

    void rotateAroundY(float angle)
    {
        angle = glm::radians(angle * mouseSensitivity);
        float newx = cosf(angle) * eye.x - sin(angle) * eye.z;
        float newz = cosf(angle) * eye.z + sin(angle) * eye.x;
        eye = glm::vec3(newx, eye.y, newz);
        newx = cosf(angle) * up.x - sin(angle) * up.z;
        newz = cosf(angle) * up.z + sin(angle) * up.x;
        up = glm::vec3(newx, up.y, newz);
    }

    void rotateAroundZ(float angle)
    {
        angle = glm::radians(angle * mouseSensitivity);
        float newy = cosf(angle) * eye.y - sin(angle) * eye.x;
        float newx = cosf(angle) * eye.x + sin(angle) * eye.y;
        eye = glm::vec3(newx, newy, eye.z);
        newy = cosf(angle) * up.y - sin(angle) * up.x;
        newx = cosf(angle) * up.x + sin(angle) * up.y;
        up = glm::vec3(newx, newy, up.z);
    }

    void changeZoom(float offset)
    {
        zoom -= offset * zoomSensitivity;
        if (zoom < 1.0f) zoom = 1.0f;
        if (zoom > 45.0f) zoom = 45.0f;
    }
};


#endif // EYEVIEW_H
