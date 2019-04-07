#include "HUDComponent.h"

#include "game/GameComponents/Misc/SelectableComponent.h"
#include "game/GameComponents/Humans/HumanAttributes.h"
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

	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x - 160, 160));
	ImGui::SetNextWindowPos(ImVec2(80, io.DisplaySize.y - 180));
	ImGui::SetNextWindowBgAlpha(0.4f);
	if (ImGui::Begin("Main Bottom Frame", (bool*)(!editorMan->onEdit()), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar))
	{

		if (player->getSelection() != nullptr && player->getSelection()->has_component("HumanAttributes"))
		{
			humanAttributes();
		} 
		else if (player->getSelection() != nullptr && player->getSelection()->has_component("ResourceAttributes"))
		{
			resourceAttributes();
		}

		ImGui::End();
	}
}

void HUDComponent::humanAttributes()
{
	SharedPointer<HumanAttributes> human(player->getSelection()->get_component<HumanAttributes>("HumanAttributes"));
	ImGui::Indent();

	ImGui::Text("Human - %s", human->properties.name.c_str());

	ImGui::Columns(2, "Columns", true);
	{
		ImGui::Text("%s", "Properties");

		if (ImGui::CollapsingHeader("Properties"))
		{
			ImGui::Indent();

			ImGui::Text("Name: %s", human->properties.name.c_str());
			ImGui::Text("Age: %.0f", human->properties.age);

			if (ImGui::CollapsingHeader("Experiences"))
			{
				ImGui::Indent();

				human->properties.experiences.editor();

				ImGui::Unindent();
			}

			ImGui::Unindent();
		}

		ImGui::NextColumn();
		ImGui::Text("%s", "Requires");

		if (ImGui::CollapsingHeader("Requires"))
		{
			ImGui::Indent();


			ImGui::Unindent();
		}

		if (ImGui::Button("Build Construction")) {
			human->production();
		}

	}
	ImGui::Columns(1);

	

	ImGui::Unindent();
}

void HUDComponent::resourceAttributes() {
	SharedPointer<ResourceAttributes> res(player->getSelection()->get_component<ResourceAttributes>("ResourceAttributes"));
	ImGui::Indent();

	ImGui::Text("Attributes");

	if (ImGui::CollapsingHeader("Properties"))
	{
		ImGui::Indent();

		/*static float progress = 0.0f, progress_dir = 1.0f;
		progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
		if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
		if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }

		float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
		char buf[32];
		sprintf(buf, "%d/%d", (int)(progress_saturated * 1753), 1753);
		ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), buf);*/

		char buf[32];
		sprintf(buf, "%.0f/%.0f", res->getProperties().resource.x, res->getProperties().resource.y);

		ImGui::Text("Resources: ");
		ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
		ImGui::ProgressBar(res->getProperties().resource.x/res->getProperties().resource.y, ImVec2(0.f, 0.f), buf);
		

		/*ImGui::Indent();
		static char resName[20] = {};

		ImGui::Text(("Resource Name: " + properties.name).c_str());
		ImGui::InputText("##resName", resName, sizeof(resName));
		if (ImGui::Button("Refresh Name"))
		{
			properties.name = resName;
		}
		ImGui::Unindent();

		ImGui::Indent();
		static char typeName[20] = {};

		ImGui::Text(("Type Name: " + properties.type).c_str());
		ImGui::InputText("##typeName", typeName, sizeof(typeName));
		if (ImGui::Button("Refresh Name"))
		{
			properties.name = resName;
		}
		ImGui::Unindent();*/


		/*ImGui::Indent();
		ImGui::Text("Current Resource");
		ImGui::SliderFloat("##resource", &properties.resource.x, 0.0f, properties.resource.y);
		ImGui::Unindent();*/

		ImGui::Unindent();
	}

	if (ImGui::CollapsingHeader("Requires"))
	{
		ImGui::Indent();

		/*ImGui::Indent();
		ImGui::Text("Minimum Experience(0f, 100f)");
		ImGui::SliderFloat("##minExperience", &requires.minExperience, 0.0f, 100.0f);
		ImGui::Unindent();*/

		ImGui::Unindent();
	}
	
	ImGui::Unindent();

}
