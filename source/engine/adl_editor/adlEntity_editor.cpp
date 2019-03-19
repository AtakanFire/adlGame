#include "adlEntity_editor.h" 
#include "engine/adl_debug/imgui/imgui.h"

 
adlEntity_editor::adlEntity_editor() {  
 
}  
 
adlEntity_editor::~adlEntity_editor() {  
 
}

void adlEntity_editor::update(std::vector<adlEntity_shared_ptr>& entities)
{
	
	/*
	bool *p = NULL;
	uniqueId_ = 0;

	ImGui::Begin("Entity Editor", p, ImGuiWindowFlags_MenuBar);


	if (ImGui::BeginMenuBar())
	{
		ImGui::Text("Entities");

		ImGui::Text("|");

		if (ImGui::BeginMenu("Show"))
		{
			if (ImGui::MenuItem("All", ""))
			{
				std::cout << "That isn't added yet" << std::endl;
			}

		ImGui::EndMenu();
		}

		ImGui::Text("|");

		if (ImGui::BeginMenu("Settings"))
		{
			if (ImGui::BeginMenu("Snap"))
			{
				std::string tag = "Snap Unit##snapUnit";
				ImGui::InputFloat(tag.c_str(), &snapUnit, 0.1);

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Serialize/Deserialize", ""))
			{
				serializeAllDatas_ = !serializeAllDatas_;
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (serializeAllDatas_)
	{
		serializeEntities(entities);
	}

	ImGui::End();
	*/

	ImGui::Begin("Entity Editor");
	ImGui::Text("Entities\n");

	if (ImGui::CollapsingHeader("Entities"))
	{
		ImGui::Indent();

		for (unsigned int i = 0; i < entities.size(); i++)
		{
			std::string actr = entities[i]->get_name();
			//This might cause problems for entities with the same name
			if (ImGui::CollapsingHeader(actr.c_str()))
			{
				ImGui::Indent();
				ImGui::Text("Entity (%d)", i);

				for (auto component : entities[i]->get_all_component())
				{
					ImGui::Indent();
					if (ImGui::CollapsingHeader(component->get_type_name().c_str()))
					{
						component->editor();
					}
					ImGui::Unindent();
				}

				ImGui::Unindent();
			}
		}
		ImGui::Unindent();
	}

	ImGui::End();
}
