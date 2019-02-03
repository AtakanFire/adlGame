#include "adlEntity.h"

#include "adlEntity_factory.h"

unsigned int adlEntity::current_id = 1;

adlEntity::adlEntity()
	: id_(current_id++)
{
	REGISTER_ENTITY(adlEntity)

	name_ = "Entity_" + std::to_string(id_);
}

adlEntity::~adlEntity()
{

}

void adlEntity::init()
{
}

void adlEntity::update(float dt)
{
}

unsigned int adlEntity::get_id()
{
	return id_;
}

unsigned int adlEntity::getId()
{
	return get_id();
}

const std::string& adlEntity::get_name()
{
	return name_;
}

const std::string& adlEntity::getName()
{
	return get_name();
}
void adlEntity::set_name(const std::string& name)
{
	name_ = name;
}

void adlEntity::setName(const std::string & name)
{
	set_name(name);
}

const std::string& adlEntity::get_type_name()
{
	return type_name;
}

const std::string & adlEntity::getTypeName()
{
	return get_type_name();
}

void adlEntity::serialize(PrettyWriter<StringBuffer>& writer)
{
	writer.String("id");
	writer.Uint(id_);

	writer.String("name");
	writer.String(name_.c_str(), static_cast<SizeType>(name_.length()));

	writer.String("typeName");
	writer.String(type_name.c_str(), static_cast<SizeType>(type_name.length()));
}

void adlEntity::deserialize(const rapidjson::Value& reader)
{
	std::cout << type_name << std::endl;

	id_ = reader["id"].GetUint();
	name_ = reader["name"].GetString();
	type_name = reader["typeName"].GetString();

}