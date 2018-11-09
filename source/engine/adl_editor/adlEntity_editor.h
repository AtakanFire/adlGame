#ifndef adlEntity_editor_h__
#define adlEntity_editor_h__  
 
#include "engine/adl_entities/adlActor.h"

class adlEntity_editor 
{  
public:  
	adlEntity_editor();  
	~adlEntity_editor();  
 
	void update(std::vector<adlEntity*>& entities);

	void serializeEntities(std::vector<adlEntity*>& entities);
	void deserializeEntities(const rapidjson::Value& reader);

private:  
	void typeBasedSerializer(rapidjson::Value& val, rapidjson::Document::AllocatorType& allocator);


};  
 
#endif // adlEntity_editor_h__  
 
