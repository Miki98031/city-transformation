//
// Created by mihailo on 6.4.24..
//

#include "Cobblestone.h"
float Cobblestone::vertices[Cobblestone::numberOfVertices] = {0}; // Initialize static member variable
int Cobblestone::counterVertices = 0;
int Cobblestone::counterVAO = 0;
int Cobblestone::counterTexture = 0;
unsigned Cobblestone::cobblestoneVAO = 0;
unsigned Cobblestone::cobblestoneTexture = 0;
unsigned Cobblestone::cobblestoneVBO = 0;