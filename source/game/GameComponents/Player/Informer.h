#ifndef Informer_h__
#define Informer_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"

class Informer : public adlEntity_component { 

public:

	Informer();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

private:

};

#endif //Informer_h__
