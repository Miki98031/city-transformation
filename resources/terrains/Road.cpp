//
// Created by mihailo on 8.4.24..
//

#include "Road.h"
std::string Road::roadTexturePath = "resources/textures/road.jpg";
std::string Road::roadTextureSpecularPath = "resources/textures/73_street_paving_rounded_cobblestone_texture-seamless-hr_specular.jpg";
float Road::vertices[Road::count] = {0}; // Initialize static member variable
int Road::counterVertices = 0;
int Road::counterVAO = 0;
int Road::counterTexture = 0;
unsigned Road::roadVAO = 0;
unsigned Road::roadTexture = 0;
unsigned Road::roadVBO = 0;
int Road::counterTextureSpecular = 0;
unsigned Road::roadTextureSpecular = 0;