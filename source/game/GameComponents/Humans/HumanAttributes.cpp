#include "HumanAttributes.h"

#include "engine/adl_entities/adlTransform_component.h"

#include "game/GameComponents/Misc/SelectableComponent.h"


HumanAttributes::HumanAttributes()
{
	REGISTER_COMPONENT(HumanAttributes)
}

bool HumanAttributes::init(const rapidjson::Value& json_object) {
	const rapidjson::Value& propertiesObject = json_object["properties"];
	const rapidjson::Value& requiresObject = json_object["requires"];

	properties.name = propertiesObject["name"].GetString();
	properties.age = propertiesObject["age"].GetFloat();

	properties.owned.load(propertiesObject["owned"]);
	properties.experiences.load(propertiesObject["experiences"]);

	requires.needs.load(requiresObject["needs"]);

	return true;
}

void HumanAttributes::post_init() {

}

void HumanAttributes::update(float dt) {
	SharedPointer<SelectableComponent> selectCom(owner->get_component<SelectableComponent>("SelectableComponent"));

	if (selectCom->getTarget())
	{
		SharedPointer<adlTransform_component> transCom(owner->get_component<adlTransform_component>("adlTransform_component"));
		transCom->set_rotation(adlVec3(transCom->get_rotation().x, transCom->get_rotation().y + 1 * dt, transCom->get_rotation().z));
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

		if (ImGui::CollapsingHeader("Experiences"))
		{
			ImGui::Text("Consumable Resources");
			ImGui::Indent();
			properties.experiences.editor();
			ImGui::Unindent();
		}


		if (ImGui::CollapsingHeader("Owned"))
		{
			ImGui::Text("Consumable Resources");
			ImGui::Indent();
			properties.owned.editor();
			ImGui::Unindent();
		}


		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Requires"))
	{
		ImGui::Indent();

		if (ImGui::CollapsingHeader("Needs"))
		{
			ImGui::Text("Consumable Resources");
			ImGui::Indent();
			requires.needs.editor();
			ImGui::Unindent();
		}

		ImGui::Unindent();
	}

	ImGui::Unindent();
}


