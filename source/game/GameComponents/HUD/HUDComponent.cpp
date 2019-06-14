#include "HUDComponent.h"

#include "game/GameGeneric/GameFunctions.h"

#include "game/GameComponents/Misc/SelectableComponent.h"
#include "game/GameComponents/Humans/HumanAttributes.h"
#include "game/GameComponents/Resources/ResourceAttributes.h"
#include "game/GameComponents/Constructions/ConstructionAttributes.h"
#include "game/GameComponents/Constructions/ManufacturerConstruction.h"
#include "game/GameComponents/Player/Informer.h"


HUDComponent::HUDComponent()
{
	REGISTER_COMPONENT(HUDComponent)
}

bool HUDComponent::init(const rapidjson::Value& json_object) {
	return true;
}

void HUDComponent::post_init() {
	editorMan = &adlEditor_manager::get();
	GameManager* gameMan = &GameManager::get();
	gameMan->setTaggedEntity("HUD", owner);

	player = (gameMan->getTaggedEntity("Player")->get_component<PlayerAttributes>("PlayerAttributes")).lock();

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
		gameLog.Draw();
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
	float storageCapacity = 800; // player->getStorageCapacity();

	if (ImGui::BeginMainMenuBar())
	{
		ImGui::SetNextWindowBgAlpha(0.6f);
		if (ImGui::BeginMenu("Stored Resources"))
		{
			//std::cout << stored.consumable[0] << std::endl;

			ImGui::TextColored(ImVec4(0.5, 0.8, 0.4, 1.0),"Consumable Resources");
			progressBarGenerator(stored.consumableTypes, stored.consumable, storageCapacity, false);
			ImGui::Separator();

			ImGui::TextColored(ImVec4(0.5, 0.8, 0.4, 1.0), "Derived Resources");
			progressBarGenerator(stored.derivedTypes, stored.derived, storageCapacity, false);
			ImGui::Separator();


			ImGui::TextColored(ImVec4(0.5, 0.8, 0.4, 1.0), "Humanly Resources");
			progressBarGenerator(stored.humanlyTypes, stored.humanly, storageCapacity, false);

			ImGui::EndMenu();
		}

		ImGui::Text("|");

		if (player->getSelection() != nullptr)
		{
			SharedPointer<SelectableComponent> selected(player->getSelection()->get_component<SelectableComponent>("SelectableComponent"));
			ImGui::Text(selected->getNameFromAttributes().c_str());
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Selected: %s \n", selected->getNameFromAttributes().c_str());
			}

			if (selected->getTarget())
			{
				ImGui::Text(" > ");
				ImGui::Text(selected->getTarget()->getNameFromAttributes().c_str());
				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip("Targeted: %s \n", selected->getTarget()->getNameFromAttributes().c_str());
				}
			}
			ImGui::Text("|");
		}


		//ImGui::Text("Loading %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]);

		gameLog.MainMenu();


		ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - ImGui::CalcTextSize(" | adlGame ").x);

		ImGui::Text("|");
		if (ImGui::BeginMenu("adlGame"))
		{
			ImGui::MenuItem("Game Actions", NULL, &gameLog.opened);
			ImGui::EndMenu();
		}

		// Human Count etc.
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
			ImGui::Text("Unknown Game Object Selected!");
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
	

	std::string title("" + pro.name + "(Human)" + (selected->getTarget() ? " -> " : " ") + (selected->getTarget() ? selected->getTarget()->getNameFromAttributes() : " "));

	if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
	{
		
		ImGui::Indent();

		ImGui::Separator();
		//ImGui::Text("Human : %s %s %s", pro.name.c_str(), selected->getTarget() ? "->" : " ", selected->getTarget() ? selected->getTarget()->getOwner()->getName().c_str() : " ");

		ImGui::Columns(3, "Columns", true);
		{
			ImGui::TextColored(ImVec4(0.0, 120, 0, 1.0), "General Properties");

			ImGui::Indent();
			ImGui::Text("%s", "Properties");

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

			if (carrying.takenObject != "")
			{
				ImGui::Text("Carried: %s(%.0f)", carrying.takenObject.c_str(), carrying.taken);
			}
			else {
				ImGui::Text("Carried: Empty");
			}
					
			ImGui::Unindent();


			ImGui::Text("%s", "Experiences");
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("If there is time, human can learn everything.\n");

			if (ImGui::CollapsingHeader("Experiences"))
			{
				ImGui::Indent();

				ImGui::TextColored(ImVec4(0, 102, 0, 1.0), "Consumable Resources");
				progressBarGenerator(exp.consumableTypes, exp.consumable);

				ImGui::TextColored(ImVec4(0, 102, 0, 1.0), "Derived Resources");
				progressBarGenerator(exp.derivedTypes, exp.derived);

				ImGui::TextColored(ImVec4(0, 102, 0, 1.0), "Humanly Resources");
				progressBarGenerator(exp.humanlyTypes, exp.humanly);

				ImGui::Unindent();
			}

			ImGui::Unindent();

			ImGui::NextColumn();
			ImGui::Text("%s", "Requires");
			ImGui::Text("%s", "Needs");
			ImGui::Indent();
			progressBarGenerator(req.needsTypes, req.needs, 100, true, true, true);
			ImGui::Unindent();

			ImGui::NextColumn();
			ImGui::Text("%s", "Productions");
			ImGui::Text("%s", "Abilities");
			ImGui::Indent();
			buildConstructionTool("House");
			buildConstructionTool("Blacksmith");
			ImGui::Unindent();

		}
		ImGui::Columns(1);

		ImGui::Unindent();

		ImGui::End();
	}
}

void HUDComponent::resourceAttributes() {
	SharedPointer<ResourceAttributes> res(player->getSelection()->get_component<ResourceAttributes>("ResourceAttributes"));
	SharedPointer<SelectableComponent> selected(player->getSelection()->get_component<SelectableComponent>("SelectableComponent"));

	std::string title("" + res->getProperties().name + "(Resource)");

	if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
	{
		ImGui::Indent();

		ImGui::Separator();
		//ImGui::Text("Resource: %s", res->getProperties().name.c_str());

		ImGui::Columns(3, "Columns", true);
		{
			ImGui::Text("%s", "Properties");

			ImGui::Indent();

			ImGui::Text("Name: %s", res->getProperties().name.c_str());
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Resources Name");

			ImGui::Text("Type: %s", res->getProperties().type.c_str());
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Resource Type");

			ImGui::Unindent();

			ImGui::NextColumn();
			ImGui::Text("%s", "Requires");

			ImGui::Indent();

			ImGui::Unindent();

			ImGui::NextColumn();
			ImGui::Text("%s", "Stats");

			ImGui::Indent();

			char buf[32];
			sprintf(buf, "%.0f/%.0f", res->getProperties().resource.x, res->getProperties().resource.y);

			ImGui::Text("%s: ", res->getProperties().type.c_str());
			ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
			ImGui::ProgressBar(res->getProperties().resource.x / res->getProperties().resource.y, ImVec2(0.f, 0.f), buf);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Resource Percentage\nCurrent/Max");

			ImGui::Unindent();

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

	std::string title("" + pro.name + "(Construction)");

	if (ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoResize /*| ImGuiWindowFlags_NoScrollWithMouse*/ | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus /*| ImGuiWindowFlags_NoTitleBar*/))
	{
		ImGui::Indent();

		ImGui::Separator();

		ImGui::Columns(3, "Columns", true);
		{
			ImGui::Text("%s", "Properties");

			ImGui::Indent();

			ImGui::Text("Name: %s", pro.name.c_str());
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Construction Name");

			ImGui::Text("Durability: %.0f", pro.durability);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Construction Durability");

			ImGui::Unindent();

			ImGui::NextColumn();
			ImGui::Text("%s", "Requires");

			ImGui::Indent();

			if (selected->hasComponent<StorageConstruction>())
			{
				ImGui::SameLine();
				ImGui::Text("(StorageConstruction)");
			}


			if (selected->hasComponent<ManufacturerConstruction>())
			{
				ImGui::SameLine();
				ImGui::Text("(Manufacturer)");

				SharedPointer<ManufacturerConstruction> facturer = selected->getComponent<ManufacturerConstruction>();
				AllResources consumeData = facturer->getConsume();
				AllResources deriveData =  facturer->getDerive();

				ImGui::Text("Needed");
				ImGui::Indent();
				for (int i = 0; i < consumeData.allTypes().size(); i++)
				{
					if (consumeData.allValues()[i] != 0)
					{
						ImGui::Text("%s: %.2f", consumeData.allTypes()[i].c_str(), consumeData.allValues()[i]);
					}
				}
				ImGui::Unindent();

				ImGui::Text("Factored");
				ImGui::Indent();
				for (int i = 0; i < deriveData.allTypes().size(); i++)
				{
					if (deriveData.allValues()[i] != 0)
					{
						ImGui::Text("%s: %.2f", deriveData.allTypes()[i].c_str(), deriveData.allValues()[i]);
					}
				}




				ImGui::Unindent();
			}

			ImGui::Unindent();

			ImGui::NextColumn();
			ImGui::Text("%s", "Stats");

			ImGui::Indent();

			char buf[32];
			sprintf(buf, "%.0f/%.0f", 1.0f, 1.0f);

			ImGui::Text("Construction: ");
			ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
			ImGui::ProgressBar(1 / 1, ImVec2(0.f, 0.f), buf);

			ImGui::Unindent();

		}
		ImGui::Columns(1);

		ImGui::Unindent();

		ImGui::End();
	}
}

void HUDComponent::progressBarGenerator(std::vector<std::string> text, float value[], float limit, bool indent, bool showAll, bool valueColor)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (!showAll && value[i] == 0)
		{
			continue;
		}

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

			if (valueColor)
			{
				float c = (value[i] / limit);
				ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1 - c, c, 0, 1.0));
				//ImGui::Text("%.3f", value[i] / limit);
			}

			ImGui::ProgressBar(value[i] / limit, ImVec2(-1.f, 0.f), buf);

			if (valueColor)
			{
				ImGui::PopStyleColor();
			}


			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("%s: %.0f/%.0f(Current/Max)", text[i].c_str(), value[i], limit);
		}	

		if (indent)
			ImGui::Unindent();
	}
}

void HUDComponent::buildConstructionTool(std::string name)
{
	GameManager* gameMan = &GameManager::get();
	SharedPointer<Informer> informer = (gameMan->getTaggedEntity("Informer")->get_component<Informer>("Informer")).lock();
	SharedPointer<HumanAttributes> human(player->getSelection()->get_component<HumanAttributes>("HumanAttributes"));


	if (ImGui::Button(("Build " + name).c_str(), ImVec2(-1, 40))) {
		player->onConstruct = name;
	}
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();

		Informer::GameObjectInfo info = informer->getGameObjectInfo(name);
		Informer::GameObjectInfo infoExp = informer->getGameObjectInfo(name, "Experience");
		std::vector<std::string> informations = {};

		std::vector<std::string> inf(info.types);
		inf.insert(inf.end(), infoExp.types.begin(), infoExp.types.end());
		std::sort(inf.begin(), inf.end());
		inf.erase(std::unique(inf.begin(), inf.end()), inf.end());

		ImGui::PushItemWidth(-1);
		if (human->checkExperience(name) && player->checkStoredResources(name))
		{
			ImGui::TextColored(ImVec4(0.2, 1.0, 0.2, 1.0), "\t\t  %s  \t\t", info.name.c_str());
		}
		else
		{
			ImGui::TextColored(ImVec4(1.0, 0.2, 0.2, 1.0), "\t\t  %s  \t\t", info.name.c_str());
		}

		ImGui::Columns(3, "ToolTipTypeColumns", true);
		{
			ImGui::PushItemWidth(-1);
			ImGui::Text("Req:  ");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::Text(" Res ");
			ImGui::NextColumn();
			ImGui::PushItemWidth(-1);
			ImGui::Text(" Exp ");
		}
		ImGui::Columns(1);
		
		for (int i = 0; i < inf.size(); i++)
		{
			ImGui::Columns(3, "ToolTipColumns", true);
			{
				ImGui::PushItemWidth(-1);
				ImGui::Text("%s: ", inf[i].c_str()); // Type: 
				ImGui::NextColumn();

				ImGui::PushItemWidth(-1);
				std::vector<std::string>::iterator itr = std::find(info.types.begin(), info.types.end(), inf[i]);
				int index = -1;
				if (itr != info.types.end())
					index = std::distance(info.types.begin(), itr);

				if (index != -1 && player->getStored().find(inf[i]) > info.values[index])
				{
					ImGui::TextColored(ImVec4(0.0, 1.0, 0.0, 1.0), " %.0f\t", info.values[index]); // Res 
				}
				else if(index != -1)
				{
					ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), " %.0f\t", info.values[index]); // Res 
				}
				ImGui::NextColumn();
				std::vector<std::string>::iterator itrExp = std::find(infoExp.types.begin(), infoExp.types.end(), inf[i]);
				int indexExp = -1;
				if (itrExp != infoExp.types.end())
					indexExp = std::distance(infoExp.types.begin(), itrExp);

				if (indexExp != -1 && human->getExperiences().find(inf[i]) > infoExp.values[indexExp])
				{
					ImGui::TextColored(ImVec4(0.0, 1.0, 0.0, 1.0), " %.0f\t", infoExp.values[indexExp]); // Exp 
				}
				else if (indexExp != -1)
				{
					ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), " %.0f\t", infoExp.values[indexExp]); // Exp 
				}
			}
			ImGui::Columns(1);
		}

		ImGui::EndTooltip();
	}

}
void HUDComponent::modal()
{
	ImGui::OpenPopup("Modal window");
	bool open = true;
	if (ImGui::BeginPopupModal("Modal window", &open, ImGuiWindowFlags_NoResize))
	{
		ImGui::Text("Modal");
		if (ImGui::Button("Close"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}
