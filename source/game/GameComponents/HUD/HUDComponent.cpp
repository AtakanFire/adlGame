#include "HUDComponent.h"

#include "game/GameGeneric/GameFunctions.h"

#include "game/GameComponents/Misc/SelectableComponent.h"
#include "game/GameComponents/Humans/HumanAttributes.h"
#include "game/GameComponents/Resources/ResourceAttributes.h"
#include "game/GameComponents/Constructions/ConstructionAttributes.h"


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

	ImGuiStyle& style = ImGui::GetStyle();
	defaultStyle = style;
	GameFunctions::ImGuiStyler();
}

void HUDComponent::update(float dt) {

	if (!editorMan->onEdit())
	{
		mainMenu();
		if (player->getSelection())
		{
			mainLayout();
		}
	}
}

void HUDComponent::destroy() {

}

void HUDComponent::editor() {
	ImGui::Indent();
	if (ImGui::Button("Be Game Style", ImVec2(-1, 20))) {
		GameFunctions::ImGuiStyler();
	}
	if (ImGui::Button("Reverse Style", ImVec2(-1, 20))) {
		ImGuiStyle& style = ImGui::GetStyle();
		style = defaultStyle;
	}
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
	ImGuiIO& io = ImGui::GetIO();

	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 160, 160));
	ImGui::SetNextWindowPos(ImVec2(80, io.DisplaySize.y - 180));
	ImGui::SetNextWindowBgAlpha(0.4f);

	if (player->getSelection() != nullptr && player->getSelection()->has_component("HumanAttributes"))
	{		
		humanAttributes();
	}
	else if (player->getSelection() != nullptr && player->getSelection()->has_component("ResourceAttributes"))
	{
		resourceAttributes();
	}
	else if (player->getSelection() != nullptr && player->getSelection()->has_component("ConstructionAttributes"))
	{
		constructionAttributes();
	}
	else if (player->getSelection() != nullptr)
	{
		std::string title("Some Thing Selected!");

		if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
		{

		}
	}
}

void HUDComponent::humanAttributes()
{
	SharedPointer<HumanAttributes> human(player->getSelection()->get_component<HumanAttributes>("HumanAttributes"));
	SharedPointer<SelectableComponent> selected(player->getSelection()->get_component<SelectableComponent>("SelectableComponent"));

	std::string title("Human : " + human->properties.name + (selected->getTarget() ? "->" : " ") + (selected->getTarget() ? selected->getTarget()->getOwner()->getName() : " "));

	if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
	{
		
		ImGui::Indent();

		ImGui::Separator();
		//ImGui::Text("Human : %s %s %s", human->properties.name.c_str(), selected->getTarget() ? "->" : " ", selected->getTarget() ? selected->getTarget()->getOwner()->getName().c_str() : " ");

		ImGui::Columns(4, "Columns", true);
		{
			ImGui::Text("%s", "Properties");

			if (ImGui::CollapsingHeader("Properties"))
			{
				ImGui::Indent();

				ImGui::Text("Name: %s", human->properties.name.c_str());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Change Name with 'Right Click'");
				if (ImGui::BeginPopupContextItem("Change Name"))
				{
					char humanName[64] = "";
					if (ImGui::InputText("Human Name", humanName, 64, ImGuiInputTextFlags_EnterReturnsTrue))
					{
						human->properties.name = humanName;
					}

					ImGui::EndPopup();
				}

				ImGui::Text("Age: %.0f", human->properties.age);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("People die when they get old.");

				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Requires");

			if (ImGui::CollapsingHeader("Needs"))
			{
				ImGui::Indent();


				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Productions");

			if (ImGui::CollapsingHeader("Abilities"))
			{
				ImGui::Indent();

				if (ImGui::Button("Build Construction", ImVec2(-1, 40))) {
					human->production();
				}

				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Experiences");

			if (ImGui::CollapsingHeader("Experiences"))
			{
				ImGui::Indent();

				human->properties.experiences.editor();

				ImGui::Unindent();
			}
		}
		ImGui::Columns(1);

		ImGui::Unindent();

		ImGui::End();
	}
}

void HUDComponent::resourceAttributes() {
	SharedPointer<ResourceAttributes> res(player->getSelection()->get_component<ResourceAttributes>("ResourceAttributes"));
	SharedPointer<SelectableComponent> selected(player->getSelection()->get_component<SelectableComponent>("SelectableComponent"));

	std::string title("Resource : " + res->getProperties().name);

	if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
	{
		ImGui::Indent();

		ImGui::Separator();
		//ImGui::Text("Resource: %s", res->getProperties().name.c_str());

		ImGui::Columns(3, "Columns", true);
		{
			ImGui::Text("%s", "Properties");

			if (ImGui::CollapsingHeader("Properties"))
			{
				ImGui::Indent();

				ImGui::Text("Name: %s", res->getProperties().name.c_str());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Resources Name");

				ImGui::Text("Type: %s", res->getProperties().type.c_str());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Resource Type");

				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Requires");

			if (ImGui::CollapsingHeader("Requires"))
			{
				ImGui::Indent();



				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Stats");

			if (ImGui::CollapsingHeader("Stats"))
			{
				ImGui::Indent();

				char buf[32];
				sprintf(buf, "%.0f/%.0f", res->getProperties().resource.x, res->getProperties().resource.y);

				ImGui::Text("Resources: ");
				ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
				ImGui::ProgressBar(res->getProperties().resource.x / res->getProperties().resource.y, ImVec2(0.f, 0.f), buf);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Resource Percentage\nCurrent/Max");

				ImGui::Unindent();
			}

		}
		ImGui::Columns(1);

		ImGui::Unindent();


		ImGui::End();
	}
}

void HUDComponent::constructionAttributes()
{
	SharedPointer<ConstructionAttributes> con(player->getSelection()->get_component<ConstructionAttributes>("ConstructionAttributes"));
	SharedPointer<SelectableComponent> selected(player->getSelection()->get_component<SelectableComponent>("SelectableComponent"));

	std::string title("Construction : " + con->properties.name);

	if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
	{
		ImGui::Indent();

		ImGui::Separator();
		//ImGui::Text("Construction: %s", con->properties.name.c_str());

		ImGui::Columns(3, "Columns", true);
		{
			ImGui::Text("%s", "Properties");

			if (ImGui::CollapsingHeader("Properties"))
			{
				ImGui::Indent();

				ImGui::Text("Name: %s", con->properties.name.c_str());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Construction Name");

				ImGui::Text("Age: %.0f", con->properties.durability);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Construction Durability");

				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Requires");

			if (ImGui::CollapsingHeader("Requires"))
			{
				ImGui::Indent();



				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Stats");

			if (ImGui::CollapsingHeader("Stats"))
			{
				ImGui::Indent();

				char buf[32];
				sprintf(buf, "%.0f/%.0f", 0, 1);

				ImGui::Text("Construction: ");
				ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
				ImGui::ProgressBar(0 / 1, ImVec2(0.f, 0.f), buf);

				ImGui::Unindent();
			}

		}
		ImGui::Columns(1);

		ImGui::Unindent();


		ImGui::End();
	}
}
