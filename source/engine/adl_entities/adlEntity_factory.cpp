#include "adlEntity_factory.h"


adlEntity_factory::adlEntity_factory()
{
}

const std::vector<std::string>& adlEntity_factory::get_all_registered_entities() const
{
	return registered_entities_;
}

const std::vector<std::string>& adlEntity_factory::get_all_registered_lights() const
{
	return registered_lights_;
}


void* adlEntity_factory::construct_entity(const std::string& class_name)
{
	adlLogger* logger = &adlLogger::get();

	map_type::iterator i = entities_.find(class_name);
	if (i == entities_.end())
	{
		logger->log_error("Entity " + class_name + " is not registered.");
		return nullptr;
	}

	return i->second();
}

void* adlEntity_factory::construct_light(const std::string& class_name)
{
	adlLogger* logger = &adlLogger::get();

	map_type::iterator i = lights_.find(class_name);
	if (i == lights_.end())
	{
		logger->log_error("Light " + class_name + " is not registered.");
		return nullptr;
	}

	return i->second();
}