#include "HUD.h"

#include "engine/adl_entities/adlEntity_factory.h"

HUD::HUD()
{
	REGISTER_ENTITY(HUD)
}

HUD::~HUD()
{

}

void HUD::init() {

}

void HUD::update(float dt) {

}


void HUD::serialize(PrettyWriter<StringBuffer>& writer)
{
	adlEntity::serialize(writer);

}

void HUD::deserialize(const rapidjson::Value& reader)
{
	adlEntity::deserialize(reader);

}



