#include "entities/E_test.h"
#include "components_tags.h"

struct Entity InstantiateTestEntity() {
    struct Entity E_Test;
    InitializeEntity(&E_Test);
    printf("Spawned Test Entity %d\n", E_Test.id);
    return E_Test;
}