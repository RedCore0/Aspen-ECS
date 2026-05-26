#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include "ecs_core.h"

extern int TestComponentData[MAX_ENTITIES];

void AddTest(const struct Entity *entity, int value);
bool HasTest(const struct Entity *entity);
int GetTest(const struct Entity *entity);
void RemoveTest(const struct Entity *entity);

#endif