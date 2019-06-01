#include "PlayerAttributes.h"

#include "game/GameComponents/Player/Informer.h"
#include "game/GameGeneric/GameFunctions.h"


PlayerAttributes::PlayerAttributes()
{
	REGISTER_COMPONENT(PlayerAttributes)
}

bool PlayerAttributes::init(const rapidjson::Value& json_object) {
	const rapidjson::Value& storedJSON = json_object["stored"];
	const rapidjson::Value& t = storedJSON["types"];
	const rapidjson::Value& s = storedJSON["store"];
	
	std::string tt  =  t.GetString();
	std::vector<std::string> storedTypes = GameFunctions::SplitString(tt, " ");

	rapidjson::Value::ConstValueIterator itr = s.Begin();
	const rapidjson::Value& storedInfo = *itr;
	stored.find(storedTypes[0]) = storedInfo.GetFloat();

	for (int i = 1; i < storedTypes.size(); i++)
	{
		const rapidjson::Value& counter = *++itr;
		stored.find(storedTypes[i]) = counter.GetFloat();
	}

	return true;
}

void PlayerAttributes::post_init() {
	GameManager* gameMan = &GameManager::get();
	gameMan->setTaggedEntity("Player", owner);
}

void PlayerAttributes::update(float dt) {

}

void PlayerAttributes::destroy() {

}

void PlayerAttributes::editor() {
	ImGui::Indent();

	if (ImGui::CollapsingHeader("Stored"))
		stored.editor();
	
	ImGui::Unindent();
}

Entity PlayerAttributes::getSelection()
{
	return selection;
}

void PlayerAttributes::setSelection(Entity selected)
{
	selection = selected;
	// std::cout << "Selected->Name: " << selection->getName() << std::endl;
}

bool PlayerAttributes::checkStoredResources(std::string entityName)
{
	GameManager* gameMan = &GameManager::get();
	SharedPointer<Informer> informer = (gameMan->getTaggedEntity("Informer")->get_component<Informer>("Informer")).lock();
	return checkStoredResources(informer->getGameObjectInfo(entityName).types, informer->getGameObjectInfo(entityName).values);
}

bool PlayerAttributes::checkStoredResources(std::vector<std::string> types, std::vector<float> values)
{
	for (int i = 0; i < types.size(); i++)
	{
		if (stored.find(types[i]) < values[i])
		{
			return false;
		}
	}

	return true;
}

void PlayerAttributes::useStoredResources(std::string entityName)
{
	GameManager* gameMan = &GameManager::get();
	SharedPointer<Informer> informer = (gameMan->getTaggedEntity("Informer")->get_component<Informer>("Informer")).lock();


	useStoredResources(informer->getGameObjectInfo(entityName).types, informer->getGameObjectInfo(entityName).values);
}


void PlayerAttributes::useStoredResources(std::vector<std::string> types, std::vector<float> values)
{
	for (int i = 0; i < types.size(); i++)
	{
		stored.find(types[i]) -= values[i];
	}
}

bool PlayerAttributes::useStoredResource(std::string type, float val)
{
	if (stored.find(type) - val > 0)
	{
		stored.find(type) -= val;
		return true;
	}
	return false;
}


