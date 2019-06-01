#ifndef PlayerAttributes_h__
#define PlayerAttributes_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameGeneric/GameStructures.h"
#include "game/GameGeneric/GameManager.h"

class PlayerAttributes : public adlEntity_component { 

public:

	PlayerAttributes();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	AllResources &getStored() { return stored; };

	Entity getSelection();
	void setSelection(Entity selected);

	std::string onConstruct = "";

	bool checkStoredResources(std::string entityName);
	bool checkStoredResources(std::vector<std::string> types, std::vector<float> values);
	void useStoredResources(std::string entityName);
	void useStoredResources(std::vector<std::string> types, std::vector<float> values);
	bool useStoredResource(std::string type, float val);

private:

	Entity selection;

	AllResources stored;


};

#endif //PlayerAttributes_h__
