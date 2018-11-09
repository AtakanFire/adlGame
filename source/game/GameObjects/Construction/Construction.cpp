#include "Construction.h"

#include "engine/adl_entities/adlEntity_factory.h"

Construction::Construction()
{
	REGISTER_ENTITY(Construction)
}

Construction::~Construction()
{

}

void Construction::init() {

}

void Construction::update(float dt) {
	//std::cout << "Construction" << std::endl;

}



void Construction::serialize(PrettyWriter<StringBuffer>& writer)
{
	adlActor::serialize(writer);

	writer.String("Attributes");

	writer.StartObject();

	//jsonUtil.serialize("Properties", "Object");
	//jsonUtil.serialize("Name", "String", getName().c_str());

	writer.String("Properties");
	writer.StartObject();
	writer.String("Name");
	writer.String("Construction deserialize isn't added yet!");

	writer.String("Durability");
	writer.Double(10);

	writer.String("Worker");
	writer.Double(0);
	writer.EndObject();

	writer.EndObject();
}

void Construction::deserialize(const rapidjson::Value& reader)
{
	adlActor::deserialize(reader);

}

