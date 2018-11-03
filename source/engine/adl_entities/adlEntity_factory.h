#ifndef adl_entity_factory_h__
#define adl_entity_factory_h__

#include "engine/adl_debug/adlLogger.h"
#include "engine/adlMemory.h"

#include <map>
#include <memory>

template <class T> void* constructor() { return (void*)new T(); }
typedef void*(*constructor_t)();
typedef std::map<std::string, constructor_t> map_type;

#define REGISTER_ENTITY(class_name) adlEntity_factory* factory = &adlEntity_factory::get(); \
								   factory->register_class<class_name>(#class_name, true); \
								   type_name = #class_name;

#define REGISTER_LIGHT(class_name) adlEntity_factory* factory = &adlEntity_factory::get(); \
								   factory->register_class<class_name>(#class_name, false);\
								   type_name = #class_name;
class adlEntity_factory
{
public:
	static adlEntity_factory& get()
	{
		static adlEntity_factory instance;
		return instance;
	}

	template <class T>
	void register_class(const std::string& class_name, bool isEntity)
	{
		if (isEntity)
		{
			if (entities_.count(class_name) == 0)
			{
				entities_.insert(std::make_pair(class_name, &constructor<T>));
				registered_entities_.push_back(class_name);
			}
		}
		else
		{
			if (lights_.count(class_name) == 0)
			{
				lights_.insert(std::make_pair(class_name, &constructor<T>));
				registered_lights_.push_back(class_name);
			}
		}
	}

	void* construct_entity(const std::string& class_name);
	void* construct_light(const std::string& class_name);

	const std::vector<std::string>& get_all_registered_actors() const;
	const std::vector<std::string>& get_all_registered_lights() const;


private:
	adlEntity_factory();

	map_type entities_;
	map_type lights_;
	std::vector<std::string> registered_entities_;
	std::vector<std::string> registered_lights_;
};

#endif // adl_entity_factory_h__