#include "ConstructionComponent.h"

ConstructionComponent::ConstructionComponent()
{
	REGISTER_COMPONENT(ConstructionComponent)
}

bool ConstructionComponent::init(const rapidjson::Value& json_object) {
	return true;
}

void ConstructionComponent::post_init() {

}

void ConstructionComponent::update(float dt) {
	std::cout << "Construction" << std::endl;
}

void ConstructionComponent::destroy() {

}

void ConstructionComponent::editor() {
	ImGui::Indent();

	ImGui::Unindent();
}

