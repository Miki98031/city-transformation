//
// Created by mihailo on 6.4.24..
//

#ifndef PROJECT_BASE_BUILDING_H
#define PROJECT_BASE_BUILDING_H


#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "BuildingBase.h"
#include "BuildingRoof.h"

class Building {
private:
    friend class BuildingBase;
    friend class BuildingRoof;

private:
    glm::vec3 position;
    float rotateAngle;
    glm::vec3 additionalTranslate;

private:
    BuildingBase* base;
    BuildingRoof* roof;

public:
    Building(glm::vec3 position, float rotateAngle, glm::vec3 additionalTranslate) {
        this->position = glm::vec3(position.x, position.y, position.z);
        this->rotateAngle = rotateAngle;
        this->additionalTranslate = additionalTranslate;

        base = new BuildingBase(position, rotateAngle, additionalTranslate);
        roof = new BuildingRoof(position, rotateAngle, additionalTranslate);
    }

    const glm::vec3 &getPosition() const {
        //std::cout << position.x << " " << position.y << " " << position.z << std::endl;
        return position;
    }

    float getRotateAngle() const {
        return rotateAngle;
    }

    const glm::vec3 &getAdditionalTranslate() const {
        //std::cout << additionalTranslate.x << " " << additionalTranslate.y << " " << additionalTranslate.z << std::endl;
        return additionalTranslate;
    }

    static void makeInnerBuildings(std::vector<Building*> &buildings) {
        std::string positionsPath = "resources/buildings/inner_positions.txt";
        std::ifstream in(positionsPath);
        std::string line;
        float rotateAngle = 0.0;
        glm::vec3 additionalTranslate;
        glm::vec3 position;

        while(getline(in, line)) {
            std::stringstream iss(line);
            if(line.find("\n") == 0) {
                break;
            }

            if(line.find("//zeleni venac far upper side") == 0) {
                rotateAngle = 20.0;
                additionalTranslate = glm::vec3(-0.215, 0.0, 1.013);
            }

            else if(line.find("//zadarska middle near side") == 0) {
                rotateAngle = -30.0;
                additionalTranslate = glm::vec3(-2.05, 0.0, -1.57);
            }

            else if(line.find("//zadarska lower near side") == 0) {
                rotateAngle = -15.0;
                additionalTranslate = glm::vec3(-1.48, 0.0, 0.2);
            }

            else if(line.find("//zadarska middle far side") == 0) {
                rotateAngle = -30.0;
                additionalTranslate = glm::vec3(-2.05, 0.0, -1.57);
            }

            else if(line.find("//zadarska lower far side") == 0) {
                rotateAngle = -15.0;
                additionalTranslate = glm::vec3(-1.48, 0.0, 0.2);
            }

            else if(line.find("//kralja petra near side") == 0) {
                rotateAngle = 20.0;
                additionalTranslate = glm::vec3(2.29, 0.0, 0.11);
            }

            else if(line.find("//kralja petra far side") == 0) {
                rotateAngle = 20.0;
                additionalTranslate = glm::vec3(2.29, 0.0, 0.11);
            }

            else if(line.find("//river upper far side") == 0) {
                rotateAngle = -20.0;
                additionalTranslate = glm::vec3(-4.13, 0.0, 0.75);
            }

            else if(line.find("//river lower far side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.0, 0.0, 0.0);
            }

            else if(line.find("//kneza sime markovica near side") == 0) {
                rotateAngle = 40.051;
                additionalTranslate = glm::vec3(9.899, 0.0, 0.118);
            }

            else if(line.find("//pop-lukina near side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(-1.41, 0.0, 0.482);
            }

            else if(line.find("//srebrenicka upper side") == 0) {
                rotateAngle = -5.0;
                additionalTranslate = glm::vec3(-0.406, 0.0, -0.15);
            }
            else if(line.find("//river upper near side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.082, 0.0, -0.082);
            }

            else if(line.find("//kneza sime markovica far side") == 0) {
                rotateAngle = 40.051;
                additionalTranslate = glm::vec3(9.899, 0.0, 0.118);
            }

            else if(line.find("//ulaz desno gore") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(-0.235, 0.0, -0.183);
            }

            else if(line.find("//ulaz desno dole") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.315, 0.0, 0.347);
            }

            else if(line.find("//zid desno blize") == 0) {
                rotateAngle = -10.0;
                additionalTranslate = glm::vec3(-2.67, 0.0, -1.522);
            }

            else {
                break;
            }

            while(getline(in, line)) {
                std::stringstream iss(line);
                if(line.find("*******************************************") == 0) {
                    break;
                }
                iss >> position.x >> position.y >> position.z;
                buildings.push_back(new Building(position, rotateAngle, additionalTranslate));
            }
        }
    }

    static void makeWalls(std::vector<Building*> &buildings) {
        std::string positionsPath = "resources/buildings/wall_positions.txt";
        std::ifstream in(positionsPath);
        std::string line;
        float rotateAngle = 0.0;
        glm::vec3 additionalTranslate;
        glm::vec3 position;

        while(getline(in, line)) {
            std::stringstream iss(line);
            if(line.find("\n") == 0) {
                break;
            }

            if(line.find("//river upper near side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.0, 0.0, 0.0);
            }

            else if(line.find("//river lower near side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.0, 0.0, 0.0);
            }

            else if(line.find("//zeleni venac near upper side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.0, 0.0, 0.0);
            }

            else if(line.find("//zeleni venac near lower side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(-0.0, 0.0, -0.0);
            }

            else if(line.find("//kneza sime markovica far side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.0, 0.0, 0.0);
            }

            else if(line.find("//pop-lukina far side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.0, 0.0, 0.0);
            }

            else if(line.find("//pariska far side") == 0) {
                rotateAngle = 0.0;
                additionalTranslate = glm::vec3(0.0, 0.0, 0.0);
            }

            else {
                break;
            }

            while(getline(in, line)) {
                std::stringstream iss(line);
                if(line.find("*******************************************") == 0) {
                    break;
                }
                iss >> position.x >> position.y >> position.z;
                buildings.push_back(new Building(position, rotateAngle, additionalTranslate));
            }
        }
    }
};

#endif //PROJECT_BASE_BUILDING_H
