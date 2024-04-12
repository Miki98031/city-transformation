//
// Created by mihailo on 7.4.24..
//

#include "Grass.h"
std::string Grass::grassTexturePath = "resources/textures/grass.jpg";
std::string Grass::grassTextureSpecularPath = "resources/textures/10_grass_cutted_texture_PBR_SPEC.jpg";
float Grass::vertices[Grass::count] = {0}; // Initialize static member variable
int Grass::counterVertices = 0;
int Grass::counterVAO = 0;
int Grass::counterTexture = 0;
unsigned Grass::grassVAO = 0;
unsigned Grass::grassTexture = 0;
unsigned Grass::grassVBO = 0;
int Grass::counterTextureSpecular = 0;
unsigned Grass::grassTextureSpecular = 0;