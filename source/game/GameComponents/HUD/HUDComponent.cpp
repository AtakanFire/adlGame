#include "HUDComponent.h"

#include "engine/adl_editor/adlEditor_manager.h"


HUDComponent::HUDComponent()
{
	REGISTER_COMPONENT(HUDComponent)
}

bool HUDComponent::init(const rapidjson::Value& json_object) {
	return true;
}

void HUDComponent::post_init() {

}

void HUDComponent::update(float dt) {
	adlEditor_manager* editorMan = &adlEditor_manager::get();
	bool onEdit = editorMan->onEdit();
	if (!onEdit)
	{
		MainMenu();
	}
}

void HUDComponent::MainMenu()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Text("adlGame");

		ImGui::Text("|");



		ImGui::EndMainMenuBar();
	}
}



void HUDComponent::destroy() {

}

void HUDComponent::editor() {
	ImGui::Indent();

	ImGui::Unindent();
}

