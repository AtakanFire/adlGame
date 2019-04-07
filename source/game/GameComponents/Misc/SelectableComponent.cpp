#include "SelectableComponent.h"

#include "engine/adlInput.h"

#include "game/GameGeneric/GameFunctions.h"

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

}

void SelectableComponent::under_mouse() {
	if (GameFunctions::CheckImGuiClicked())
	{
		return;
	}

	adlInput* input = &adlInput::get();
	
	if (input->get_mouse_down(ADL_BUTTON_LEFT)) {
		player->setSelection(this->owner);
		std::cout << owner->getName() << " Selected!" << std::endl;
	} else if (input->get_mouse_down(ADL_BUTTON_RIGHT)) {
		if (player->getSelection() != nullptr && player->getSelection()->has_component("SelectableComponent"))
		{
			SharedPointer<SelectableComponent> selected(player->getSelection()->get_component<SelectableComponent>("SelectableComponent"));
			
			if (selected->owner->has_component("HumanAttributes") && selected->owner != owner)
			{
				selected->setTarget(this);
				//std::cout << selected->owner->getName() << " -> " << selected->getTarget()->getOwner()->getName() << std::endl;
			}
		}
		std::cout << owner->getName() << " Targeted!" << std::endl;
	}
}

void SelectableComponent::on_mouse_hover_end() {

}

SelectableComponent* SelectableComponent::getTarget()
{
	return target;
}

void SelectableComponent::setTarget(SelectableComponent* newTarget)
{
	target = newTarget;
}
