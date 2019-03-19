#ifndef ConstructionComponent_h__
#define ConstructionComponent_h__

#include "engine/adl_entities/adlEntity_component.h"
#include "game/GameGeneric/GameGenericTypedef.h"

class ConstructionComponent : public adlEntity_component { 

public:

	ConstructionComponent();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

private:

};

#endif //ConstructionComponent_h__
