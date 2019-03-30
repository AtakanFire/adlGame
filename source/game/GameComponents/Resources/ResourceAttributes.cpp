#include "ResourceAttributes.h"

ResourceAttributes::ResourceAttributes()
{
	REGISTER_COMPONENT(ResourceAttributes)
}

bool ResourceAttributes::init(const rapidjson::Value& json_object) {
	const rapidjson::Value& propertiesObject = json_object["properties"];
	const rapidjson::Value& requiresObject = json_object["requires"];

	properties.name = propertiesObject["name"].GetString();

	rapidjson::Value::ConstValueIterator itr = propertiesObject["resource"].Begin();

	const rapidjson::Value& minRes = *itr;
	const rapidjson::Value& maxRes = *++itr;

	properties.resource.x = minRes.GetFloat();
	properties.resource.y = maxRes.GetFloat();

	requires.minExperience = requiresObject["minExperience"].GetFloat();

	return true;
}

void ResourceAttributes::post_init() {

}

void ResourceAttributes::update(float dt) {

}

void ResourceAttributes::destroy() {

}

void ResourceAttributes::editor() {
	ImGui::Indent();

	ImGui::Text("Attributes");

	if (ImGui::CollapsingHeader("Properties"))
	{
		ImGui::Indent();

		ImGui::Indent();
		static char resName[20] = {};

		ImGui::Text(("Resource Name: " + properties.name).c_str());
		ImGui::InputText("##resName", resName, sizeof(resName));
		if (ImGui::Button("Refresh Name"))
		{
			properties.name = resName;
		}
		ImGui::Unindent();


		ImGui::Indent();
		ImGui::Text("Current Resource");
		ImGui::SliderFloat("##resource", &properties.resource.x, 0.0f, properties.resource.y);
		ImGui::Unindent();

		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Requires"))
	{
		ImGui::Indent();

		ImGui::Indent();
		ImGui::Text("Minimum Experience(0f, 100f)");
		ImGui::SliderFloat("##minExperience", &requires.minExperience, 0.0f, 100.0f);
		ImGui::Unindent();
	}


	ImGui::Unindent();
}

