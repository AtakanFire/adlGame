#ifndef Construction_h__
#define Construction_h__

#include "engine/adl_entities/adlActor.h"

class Construction : public adlActor { 

public:

	Construction();
	~Construction();

	virtual void init() override;
	virtual void update(float dt) override;

	virtual void serialize(PrettyWriter<StringBuffer>& writer) override;
	virtual void deserialize(const rapidjson::Value & reader) override;

private:

};

#endif //Construction_h__
