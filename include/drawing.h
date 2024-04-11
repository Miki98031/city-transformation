//
// Created by mihailo on 10.4.24..
//

#ifndef PROJECT_BASE_DRAWING_H
#define PROJECT_BASE_DRAWING_H

#include "learnopengl/shader.h"
#include "learnopengl/model.h"
#include "../resources/buildings/Building.h"
#include "../resources/terrains/Cobblestone.h"
#include "../resources/terrains/Grass.h"
#include "../resources/terrains/Road.h"
#include "../resources/buildings/Door.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int SCREEN_WIDTH = 1366;
const unsigned int SCREEN_HEIGHT = 768;

void drawBackpack(Shader backpackShader, Model backpack, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    //set projection and view
    backpackShader.use();
    glm::mat4 backpackProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    backpackShader.setMat4("backpackProjection", backpackProjection);
    glm::mat4 backpackView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    backpackShader.setMat4("backpackView", backpackView);

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 backpackModel = glm::mat4(1.0f);
    backpackModel = glm::translate(backpackModel, glm::vec3(0.0, 0.0, 0.0));
    backpackModel = glm::scale(backpackModel, glm::vec3(1.0, 1.0, 1.0));
    backpackShader.setMat4("backpackModel", backpackModel);

    //draw backpack
    backpack.Draw(backpackShader);
}


void drawFountain(Shader fountainShader, Model fountain, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    //set projection and view
    fountainShader.use();
    glm::mat4 fountainProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    fountainShader.setMat4("fountainProjection", fountainProjection);
    glm::mat4 fountainView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    fountainShader.setMat4("fountainView", fountainView);

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 fountainModel = glm::mat4(1.0f);
    fountainModel = glm::translate(fountainModel, glm::vec3(3.0, 0.1, -12.0));
    fountainModel = glm::rotate(fountainModel, glm::radians((float) -21.0), glm::vec3(0.0f, 1.0f, 0.0f));
    fountainModel = glm::scale(fountainModel, glm::vec3(1.0, 1.0, 1.0));
    fountainShader.setMat4("fountainModel", fountainModel);

    //draw fountain
    fountain.Draw(fountainShader);
}

void drawChurch(Shader churchShader, Model church, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    //set projection and view
    churchShader.use();
    glm::mat4 churchProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    churchShader.setMat4("churchProjection", churchProjection);
    glm::mat4 churchView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    churchShader.setMat4("churchView", churchView);

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 churchModel;

    //first church
    churchModel = glm::mat4(1.0f);
    churchModel = glm::translate(churchModel, glm::vec3(0.0, 0.01, 0.0));
    churchShader.setMat4("churchModel", churchModel);
    church.Draw(churchShader);

    //second church
    churchModel = glm::mat4(1.0f);
    churchModel = glm::translate(churchModel, glm::vec3(8.5, 0.01, -24.0));
    churchModel = glm::rotate(churchModel, glm::radians((float) -180.0), glm::vec3(0.0f, 1.0f, 0.0f));
    churchModel = glm::scale(churchModel, glm::vec3(1.3, 1.3, 1.3));
    churchShader.setMat4("churchModel", churchModel);
    church.Draw(churchShader);
}

void drawDoor(Shader leftDoorShader, Model leftDoor, Shader rightDoorShader, Model rightDoor, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp, Door &door) {
    //set projection and view
    leftDoorShader.use();
    glm::mat4 leftDoorProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    leftDoorShader.setMat4("leftDoorProjection", leftDoorProjection);
    glm::mat4 leftDoorView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    leftDoorShader.setMat4("leftDoorView", leftDoorView);
    rightDoorShader.use();
    glm::mat4 rightDoorProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    rightDoorShader.setMat4("rightDoorProjection", rightDoorProjection);
    glm::mat4 rightDoorView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    rightDoorShader.setMat4("rightDoorView", rightDoorView);

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 leftDoorModel = glm::mat4(1.0f);
    glm::mat4 rightDoorModel = glm::mat4(1.0f);

    if(door.isDoorClosed() == true) {
        //std::cout << "ovde1" << std::endl;
        leftDoorModel = glm::translate(leftDoorModel, glm::vec3(9.5, 0.79, -11.75));
        leftDoorModel = glm::rotate(leftDoorModel, glm::radians(float(90.0)), glm::vec3(0.0f, 1.0f, 0.0f));
        rightDoorModel = glm::translate(rightDoorModel, glm::vec3(9.5, 0.79, -12.25));
        rightDoorModel = glm::rotate(rightDoorModel, glm::radians((float) 90.0), glm::vec3(0.0f, 1.0f, 0.0f));
        door.setLeftDoorPosition(glm::vec3(9.5, 0.79, -11.75));
        door.setRightDoorPosition(glm::vec3(9.5, 0.79, -12.25));
    }

    else if(door.isDoorOpened() == true) {
        //std::cout << "ovde2" << std::endl;
        leftDoorModel = glm::translate(leftDoorModel, glm::vec3(9.75, 0.79, -11.5));
        leftDoorModel = glm::rotate(leftDoorModel, glm::radians(float(0.0)), glm::vec3(0.0f, 1.0f, 0.0f));
        rightDoorModel = glm::translate(rightDoorModel, glm::vec3(9.75, 0.79, -12.5));
        rightDoorModel = glm::rotate(rightDoorModel, glm::radians((float) 180.0), glm::vec3(0.0f, 1.0f, 0.0f));
        door.setLeftDoorPosition(glm::vec3(9.75, 0.79, -11.5));
        door.setRightDoorPosition(glm::vec3(9.75, 0.79, -12.5));
    }

    else if(door.isDoorOpening() == true) {
        //std::cout << "ovde3" << std::endl;
        float doorOffset = door.getDoorOffset();
        float doorSpeed = door.getDoorSpeed();

        if (doorOffset < 90.0) {
            float translateOffsetX = 2 * doorOffset * 0.00138889;
            float translateOffsetZ = 2 * doorOffset * 0.00138889;

            leftDoorModel = glm::translate(leftDoorModel, glm::vec3(9.5 + translateOffsetX, 0.79, -11.75 + translateOffsetZ));
            leftDoorModel = glm::rotate(leftDoorModel, glm::radians((float)90.0-doorOffset), glm::vec3(0.0f, 1.0f, 0.0f));
            rightDoorModel = glm::translate(rightDoorModel, glm::vec3(9.5 + translateOffsetX, 0.79, -12.25 - translateOffsetZ));
            rightDoorModel = glm::rotate(rightDoorModel, glm::radians((float)90.0+doorOffset), glm::vec3(0.0f, 1.0f, 0.0f));
            door.setLeftDoorPosition(glm::vec3(9.5 + translateOffsetX, 0.79, -11.75 + translateOffsetZ));
            door.setRightDoorPosition(glm::vec3(9.5 + translateOffsetX, 0.79, -12.25 - translateOffsetZ));

            door.setDoorOffset(doorOffset + doorSpeed);
        }
        else {
            leftDoorModel = glm::translate(leftDoorModel, glm::vec3(9.75, 0.79, -11.5));
            leftDoorModel = glm::rotate(leftDoorModel, glm::radians(float(0.0)), glm::vec3(0.0f, 1.0f, 0.0f));
            rightDoorModel = glm::translate(rightDoorModel, glm::vec3(9.75, 0.79, -12.5));
            rightDoorModel = glm::rotate(rightDoorModel, glm::radians((float) 180.0), glm::vec3(0.0f, 1.0f, 0.0f));
            door.setLeftDoorPosition(glm::vec3(9.75, 0.79, -11.5));
            door.setRightDoorPosition(glm::vec3(9.75, 0.79, -12.5));

            door.setDoorOpening(false);
            door.setDoorOpened(true);
        }
    }

    else if(door.isDoorClosing() == true) {
        //std::cout << "ovde3" << std::endl;
        float doorOffset = door.getDoorOffset();
        float doorSpeed = door.getDoorSpeed();

        if (doorOffset > 0.0) {
            float translateOffsetX = - 2 * (90.0 - doorOffset) * 0.00138889;
            float translateOffsetZ = - 2 * (90.0 - doorOffset) * 0.00138889;

            leftDoorModel = glm::translate(leftDoorModel, glm::vec3(9.75 + translateOffsetX, 0.79, -11.5 + translateOffsetZ));
            leftDoorModel = glm::rotate(leftDoorModel, glm::radians((float)90.0-doorOffset), glm::vec3(0.0f, 1.0f, 0.0f));
            rightDoorModel = glm::translate(rightDoorModel, glm::vec3(9.75 + translateOffsetX, 0.79, -12.5 - translateOffsetZ));
            rightDoorModel = glm::rotate(rightDoorModel, glm::radians((float) 90.0+doorOffset), glm::vec3(0.0f, 1.0f, 0.0f));
            door.setLeftDoorPosition(glm::vec3(9.75 + translateOffsetX, 0.79, -11.5 + translateOffsetZ));
            door.setRightDoorPosition(glm::vec3(9.75 + translateOffsetX, 0.79, -12.5 - translateOffsetZ));

            door.setDoorOffset(doorOffset - doorSpeed);
        }
        else {
            leftDoorModel = glm::translate(leftDoorModel, glm::vec3(9.5, 0.79, -11.75));
            leftDoorModel = glm::rotate(leftDoorModel, glm::radians(float(90.0)), glm::vec3(0.0f, 1.0f, 0.0f));
            rightDoorModel = glm::translate(rightDoorModel, glm::vec3(9.5, 0.79, -12.25));
            rightDoorModel = glm::rotate(rightDoorModel, glm::radians((float) 90.0), glm::vec3(0.0f, 1.0f, 0.0f));
            door.setLeftDoorPosition(glm::vec3(9.5, 0.79, -11.75));
            door.setRightDoorPosition(glm::vec3(9.5, 0.79, -12.25));

            door.setDoorClosing(false);
            door.setDoorClosed(true);
        }
    }

    leftDoorShader.use();
    leftDoorModel = glm::scale(leftDoorModel, glm::vec3(0.452, 0.452, 0.452));
    leftDoorShader.setMat4("leftDoorModel", leftDoorModel);
    leftDoor.Draw(leftDoorShader);

    rightDoorShader.use();
    rightDoorModel = glm::scale(rightDoorModel, glm::vec3(0.452, 0.452, 0.452));
    rightDoorShader.setMat4("rightDoorModel", rightDoorModel);
    rightDoor.Draw(rightDoorShader);
}

void drawTavern(Shader tavernShader, Model tavern, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    //set projection and view
    tavernShader.use();
    glm::mat4 tavernProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    tavernShader.setMat4("tavernProjection", tavernProjection);
    glm::mat4 tavernView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    tavernShader.setMat4("tavernView", tavernView);

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 tavernModel;

    //first tavern
    tavernModel = glm::mat4(1.0f);
    tavernModel = glm::translate(tavernModel, glm::vec3(7.0, 0.25, -22.0));
    tavernModel = glm::rotate(tavernModel, glm::radians((float) -15.0), glm::vec3(0.0f, 1.0f, 0.0f));
    tavernModel = glm::scale(tavernModel, glm::vec3(1.0, 1.0, 1.0));
    tavernShader.setMat4("tavernModel", tavernModel);
    tavern.Draw(tavernShader);

    //second tavern
    //tavernModel = glm::mat4(1.0f);
    //tavernModel = glm::translate(tavernModel, glm::vec3(-1.0, 0.2, -2.0));
    //tavernModel = glm::rotate(tavernModel, glm::radians((float) 165.0), glm::vec3(0.0f, 1.0f, 0.0f));
    //tavernModel = glm::scale(tavernModel, glm::vec3(0.2, 0.2, 0.2));
    //tavernShader.setMat4("tavernModel", tavernModel);
    //tavern.Draw(tavernShader);
}

void drawBuildingBase(Shader buildingBaseShader, std::vector<Building*> &buildings, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    buildingBaseShader.use();
    glm::mat4 buildingBaseProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    buildingBaseShader.setMat4("buildingBaseProjection", buildingBaseProjection);
    glm::mat4 buildingBaseView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    buildingBaseShader.setMat4("buildingBaseView", buildingBaseView);

    // render boxes
    glBindVertexArray(BuildingBase::getBuildingBaseVAO());
    int buildingBaseLength = buildings.size();

    for (int i = 0; i < buildingBaseLength; i++)
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, buildings[i]->getBase()->getBuildingBaseTexture());
        float buildingBaseHeight = buildings[i]->getBase()->getBuildingBaseHeight();

        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 buildingBaseModel = glm::mat4(1.0f);
        buildingBaseModel = glm::translate(buildingBaseModel, buildings[i]->getAdditionalTranslate());
        buildingBaseModel = glm::rotate(buildingBaseModel, glm::radians(buildings[i]->getRotateAngle()), glm::vec3(0.0f, 1.0f, 0.0f));
        buildingBaseModel = glm::translate(buildingBaseModel, buildings[i]->getPosition() + glm::vec3(0.0, buildingBaseHeight/2.0, 0.0));
        buildingBaseModel = glm::scale(buildingBaseModel, glm::vec3(1.0, buildingBaseHeight, 1.0));
        buildingBaseShader.setMat4("buildingBaseModel", buildingBaseModel);

        //draw building base
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void drawBuildingRoof(Shader buildingRoofShader, std::vector<Building*> &buildings, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    //set projection and view
    buildingRoofShader.use();
    glm::mat4 buildingRoofProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    buildingRoofShader.setMat4("buildingRoofProjection", buildingRoofProjection);
    glm::mat4 buildingRoofView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    buildingRoofShader.setMat4("buildingRoofView", buildingRoofView);

    // render boxes
    glBindVertexArray(BuildingRoof::getBuildingRoofVAO());
    int buildingRoofLength = buildings.size();

    for (int i = 0; i < buildingRoofLength; i++) {
        if(buildings[i]->getIsWall() == false) {
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, buildings[i]->getRoof()->getBuildingRoofTexture());
            float buildingRoofHeight = buildings[i]->getRoof()->getBuildingRoofHeight();
            float buildingBaseHeight = buildings[i]->getBase()->getBuildingBaseHeight();

            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 buildingRoofModel = glm::mat4(1.0f);
            buildingRoofModel = glm::translate(buildingRoofModel, buildings[i]->getAdditionalTranslate());
            buildingRoofModel = glm::rotate(buildingRoofModel, glm::radians(buildings[i]->getRotateAngle()),glm::vec3(0.0f, 10.0f, 0.0f));
            buildingRoofModel = glm::translate(buildingRoofModel,buildings[i]->getPosition() + glm::vec3(0.0, buildingBaseHeight, 0.0));
            buildingRoofModel = glm::scale(buildingRoofModel, glm::vec3(1.0, buildingRoofHeight, 1.0));
            buildingRoofShader.setMat4("buildingRoofModel", buildingRoofModel);

            //draw building roof
            glDrawArrays(GL_TRIANGLES, 0, 24);
        }
    }
}

void drawCobblestone(Shader cobblestoneShader, Cobblestone cobblestone, unsigned cobblestone_texture, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    //bind Texture
    cobblestoneShader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cobblestone_texture);

    //set projection and view
    glm::mat4 cobblestoneProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    cobblestoneShader.setMat4("cobblestoneProjection", cobblestoneProjection);
    glm::mat4 cobblestoneView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    cobblestoneShader.setMat4("cobblestoneView", cobblestoneView);

    // render boxes
    glBindVertexArray(Cobblestone::getCobblestoneVAO());

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 cobblestoneModel = glm::mat4(1.0f);
    cobblestoneModel = glm::translate(cobblestoneModel, glm::vec3(-3.5, 0.0, -24.5));
    cobblestoneModel = glm::scale(cobblestoneModel, glm::vec3(1.0, 1.0, 1.0));
    cobblestoneShader.setMat4("cobblestoneModel", cobblestoneModel);

    //draw cobblestone
    glDrawArrays(GL_TRIANGLES, 0, 1950);
}

void drawGrass(Shader grassShader, Grass grass, unsigned grass_texture, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    //bind Texture
    grassShader.use();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, grass_texture);

    //set projection and view
    glm::mat4 grassProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    grassShader.setMat4("grassProjection", grassProjection);
    glm::mat4 grassView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    grassShader.setMat4("grassView", grassView);

    // render boxes
    glBindVertexArray(Grass::getGrassVAO());

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 grassModel = glm::mat4(1.0f);
    grassModel = glm::translate(grassModel, glm::vec3(-50.5, 0.0, -50.0));
    grassModel = glm::scale(grassModel, glm::vec3(1.0, 1.0, 1.0));
    grassShader.setMat4("grassModel", grassModel);

    //draw grass
    glDrawArrays(GL_TRIANGLES, 0, 60000);
}

void drawRoad(Shader roadShader, Road road, unsigned road_texture, float fov, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
    //bind Texture
    roadShader.use();
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, road_texture);

    //set projection and view
    glm::mat4 roadProjection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    roadShader.setMat4("roadProjection", roadProjection);
    glm::mat4 roadView = glm::lookAt(cameraPos,  cameraPos + cameraFront, cameraUp);
    roadShader.setMat4("roadView", roadView);

    // render boxes
    glBindVertexArray(Road::getRoadVAO());

    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 roadModel = glm::mat4(1.0f);
    roadModel = glm::translate(roadModel, glm::vec3(9.5, 0.0, -12.5));
    roadModel = glm::scale(roadModel, glm::vec3(1.0, 1.0, 1.0));
    roadShader.setMat4("roadModel", roadModel);

    //draw road
    glDrawArrays(GL_TRIANGLES, 0, 240);
}

#endif //PROJECT_BASE_DRAWING_H
