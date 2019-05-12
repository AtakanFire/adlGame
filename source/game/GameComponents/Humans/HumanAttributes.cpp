#include "HumanAttributes.h"

#include "engine/adl_entities/adlTransform_component.h"

#include "game/GameComponents/Misc/SelectableComponent.h"
#include "game/GameComponents/Constructions/StorageConstruction.h"

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

		Entity entity = selectCom->getTarget()->getOwner();

		if (entity->has_component("ResourceAttributes"))
		{
			SharedPointer<ResourceAttributes> res(entity->get_component<ResourceAttributes>("ResourceAttributes"));
			gathering(res, 0.02 * dt);
		}
		else if (entity->has_component("ConstructionAttributes"))
		{
			SharedPointer<StorageConstruction> construction(entity->get_component<StorageConstruction>("StorageConstruction"));
			construction->storing(owner, carrying.takenObject, carrying.taken);
			dropped();
		}

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

void HumanAttributes::took(std::string taken, float weight)
{
	if (taken != carrying.takenObject || carrying.takenObject == "")
	{
		carrying.taken = 0;
		carrying.takenObject = taken;
	} 
	
	if (carrying.taken + weight <= carrying.maxCarry)
	{
		carrying.taken += weight;
		gainExperience(taken, weight/10); // experienceRate = weight/10 for now
	}
	else {
		carrying.taken = carrying.maxCarry;
	}
}

void HumanAttributes::dropped()
{
	carrying.takenObject = "";
	carrying.taken = 0;
}

void HumanAttributes::bring()
{
	GameManager* gameMan = &GameManager::get();
	SharedPointer<StorageConstruction> storage = (gameMan->getTaggedEntity("StorageConstruction")->get_component<StorageConstruction>("StorageConstruction")).lock();
	storage->storing(owner, carrying.takenObject, carrying.taken);
	dropped();
}

void HumanAttributes::gathering(SharedPointer<ResourceAttributes> res, float cost)
{
	if (carrying.taken < carrying.maxCarry && !res->exhaustion(cost))
	{
		took(res->getProperties().type, cost);
	}
	else 
	{
		bring();
	}
}

void HumanAttributes::production(std::string entityName, adlVec3 location)
{
	Entity construction = sceneManager->add_entity_to_scene(entityName);
	SharedPointer<SelectableComponent> selectCom(construction->get_component<SelectableComponent>("SelectableComponent"));
	selectCom->set_position(location);
}

void HumanAttributes::gainExperience(std::string type, float exp)
{
	experiences.find(type) += exp;
}
