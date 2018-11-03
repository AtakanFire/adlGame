#include "adlActor.h"

#include "adlEntity_factory.h"
#include "engine/adl_resource/adlResource_manager.h"

#include "engine/adl_resource/adlJsonUtilities.h"

adlActor::adlActor()
{
	REGISTER_ENTITY(adlActor)
}


adlActor::~adlActor()
{
}

void adlActor::init()
{
}

void adlActor::update(float dt)
{

}

void adlActor::serialize(PrettyWriter<StringBuffer>& writer)
{
	adlEntity::serialize(writer);

	// TODO: use json utils for serialize and deserialize

	//jsonUtil.serialize("transform", "Object", 1);
	//jsonUtil.serialize("position", "adlVec3", transform_.o.x, transform_.o.y, transform_.o.z);
	//jsonUtil.serialize("rotation", "adlVec3", transform_.rot.x, transform_.rot.y, transform_.rot.z);
	//jsonUtil.serialize("scale", "adlVec3", transform_.scale.x, transform_.scale.y, transform_.scale.z);
	//jsonUtil.serialize("transform", "Object", 0);

	//jsonUtil.serialize("model", "Object", 1);
	//jsonUtil.serialize("mesh", "String", getModel()->get_name().c_str());
	//jsonUtil.serialize("material", "String", getMaterial()->get_name().c_str());

	writer.String("transform");

	writer.StartObject();

	writer.String("position");
	writer.StartArray();
	writer.Double(transform_.o.x);
	writer.Double(transform_.o.y);
	writer.Double(transform_.o.z);
	writer.EndArray();

	writer.String("rotation");
	writer.StartArray();
	writer.Double(transform_.rot.x);
	writer.Double(transform_.rot.y);
	writer.Double(transform_.rot.z);
	writer.EndArray();

	writer.String("scale");
	writer.StartArray();
	writer.Double(transform_.scale.x);
	writer.Double(transform_.scale.y);
	writer.Double(transform_.scale.z);
	writer.EndArray();

	writer.EndObject();

	writer.String("model");

	writer.StartObject();

	writer.String("mesh");
	writer.String(getModel()->get_name().c_str());

	if (getMaterial())
	{
		writer.String("material");
		writer.String(getMaterial()->get_name().c_str());
	}



	writer.EndObject();

}

void adlActor::deserialize(const rapidjson::Value & reader)
{
	adlEntity::deserialize(reader);


	// TODO:

	//jsonUtil.deserialize("transform", "Object", 1)
	//setPosition(jsonUtil.deserialize("position", "adlVec3"));
	//setRotation(jsonUtil.deserialize("rotation", "adlVec3"));
	//setScale(jsonUtil.deserialize("scale", "adlVec3"));

	//jsonUtil.deserialize("model", "Object" , 0)
	//setPosition(jsonUtil.deserialize("mesh", "string"));
	//if(jsonUtil.hasMember("material"))
	//	setPosition(jsonUtil.deserialize("material", "string"));

	const rapidjson::Value& readerTransform = reader["transform"];
	const rapidjson::Value& readerPos = readerTransform["position"];

	setPosition(adlVec3(readerPos[0].GetFloat(), readerPos[1].GetFloat(), readerPos[2].GetFloat()));

	const rapidjson::Value& readerRotation = readerTransform["rotation"];

	setRotation(adlVec3(readerRotation[0].GetFloat(), readerRotation[1].GetFloat(), readerRotation[2].GetFloat()));

	const rapidjson::Value& readerScale = readerTransform["scale"];

	setScale(adlVec3(readerScale[0].GetFloat(), readerScale[1].GetFloat(), readerScale[2].GetFloat()));


	const rapidjson::Value& readerModel = reader["model"];
	const rapidjson::Value& readerMesh = readerModel["mesh"];

	adlResource_manager* adl_rm = &adlResource_manager::get();
	setModel(adl_rm->getModel(readerMesh.GetString()));


	if (readerModel.HasMember("material"))
	{
		const rapidjson::Value& readerMaterial = readerModel["material"];
		setMaterial(adl_rm->getMaterial(readerMaterial.GetString()));
	}
}

adlTransform adlActor::get_transform()
{
	return transform_;
}

adlTransform adlActor::getTransform()
{
	return get_transform();
}

void adlActor::set_transform(adlTransform transform)
{
	transform_.o = transform.o;
	transform_.rot = transform.rot;
	transform_.scale = transform.scale;
}

void adlActor::setTransform(adlTransform transform)
{
	set_transform(transform);
}

adlModel_shared_ptr adlActor::get_model() const
{
	return model_;
}

adlColor adlActor::get_color() const
{
	return color_;
}

adlMaterial_shared_ptr adlActor::get_material() const
{
	return material_;
}

void adlActor::set_material(adlMaterial_shared_ptr material)
{
	material_ = material;
	model_->set_material(material);
}

void adlActor::set_position(adlVec3 position)
{
	transform_.o = position;
}

void adlActor::set_rotation(adlVec3 rotation)
{
	transform_.rot = rotation;
}

void adlActor::set_scale(adlVec3 scale)
{
	transform_.scale = scale;
}

adlVec3 adlActor::get_position() const
{
	return transform_.o;
}

adlVec3 adlActor::get_rotation() const
{
	return transform_.rot;
}

adlVec3 adlActor::get_scale() const
{
	return transform_.scale;
}

adlVec3 adlActor::getPosition()
{
	return get_position();
}

adlVec3 adlActor::getRotation()
{
	return get_rotation();
}

adlVec3 adlActor::getScale()
{
	return get_scale();
}

adlModel_shared_ptr adlActor::getModel()
{
	return get_model();
}

adlMaterial_shared_ptr adlActor::getMaterial()
{
	return get_material();
}

void adlActor::setMaterial(adlMaterial_shared_ptr material)
{
	set_material(material);
}

void adlActor::setScale(adlVec3 scale)
{
	set_scale(scale);
}

void adlActor::setPosition(adlVec3 position)
{
	set_position(position);
}

void adlActor::setRotation(adlVec3 rotation)
{
	set_rotation(rotation);
}

adlColor adlActor::getColor()
{
	return get_color();
}

void adlActor::setModel(adlModel_shared_ptr model)
{
	set_model(model);
}

void adlActor::set_model(adlModel_shared_ptr model)
{
	model_ = model;
}