//
// Created by mihailo on 9.4.24..
//

#ifndef PROJECT_BASE_WALL_H
#define PROJECT_BASE_WALL_H

#include <string>

#include <glm/vec3.hpp>
#include <string>
#include "BuildingBase.h"

class Wall : public BuildingBase {
private:
    static float buildingBaseHeight;
    static std::string buildingBaseTexturePath;

private:
    static int counterTexture;
    static unsigned buildingBaseTexture;

public:
    Wall(glm::vec3 position, float rotateAngle, glm::vec3 additionalTranslate)
    : BuildingBase(position, rotateAngle, additionalTranslate) {}

    float getBuildingBaseHeight() override {
        return buildingBaseHeight;
    }

    unsigned getBuildingBaseTexture() override {
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
            unsigned char *data = stbi_load(buildingBaseTexturePath.c_str(), &width, &height, &nrChannels, 0);
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

            buildingBaseTexture = texture;
        }

        return buildingBaseTexture;
    }
};


#endif //PROJECT_BASE_WALL_H
