#include "MovementComponent.h"

#include "game/GameComponents/Misc/SelectableComponent.h"


MovementComponent::MovementComponent()
{
	REGISTER_COMPONENT(MovementComponent)
}

bool MovementComponent::init(const rapidjson::Value& json_object) {
	return true;
}

void MovementComponent::post_init() {
	if (isMovable)
	{
		SharedPointer<SelectableComponent> selfSelected(owner->get_component<SelectableComponent>("SelectableComponent"));
		selfSelected->set_static(false);
	}
}

void MovementComponent::update(float dt) {

}

void MovementComponent::destroy() {

}

void MovementComponent::editor() {
	ImGui::Indent();

	ImGui::Unindent();
}

void MovementComponent::move(adlVec3 targetPos)
{
	SharedPointer<SelectableComponent> selfSelected(owner->get_component<SelectableComponent>("SelectableComponent"));
	selfSelected->apply_force(targetPos - selfSelected->get_position(), 10);
}