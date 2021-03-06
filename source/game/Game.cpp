#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_entities/adlRender_component.h"
#include "engine/adl_entities/adlPhysics_component.h"
#include "engine/adl_entities/adlPoint_light_component.h"
#include "engine/adl_entities/adlSun_component.h"
#include "engine/adl_resource/adlTerrain.h"

#include "game/GameGeneric/GameGenericTypedef.h"

#include "game/GameComponents/Player/PlayerAttributes.h"
#include "game/GameComponents/Constructions/ConstructionAttributes.h"
#include "game/GameComponents/Resources/ResourceAttributes.h"
#include "game/GameComponents/Humans/HumanAttributes.h"	
#include "game/GameComponents/HUD/HUDComponent.h"	
#include "game/GameComponents/Player/Informer.h"	

#include "game/GameComponents/Constructions/StorageConstruction.h"
#include "game/GameComponents/Constructions/ManufacturerConstruction.h"

#include "game/GameComponents/Misc/SelectableComponent.h"	
#include "game/GameComponents/Misc/MovementComponent.h"	

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
	terrain->set_blend_map(adl_rm->get_texture("black"));
	terrain->set_texture_pack(adl_rm->get_texture_pack("default"));
	adl_scene_manager->set_terrain(terrain);


	sunEntity = adl_scene_manager->add_entity_to_scene("Sun");
	adl_scene_manager->set_sun(sunEntity);

	// Game Components
	PlayerAttributes pAtr;
	ConstructionAttributes cAtr;
	ResourceAttributes rAtr;
	HumanAttributes hAtr;
	HUDComponent hudC;
	Informer inf;

	StorageConstruction strCon;
	ManufacturerConstruction manCon;
	
	SelectableComponent selectC;
	MovementComponent moveC;

	Entity player = adl_scene_manager->add_entity_to_scene("Player");
	Entity informer = adl_scene_manager->add_entity_to_scene("Informer");

	Entity hud = adl_scene_manager->add_entity_to_scene("HUD");

	std::vector<Entity> trees;
	for (int i = 0; i < 4; i++)
	{
		trees.push_back(adl_scene_manager->add_entity_to_scene("Tree"));
		SharedPointer<SelectableComponent> tree = trees[i]->get_component<SelectableComponent>("SelectableComponent").lock();
		tree->set_position(adlVec3(tree->get_position().x - i * 3, tree->get_position().y, tree->get_position().z - (i * 2) % 3));
	}

	Entity stoneMine = adl_scene_manager->add_entity_to_scene("StoneMine");
	Entity metalMine = adl_scene_manager->add_entity_to_scene("MetalMine");

	Entity sheep = adl_scene_manager->add_entity_to_scene("Sheep");
	Entity cow = adl_scene_manager->add_entity_to_scene("Cow");

	std::vector<Entity> cottons;
	for (int i = 0; i < 2; i++)
	{
		cottons.push_back(adl_scene_manager->add_entity_to_scene("Cotton"));
		SharedPointer<SelectableComponent> cotton = cottons[i]->get_component<SelectableComponent>("SelectableComponent").lock();
		cotton->set_position(adlVec3(cotton->get_position().x - i * 2, cotton->get_position().y, cotton->get_position().z + i * 2));
	}

	Entity inn = adl_scene_manager->add_entity_to_scene("Inn");
	//Entity house = adl_scene_manager->add_entity_to_scene("House");
	//Entity blacksmith = adl_scene_manager->add_entity_to_scene("Blacksmith");

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

	return true;
}
