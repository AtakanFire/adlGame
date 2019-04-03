#include "SelectableComponent.h"

#include "engine/adlInput.h"


SelectableComponent::SelectableComponent()
{
	REGISTER_COMPONENT(SelectableComponent)
	
}

bool SelectableComponent::init(const rapidjson::Value& json_object) {
	adlPhysics_component::init(json_object);
	return true;
}

void SelectableComponent::post_init() {
	adlPhysics_component::post_init();
	player = &PlayerAttributes::get();

}

void SelectableComponent::update(float dt) {
	adlPhysics_component::update(dt);

}

void SelectableComponent::destroy() {
	adlPhysics_component::destroy();

}

void SelectableComponent::editor() {
	ImGui::Indent();

	if (ImGui::CollapsingHeader("Physics"))
	{
		ImGui::Indent();

		adlPhysics_component::editor();

		ImGui::Unindent();
	}


	ImGui::Unindent();
}

void SelectableComponent::on_mouse_hover_start() {
	//std::cout << "Mouse hover start" << std::endl;
}

void SelectableComponent::under_mouse() {
	adlInput* input = &adlInput::get();
	
	if (input->get_mouse_down(ADL_BUTTON_LEFT)) {
		isSelected = true;
		player->setSelection(this->owner);
		std::cout << "Selected" << std::endl;
	}
	//std::cout << "Under mouse" << std::endl;
}

void SelectableComponent::on_mouse_hover_end() {
	//std::cout << "Mouse hover end" << std::endl;
}

bool SelectableComponent::getSelection() {
	return isSelected;
}