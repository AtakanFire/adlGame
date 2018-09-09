#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlSun.h"
#include "engine/adl_entities/adlEntity_factory.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init()
{
	adlActor_shared_ptr actor = MAKE_SHARED(Test_actor);
	actor->set_name("Big_Ass_Cube_#1");
	adl_scene_manager->addToScene(actor);

	adlActor_shared_ptr landscape = MAKE_SHARED(Test_actor);
	adl_scene_manager->addToScene(landscape);
	landscape->set_position(adlVec3(0, -15, 20));
	landscape->setModel(adl_rm->getModel("Landscape"));
	landscape->set_name("Landscape");

	adlActor_shared_ptr material_actor = MAKE_SHARED(Material_test);
	adl_scene_manager->addToScene(material_actor);

	adlActor_shared_ptr axisArrow = MAKE_SHARED(adlActor);
	adl_scene_manager->addToScene(axisArrow);
	axisArrow->setPosition(adlVec3(5.0f, 0.0f, 8.0f));
	//axisArrow->setRotation(adlVec3(0.0f, 0.0f, 0.0f));
	axisArrow->setScale(adlVec3(1.0f));
	axisArrow->setModel(adl_rm->getModel("AxisArrow"));
	axisArrow->set_name("AxisArrowBlend");

	adlActor_shared_ptr axisArrowFBX = MAKE_SHARED(adlActor);
	adl_scene_manager->addToScene(axisArrowFBX);
	axisArrowFBX->setPosition(adlVec3(10.0f, 0.0f, 8.0f));
	//axisArrowFBX->setRotation(adlVec3(0.0f, 0.0f, 0.0f));
	axisArrowFBX->setScale(adlVec3(1.0f));
	axisArrowFBX->setModel(adl_rm->getModel("AxisArrowFBX"));
	axisArrowFBX->set_name("AxisArrowFBX");

	adlActor_shared_ptr axisArrowOBJ = MAKE_SHARED(adlActor);
	adl_scene_manager->addToScene(axisArrowOBJ);
	axisArrowOBJ->setPosition(adlVec3(15.0f, 0.0f, 8.0f));
	axisArrowOBJ->setRotation(adlVec3(0.0f, 0.0f, 0.0f));
	axisArrowOBJ->setScale(adlVec3(1.0f));
	axisArrowOBJ->setModel(adl_rm->getModel("AxisArrowOBJ"));
	axisArrowOBJ->set_name("AxisArrowOBJ");

	adlActor_shared_ptr wuson = MAKE_SHARED(Material_new_test);
	adl_scene_manager->addToScene(wuson);

	adlSun_shared_ptr sun = MAKE_SHARED(adlSun);
	adl_scene_manager->setSun(sun);

	adlPoint_light_shared_ptr point_light = MAKE_SHARED(adlPoint_light);
	adl_scene_manager->addPointLightToScene(point_light);
	point_light->set_name("Light_#1");

	adlPoint_light_shared_ptr second_light = MAKE_SHARED(adlPoint_light);
	adl_scene_manager->addPointLightToScene(second_light);
	second_light->set_position(adlVec3(0, 0, 20));
	second_light->set_name("Light_#2");

	for (int i = 0; i < 20; i++)
	{
		adlActor_shared_ptr multi_actor = MAKE_SHARED(Material_test);
		adl_scene_manager->spawnActor(multi_actor, adlVec3(i * 3, 0, 0));
	}

	adlCamera* camera = ADL_NEW(adlCamera);
	camera->set_camera_type(ct_rts);
	camera->init();

	adl_scene_manager->set_camera(camera);

	adl_window->set_mouse_visible(false);

	adlEntity_factory* factory = &adlEntity_factory::get();
	adlActor* new_actor = (adlActor*)factory->construct_actor("Test_actor");
	if (new_actor != nullptr)
	{
		adlActor_shared_ptr my_ptr(new_actor);
		adl_scene_manager->addToScene(my_ptr);
		my_ptr->set_position(adlVec3(0, 10, 0));
		my_ptr->set_name("Big_Ass_Cube_#2");
	}

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
