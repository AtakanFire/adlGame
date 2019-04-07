#ifndef HumanAttributes_h__
#define HumanAttributes_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "engine/adlScene_manager.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameGeneric/GameStructures.h"

class HumanAttributes : public adlEntity_component { 

public:

	HumanAttributes();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	// Human Attributes
	struct HumanProperties {
		std::string name = "";
		float age = 18;

		ConsumableResources owned;
		ConsumableResources experiences;
	};

	struct HumanRequires { 
		ConsumableResources needs; // ~ Basic Game Version of "Maslow's Hierarchy of Needs" ~
	};

	HumanProperties properties;
	HumanRequires requires;

	void gathering();
	void production();

	void movement(adlVec3 targetPos);


private:

	adlScene_manager* sceneManager;

};

#endif //HumanAttributes_h__
