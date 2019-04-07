#include "PlayerAttributes.h"

PlayerAttributes::PlayerAttributes()
{
	REGISTER_COMPONENT(PlayerAttributes)
}

bool PlayerAttributes::init(const rapidjson::Value& json_object) {
	return true;
}

void PlayerAttributes::post_init() {

}

void PlayerAttributes::update(float dt) {

}

void PlayerAttributes::destroy() {

}

void PlayerAttributes::editor() {
	ImGui::Indent();

	ImGui::Unindent();
}

Entity PlayerAttributes::getSelection()
{
	return selection;
}

void PlayerAttributes::setSelection(Entity selected)
{
	selection = selected;
	// std::cout << "Selected->Name: " << selection->getName() << std::endl;
}

