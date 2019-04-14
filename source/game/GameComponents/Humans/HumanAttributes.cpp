#include "HumanAttributes.h"

#include "engine/adl_entities/adlTransform_component.h"

#include "game/GameComponents/Misc/SelectableComponent.h"
#include "game/GameComponents/Resources/ResourceAttributes.h"
#include "game/GameComponents/Constructions/ConstructionAttributes.h"

HumanAttributes::HumanAttributes()
{
	REGISTER_COMPONENT(HumanAttributes)
}

bool HumanAttributes::init(const rapidjson::Value& json_object) {
	const rapidjson::Value& propertiesObject = json_object["properties"];
	const rapidjson::Value& requiresObject = json_object["requires"];
	const rapidjson::Value& needs = requiresObject["needs"];

	properties.name = propertiesObject["name"].GetString();
	properties.age = propertiesObject["age"].GetFloat();
	properties.gender = propertiesObject["gender"].GetFloat();

	rapidjson::Value::ConstValueIterator itr = needs.Begin();

	const rapidjson::Value& firstNeed = *itr;
	requires.needs[0] = firstNeed.GetFloat();

	for (int i = 1; i < requires.needsTypes.capacity(); i++)
	{
		const rapidjson::Value& needCounter = *++itr;
		requires.needs[i] = needCounter.GetFloat();
	}


	return true;
}

void HumanAttributes::post_init() {
	sceneManager = &adlScene_manager::get();
}

void HumanAttributes::update(float dt) {
	SharedPointer<SelectableComponent> selectCom(owner->get_component<SelectableComponent>("SelectableComponent"));

	if (selectCom->getTarget())
	{
		SharedPointer<adlTransform_component> transCom(owner->get_component<adlTransform_component>("adlTransform_component"));
		transCom->set_rotation(adlVec3(transCom->get_rotation().x, transCom->get_rotation().y + 1 * dt, transCom->get_rotation().z));
	
		gathering(selectCom->getTarget()->getOwner(), 0.02 * dt);
	}
}

void HumanAttributes::destroy() {

}

void HumanAttributes::editor() {
	ImGui::Indent();

	if (ImGui::CollapsingHeader("Properties"))
	{
		ImGui::Indent();

		ImGui::Indent();
		static char conName[20] = {};

		ImGui::Text(("Resource Name: " + properties.name).c_str());
		ImGui::InputText("##resName", conName, sizeof(conName));
		if (ImGui::Button("Refresh Name"))
		{
			properties.name = conName;
		}
		ImGui::Unindent();


		ImGui::Indent();
		ImGui::Text("Age");
		ImGui::SliderFloat("##age", &properties.age, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Requires"))
	{
		ImGui::Indent();

		if (ImGui::CollapsingHeader("Needs"))
		{
			ImGui::Text("Needs");
			ImGui::Indent();

			for (int i = 0; i < requires.needsTypes.capacity(); i++)
			{
				ImGui::Indent();

				ImGui::Text("%s(0f, 100f)", requires.needsTypes[i].c_str());
				ImGui::SliderFloat(std::string("##" + requires.needsTypes[i]).c_str(), &requires.needs[i], 0.0f, 100.0f);

				ImGui::Unindent();
			}

			ImGui::Unindent();
		}

		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Experiences"))
	{
		ImGui::Indent();

		experiences.editor();

		ImGui::Unindent();
	}

	ImGui::Unindent();
}

void HumanAttributes::gathering(Entity &entity, float cost)
{
	if (entity->has_component("ResourceAttributes"))
	{
		SharedPointer<ResourceAttributes> res(entity->get_component<ResourceAttributes>("ResourceAttributes"));
		res->exhaustion(cost);

		if (res->getProperties().type != carrying.carriedType)
		{
			carrying.carriedType = res->getProperties().type;
			carrying.carried = 0;
		}

		carrying.carried += cost;

		PlayerAttributes* player = &PlayerAttributes::get();

		AllResources* stored = &player->getStored();

		stored->find(res->getProperties().type) += cost;



	}
}

void HumanAttributes::production(std::string entityName)
{
	Entity construction = sceneManager->add_entity_to_scene(entityName);
	SharedPointer<SelectableComponent> selectCom(construction->get_component<SelectableComponent>("SelectableComponent"));
	SharedPointer<adlTransform_component> transCom(construction->get_component<adlTransform_component>("adlTransform_component"));
	selectCom->set_position(adlVec3(0, 0, -10));
	transCom->set_position(adlVec3(0, 0, -10));
}
