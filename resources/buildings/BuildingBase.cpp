//
// Created by mihailo on 6.4.24..
//

#include "BuildingBase.h"

float BuildingBase::vertices[BuildingBase::numberOfVertices] = {0}; // Initialize static member variable
int BuildingBase::counterVertices = 0;
int BuildingBase::counterVAO = 0;
unsigned BuildingBase::buildingBaseVAO = 0;
unsigned BuildingBase::buildingBaseVBO = 0;
