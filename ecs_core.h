#ifndef ECS_CORE_H
#define ECS_CORE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_ENTITIES 5000

extern int EntityIDs;
extern int ActiveEntityCount;
extern int ActiveEntities[MAX_ENTITIES];
extern int EntityToIndex[MAX_ENTITIES];
extern uint64_t EntitySignatures[MAX_ENTITIES];

typedef enum {
    COMPONENT_NONE = 0,
    COMPONENT_TEST = 1 << 0
    //keep adding up to 1 << 63
} ComponentType;

#define GetComponent(entity, CompName) Get##CompName(entity)
#define AddComponent(entity, CompName, ...) Add##CompName(entity, __VA_ARGS__)
#define HasComponent(entity, CompName) Has##CompName(entity)
#define RemoveComponent(entity, CompName) Remove##CompName(entity)

#define InstantiateEntity(Type, ...) Instantiate##Type##Entity(__VA_ARGS__)

struct Entity {
    int id;
    int generation;
};

typedef struct {
    int arr [MAX_ENTITIES];
    int top;
} Stack;

extern Stack AvailableIDs;

void InitializeStack(Stack *stack);
bool StackEmpty(const Stack *stack);
bool StackFull(const Stack *stack);
void PushToStack(Stack *stack, const int id);
int PopFromStack(Stack *stack);
int PeekStack(const Stack *stack);

void InitializeEntity(struct Entity *entity);
void DestroyEntity(struct Entity *entity);

#endif