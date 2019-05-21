#include "ResourceAttributes.h"

#include "engine/adl_entities/adlTransform_component.h"
#include "game/GameGeneric/EasingFunctions.h"

ResourceAttributes::ResourceAttributes()
{
	REGISTER_COMPONENT(ResourceAttributes)
}

bool ResourceAttributes::init(const rapidjson::Value& json_object) {
	const rapidjson::Value& propertiesObject = json_object["properties"];

	properties.name = propertiesObject["name"].GetString();
	properties.type = propertiesObject["type"].GetString();

	rapidjson::Value::ConstValueIterator itr = propertiesObject["resource"].Begin();

	const rapidjson::Value& minRes = *itr;
	const rapidjson::Value& maxRes = *++itr;

	properties.resource.x = minRes.GetFloat();
	properties.resource.y = maxRes.GetFloat();

	return true;
}

void ResourceAttributes::post_init() {

}

void ResourceAttributes::update(float dt) {
	//grow(0.01 * dt);

	if (owner->has_component("adlTransform_component")) // Resize by resource
	{
		SharedPointer<adlTransform_component> transCom(owner->get_component<adlTransform_component>("adlTransform_component"));
		transCom->set_scale(EasingFunctions::easeInElastic(properties.resource.x / properties.resource.y) + 0.2f);
	}	

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
		static char typeName[20] = {};

		ImGui::Text(("Type Name: " + properties.type).c_str());
		ImGui::InputText("##typeName", typeName, sizeof(typeName));
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

	ImGui::Unindent();
}

ResourceAttributes::ResourceProperties ResourceAttributes::getProperties()
{
	return properties;
}

void ResourceAttributes::grow(float growing)
{
	properties.resource.x += growing;
	normalizeResource();
}

bool ResourceAttributes::exhaustion(float exhausting)
{
	properties.resource.x -= exhausting;
	normalizeResource();
	return properties.resource.x == 0.0f;
}

void ResourceAttributes::normalizeResource()
{
	if (properties.resource.x > properties.resource.y)
	{
		properties.resource.x = properties.resource.y;
	}
	else if (properties.resource.x < 0)
	{
		properties.resource.x = 0;
	}
}

