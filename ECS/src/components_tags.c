#include "components_tags.h"

#define COMPONENT(Name, Body) DEFINE_COMPONENT_TYPE(Name, Name##Component)
#define TAG(Name)             DEFINE_TAG_TYPE(Name)

#include "components_tags.def"

#undef COMPONENT
#undef TAG