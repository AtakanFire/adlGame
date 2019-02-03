#include "adlEntity_editor.h" 

#include "engine/adl_debug/imgui/imgui.h"

#include <document.h>
#include <string>
#include <stringbuffer.h>

 
bool serializeAllDatas_ = true;
int uniqueId_;
float snapUnit = 0.1f;;


adlEntity_editor::adlEntity_editor() 
{  
	serializeAllDatas_ = true;
	uniqueId_ = 0;
	snapUnit = 0.1f;
}  
 
adlEntity_editor::~adlEntity_editor() {  
 
}

void adlEntity_editor::update(std::vector<adlEntity*>& entities)
{
	bool *p = NULL;
	uniqueId_ = 0;

	ImGui::Begin("Entity Editor", p, ImGuiWindowFlags_MenuBar);


	if (ImGui::BeginMenuBar())
	{
		ImGui::Text("Entities");

		ImGui::Text("|");

		if (ImGui::BeginMenu("Show"))
		{
			if (ImGui::MenuItem("All", ""))
			{
				std::cout << "That isn't added yet" << std::endl;
			}

		ImGui::EndMenu();
		}

		ImGui::Text("|");

		if (ImGui::BeginMenu("Settings"))
		{
			if (ImGui::BeginMenu("Snap"))
			{
				std::string tag = "Snap Unit##snapUnit";
				ImGui::InputFloat(tag.c_str(), &snapUnit, 0.1);

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Serialize/Deserialize", ""))
			{
				serializeAllDatas_ = !serializeAllDatas_;
			}

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (serializeAllDatas_)
	{
		serializeEntities(entities);

	}

	ImGui::End();
}

void adlEntity_editor::serializeEntities(std::vector<adlEntity*>& entities)
{
	//jsonUtils wasn't ready yet, so serialize then deserialize every frame

	// Serialize from Classes
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

	std::string serializedData(sb.GetString(), sb.GetSize());


	// Deserialize to Classes
	rapidjson::Document document;

	document.Parse(serializedData.c_str());
		
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value& entitiesJSON = document["Entities"];

	//typeBasedSerializer(entitiesJSON);
	
	if (ImGui::CollapsingHeader("Entities"))
	{
		ImGui::Indent();


		assert(entitiesJSON.IsArray());
		for (rapidjson::Value::ValueIterator itr = entitiesJSON.Begin(); itr != entitiesJSON.End(); ++itr) {
			rapidjson::Value& attribute = *itr;

			if (ImGui::CollapsingHeader(attribute["name"].GetString()))
			{
				ImGui::Indent();

				typeBasedSerializer(attribute, allocator);

				ImGui::Unindent();
			}

		}

		ImGui::Unindent();
	}


	for (rapidjson::Value::ConstValueIterator itr = entitiesJSON.Begin(); itr != entitiesJSON.End(); ++itr)
	{
		const rapidjson::Value& entityItr = *itr;

		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i]->getId() == entityItr["id"])
			{
				entities[i]->deserialize(entityItr);
			}
		}

	}
}

void adlEntity_editor::typeBasedSerializer(rapidjson::Value& val, rapidjson::Document::AllocatorType& allocator)
{
	switch (val.GetType())
	{
	case rapidjson::Type::kArrayType:
		if (val.IsArray())
		{
			std::string tag = "[]##" + std::to_string(uniqueId_);
			uniqueId_++;
			if (ImGui::CollapsingHeader(tag.c_str()))
			{
				ImGui::Indent();
				assert(val.IsArray());
				for (rapidjson::Value::ValueIterator itr = val.Begin(); itr != val.End(); ++itr) 
				{
					rapidjson::Value& attribute = *itr;
					typeBasedSerializer(attribute, allocator);
				}

				ImGui::Unindent();
			}
		}
		break;
	case rapidjson::Type::kFalseType:
		std::cout << "kFalseType";
		break;
	case rapidjson::Type::kNullType:
		std::cout << "kNullType";
		break;
	case rapidjson::Type::kNumberType:
		
		if (val.IsDouble())
		{
			std::string tag = "Assign##" + std::to_string(uniqueId_);
			uniqueId_++;
			std::string tag2 = "drag##d" + std::to_string(uniqueId_);
			uniqueId_++;

			float temp = val.GetFloat();
			ImGui::InputFloat(tag.c_str(), &temp, snapUnit);
			ImGui::DragFloat(tag2.c_str(), &temp, snapUnit);
			assert(val.IsFloat());
			val.SetFloat(temp);
		}
		if (val.IsInt())
		{
			std::string tag = std::to_string(val.GetInt()) + "##" + std::to_string(uniqueId_);
			uniqueId_++;
			ImGui::Text(tag.c_str());
		}
		break;
	case rapidjson::Type::kObjectType:
		assert(val.IsObject());
		for (rapidjson::Value::MemberIterator objItr = val.MemberBegin(); objItr != val.MemberEnd(); ++objItr) {

			std::string tag = (objItr->name.GetString()) + ("##" + std::to_string(uniqueId_));
			uniqueId_++;

			if (ImGui::CollapsingHeader(tag.c_str()))
			{
				ImGui::Indent();
				typeBasedSerializer(objItr->value, allocator);

				ImGui::Unindent();
			}
		};
		break;
	case rapidjson::Type::kStringType:
		assert(val.IsString());
		if (val.IsString())
		{
			std::string tag = /*val.GetString() + */("Max char: 20 ##" + std::to_string(uniqueId_));
			uniqueId_++;
			//ImGui::Text(tag.c_str());

			std::string temp = val.GetString();
			static char buff[20] = {};

			ImGui::InputText(tag.c_str(), &buff[0], sizeof(buff));

			/*std::cout << "--" << std::endl;
			std::cout << temp << std::endl;
			std::cout << buff << std::endl;*/

			if (ImGui::Button("Assign"))
			{
				temp.assign(buff);
				val.SetString(temp.c_str(), temp.length(), allocator);
			}			
		}
		break;
	case rapidjson::Type::kTrueType:
		std::cout << "kTrueType";
		break;

	default:
		std::cout << "default";
		break;
	}
}

/*
void adlEntity_editor::typeBasedSerializer(const rapidjson::Value& val)
{
	switch (val.GetType())
	{
	case rapidjson::Type::kArrayType:
		std::cout << "[";
		assert(val.IsArray());
		for (rapidjson::Value::ConstValueIterator itr = val.Begin(); itr != val.End(); ++itr) {
			const rapidjson::Value& attribute = *itr;
			typeBasedSerializer(attribute);
		}
		std::cout << "]";
		break;
	case rapidjson::Type::kFalseType:
		std::cout << "kFalseType";
		break;
	case rapidjson::Type::kNullType:
		std::cout << "kNullType";
		break;
	case rapidjson::Type::kNumberType:
		//std::cout << "kNumberType : ";

		if (val.IsDouble())
		{
			std::cout << val.GetDouble() << " ";
		}
		if (val.IsInt())
		{
			std::cout << val.GetInt() << " ";
		}
		break;
	case rapidjson::Type::kObjectType:
		std::cout << "{" << std::endl;
		assert(val.IsObject());
		for (rapidjson::Value::ConstMemberIterator objItr = val.MemberBegin(); objItr != val.MemberEnd(); ++objItr) {
			std::cout << objItr->name.GetString() << ": ";

			typeBasedSerializer(objItr->value);

			std::cout << std::endl;
		};
		std::cout << "}" << std::endl;

		break;
	case rapidjson::Type::kStringType:
		std::cout << val.GetString();
		break;
	case rapidjson::Type::kTrueType:
		std::cout << "kTrueType";
		break;

	default:
		std::cout << "default";
		break;
	}
}
*/