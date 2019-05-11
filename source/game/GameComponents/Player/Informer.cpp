#include "Informer.h"

Informer::Informer()
{
	REGISTER_COMPONENT(Informer)
}

bool Informer::init(const rapidjson::Value& json_object) {




	return true;
}

void Informer::post_init() {

}

void Informer::update(float dt) {

}

void Informer::destroy() {

}

void Informer::editor() {
	ImGui::Indent();

	ImGui::Unindent();
}

