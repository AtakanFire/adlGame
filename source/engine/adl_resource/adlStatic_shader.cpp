#include "adlStatic_shader.h"

#include <iostream>
#include "engine/adl_entities/adlEntity.h"
#include "engine/adl_resource/adlMaterial.h"
#include "engine/adl_entities/adlPoint_light_component.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_entities/adlSun_component.h"


adlStatic_shader::adlStatic_shader(const std::string& vertex_file, const std::string& fragment_file)
{
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		point_light_position_locations_.push_back(-1);
		point_light_ambient_locations_.push_back(-1);
		point_light_diffuse_locations_.push_back(-1);
		point_light_specular_locations_.push_back(-1);
		point_light_constant_locations_.push_back(-1);
		point_light_linear_locations_.push_back(-1);
		point_light_quadratic_locations_.push_back(-1);
	}

	init(vertex_file, fragment_file);
}


adlStatic_shader::~adlStatic_shader()
{

}

void adlStatic_shader::bind_attributes()
{
	bind_attribute(0, "position");
	bind_attribute(1, "normal");
	bind_attribute(2, "uv");
}

void adlStatic_shader::get_all_uniform_locations()
{
	mvp_matrix_location_		= get_uniform_location("mvp_matrix");
	model_matrix_location_		= get_uniform_location("model_matrix");
	camera_position_location_	= get_uniform_location("camera_position");
	text_color_location_		= get_uniform_location("text_color");
	projection_matrix_location_ = get_uniform_location("projection");
	view_matrix_location_		= get_uniform_location("view_matrix");
	color_location_				= get_uniform_location("color");

	ambient_location_	= get_uniform_location("material.ambient");
	diffuse_location_	= get_uniform_location("material.diffuse");
	specular_location_	= get_uniform_location("material.specular");
	shininess_location_	= get_uniform_location("material.shininess");

	light_color_location_		= get_uniform_location("light_color");
	light_position_location_	= get_uniform_location("sun.light_position");
	light_ambient_location_		= get_uniform_location("sun.ambient");
	light_diffuse_location_		= get_uniform_location("sun.diffuse");
	light_specular_location_	= get_uniform_location("sun.specular");

	texture_location_			= get_uniform_location("material.diffuse");
	texture_specular_location_	= get_uniform_location("material.specular");

	r_texture_location_ = get_uniform_location("r_texture");
	g_texture_location_ = get_uniform_location("g_texture");
	b_texture_location_ = get_uniform_location("b_texture");
	blend_texture_location_ = get_uniform_location("blend_texture");
	background_texture_location_ = get_uniform_location("background_texture");

	point_light_count_location_ = get_uniform_location("point_light_number");
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		std::string index = std::to_string(i);
		point_light_position_locations_[i] = get_uniform_location("point_lights[" + index + "].position");
		point_light_ambient_locations_[i] = get_uniform_location("point_lights[" + index + "].ambient");
		point_light_diffuse_locations_[i] = get_uniform_location("point_lights[" + index + "].diffuse");
		point_light_specular_locations_[i] = get_uniform_location("point_lights[" + index + "].specular");
		point_light_constant_locations_[i] = get_uniform_location("point_lights[" + index + "].constant");
		point_light_linear_locations_[i] = get_uniform_location("point_lights[" + index + "].linear");
		point_light_quadratic_locations_[i] = get_uniform_location("point_lights[" + index + "].quadratic");
	}

	switch_location_ = get_uniform_location("switch_");
}

void adlStatic_shader::load_mvp(const adlMat4& matrix)
{
	load_matrix(mvp_matrix_location_, matrix);
}

void adlStatic_shader::load_model_matrix(const adlMat4& model_matrix)
{
	load_matrix(model_matrix_location_, model_matrix);
}

void adlStatic_shader::load_camera_position(adlVec3 position)
{
	load_vector(camera_position_location_, position);
}

void adlStatic_shader::load_text_color(adlVec3 color)
{
	load_vector(text_color_location_, color);
}

void adlStatic_shader::load_projection_matrix(const adlMat4& matrix)
{
	load_matrix(projection_matrix_location_, matrix);
}

void adlStatic_shader::load_material(adlMaterial_shared_ptr material)
{
	load_vector(ambient_location_, material->get_ambient());
	load_vector(diffuse_location_, material->get_diffuse());
	load_vector(specular_location_, material->get_specular());
	load_float(shininess_location_, material->get_shininess());
}

void adlStatic_shader::load_light(adlEntity_shared_ptr light)
{
	adlLogger* logger = &adlLogger::get();
	if (!light)
	{
		return;
	}
	if (!light->has_component("adlTransform_component"))
	{
		logger->log_warning("Point light " + light->get_name() + " does not have a transform component");
		return;
	}
	if (!light->has_component("adlSun_component"))
	{
		return;
	}

	std::shared_ptr<adlSun_component> light_component = std::shared_ptr(light->get_component<adlSun_component>("adlSun_component"));
	std::shared_ptr<adlTransform_component> trans_component = std::shared_ptr(light->get_component<adlTransform_component>("adlTransform_component"));

	load_vector(light_position_location_, trans_component->get_position());
	load_vector(light_color_location_, light_component->get_color().to_vec3());

	load_vector(light_ambient_location_, light_component->get_ambient());
	load_vector(light_diffuse_location_, light_component->get_diffuse());
	load_vector(light_specular_location_, light_component->get_specular());
}

void adlStatic_shader::load_texture()
{
	load_int(texture_location_, 0);
	load_int(texture_specular_location_, 1);
}


void adlStatic_shader::load_point_lights(const std::vector<adlEntity_shared_ptr>& point_lights)
{
	adlLogger* logger = &adlLogger::get();
	load_int(point_light_count_location_, point_lights.size());
	for (unsigned int i = 0; i < point_lights.size(); i++)
	{
		adlEntity_shared_ptr point_light = point_lights[i];
		if (!point_light->has_component("adlTransform_component"))
		{
			logger->log_warning("Point light " + point_light->get_name() + " does not have a transform component");
			continue;
		}
		if (!point_light->has_component("adlPoint_light_component"))
		{
			continue;
		}

		std::shared_ptr<adlPoint_light_component> point_light_component = std::shared_ptr(point_light->get_component<adlPoint_light_component>("adlPoint_light_component"));
		std::shared_ptr<adlTransform_component> trans_component = std::shared_ptr(point_light->get_component<adlTransform_component>("adlTransform_component"));

		load_vector(point_light_position_locations_[i], trans_component->get_position());

		load_vector(point_light_ambient_locations_[i], point_light_component->get_ambient());
		load_vector(point_light_diffuse_locations_[i], point_light_component->get_diffuse());
		load_vector(point_light_specular_locations_[i], point_light_component->get_specular());

		load_float(point_light_constant_locations_[i], point_light_component->get_constant());
		load_float(point_light_linear_locations_[i], point_light_component->get_linear());
		load_float(point_light_quadratic_locations_[i], point_light_component->get_quadratic());
	}
}

void adlStatic_shader::load_light_color(adlVec3 color)
{
	load_vector(light_color_location_, color);
}

void adlStatic_shader::load_color(adlVec3 color)
{
	load_vector(color_location_, color);
}

void adlStatic_shader::load_view_matrix(const adlMat4& matrix)
{
	load_matrix(view_matrix_location_, matrix);
}

void adlStatic_shader::load_switch(bool yn)
{
	load_bool(switch_location_, yn);
}

void adlStatic_shader::load_texture_units()
{
	load_int(background_texture_location_, 0);
	load_int(r_texture_location_, 1);
	load_int(g_texture_location_, 2);
	load_int(b_texture_location_, 3);
	load_int(blend_texture_location_, 4);
}