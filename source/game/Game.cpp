#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_entities/adlRender_component.h"
#include "engine/adl_entities/adlPhysics_component.h"
#include "engine/adl_entities/adlPoint_light_component.h"
#include "engine/adl_entities/adlSun_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"

#include "game/GameComponents/Player/PlayerAttributes.h"
#include "game/GameComponents/Constructions/ConstructionAttributes.h"
#include "game/GameComponents/Resources/ResourceAttributes.h"
#include "game/GameComponents/Humans/HumanAttributes.h"	

#include "game/GameComponents/HUD/HUDComponent.h"	

#include "game/GameComponents/Misc/SelectableComponent.h"	

//#include "game/GameComponents/Behaviours/"	

Game::Game()
{

}

Game::~Game()
{

}


bool Game::init()
{
	// adl Components
	adlTransform_component tc;
	adlRender_component r;
	adlPhysics_component p;
	adlPoint_light_component l;
	adlSun_component sunC;

	adlScene_shared_ptr scene = adl_scene_manager->create_empty_scene("new_scene");
	adl_scene_manager->set_active_scene(scene);

	scene->set_cube_map(adl_rm->get_cube_map("default"));
	
	listener_ = ADL_NEW(Physics_listener);
	adl_scene_manager->add_physics_observer(listener_);

	adlCamera* scene_camera = ADL_NEW(adlCamera);
	scene_camera->set_camera_type(ct_god_mode);
	scene_camera->init();
	scene_camera->set_pitch(-50);
	scene_camera->set_position(adlVec3(0, 30, 10));

	adl_scene_manager->set_camera(scene_camera);
	scene->set_camera(scene_camera);

	adlTerrain_shared_ptr terrain = adl_rm->get_terrain("FlatTerrain");
	adl_scene_manager->set_terrain(terrain);
	
	sunEntity = adl_scene_manager->add_entity_to_scene("Sun");
	adl_scene_manager->set_sun(sunEntity);

	// Game Components
	PlayerAttributes pAtr;
	ConstructionAttributes cAtr;
	ResourceAttributes rAtr;
	HumanAttributes hAtr;
	HUDComponent hudC;

	SelectableComponent selectC;


	Entity player = adl_scene_manager->add_entity_to_scene("Player");

	Entity hud = adl_scene_manager->add_entity_to_scene("HUD");


	/*for (int i = 0; i < 10; i++)
	{
		Entity resource = adl_scene_manager->add_entity_to_scene("Resource");
		std::shared_ptr<adlTransform_component> resourceTransform = std::shared_ptr(resource->get_component<adlTransform_component>("adlTransform_component"));
		resourceTransform->set_position(adlVec3(i * 2, 0, 0));
	}*/

	Entity resource = adl_scene_manager->add_entity_to_scene("Resource");

	Entity construction = adl_scene_manager->add_entity_to_scene("Construction");

	Entity human = adl_scene_manager->add_entity_to_scene("Human");

	return true;
}

bool Game::update(float dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	if (adl_input->get_key(adl_key_left_alt) && adl_input->get_key_down(adl_key_f))
	{
		adl_window->toggle_fullscreen();
	}

	/*if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key(adl_key_y))
	{
		if (sun->has_component("adlPhysics_component"))
		{
			std::shared_ptr<adlPhysics_component> component = std::shared_ptr(sun->get_component<adlPhysics_component>("adlPhysics_component"));
			component->apply_force(adlVec3(0, 0, 1), 2);
		}
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_h))
	{
		adlEntity_factory* fac = &adlEntity_factory::get();
		fac->remove_component_from_entity(sun, "adlPhysics_component");
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_n))
	{
		if (!sun->has_component("adlPhysics_component"))
		{
			adlEntity_factory* fac = &adlEntity_factory::get();
			fac->add_component_to_entity(sun, "adlPhysics_component");
		}
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_l))
	{
		if (sun->has_component("adlPhysics_component"))
		{
			std::shared_ptr<adlPhysics_component> component = std::shared_ptr(sun->get_component<adlPhysics_component>("adlPhysics_component"));
			component->stop();
		}
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_j))
	{
		adlEntity_factory* fac = &adlEntity_factory::get();
		fac->remove_component_from_entity(sun, "adlPoint_light_component");
	}

	if (adl_input->get_key(adl_key_left_ctrl) && adl_input->get_key_down(adl_key_m))
	{
		adlEntity_factory* fac = &adlEntity_factory::get();
		fac->add_component_to_entity(sun, "adlPoint_light_component");
	}*/

	return true;
}
