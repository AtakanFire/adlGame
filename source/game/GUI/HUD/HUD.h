#ifndef HUD_h__
#define HUD_h__

#include "engine/adl_entities/adlEntity.h"

class HUD : public adlEntity { 

public:

	HUD();
	~HUD();

	virtual void init() override;
	virtual void update(float dt) override;

	virtual void serialize(PrettyWriter<StringBuffer>& writer) override;
	virtual void deserialize(const rapidjson::Value & reader) override;

private:

};

#endif //HUD_h__
