#include "ecs_core.h"

int EntityIDs = 0;
int ActiveEntityCount = 0;
int ActiveEntities[MAX_ENTITIES];
int EntityToIndex[MAX_ENTITIES];
uint64_t EntitySignatures[MAX_ENTITIES] = {0};
Stack AvailableIDs;

void InitializeStack(Stack *stack) {
    stack->top = -1;
}

bool StackEmpty(const Stack *stack) {
    return (stack->top == -1);
}

bool StackFull(const Stack *stack) {
    return (stack->top == MAX_ENTITIES-1);
}

void PushToStack(Stack *stack, const int id) {
    if (StackFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = id;
    //printf("Pushed %d\n", id);
}

int PopFromStack(Stack *stack) {
    if (StackEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    int popped = stack->arr[stack->top];
    stack->top--;
    printf("Popped %d\n", popped);
    return popped;
}

int PeekStack(const Stack *stack) {
    if (StackEmpty(stack)) {
        printf("Stack Empty\n");
        return -1;
    }
    return stack->arr[stack->top];
}


void InitializeEntity(struct Entity *entity) {
    if (!StackEmpty(&AvailableIDs)) {
        entity->id = PopFromStack(&AvailableIDs);
    }else {
        entity->id = EntityIDs;
        EntityIDs++;
        entity->generation = 0;
    }

    ActiveEntities[ActiveEntityCount] = entity->id;
    EntityToIndex[entity->id] = ActiveEntityCount;
    ActiveEntityCount++;
}

void DestroyEntity(struct Entity *entity) {
    EntitySignatures[entity->id] = COMPONENT_NONE;

    int indexOfDestroyEntity = EntityToIndex[entity->id];
    int indexOfLastEntity = ActiveEntityCount - 1;
    int lastEntityId = ActiveEntities[indexOfLastEntity];

    ActiveEntities[indexOfDestroyEntity] = lastEntityId;
    EntityToIndex[lastEntityId] = indexOfDestroyEntity;

    ActiveEntityCount--;

    PushToStack(&AvailableIDs, entity->id);
    entity->generation++;
    entity->id = -1;
}