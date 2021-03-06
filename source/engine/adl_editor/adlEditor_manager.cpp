#include "adlEditor_manager.h"

#include "engine/adl_debug/imgui/imgui.h"
#include "engine/adlInput.h"
#include "engine/adlWindow.h"
#include "engine/adlMemory.h"
#include "engine/adlScene_manager.h"
#include "engine/adlShared_types.h"
#include "engine/adl_renderer/adlCamera.h"
#include "engine/adl_entities/adlEntity_factory.h"
#include "adlTerrain_editor.h"

adlEditor_manager::adlEditor_manager()
	:	main_editor_open_(false),
		scene_editor_open_(false),
		entity_editor_open_(false),
		resource_manager_editor_open_(false),
		terrain_editor_open_(false),
		scene_editor_(nullptr),
		spawn_editor_(nullptr),
		entity_editor_(nullptr),
		resource_editor_(nullptr),
		terrain_editor_(nullptr)
{
	entity_editor_ = ADL_NEW(adlEntity_editor);
	spawn_editor_ = ADL_NEW(adlSpawn_editor);
	scene_editor_ = ADL_NEW(adlScene_editor);
	resource_editor_ = ADL_NEW(adlResource_manager_editor);
	terrain_editor_ = ADL_NEW(adlTerrain_editor);
}

void adlEditor_manager::init()
{
	adlScene_manager* scene_manager = &adlScene_manager::get();
	scene_manager->add_physics_observer(terrain_editor_);
}

void adlEditor_manager::MainMenu()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("adl Editors"))
		{
			ImGui::Checkbox("Entity Editor", &entity_editor_open_);
			ImGui::Checkbox("Terrain Editor", &terrain_editor_open_);
			ImGui::Checkbox("Resource Manager", &resource_manager_editor_open_);
			ImGui::Checkbox("Help", &help_open_);

			if (ImGui::MenuItem("Close All Editors", "CTRL+Q"))
			{
				entity_editor_open_ = false;
				terrain_editor_open_ = false;
				help_open_ = false;
				show_demo_window_ = false;
				spawner_editor_open_ = false;
				scene_editor_open_ = false;
				resource_editor_ = false;
			}

			ImGui::EndMenu();

		}
		ImGui::Text("|");

		if (ImGui::BeginMenu("Game"))
		{
			if (ImGui::MenuItem("Spawn", "F2"))
			{
				spawner_editor_open_ = !spawner_editor_open_;
			}

			ImGui::EndMenu();
		}		

		ImGui::Text("|");

		if (ImGui::BeginMenu("Cameras"))
		{
			adlScene_manager* scene_manager = &adlScene_manager::get();
			adlCamera* c = scene_manager->getCamera();

			if (ImGui::MenuItem("GOD")) { c->set_camera_type(ct_god_mode); }
			if (ImGui::MenuItem("RTS")) { c->set_camera_type(ct_rts); }
			if (ImGui::MenuItem("FPS")) { c->set_camera_type(ct_fps); }
			if (ImGui::MenuItem("Custom")) { c->set_camera_type(ct_custom); }
			if (ImGui::MenuItem("Camera Activity", "SHIFT+TAB")) { 
				scene_manager->get_camera()->toggle_active();
			}

			ImGui::EndMenu();
		}

		ImGui::Text("|");

		if (ImGui::BeginMenu("Scenes"))
		{
			ImGui::Checkbox("Scene Editor", &scene_editor_open_);
			if (ImGui::MenuItem("Save Scene", "CTRL+S")) { }
			if (ImGui::MenuItem("Open Scene", "CTRL+O")) { }

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void adlEditor_manager::update()
{
	adlInput* input = &adlInput::get();
	adlScene_manager* scene_manager = &adlScene_manager::get();
	if (input->get_key(adl_key_quotedbl) || (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_left_shift)))
	{
		main_editor_open_ = !main_editor_open_;
		scene_manager->get_camera()->toggle_active();

		adlWindow* window = adlWindow::get();
		if (main_editor_open_)
		{
			was_mouse_visible_ = window->is_mouse_visible();
			window->set_mouse_visible(true);
			scene_editor_open_ = false;
		}
		else
		{	// Gameplay -> Close Editor
			adlCamera* c = scene_manager->getCamera();
			c->set_camera_type(ct_rts);
			c->set_paused(false);
			window->set_mouse_visible(true);
			// window->set_mouse_visible(was_mouse_visible_);

			entity_editor_open_ = false;
			terrain_editor_open_ = false;
			terrain_editor_->set_open(false);
			help_open_ = false;		
			show_demo_window_ = false;

			spawner_editor_open_ = false;	
			scene_editor_open_ = false;

		}
	}

	if (main_editor_open_)
	{
		MainMenu();

		// adlEditor Shortcuts
		if (input->get_key_down(adl_key_f1))
		{
			help_open_ = !help_open_;
		}
		if (input->get_key_down(adl_key_f2))
		{
			entity_editor_open_ = !entity_editor_open_;
		}
		if (input->get_key_down(adl_key_f3))
		{
			spawner_editor_open_ = !spawner_editor_open_;
		}
		if (input->get_key(adl_key_left_ctrl) && input->get_key_down(adl_key_q))
		{
			entity_editor_open_ = false;
			terrain_editor_open_ = false;
			terrain_editor_->set_open(false);
			help_open_ = false;
			show_demo_window_ = false;
			spawner_editor_open_ = false;
			scene_editor_open_ = false;
		}
		if (input->get_key(adl_key_left_ctrl) && input->get_key_up(adl_key_less))
		{
			scene_manager->get_camera()->toggle_active();
		}

		if (input->get_key(adl_key_left_alt) && input->get_key_down(adl_key_less))
		{
			adlCamera* c = scene_manager->getCamera();
			if (c->get_camera_type() == Camera_type::ct_god_mode)
			{
				c->set_camera_type(ct_rts);
			}
			else
			{
				c->set_camera_type(ct_god_mode);
			}
		}

		// adlEditors
		if (entity_editor_open_)
		{
			entity_editor_->update(scene_manager->get_all_entities());
		}

		if (terrain_editor_open_)
		{
			terrain_editor_->set_open(true);
			terrain_editor_->update();
		}
		else
		{
			terrain_editor_->set_open(false);
		}

		if (scene_editor_open_)
		{
			scene_editor_->update();
		}
		if (resource_manager_editor_open_)
		{
			resource_editor_->update();
		}
		if (help_open_)
		{
			ImGui::Begin("Help");
			ImGui::Text("Close/Open Editor: 'CTRL(or CMD)+Shift or \"'");
			ImGui::Text("Show/Hide Sub Editors:  'adl Editors-> Toggle Checkbox'");
			ImGui::Text("Game Menu:  'Game-> ...'");
			ImGui::Text("Spawn Editor: 'Game-> Spawn(F2)'");
			ImGui::Text("Change Cameras:  'Cameras-> <CamType>'");
			ImGui::Text("Scene Editor: 'Scene-> <Open(ctrl+o)/Save(ctrl+s) Scene>'");

			if (ImGui::CollapsingHeader("Spawn"))
			{
				ImGui::Indent();

				ImGui::Text("Choose an entity then click the spawn button!");

				ImGui::Unindent();
			}

			if (ImGui::CollapsingHeader("Cameras"))
			{
				ImGui::Indent();

				ImGui::Text("Choose your camera type!");

				ImGui::Unindent();
			}

			if (ImGui::CollapsingHeader("Scene"))
			{
				ImGui::Indent();

				ImGui::Text("Open or save your scene.");

				ImGui::Unindent();
			}

			if (ImGui::CollapsingHeader("Some Shortcuts"))
			{
				ImGui::Indent();

				ImGui::Text("\t__Generic shortcuts__");
				ImGui::Text("Close/Open Editor: 'CTRL(or CMD)+Shift or \"'");
				ImGui::Text("\n");

				ImGui::Text("\t__On the editor__");
				ImGui::Text("Show bounds: 'rightctrl+k'");
				ImGui::Text("Show Wireframes: 'rightctrl+l'");
				ImGui::Text("Toggle Mouse Cursor: '<'");
				ImGui::Text("Toggle Cam Movement: 'ctrl+<'");
				ImGui::Text("Switch RTS/GOD Cam: 'alt+<'");

				ImGui::Unindent();
			}

			if (ImGui::CollapsingHeader("Extras"))
			{
				ImGui::Indent();
				ImGui::Checkbox("Demo Window", &show_demo_window_);

				if (show_demo_window_)
					ImGui::ShowDemoWindow(&show_demo_window_);
				ImGui::Unindent();
			}

			ImGui::End();
		}
		if (spawner_editor_open_)
		{
			spawn_editor_->init();
			spawn_editor_->update(scene_manager);
			spawner_editor_open_ = spawn_editor_->get_visible();
		}
	}

}

bool adlEditor_manager::onEdit()
{
	return main_editor_open_;
}

void adlEditor_manager::clean_up()
{
	ADL_DELETE(entity_editor_);
	ADL_DELETE(spawn_editor_);
	ADL_DELETE(scene_editor_);
	ADL_DELETE(resource_editor_);
	ADL_DELETE(terrain_editor_);
}
