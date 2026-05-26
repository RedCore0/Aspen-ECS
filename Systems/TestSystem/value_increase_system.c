#include "value_increase_system.h"
#include "ecs_core.h"
#include  "test_component.h"

void ValueIncrease(void) {
    uint64_t systemSignature = COMPONENT_TEST;
    for (int i = 0; i < ActiveEntityCount; i++) {
        int EntityID = ActiveEntities[i];
        if ((EntitySignatures[i] & systemSignature) == systemSignature) {
            struct Entity CurrentEntity = {.id = EntityID, .generation = 0};
            int currentValue = GetComponent(&CurrentEntity, Test);
            currentValue += 1;
            TestComponentData[CurrentEntity.id] = currentValue;
            printf("Entity %d value increased to %d\n", EntityID, currentValue);
        }
    }
}