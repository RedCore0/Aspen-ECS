#ifndef COMPONENTS_TAGS_H
#define COMPONENTS_TAGS_H

#include "ecs_core.h"

typedef enum {
    COMPONENT_NONE = -1,

    #define COMPONENT(Name, Body) COMPONENT_##Name,
    #define TAG(Name)             COMPONENT_TAG_##Name,
    #include "components_tags.def"

#undef COMPONENT
    #undef TAG

    COMPONENT_COUNT
} ComponentType;

#define COMPONENT(Name, Body) typedef struct Body Name##Component;
#define TAG(Name)
#include "components_tags.def"
#undef COMPONENT
#undef TAG


#define COMPONENT(Name, Body) DECLARE_COMPONENT_TYPE(Name, Name##Component)
#define TAG(Name)             DECLARE_TAG_TYPE(Name)
#include "components_tags.def"
#undef COMPONENT
#undef TAG

#endif