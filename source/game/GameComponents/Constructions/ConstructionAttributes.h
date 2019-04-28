#ifndef ConstructionAttributes_h__
#define ConstructionAttributes_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameGeneric/GameStructures.h"

class ConstructionAttributes : public adlEntity_component { 

public:

	ConstructionAttributes();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	// Construction Attributes
	struct ConstructionProperties {
		std::string name = "";
		float durability = 100;
	};

	struct ConstructionRequires {
		AllResources experiences; // Min Experience Needs
		AllResources resources; // Min Resource Needs
	};


	ConstructionProperties &getProperties() { return properties; };
	ConstructionRequires &getRequires() { return requires; };

	void gathering(Entity &entity, std::string takenObject, float taken);
	void production(std::string entityName);

private:

	ConstructionProperties properties;
	ConstructionRequires requires;


};

#endif //ConstructionAttributes_h__
