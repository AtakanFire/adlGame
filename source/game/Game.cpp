#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlSun.h"
#include "engine/adl_entities/adlEntity_factory.h"

#include "game/GUI/HUD/HUD.h"
#include "game/GameObjects/Construction/Construction.h"

Game::Game()
{
}

Game::~Game()
{

}

bool Game::init()
{
	adlScene_shared_ptr scene = adl_scene_manager->create_empty_scene("NewScene");
	adl_scene_manager->set_active_scene(scene);

	scene->set_cube_map(adl_rm->get_cube_map("default"));

	Cube_actor cube;


	adlSun_shared_ptr sun = MAKE_SHARED(adlSun);
	sun->set_position(adlVec3(0, 300, 20));
	adl_scene_manager->setSun(sun);

	adlPoint_light_shared_ptr point_light = MAKE_SHARED(adlPoint_light);
	point_light->set_name("Light_#1");

	adlCamera* camera = ADL_NEW(adlCamera);
	camera->set_camera_type(ct_god_mode);
	camera->init();

	adl_scene_manager->set_camera(camera);

	adl_window->set_mouse_visible(false);

	scene->set_sun(sun);
	scene->set_camera(camera);

	for (int i = 0; i < 10; i++)
	{
		Construction* house = new Construction();
		house->setModel(adl_rm->getModel("PlaceHouse"));
		house->setMaterial(adl_rm->getMaterial("PlaceHouse"));
		scene->spawnActor(house);
		house->set_position(adlVec3(i*3, 0, 0));
		house->setName("PlaceHouse" + std::to_string(i));
	}

	for (int i = 0; i < 5; i++)
	{
		adlActor* axis = new adlActor();
		axis->setModel(adl_rm->getModel("AxisArrowFBX"));
		scene->spawnActor(axis);
		axis->set_position(adlVec3(0, (10+i * 3), 0));
		axis->setName("Axis" + std::to_string(i));

	}


	adlActor* actor = new adlActor();
	actor->setModel(adl_rm->getModel("Plane"));
	scene->spawnActor(actor, adlVec3(0), adlVec3(0), adlVec3(100, 100, 100));
	actor->setName("Plane");


	HUD* hud = new HUD();
	scene->spawnEntity(hud);
	hud->setName("HUD");


	
	std::cout << "\n\n\n" << std::endl;

	std::cout << sun->getName() << ": " << sun->getTypeName() << std::endl;

	for (auto entity : scene->getAllEntities())
	{
		std::cout << entity->getName() << ": " << entity->getTypeName() << std::endl;
	}

	std::cout << "\n\n\n" << std::endl;

	adlTerrain_shared_ptr terrain = adl_rm->get_terrain("test_terrain");
	




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

	Game x(Game());

	return true;
}
