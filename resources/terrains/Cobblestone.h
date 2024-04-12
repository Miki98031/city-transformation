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
#include "stb_image.h"

class Cobblestone {
private:
    const static int SIZE_X = 13;
    const static int SIZE_Z = 25;
    const static int VERTEX_COUNT_X = 13;
    const static int VERTEX_COUNT_Z = 25;
    const static int count = VERTEX_COUNT_X * VERTEX_COUNT_Z * 6 * 5;

    static float vertices[count];
    static int counterVertices;

private:
    static int counterVAO;
    static int counterTexture;
    static unsigned cobblestoneVAO;
    static unsigned cobblestoneTexture;
    static unsigned cobblestoneVBO;

public:
    Cobblestone() {
        if (counterVertices++ == 0) generateTerrain();
    }

    void generateTerrain() {
        int vp = 0;
        float t1ax, t1bx, t1cx, t1ay, t1by, t1cy, t1az, t1bz, t1cz = 0;
        float t2ax, t2bx, t2cx, t2ay, t2by, t2cy, t2az, t2bz, t2cz = 0;
        for (int i = 0; i < VERTEX_COUNT_X; i++) {
            for (int j = 0; j < VERTEX_COUNT_Z; j++) {
                t1ax = ((float) i) / VERTEX_COUNT_X * SIZE_X; t1ay = -0.0; t1az = ((float) j) / VERTEX_COUNT_Z * SIZE_Z;
                t1bx = ((float) i + 1) / VERTEX_COUNT_X * SIZE_X; t1by = -0.0; t1bz = ((float) j) / VERTEX_COUNT_Z * SIZE_Z;
                t1cx = ((float) i + 1) / VERTEX_COUNT_X * SIZE_X; t1cy = -0.0; t1cz = ((float) j + 1) / VERTEX_COUNT_Z * SIZE_Z;

                t2ax = ((float) i + 1) / VERTEX_COUNT_X * SIZE_X; t2ay = -0.0; t2az = ((float) j + 1) / VERTEX_COUNT_Z * SIZE_Z;
                t2bx = ((float) i) / VERTEX_COUNT_X * SIZE_X; t2by = -0.0; t2bz = ((float) j + 1) / VERTEX_COUNT_Z * SIZE_Z;
                t2cx = ((float) i) / VERTEX_COUNT_X * SIZE_X; t2cy = -0.0; t2cz = ((float) j) / VERTEX_COUNT_Z * SIZE_Z;

                //std::cout << t1ax << " " << t1ay << " " << t1az << std::endl;
                //std::cout << t1bx << " " << t1by << " " << t1bz << std::endl;
                //std::cout << t1cx << " " << t1cy << " " << t1cz << std::endl << std::endl;

                vertices[vp++] = t1bx; vertices[vp++] = t1by; vertices[vp++] = t1bz; vertices[vp++] = 1.0; vertices[vp++] = 0.0;
                vertices[vp++] = t1ax; vertices[vp++] = t1ay; vertices[vp++] = t1az; vertices[vp++] = 0.0; vertices[vp++] = 0.0;
                vertices[vp++] = t1cx; vertices[vp++] = t1cy; vertices[vp++] = t1cz; vertices[vp++] = 1.0; vertices[vp++] = 1.0;

                //std::cout << t2ax << " " << t2ay << " " << t2az << std::endl;
                //std::cout << t2bx << " " << t2by << " " << t2bz << std::endl;
                //std::cout << t2cx << " " << t2cy << " " << t2cz << std::endl << std::endl;

                vertices[vp++] = t2bx; vertices[vp++] = t2by; vertices[vp++] = t2bz; vertices[vp++] = 0.0; vertices[vp++] = 1.0;
                vertices[vp++] = t2ax; vertices[vp++] = t2ay; vertices[vp++] = t2az; vertices[vp++] = 1.0; vertices[vp++] = 1.0;
                vertices[vp++] = t2cx; vertices[vp++] = t2cy; vertices[vp++] = t2cz; vertices[vp++] = 0.0; vertices[vp++] = 0.0;
            }
        }
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

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3*sizeof(float)));
            glEnableVertexAttribArray(1);

            cobblestoneVBO = VBO;
            cobblestoneVAO = VAO;
        }

        return cobblestoneVAO;
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
            std::string texturePath = "resources/textures/cobblestone9.jpg";
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

    static void freeBuffers() {
        glDeleteVertexArrays(1, &cobblestoneVAO);
        glDeleteBuffers(1, &cobblestoneVBO);
    }
};


#endif //PROJECT_BASE_COBBLESTONE_H
