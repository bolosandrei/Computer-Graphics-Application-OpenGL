#include "Camera.hpp"
#include <glm/gtx/euler_angles.hpp>

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;

        //TODO - Update the rest of camera parameters
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = -glm::normalize(glm::cross(cameraUp, cameraFrontDirection));
        this->cameraOrigUp = cameraUp;
        this->cameraUpDirection = glm::cross(cameraRightDirection, cameraFrontDirection);
        this->cameraOrigFront = cameraFrontDirection;
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        if (direction == MOVE_FORWARD) {
            cameraPosition = cameraPosition + speed * cameraFrontDirection;
        }

        if (direction == MOVE_BACKWARD) {
            cameraPosition = cameraPosition + speed * -cameraFrontDirection;
        }

        if (direction == MOVE_LEFT) {
            cameraPosition = cameraPosition + speed * -cameraRightDirection;
        }

        if (direction == MOVE_RIGHT) {
            cameraPosition = cameraPosition + speed * cameraRightDirection;
        }

        if (direction == MOVE_UPWARD) {
            cameraPosition = cameraPosition + speed * cameraUpDirection;
        }

        if (direction == MOVE_DOWNWARD) {
            cameraPosition = cameraPosition + speed * -cameraUpDirection;
        }
        /*cameraTarget = normalize((cameraPosition + cameraOrigFront));*/
        cameraTarget = cameraPosition + cameraFrontDirection;
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        glm::mat4 eulerAngle = glm::yawPitchRoll(glm::radians(yaw), glm::radians(pitch), 0.0f);

        ////if (glm::radians(pitch) < 1.5708f && glm::radians(pitch) > -1.5708f) {
        cameraFrontDirection = glm::vec3(glm::normalize((eulerAngle * glm::vec4(cameraOrigFront, 0.0f))));
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraOrigUp));
        cameraUpDirection = glm::cross(cameraRightDirection, cameraFrontDirection);
        /*cameraTarget = cameraPosition + cameraFrontDirection;*/
        cameraTarget = cameraPosition + cameraFrontDirection;
        ////}

        //glm::vec3 direction;
        //direction.x = /*sin(glm::radians(yaw)) * cos(glm::radians(pitch))*/ sin(glm::radians(pitch));
        //direction.y = /*sin(glm::radians(pitch))*/ sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        //direction.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));

        //glm::vec3 front = glm::normalize(direction);

        //cameraFrontDirection = front;
        //cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
        //cameraTarget = cameraPosition + cameraFrontDirection;
    }
}