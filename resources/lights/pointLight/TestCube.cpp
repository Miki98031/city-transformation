//
// Created by mihailo on 11.4.24..
//

#include "TestCube.h"
std::string TestCube::testCubeTexturePath = "resources/textures/container2.png";
std::string TestCube::testCubeTextureSpecularPath = "resources/textures/container2_specular.png";
float TestCube::vertices[TestCube::numberOfVertices] = {0}; // Initialize static member variable
int TestCube::counterVertices = 0;
int TestCube::counterVAO = 0;
unsigned TestCube::testCubeVAO = 0;
unsigned TestCube::testCubeVBO = 0;
int TestCube::counterTexture = 0;
unsigned TestCube::testCubeTexture = 0;
int TestCube::counterTextureSpecular = 0;
unsigned TestCube::testCubeTextureSpecular = 0;

const glm::vec3 &TestCube::getPosition() const {
    return position;
}
