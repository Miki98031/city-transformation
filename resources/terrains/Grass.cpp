//
// Created by mihailo on 7.4.24..
//

#include "Grass.h"
float Grass::vertices[Grass::count] = {0}; // Initialize static member variable
int Grass::counterVertices = 0;
int Grass::counterVAO = 0;
int Grass::counterTexture = 0;
unsigned Grass::grassVAO = 0;
unsigned Grass::grassTexture = 0;
unsigned Grass::grassVBO = 0;