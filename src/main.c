#include "ecs_core.h"
#include "components_tags.h"
#include "systems/S_value_increase.h"
#include "entities/E_test.h"

int main(void) {
    InitializeStack(&AvailableIDs);

    struct Entity E_Test = InstantiateEntity(Test);
    AddComponent(&E_Test, Test, 1);
    AddTag(&E_Test, Default);
    printf("Entity with value: %d\n", GetComponent(E_Test.id, Test).value);
    if (HasTag(&E_Test, Default)) {
        printf("Has default tag\n");
    }
    ValueIncrease();
    RemoveComponent(&E_Test, Test);
    DestroyEntity(&E_Test);
    return 0;
}