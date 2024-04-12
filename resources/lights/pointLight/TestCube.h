//
// Created by mihailo on 11.4.24..
//

#ifndef PROJECT_BASE_TESTCUBE_H
#define PROJECT_BASE_TESTCUBE_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "stb_image.h"

class TestCube {
private:
    static std::string testCubeTexturePath;
    static std::string testCubeTextureSpecularPath;

private:
    const static int numberOfVertices = 288;
    static float vertices[numberOfVertices];
    static int counterVertices;

private:
    static int counterTexture;
    static int counterVAO;
    static unsigned testCubeTexture;
    static unsigned testCubeVAO;
    static unsigned testCubeVBO;
    static int counterTextureSpecular;
    static unsigned testCubeTextureSpecular;

private:
    glm::vec3 position;
    float rotateAngle;
    glm::vec3 additionalTranslate;

public:
    const glm::vec3 &getPosition() const;

    TestCube() {
        if (counterVertices++ == 0) loadVertices("resources/lights/pointLight/light_vertices.txt");
    }

    static unsigned getTestCubeTexture() {
        if (counterTexture++ == 0) {
            testCubeTexture = loadTexture(testCubeTexturePath);
        }
        return testCubeTexture;
    }

    static unsigned getTestCubeTextureSpecular() {
        if (counterTextureSpecular++ == 0) {
            testCubeTextureSpecular = loadTexture(testCubeTextureSpecularPath);
        }
        return testCubeTextureSpecular;
    }

    static unsigned loadTexture(std::string texturePath) {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrComponents;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {

            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        return texture;
    }

    static unsigned getTestCubeVAO() {
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

            testCubeVBO = VBO;
            testCubeVAO = VAO;
        }

        return testCubeVAO;
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
        glDeleteVertexArrays(1, &testCubeVAO);
        glDeleteBuffers(1, &testCubeVBO);
    }
};


#endif //PROJECT_BASE_TESTCUBE_H
