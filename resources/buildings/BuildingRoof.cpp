//
// Created by mihailo on 6.4.24..
//

#include "BuildingRoof.h"


float BuildingRoof::vertices[BuildingRoof::numberOfVertices] = {0}; // Initialize static member variable
int BuildingRoof::counterVertices = 0;
int BuildingRoof::counterVAO = 0;
unsigned BuildingRoof::buildingRoofVAO = 0;
unsigned BuildingRoof::buildingRoofVBO = 0;