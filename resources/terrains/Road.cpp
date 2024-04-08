//
// Created by mihailo on 8.4.24..
//

#include "Road.h"
float Road::vertices[Road::count] = {0}; // Initialize static member variable
int Road::counterVertices = 0;
int Road::counterVAO = 0;
int Road::counterTexture = 0;
unsigned Road::roadVAO = 0;
unsigned Road::roadTexture = 0;
unsigned Road::roadVBO = 0;