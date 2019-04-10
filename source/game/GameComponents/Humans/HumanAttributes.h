#ifndef HumanAttributes_h__
#define HumanAttributes_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "engine/adlScene_manager.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameGeneric/GameStructures.h"
#include "game/GameGeneric/GameFunctions.h"

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
		int gender = 1; // Female, Male 
		
		// Parents, House ~ ->  Spouse, Childs, Health
	};

	struct HumanRequires { // Needs: Food, Cloth, Happy, ~ -> House, Spouse
		// ~ Basic Game Version of "Maslow's Hierarchy of Needs" ~
		std::vector<std::string> needsTypes = { "Food", "Cloth", "Happy" };

		float needs[3] = { 0 }; // Food, Cloth, Happy
	};

	struct HumanExperiences { // If there is time, human can learn everything.
		std::vector<std::string> consumableTypes = { "Food", "Wood", "Stone", "Metal", "Cotton" };
		std::vector<std::string> derivedTypes = { "Cloth", "Lumber", "Gold" };
		std::vector<std::string> humanlyTypes = { "Happy", "Knowledge"};

		float consumable[ConsumableResources::ConsumableResourcesCOUNT] = { 0 }; // Food, Wood, Stone, Metal, Cotton
		float derived[DerivedResources::DerivedResourcesCOUNT] = { 0 }; // Cloth, Lumber, Gold
		float humanly[HumanlyResources::HumanlyResourcesCOUNT] = { 0 }; // Happy, Knowledge
	};

	HumanProperties &getProperties() { return properties; };
	HumanRequires &getRequires() { return requires; };
	AllResources &getExperiences() { return experiences; };
	//HumanExperiences &getHas() { return has; };

	void gathering();
	void production();

	void movement(adlVec3 targetPos);


private:

	adlScene_manager* sceneManager;

	HumanProperties properties;
	HumanRequires requires;
	AllResources experiences;
	//HumanExperiences has; //Owned, has, existing

};

#endif //HumanAttributes_h__
