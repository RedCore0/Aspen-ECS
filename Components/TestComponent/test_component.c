#include "test_component.h"

int TestComponentData[MAX_ENTITIES];

void AddTest(const struct Entity *entity, int value) {
    TestComponentData[entity->id] = value;
    EntitySignatures[entity->id] |= COMPONENT_TEST;
    printf("Adding Test Component with value of %d\n", value);
}

bool HasTest(const struct Entity *entity) {
    return EntitySignatures[entity->id] & COMPONENT_TEST;
}

int GetTest(const struct Entity *entity) {
    return TestComponentData[entity->id];
}

void RemoveTest(const struct Entity *entity) {
    EntitySignatures[entity->id] &= ~COMPONENT_TEST;
}