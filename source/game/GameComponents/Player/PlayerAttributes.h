#ifndef PlayerAttributes_h__
#define PlayerAttributes_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"

class PlayerAttributes : public adlEntity_component { 

public:

	static PlayerAttributes& get()
	{
		static PlayerAttributes instance;
		return instance;
	}

	PlayerAttributes();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	void setSelection(Entity selected);

private:

	Entity selection;


};

#endif //PlayerAttributes_h__
