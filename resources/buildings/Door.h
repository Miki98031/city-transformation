//
// Created by mihailo on 11.4.24..
//

#ifndef PROJECT_BASE_DOOR_H
#define PROJECT_BASE_DOOR_H


#include <glm/vec3.hpp>

class Door {
private:
    bool doorOpened = false;
    bool doorOpening = false;
    bool doorClosed = true;
    bool doorClosing = false;
    float doorOffset = 0.5;
    float doorSpeed = 0.5;
    glm::vec3 leftDoorPosition = glm::vec3(9.5, 0.79, -11.75);
    glm::vec3 rightDoorPosition = glm::vec3(9.5, 0.79, -12.25);
public:
    void setLeftDoorPosition(const glm::vec3 &leftDoorPosition) {
        Door::leftDoorPosition = leftDoorPosition;
    }

    void setRightDoorPosition(const glm::vec3 &rightDoorPosition) {
        Door::rightDoorPosition = rightDoorPosition;
    }

    const glm::vec3 &getLeftDoorPosition() const {
        return leftDoorPosition;
    }

    const glm::vec3 &getRightDoorPosition() const {
        return rightDoorPosition;
    }

    float getDoorSpeed() const {
        return doorSpeed;
    }

    bool isDoorOpened() const {
        return doorOpened;
    }

    void setDoorOpened(bool doorOpened) {
        this->doorOpened = doorOpened;
    }

    bool isDoorOpening() const {
        return doorOpening;
    }

    void setDoorOpening(bool doorOpening) {
        this->doorOpening = doorOpening;
    }

    bool isDoorClosed() const {
        return doorClosed;
    }

    void setDoorClosed(bool doorClosed) {
        this->doorClosed = doorClosed;
    }

    bool isDoorClosing() const {
        return doorClosing;
    }

    void setDoorClosing(bool doorClosing) {
        this->doorClosing = doorClosing;
    }

    float getDoorOffset() const {
        return doorOffset;
    }

    void setDoorOffset(float doorOffset) {
        this->doorOffset = doorOffset;
    }

};


#endif //PROJECT_BASE_DOOR_H
