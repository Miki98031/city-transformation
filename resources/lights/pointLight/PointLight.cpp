//
// Created by mihailo on 11.4.24..
//

#include "PointLight.h"
float PointLight::vertices[PointLight::numberOfVertices] = {0}; // Initialize static member variable
int PointLight::counterVertices = 0;
int PointLight::counterVAO = 0;
unsigned PointLight::pointLightVAO = 0;
unsigned PointLight::pointLightVBO = 0;
glm::vec3 PointLight::ambient = glm::vec3(0.05f, 0.05f, 0.05f);
glm::vec3 PointLight::diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
glm::vec3 PointLight::specular = glm::vec3(1.0f, 1.0f, 1.0f);
float PointLight::constant = 1.0f;
float PointLight::linear = 0.09;
float PointLight::quadratic = 0.032;

const glm::vec3 &PointLight::getPosition() const {
    return position;
}
