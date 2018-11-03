#include "adlScene_saver.h"

#include "engine/adl_resource/adlScene.h"
#include "engine/adl_entities/adlEntities.h"
#include "engine/adl_debug/adlLogger.h"


#include "prettywriter.h" 
#include <cstdio>
#include <string>
#include <vector>

adlScene_saver::adlScene_saver()
{
}


adlScene_saver::~adlScene_saver()
{
}

std::string adlScene_saver::get_serialized_scene(adlScene_shared_ptr scene)
{
	const std::vector<adlEntity*> entities = scene->getAllEntities();

	const std::vector<adlPoint_light_shared_ptr>& lights = scene->get_all_point_lights();
	const adlSun_shared_ptr sun = scene->get_sun();

	std::string serialized_scene = "";

	//std::string sun_serialized = serialize_sun(sun);
	// Sun also a Entity fix it later...


	StringBuffer sb;
	PrettyWriter<StringBuffer> writer(sb);

	writer.StartObject();

	writer.String("Entities");

	writer.StartArray();
	for (auto entity : entities)
	{
		writer.StartObject();

		entity->serialize(writer);

		writer.EndObject();
	}
	writer.EndArray();


	writer.EndObject();

	serialized_scene += sb.GetString();

	return serialized_scene;
}

std::string adlScene_saver::serialize_sun(adlSun_shared_ptr sun)
{
	std::string serialized_string = "\"sun\":{";

	//std::string type_name = sun->get_type_name();
	std::string name = sun->get_name();
	serialized_string += "\"name\":\"" + name + "\",";

	adlVec3 position = sun->get_position();
	adlVec3 rotation = sun->get_rotation();
	adlVec3 scale = sun->get_scale();
	adlVec3 ambient = sun->get_ambient();
	adlVec3 diffuse = sun->get_diffuse();
	adlVec3 specular = sun->get_specular();

	std::string position_string = serialize_vec3("position", position);
	std::string rotation_string = serialize_vec3("rotation", rotation);
	std::string scale_string = serialize_vec3("scale", scale);
	std::string ambient_string = serialize_vec3("ambient", ambient);
	std::string diffuse_string = serialize_vec3("diffuse", diffuse);
	std::string specular_string = serialize_vec3("specular", specular);

	serialized_string += position_string + "," + rotation_string + "," + scale_string + "," + ambient_string + "," + diffuse_string + "," + specular_string + "}";

	return serialized_string;
}

std::string adlScene_saver::serialize_point_light(adlPoint_light_shared_ptr light)
{
	std::string serialized_string = "";

	std::string type_name = light->get_type_name();
	std::string light_name = light->get_name();
	
	adlVec3 position = light->get_position();
	adlVec3 rotation = light->get_rotation();
	adlVec3 scale = light->get_scale();
	adlVec3 ambient = light->get_ambient();
	adlVec3 diffuse = light->get_diffuse();
	adlVec3 specular = light->get_specular();

	float constant = light->get_constant();
	float linear = light->get_linear();
	float quadratic = light->get_quadratic();

	std::string position_string = serialize_vec3("position", position);
	std::string rotation_string = serialize_vec3("rotation", rotation);
	std::string scale_string = serialize_vec3("scale", scale);
	std::string ambient_string = serialize_vec3("ambient", ambient);
	std::string diffuse_string = serialize_vec3("diffuse", diffuse);
	std::string specular_string = serialize_vec3("specular", specular);

	std::string constant_string = std::to_string(constant);
	std::string linear_string = std::to_string(linear);
	std::string quadratic_string = std::to_string(quadratic);

	serialized_string += "{\"type_name\":\"" + type_name + "\",";
	serialized_string += "\"name\":\"" + light_name + "\",";
	serialized_string += position_string + "," + rotation_string + "," + scale_string + ",";
	serialized_string += ambient_string + "," + diffuse_string + "," + specular_string + ",";
	serialized_string += "\"constant\":" + constant_string + ",";
	serialized_string += "\"linear\":" + linear_string + ",";
	serialized_string += "\"quadratic\":" + quadratic_string + "}";

	return serialized_string;
}

std::string adlScene_saver::serialize_vec3(const std::string& name, adlVec3 vector)
{
	std::string serialized_vector = "";

	std::string x_string = std::to_string(vector.x);
	std::string y_string = std::to_string(vector.y);
	std::string z_string = std::to_string(vector.z);

	serialized_vector += "\"" + name + "\":[" + x_string + "," + y_string + "," + z_string + "]";

	return serialized_vector;
}
