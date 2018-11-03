#ifndef Human_h__
#define Human_h__

#include "engine/adl_entities/adlActor.h"

class Human : public adlActor { 

public:

	Human();
	~Human();

	virtual void init() override;
	virtual void update(float dt) override;

	virtual void serialize(PrettyWriter<StringBuffer>& writer) override;
	virtual void deserialize(const rapidjson::Value & reader) override;

private:

};

#endif //Human_h__
