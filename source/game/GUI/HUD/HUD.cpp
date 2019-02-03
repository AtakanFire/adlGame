#include "HUD.h"

#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adl_editor/adlEditor_manager.h"

HUD::HUD()
{
	REGISTER_ENTITY(HUD)
}

HUD::~HUD()
{

}

void HUD::init() {

}

void HUD::update(float dt) 
{
	adlEditor_manager* adlEditorMan = &adlEditor_manager::get();

	if (!adlEditorMan->onEdit() && openHUD_)
	{
		MainMenu();
	}

}


void HUD::serialize(PrettyWriter<StringBuffer>& writer)
{
	adlEntity::serialize(writer);

}

void HUD::deserialize(const rapidjson::Value& reader)
{
	adlEntity::deserialize(reader);

}

void HUD::MainMenu()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Text("adl Game");
		ImGui::Text("|");

		if (ImGui::BeginMenu("Some Stats"))
		{

			ImGui::EndMenu();
		}
		ImGui::Text("|");

		if (ImGui::BeginMenu("Other Stats"))
		{
			if (ImGui::MenuItem("Options", "F2"))
			{
				
			}

			ImGui::EndMenu();
		}

		ImGui::Text("|");

		if (ImGui::BeginMenu("Another Stats"))
		{
			ImGui::Checkbox("Open HUD", &openHUD_);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}
