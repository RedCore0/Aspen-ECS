#include "ecs_core.h"
#include "test_component.h"
#include "value_increase_system.h"
#include "Test_Entity.h"

int main(void) {
    InitializeStack(&AvailableIDs);

    struct Entity E_Test = InstantiateEntity(Test);
    AddComponent(&E_Test, Test, 1);
    ValueIncrease();
    RemoveComponent(&E_Test, Test);
    DestroyEntity(&E_Test);
    return 0;
}