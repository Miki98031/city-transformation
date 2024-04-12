//
// Created by mihailo on 11.4.24..
//

#ifndef PROJECT_BASE_POINTLIGHT_H
#define PROJECT_BASE_POINTLIGHT_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "stb_image.h"

class PointLight {
public:
    static glm::vec3 ambient;
    static glm::vec3 diffuse;
    static glm::vec3 specular;
    static float constant;
    static float linear;
    static float quadratic;

private:
    const static int numberOfVertices = 288;
    static float vertices[numberOfVertices];
    static int counterVertices;

private:
    static int counterTexture;
    static int counterVAO;
    static unsigned pointLightTexture;
    static unsigned pointLightVAO;
    static unsigned pointLightVBO;

private:
    glm::vec3 position;
    float rotateAngle;
    glm::vec3 additionalTranslate;
public:
    const glm::vec3 &getPosition() const;

public:
    PointLight(glm::vec3 position) {
        if (counterVertices++ == 0) loadVertices("resources/lights/pointLight/light_vertices.txt");

        this->position = position;
    }

    static void makePointLights(std::vector<PointLight *> &pointLights) {
        std::string lightPositions = "resources/lights/pointLight/light_positions.txt";
        std::ifstream in(lightPositions);
        float x, y, z;
        glm::vec3 position;

        while(in >> position.x >> position.y >> position.z) {
            pointLights.push_back(new PointLight(position));
        }
    }

    static unsigned getPointLightVAO() {
        if (counterVAO++ == 0) {
            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3*sizeof(float)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6*sizeof(float)));
            glEnableVertexAttribArray(2);

            pointLightVBO = VBO;
            pointLightVAO = VAO;
        }

        return pointLightVAO;
    }

    static void loadVertices(std::string verticesPath) {
        std::ifstream in(verticesPath);
        float x, y, z, n1, n2, n3, t1, t2;
        int i = 0;

        while(in >> x >> y >> z >> n1 >> n2 >> n3 >> t1 >> t2) {
            vertices[i++] = x;
            vertices[i++] = y;
            vertices[i++] = z;
            vertices[i++] = n1;
            vertices[i++] = n2;
            vertices[i++] = n3;
            vertices[i++] = t1;
            vertices[i++] = t2;
        }
    }

    static void freeBuffers() {
        glDeleteVertexArrays(1, &pointLightVAO);
        glDeleteBuffers(1, &pointLightVBO);
    }
};


#endif //PROJECT_BASE_POINTLIGHT_H
