#include "StorageConstruction.h"

#include "game/GameComponents/Player/PlayerAttributes.h"


StorageConstruction::StorageConstruction()
{
	REGISTER_COMPONENT(StorageConstruction)
}

bool StorageConstruction::init(const rapidjson::Value& json_object) {
	return true;
}

void StorageConstruction::post_init() {
	GameManager* gameMan = &GameManager::get();
	gameMan->setTaggedEntity("StorageConstruction", owner);
}

void StorageConstruction::update(float dt) {

}

void StorageConstruction::destroy() {

}

void StorageConstruction::editor() {
	ImGui::Indent();

	ImGui::Unindent();
}

void StorageConstruction::storing(Entity& entity, std::string takenObject, float taken)
{
	if (takenObject != "")
	{

		GameManager* gameMan = &GameManager::get();
		SharedPointer<PlayerAttributes> player = (gameMan->getTaggedEntity("Player")->get_component<PlayerAttributes>("PlayerAttributes")).lock();
		AllResources* stored = &player->getStored();
		stored->find(takenObject) += taken;
	}
}


