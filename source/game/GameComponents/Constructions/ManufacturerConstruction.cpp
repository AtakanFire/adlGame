#include "ManufacturerConstruction.h"

#include "game/GameComponents/Player/PlayerAttributes.h"
#include "game/GameGeneric/GameManager.h"
#include "game/GameComponents/HUD/HUDComponent.h"
#include "game/GameGeneric/GameFunctions.h"
#include "game/GameComponents/Misc/SelectableComponent.h"
#include "game/GameComponents/Constructions/StorageConstruction.h"

ManufacturerConstruction::ManufacturerConstruction()
{
	REGISTER_COMPONENT(ManufacturerConstruction)
}

bool ManufacturerConstruction::init(const rapidjson::Value& json_object) {
	const rapidjson::Value& c = json_object["consume"];
	const rapidjson::Value& d = json_object["derive"];

	const rapidjson::Value& ccTypes = c["types"];
	const rapidjson::Value& ccValues = c["values"];

	const rapidjson::Value& ddTypes = d["types"];
	const rapidjson::Value& ddValues = d["values"];

	std::vector<std::string> cTypes(GameFunctions::SplitString(ccTypes.GetString(), " "));
	std::vector<std::string> cValues(GameFunctions::SplitString(ccValues.GetString(), " "));

	for (size_t i = 0; i < cTypes.size(); i++)
	{
		consume.find(cTypes[i]) = (std::stof(cValues[i]));
	}

	std::vector<std::string> dTypes(GameFunctions::SplitString(ddTypes.GetString(), " "));
	std::vector<std::string> dValues(GameFunctions::SplitString(ddValues.GetString(), " "));

	for (size_t i = 0; i < dTypes.size(); i++)
	{
		derive.find(dTypes[i]) = (std::stof(dValues[i]));
	}

	return true;
}

void ManufacturerConstruction::post_init() {

}

void ManufacturerConstruction::update(float dt) {
	
}

void ManufacturerConstruction::destroy() {

}

void ManufacturerConstruction::editor() {
	ImGui::Indent();

	ImGui::Unindent();
}

bool ManufacturerConstruction::fabricating()
{
	GameManager* gameMan = &GameManager::get();
	SharedPointer<PlayerAttributes> player = (gameMan->getTaggedEntity("Player")->get_component<PlayerAttributes>("PlayerAttributes")).lock();
	SharedPointer<StorageConstruction> storage = (gameMan->getTaggedEntity("StorageConstruction")->get_component<StorageConstruction>("StorageConstruction")).lock();
	SharedPointer<HUDComponent> hud = (gameMan->getTaggedEntity("HUD")->get_component<HUDComponent>("HUDComponent")).lock();

	if (player->checkStoredResources(consume.allTypes(), consume.allValues()))
	{
		for (int i = 0; i < derive.allTypes().size(); i++)
		{
			storage->storing(derive.allTypes()[i], derive.allValues()[i]);
		}
		player->useStoredResources(consume.allTypes(), consume.allValues());
	}
	return false;
}

