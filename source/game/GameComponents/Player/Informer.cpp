#include "Informer.h"

#include "game/GameGeneric/GameFunctions.h"
#include "game/GameGeneric/GameManager.h"

Informer::Informer()
{
	REGISTER_COMPONENT(Informer)
}

bool Informer::init(const rapidjson::Value& json_object) {
	const rapidjson::Value& req = json_object["requires"];
	
	for (rapidjson::Value::ConstValueIterator itr = req.Begin(); itr != req.End(); ++itr) {
		std::string name = (*itr)["name"].GetString();
		std::string require = (*itr)["require"].GetString();
		std::string t = (*itr)["types"].GetString();
		std::string v = (*itr)["values"].GetString();

		std::vector<std::string> types(GameFunctions::SplitString(t, ","));

		std::vector<std::string> valuesString(GameFunctions::SplitString(v, ","));
		std::vector<float> values = { };
		for (size_t i = 0; i < valuesString.size(); i++)
		{
			values.push_back(std::stof(valuesString[i]));
		}

		GameObjectInfo objectInfo(name, require, types, values);
		gameObjectsInfo.push_back(objectInfo);
	}

	return true;
}

void Informer::post_init() {
	GameManager* gameMan = &GameManager::get();
	gameMan->setTaggedEntity("Informer", owner);
}

void Informer::update(float dt) {

}

void Informer::destroy() {

}

void Informer::editor() {
	ImGui::Indent();

	if (ImGui::CollapsingHeader("Requires"))
	{
		for (size_t i = 0; i < gameObjectsInfo.size(); i++)
		{

			ImGui::Indent();
			
			if (ImGui::CollapsingHeader(gameObjectsInfo[i].name.c_str()))
			{
				ImGui::Indent();

				ImGui::Text("%s", gameObjectsInfo[i].require.c_str());


				for (size_t j = 0; j < gameObjectsInfo[i].types.size(); j++)
				{
					ImGui::Text("%s: %.2f", gameObjectsInfo[i].types[j].c_str(), gameObjectsInfo[i].values[j]);
				}

				ImGui::Unindent();
			}

			ImGui::Unindent();
		}
	}


	ImGui::Unindent();
}

Informer::GameObjectInfo Informer::getGameObjectInfo(std::string name, std::string require)
{
	
	for (int i = 0; i < gameObjectsInfo.size(); i++)
	{
		if (gameObjectsInfo[i].name == name && gameObjectsInfo[i].require == require)
		{
			return gameObjectsInfo[i];
		}
	}
	return Informer::GameObjectInfo();
}

