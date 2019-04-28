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
	AllResources& stored = player->getStored();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Total Stats"))
		{
			//std::cout << stored.consumable[0] << std::endl;

			ImGui::TextColored(ImVec4(0.5, 0.8, 0.4, 1.0),"Consumable Resources");
			progressBarGenerator(stored.consumableTypes, stored.consumable, 800, false);
			ImGui::Separator();

			ImGui::TextColored(ImVec4(0.5, 0.8, 0.4, 1.0), "Derived Resources");
			progressBarGenerator(stored.derivedTypes, stored.derived, 800, false);
			ImGui::Separator();


			ImGui::TextColored(ImVec4(0.5, 0.8, 0.4, 1.0), "Humanly Resources");
			progressBarGenerator(stored.humanlyTypes, stored.humanly, 800, false);

			ImGui::EndMenu();
		}

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

			//ImGui::Text("|");

		}

		//ImGui::Text("|");

		ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - ImGui::CalcTextSize("| adlGame").x);
		ImGui::Text("| adlGame");

		// ImGui::Checkbox("Good View", &showAll);

		// Total Resources, Human Count etc.

		// Individuals' Needs -> on a window

		// ~Science Tree, Reputation(Dignity) House

		// Settings etc.

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
	
	HumanAttributes::HumanProperties& pro = human->getProperties();
	HumanAttributes::HumanRequires& req = human->getRequires();
	AllResources& exp = human->getExperiences();
	HumanAttributes::HumanCarry& carrying = human->getCarried();
	

	std::string title("Human : " + pro.name + (selected->getTarget() ? " -> " : " ") + (selected->getTarget() ? selected->getTarget()->getOwner()->getName() : " "));

	if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
	{
		
		ImGui::Indent();

		ImGui::Separator();
		//ImGui::Text("Human : %s %s %s", pro.name.c_str(), selected->getTarget() ? "->" : " ", selected->getTarget() ? selected->getTarget()->getOwner()->getName().c_str() : " ");

		ImGui::Columns(4, "Columns", true);
		{
			ImGui::Text("%s", "General Properties");

			if (ImGui::CollapsingHeader("Properties"))
			{
				ImGui::Indent();

				ImGui::Text("Name: %s", pro.name.c_str());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Change Name with 'Right Click'");
				if (ImGui::BeginPopupContextItem("Change Name"))
				{
					ImGui::SetKeyboardFocusHere();
					char humanName[64] = "";
					if (ImGui::InputText("Human Name", humanName, 64, ImGuiInputTextFlags_EnterReturnsTrue))
					{
						pro.name = humanName;
					}

					ImGui::EndPopup();
				}

				std::string age = (pro.age < 18) ? "Child" : (pro.age < 30) ? "Teenager" : (pro.age < 50) ? "Adult" : "Elderly";
				ImGui::Text("Age: %.0f", pro.age);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("%s\n%s", age.c_str(), "People die when they get old.");

				std::string gender = (pro.gender == 0) ? "Female" : "Male";
				ImGui::Text("Gender: %s", gender.c_str());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Gender");

				ImGui::Unindent();
			}

			if (carrying.takenObject != "")
			{
				ImGui::Text("Carried: %s(%.0f)", carrying.takenObject.c_str(), carrying.taken);
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Requires");

			if (ImGui::CollapsingHeader("Needs"))
			{
				ImGui::Indent();

				progressBarGenerator(req.needsTypes, req.needs);

				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Productions");

			if (ImGui::CollapsingHeader("Abilities"))
			{
				ImGui::Indent();

				if (ImGui::Button("Build Construction", ImVec2(-1, 40))) {
					human->production("Construction");
				}

				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Experiences");
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("If there is time, human can learn everything.\n");

			if (ImGui::CollapsingHeader("Experiences"))
			{
				ImGui::Indent();

				if (ImGui::CollapsingHeader("Consumable"))
				{
					ImGui::Indent();

					progressBarGenerator(exp.consumableTypes, exp.consumable);

					ImGui::Unindent();
				}

				if (ImGui::CollapsingHeader("Derived"))
				{
					ImGui::Indent();
					
					progressBarGenerator(exp.derivedTypes, exp.derived);

					ImGui::Unindent();
				}

				if (ImGui::CollapsingHeader("Humanly"))
				{
					ImGui::Indent();
					
					progressBarGenerator(exp.humanlyTypes, exp.humanly);

					ImGui::Unindent();
				}	

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

	ConstructionAttributes::ConstructionProperties& pro = con->getProperties();
	ConstructionAttributes::ConstructionRequires& req = con->getRequires();

	std::string title("Construction : " + pro.name);

	if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
	{
		ImGui::Indent();

		ImGui::Separator();
		//ImGui::Text("Construction: %s", pro.name.c_str());

		ImGui::Columns(3, "Columns", true);
		{
			ImGui::Text("%s", "Properties");

			if (ImGui::CollapsingHeader("Properties"))
			{
				ImGui::Indent();

				ImGui::Text("Name: %s", pro.name.c_str());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Construction Name");

				ImGui::Text("Durability: %.0f", pro.durability);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Construction Durability");

				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Requires");

			if (ImGui::CollapsingHeader("Requires"))
			{
				ImGui::Indent();

				if (ImGui::CollapsingHeader("Minimum Experiences Needs"))
				{
					ImGui::Indent();

					ImGui::Text("%s", "Consumable");
					progressBarGenerator(req.experiences.consumableTypes, req.experiences.consumable);

					ImGui::Text("%s", "Derived");
					progressBarGenerator(req.experiences.derivedTypes, req.experiences.derived);

					ImGui::Text("%s", "Humanly");
					progressBarGenerator(req.experiences.humanlyTypes, req.experiences.humanly);


					ImGui::Unindent();
				}
				if (ImGui::CollapsingHeader("Minimum Resource Needs"))
				{
					ImGui::Indent();


					ImGui::Text("%s", "Consumable");
					progressBarGenerator(req.resources.consumableTypes, req.resources.consumable);

					ImGui::Text("%s", "Derived");
					progressBarGenerator(req.resources.derivedTypes, req.resources.derived);

					ImGui::Text("%s", "Humanly");
					progressBarGenerator(req.resources.humanlyTypes, req.resources.humanly);

					ImGui::Unindent();
				}


				ImGui::Unindent();
			}

			ImGui::NextColumn();
			ImGui::Text("%s", "Stats");

			if (ImGui::CollapsingHeader("Stats"))
			{
				ImGui::Indent();


				char buf[32];
				sprintf(buf, "%.0f/%.0f", 1.0f, 1.0f);

				ImGui::Text("Construction: ");
				ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
				ImGui::ProgressBar(1 / 1, ImVec2(0.f, 0.f), buf);

				ImGui::Unindent();
			}

		}
		ImGui::Columns(1);

		ImGui::Unindent();

		ImGui::End();
	}
}

void HUDComponent::progressBarGenerator(std::vector<std::string> text, float value[], float limit, bool indent)
{
	for (int i = 0; i < text.capacity(); i++)
	{
		if (indent)
			ImGui::Indent();
		
		if (limit == -1) // Unlimited
		{
			char buf[32];
			sprintf(buf, "%s: %.0f", text[i].c_str(), value[i]);
			ImGui::ProgressBar(value[i], ImVec2(-1.f, 0.f), buf);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("%s", text[i].c_str());
		}
		else
		{
			char buf[32];
			sprintf(buf, "%s", text[i].c_str(), value[i], limit);
			ImGui::ProgressBar(value[i] / limit, ImVec2(-1.f, 0.f), buf);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("%s: %.0f/%.0f(Current/Max)", text[i].c_str(), value[i], limit);

			/*
			char buf[32];
			sprintf(buf, "%s: %.0f/%.0f", text[i].c_str(), value[i], limit);
			ImGui::ProgressBar(value[i] / limit, ImVec2(-1.f, 0.f), buf);
			if (ImGui::IsItemHovered())
			ImGui::SetTooltip("%s(Current/Max)", text[i].c_str());
			*/
		}

		//ImGui::TextDisabled("%s: %.0f/%.0f", text[i].c_str(), value[i], 100.0f);
		

		if (indent)
			ImGui::Unindent();
	}
}
