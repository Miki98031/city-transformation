//
// Created by mihailo on 6.4.24..
//

#ifndef PROJECT_BASE_BUILDINGBASE_H
#define PROJECT_BASE_BUILDINGBASE_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "stb_image.h"

class BuildingBase {
private:
    const static int numberOfVertices = 180;
    static float vertices[numberOfVertices];
    static int counterVertices;

private:
    static int counterTexture;
    static int counterVAO;
    static unsigned buildingBaseTexture;
    static unsigned buildingBaseVAO;
    static unsigned buildingBaseVBO;

private:
    glm::vec3 position;
    float rotateAngle;
    glm::vec3 additionalTranslate;

public:
    BuildingBase(glm::vec3 position, float rotateAngle, glm::vec3 additionalTranslate) {
        if (counterVertices++ == 0) loadVertices("resources/buildings/base_vertices.txt");

        this->position = position;
        this->rotateAngle = rotateAngle;
        this->additionalTranslate = additionalTranslate;
    }

    virtual float getBuildingBaseHeight() = 0;
    virtual unsigned getBuildingBaseTexture() = 0;

    static unsigned getBuildingBaseVAO() {
        if (counterVAO++ == 0) {
            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3*sizeof(float)));
            glEnableVertexAttribArray(1);

            buildingBaseVBO = VBO;
            buildingBaseVAO = VAO;
        }

        return buildingBaseVAO;
    }

    static void loadVertices(std::string verticesPath) {
        std::ifstream in(verticesPath);
        float x, y, z;
        int i = 0;

        while(in >> x >> y >> z) {
            vertices[i++] = x;
            vertices[i++] = y;
            vertices[i++] = z;
        }
    }
};


#endif //PROJECT_BASE_BUILDINGBASE_H
