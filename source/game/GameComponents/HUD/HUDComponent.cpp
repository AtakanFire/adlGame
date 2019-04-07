#include "HUDComponent.h"

#include "game/GameComponents/Misc/SelectableComponent.h"
#include "game/GameComponents/Resources/ResourceAttributes.h"


HUDComponent::HUDComponent()
{
	REGISTER_COMPONENT(HUDComponent)
}

bool HUDComponent::init(const rapidjson::Value& json_object) {
	return true;
}

void HUDComponent::post_init() {
	editorMan = &adlEditor_manager::get();
	player = &PlayerAttributes::get();
}

void HUDComponent::update(float dt) {

	if (!editorMan->onEdit())
	{
		mainMenu();
		mainLayout();
	}
}

void HUDComponent::destroy() {

}

void HUDComponent::editor() {
	ImGui::Indent();

	ImGui::Unindent();
}


void HUDComponent::mainMenu()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Text("adlGame");

		ImGui::Text("|");

		if (player->getSelection() != nullptr)
		{
			SharedPointer<SelectableComponent> selected(player->getSelection()->get_component<SelectableComponent>("SelectableComponent"));
			ImGui::Text("Selected: ");
			ImGui::Text(player->getSelection()->getName().c_str());

			if (selected->getTarget())
			{
				ImGui::Text(" -> ");
				ImGui::Text(selected->getTarget()->getOwner()->getName().c_str());
			}

		}


		ImGui::EndMainMenuBar();
	}
}

void HUDComponent::mainLayout()
{
	/*ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;*/
	ImGuiIO& io = ImGui::GetIO();
	//std::cout << "ImGui: " << io.DisplaySize.x << "x" << io.DisplaySize.y << std::endl;

	
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 120));
	ImGui::SetNextWindowPos(ImVec2(0, io.DisplaySize.y - 120));
	ImGui::SetNextWindowBgAlpha(0.4f);
	if (ImGui::Begin("Main Bottom Frame", (bool*)(!editorMan->onEdit()), ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar))
	{

		if (player->getSelection() != nullptr && player->getSelection()->has_component("ResourceAttributes"))
		{
			SharedPointer<ResourceAttributes> res(player->getSelection()->get_component<ResourceAttributes>("ResourceAttributes"));
			res->editor();
		}

		ImGui::End();
	}
}


