#include "systems/S_value_increase.h"
#include "ecs_core.h"
#include "components_tags.h"

void ValueIncrease(void) {
    ForEachEntityWith(entityID, COMPONENT_Test) {
        int* test_value = &GetComponent(entityID, Test).value;
        *test_value+=1;
        printf("Entity %d value increased to %d\n",entityID, *test_value);
    }
}