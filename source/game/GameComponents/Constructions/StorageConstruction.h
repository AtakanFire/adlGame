#ifndef StorageConstruction_h__
#define StorageConstruction_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"

class StorageConstruction : public adlEntity_component { 

public:

	StorageConstruction();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	void storing(Entity &entity, std::string takenObject, float taken);
	void production(std::string entityName);

private:

};

#endif //StorageConstruction_h__
