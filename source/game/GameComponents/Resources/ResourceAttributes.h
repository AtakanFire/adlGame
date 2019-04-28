#ifndef ResourceAttributes_h__
#define ResourceAttributes_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"

class ResourceAttributes : public adlEntity_component { 

public:

	ResourceAttributes();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;
	
	// Resource Attributes 
	struct ResourceProperties {
		std::string name = "";
		std::string type = "";
		adlVec2 resource = adlVec2(0, 100); // Resource: (Current/Max)
	};

	struct ResourceRequires {
		float minExperience = 0;
	};


	ResourceProperties getProperties();
	ResourceRequires getRequires();

	void grow(float growing);
	bool exhaustion(float exhausting);


private:

	ResourceProperties properties;
	ResourceRequires requires;

	void normalizeResource();

};

#endif //ResourceAttributes_h__
