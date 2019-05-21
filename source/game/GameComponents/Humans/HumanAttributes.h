#ifndef HumanAttributes_h__
#define HumanAttributes_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "engine/adlScene_manager.h"

#include "game/GameComponents/Resources/ResourceAttributes.h"
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
		
		std::vector<std::string> parents = { "", "" }; // Mother, Father -> Life -> Copulate -> Assign, EntityName(EntityId) 


		// Parents, House ~ ->  Spouse, Childs, Health
	};

	struct HumanRequires { // Needs: Food, Cloth, Happy, ~ -> House, Spouse
		// ~ Basic Game Version of "Maslow's Hierarchy of Needs" ~
		std::vector<std::string> needsTypes = { "Food", "Cloth", "Happy" };

		float needs[3] = { 0 }; // Food, Cloth, Happy

		float needRates[3] = { 1.06, 0.001, 0.0001 }; // needsTypes

		float &find(std::string type) {
			std::vector<std::string>::iterator c = std::find(needsTypes.begin(), needsTypes.end(), type);
			if (c != needsTypes.cend()) {
				return needs[std::distance(needsTypes.begin(), c)];
			}
		}
	};

	struct HumanExperiences { // If there is time, human can learn everything.
		std::vector<std::string> consumableTypes = { "Food", "Wood", "Stone", "Metal", "Cotton" };
		std::vector<std::string> derivedTypes = { "Cloth", "Lumber", "Gold" };
		std::vector<std::string> humanlyTypes = { "Happy", "Knowledge"};

		float consumable[ConsumableResources::ConsumableResourcesCOUNT] = { 0 }; // Food, Wood, Stone, Metal, Cotton
		float derived[DerivedResources::DerivedResourcesCOUNT] = { 0 }; // Cloth, Lumber, Gold
		float humanly[HumanlyResources::HumanlyResourcesCOUNT] = { 0 }; // Happy, Knowledge
	};

	struct HumanCarry { 
		std::string takenObject = "";

		float taken = 0;
		float maxCarry = 20;
	};

	HumanProperties &getProperties() { return properties; };
	HumanRequires &getRequires() { return requires; };
	AllResources &getExperiences() { return experiences; };
	HumanCarry &getCarried() { return carrying; };

	void took(std::string taken, float weight);
	void dropped();
	void bring();

	void gathering(SharedPointer<ResourceAttributes> res, float cost);
	void production(std::string entityName, adlVec3 location = adlVec3(0, 0, 0));

	bool checkExperience(std::string entityName);
	void gainExperience(std::string type, float exp);

	void live(); 
	void satisfy(std::string type, float val); // Auto Use stored resources
	void die();

private:

	adlScene_manager* sceneManager;

	HumanProperties properties;
	HumanRequires requires;
	AllResources experiences;
	HumanCarry carrying;

	bool died = false;
};

#endif //HumanAttributes_h__
