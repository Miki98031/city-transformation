//
// Created by mihailo on 6.4.24..
//

#ifndef PROJECT_BASE_COBBLESTONE_H
#define PROJECT_BASE_COBBLESTONE_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <string>
#include <fstream>
#include <iostream>
//#include "learnopengl/filesystem.h"
#include "stb_image.h"

class Cobblestone {
private:
    const static int numberOfVertices = 72;
    static float vertices[numberOfVertices];
    static int counterVertices;

private:
    static int counterVAO;
    static int counterTexture;
    static unsigned cobblestoneVAO;
    static unsigned cobblestoneTexture;
    static unsigned cobblestoneVBO;

public:
    Cobblestone() {
        if (counterVertices++ == 0) loadVertices("resources/terrains/cobblestone_vertices.txt");
    }

    static unsigned getCobblestoneVAO() {
        if (counterVAO++ == 0) {
            unsigned int VBO, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3*sizeof(float)));
            glEnableVertexAttribArray(1);

            cobblestoneVBO = VBO;
            cobblestoneVAO = VAO;
        }

        return cobblestoneVAO;
    }

    static void loadVertices(std::string verticesPath) {
        std::ifstream in(verticesPath);
        float x, y, z, s, t, r;
        int i = 0;

        while(in >> x >> y >> z >> s >> t >> r) {
            std::cout << x << " " << y << " " << z << " " << s << " " << t << " " << r << std::endl;
            vertices[i++] = x;
            vertices[i++] = y;
            vertices[i++] = z;
            vertices[i++] = s;
            vertices[i++] = t;
            vertices[i++] = r;
        }
        std::cout << i << std::endl;
    }

    static unsigned getCobblestoneTexture() {
        if (counterTexture++ == 0) {
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
            int width, height, nrChannels;
            // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
            std::string texturePath = "resources/textures/cobblestone.jpg";
            unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);

            cobblestoneTexture = texture;
        }

        return cobblestoneTexture;
    }
};


#endif //PROJECT_BASE_COBBLESTONE_H
