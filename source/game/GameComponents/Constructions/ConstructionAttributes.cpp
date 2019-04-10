#include "ConstructionAttributes.h"

ConstructionAttributes::ConstructionAttributes()
{
	REGISTER_COMPONENT(ConstructionAttributes)
}

bool ConstructionAttributes::init(const rapidjson::Value& json_object) {
	const rapidjson::Value& propertiesObject = json_object["properties"];
	const rapidjson::Value& requiresObject = json_object["requires"];

	properties.name = propertiesObject["name"].GetString();
	properties.durability = propertiesObject["durability"].GetFloat();

	return true;
}

void ConstructionAttributes::post_init() {

}

void ConstructionAttributes::update(float dt) {

}

void ConstructionAttributes::destroy() {

}

void ConstructionAttributes::editor() {
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
		ImGui::Text("Durability");
		ImGui::SliderFloat("##durability", &properties.durability, 0.0f, 100.0f);
		ImGui::Unindent();

		ImGui::Unindent();
	}


	if (ImGui::CollapsingHeader("Requires"))
	{
		ImGui::Indent();

		if (ImGui::CollapsingHeader("Minimum Experiences"))
		{
			ImGui::Indent();

			requires.experiences.editor();

			ImGui::Unindent();
		}

		if (ImGui::CollapsingHeader("Minimum Resources"))
		{
			ImGui::Indent();
			
			requires.resources.editor();

			ImGui::Unindent();
		}

		ImGui::Unindent();
	}


	ImGui::Unindent();
}

