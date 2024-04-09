//
// Created by mihailo on 9.4.24..
//

#ifndef PROJECT_BASE_MEDIUMBUILDINGROOF_H
#define PROJECT_BASE_MEDIUMBUILDINGROOF_H

#include <string>
#include <glm/vec3.hpp>
#include <string>
#include "BuildingRoof.h"
#include "stb_image.h"

class MediumBuildingRoof : public BuildingRoof {
private:
    static float buildingRoofHeight;
    static std::string buildingRoofTexturePath;

private:
    static int counterTexture;
    static unsigned buildingRoofTexture;

public:
    MediumBuildingRoof(glm::vec3 position, float rotateAngle, glm::vec3 additionalTranslate)
    : BuildingRoof(position, rotateAngle, additionalTranslate) {}

    float getBuildingRoofHeight() override {
        return buildingRoofHeight;
    }

    unsigned getBuildingRoofTexture() override {
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
            unsigned char *data = stbi_load(buildingRoofTexturePath.c_str(), &width, &height, &nrChannels, 0);
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

            buildingRoofTexture = texture;
        }

        return buildingRoofTexture;
    }
};


#endif //PROJECT_BASE_MEDIUMBUILDINGROOF_H
