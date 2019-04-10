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
		float age = 18; // Child(<18), Teenager(18<30), Adult(30<50), Elderly(50<)

		// Gender, Parents, House ~ ->  Spouse, Childs

		ConsumableResources owned; // Remove
		ConsumableResources experiences; // Remove
	};

	struct HumanRequires { // Needs: Food, Cloth, Happy, ~ -> House, Spouse
		ConsumableResources needs; // ~ Basic Game Version of "Maslow's Hierarchy of Needs" ~
	};

	struct HumanExperiences { // If there is time, human can learn everything.
		ConsumableResources cr;
		DerivedResources dr;
		HumanlyResources hr;
	};


	HumanProperties properties;
	HumanRequires requires;
	//HumanExperiences experiences;

	void gathering();
	void production();

	void movement(adlVec3 targetPos);


private:

	adlScene_manager* sceneManager;

};

#endif //HumanAttributes_h__
