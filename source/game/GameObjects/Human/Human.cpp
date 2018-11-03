#include "Human.h"

#include "engine/adl_entities/adlEntity_factory.h"

Human::Human()
{
	REGISTER_ENTITY(Human)
}

Human::~Human()
{

}

void Human::init() {

}

void Human::update(float dt) {

}


void Human::serialize(PrettyWriter<StringBuffer>& writer)
{
	adlActor::serialize(writer);

}

void Human::deserialize(const rapidjson::Value& reader)
{
	adlActor::deserialize(reader);

}



