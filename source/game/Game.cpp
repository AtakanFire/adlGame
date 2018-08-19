#include "Game.h"

#include <iostream>

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init()
{
	adlFont_shared_ptr arial_font = adl_rm->get_font("arial");
	model = adl_rm->get_model("wuson");

	box = adl_rm->get_model("box");
	adlModel_shared_ptr mountain_model	= adl_rm->get_model("mountain");
	adlModel_shared_ptr teapot_model	= adl_rm->get_model("teapot");
	adlModel_shared_ptr at_at_model		= adl_rm->get_model("bmw");

	adlShader_shared_ptr phong_shader = adl_rm->get_shader("phong_shader");
	shader = adl_rm->get_shader("diffuse_shader");
	model->set_shader(shader);
	box->set_shader(shader);
	mountain_model->set_shader(shader);
	teapot_model->set_shader(shader);
	at_at_model->set_shader(shader);

	adlModel_shared_ptr cube_model = adl_rm->get_model("cube");
	cube_model->set_shader(phong_shader);
	at_at_.set_model(at_at_model);
	big_box_.set_model(cube_model);

	adlTransform frame = adlMatrix_frame::identity();

	light_ = ADL_NEW(adlLight, cube_model, adlColor::WHITE);
	frame.scale = adlVec3(0.1f);
	frame.o = adlVec3(0, 5, 0);
	light_->set_frame(frame);
	adl_renderer->set_light(light_);

	bison_entity_.set_model(model);
	box1_.set_model(box);
	box2_.set_model(box);
	mount_.set_model(mountain_model);
	teapot_entity_.set_model(teapot_model);

	box1_.set_frame(frame);
	box2_.set_frame(frame);
	frame.rot = adlVec3(adlMath::deg_to_rad(90), 0, 0);
	bison_entity_.set_frame(frame);

	frame.rot = adlVec3(adlMath::deg_to_rad(90), 0, 0);
	frame.o = adlVec3(0, -10.0f, 0);
	mount_.set_frame(frame);
	teapot_entity_.set_frame(frame);

	for (int i = 0; i < 20; i++)
	{
		adlEntity entity;
		entity.set_model(cube_model);
		frame.o = adlVec3((float)i * 2 - 10, 0, 0);
		frame.scale = adlVec3(0.5f);
		entity.set_frame(frame);
		boxes_.push_back(entity);
	}

	adlMat4 projection = projection.create_projection_matrix(adl_window->get_width(), adl_window->get_height(), adlMath::deg_to_rad(40), 0.1f, 1000.0f);;
	adl_renderer->set_projection(projection);

	camera->set_camera_type(ct_rts);
	adl_window->set_mouse_visible(false);

	frame.o = adlVec3(0, -2, -5);
	frame.scale = adlVec3(0.00025f);
	frame.rot = adlVec3(0);
	at_at_.set_frame(frame);

	frame.o = adlVec3(0, 30, 0);
	frame.rot = adlVec3(0);
	frame.scale = adlVec3(20);
	big_box_.set_frame(frame);

	timer_.start();

	return true;
}

bool Game::update(float dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	if (adl_input->get_key(adl_key_f))
	{
		adl_window->toggle_fullscreen();
	}

	adlMatrix_frame frame = adlMatrix_frame::identity();
	frame.o = adlVec3(model_x, -0.5f, -1.5f);
	frame.rot = adlVec3(0, 0, 0);
	frame.scale = adlVec3(0.5f, 0.5f, 0.5f);
	bison_entity_.set_frame(frame);

	frame = adlMatrix_frame::identity();
	frame.o = adlVec3(0, -0.5f, -10.0f);
	frame.rot = adlVec3(adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds()) / 8, 0, 0);
	frame.scale = adlVec3(1.1f, 1.1f, 1.1f);
	box1_.set_frame(frame);

	for (int i = 0; i < 20; i++)
	{
		adlMatrix_frame box_frame = boxes_[i].get_frame();
		box_frame.rot = adlVec3(0, adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds()) / 8, 0);
		boxes_[i].set_frame(box_frame);
		adl_renderer->render(boxes_[i], adlColor(160, 82, 45));
	}

	frame.rot = adlVec3(0.0f);
	frame.o = adlVec3(0, -10.0f, 0);
	mount_.set_frame(frame);

	frame.o = adlVec3(0, 0, -20.0f);
	frame.rot = adlVec3(adlMath::deg_to_rad(-90), 0, 0);
	frame.scale = adlVec3(0.05f);
	teapot_entity_.set_frame(frame);

	adl_renderer->render(box1_, adlColor::BLUE);
	adl_renderer->render(bison_entity_, adlColor::BLUE);
	adl_renderer->render(teapot_entity_, adlColor::BLUE);
	adl_renderer->render(mount_, adlColor::GREEN);
	adl_renderer->render(at_at_, adlColor::MAGENTA);
	adl_renderer->render(big_box_, adlColor::CYAN);

	frame.o = adlVec3(std::sin(adlMath::deg_to_rad(timer_.get_elapsed_milli_seconds() / 8)) * 10, 5, 0);
	light_->set_frame(frame);
	adl_renderer->render(light_);

	return true;
}
