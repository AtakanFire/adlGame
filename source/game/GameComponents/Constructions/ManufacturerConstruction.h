#ifndef ManufacturerConstruction_h__
#define ManufacturerConstruction_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameGeneric/GameStructures.h"

class ManufacturerConstruction : public adlEntity_component { 

public:

	ManufacturerConstruction();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	bool fabricating();

	AllResources &getConsume() { return consume; };
	AllResources &getDerive() { return derive; };

private:

	AllResources consume;
	AllResources derive;


};

#endif //ManufacturerConstruction_h__
