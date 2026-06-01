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

#define BITSET_CHUNKS 4
typedef struct {
    uint64_t chunks[BITSET_CHUNKS];
} ComponentSignature;
extern ComponentSignature EntitySignatures[MAX_ENTITIES];

void Signature_SetBit(ComponentSignature *sig, int bitIndex);
void Signature_ClearBit(ComponentSignature *sig, int bitIndex);
bool Signature_TestBit(const ComponentSignature *sig, int bitIndex);
void Signature_ClearAll(ComponentSignature *sig);
bool Signature_Matches(const ComponentSignature *entitySig, const ComponentSignature *systemSig);

#define AddComponent(entity, CompName, ...) \
    Add##CompName(entity, (CompName##Component){__VA_ARGS__})
#define GetComponent(entityID, CompName) CompName##ComponentData[entityID]
#define HasComponent(entity, CompName) Has##CompName(entity)
#define RemoveComponent(entity, CompName) Remove##CompName(entity)

#define DECLARE_COMPONENT_TYPE(CompName, TypeName) \
    extern TypeName CompName##ComponentData[MAX_ENTITIES]; \
    void Add##CompName(const struct Entity *entity, TypeName value); \
    bool Has##CompName(const struct Entity *entity); \
    void Remove##CompName(const struct Entity *entity);

#define DEFINE_COMPONENT_TYPE(CompName, TypeName) \
    TypeName CompName##ComponentData[MAX_ENTITIES]; \
    void Add##CompName(const struct Entity *entity, TypeName value) { \
        CompName##ComponentData[entity->id] = value; \
        Signature_SetBit(&EntitySignatures[entity->id], COMPONENT_##CompName); \
    } \
    bool Has##CompName(const struct Entity *entity) { \
        return Signature_TestBit(&EntitySignatures[entity->id], COMPONENT_##CompName); \
    } \
    void Remove##CompName(const struct Entity *entity) { \
        Signature_ClearBit(&EntitySignatures[entity->id], COMPONENT_##CompName); \
    }

static ComponentSignature CreateSignatureFromIDs(const int ids[], int count) {
    ComponentSignature sig = {0};
    for (int i = 0; i < count; i++) {
        Signature_SetBit(&sig, ids[i]);
    }
    return sig;
}
#define ForEachEntityWith(idVarName, ...) \
    for (struct { int i; ComponentSignature sig; int active; } _loop = { \
        .i = 0, \
        .sig = CreateSignatureFromIDs((int[]){__VA_ARGS__}, sizeof((int[]){__VA_ARGS__}) / sizeof(int)), \
        .active = 1 \
    }; \
    _loop.active && _loop.i < ActiveEntityCount; \
    _loop.i++) \
    for (int idVarName = ActiveEntities[_loop.i]; _loop.active; _loop.active = 0) \
        if (Signature_Matches(&EntitySignatures[idVarName], &_loop.sig))

#define AddTag(entity, TagName) AddTag_##TagName(entity)
#define HasTag(entity, TagName) HasTag_##TagName(entity)
#define RemoveTag(entity, TagName) RemoveTag_##TagName(entity)

#define DECLARE_TAG_TYPE(TagName) \
    void AddTag_##TagName(const struct Entity *entity); \
    bool HasTag_##TagName(const struct Entity *entity); \
    void RemoveTag_##TagName(const struct Entity *entity);

#define DEFINE_TAG_TYPE(TagName) \
    void AddTag_##TagName(const struct Entity *entity) { \
    Signature_SetBit(&EntitySignatures[entity->id], COMPONENT_TAG_##TagName); \
    } \
    bool HasTag_##TagName(const struct Entity *entity) { \
        return Signature_TestBit(&EntitySignatures[entity->id], COMPONENT_TAG_##TagName); \
    } \
    void RemoveTag_##TagName(const struct Entity *entity) { \
        Signature_ClearBit(&EntitySignatures[entity->id], COMPONENT_TAG_##TagName); \
    }

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