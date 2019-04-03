#ifndef GameGenericTypedef_h__
#define GameGenericTypedef_h__

#include "engine/adl_entities/adlEntity.h"

typedef adlEntity_shared_ptr Entity;

template<typename T>	
using SharedPointer = std::shared_ptr<T>;


//typedef adlEntity_component adlEntityComponent;
//typedef adlTransform_component adlTransformComponent;
//typedef adlRender_component adlRenderComponent;




#endif //GameGenericTypedef_h__
