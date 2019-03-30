#ifndef HUDComponent_h__
#define HUDComponent_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"

class HUDComponent : public adlEntity_component { 

public:

	HUDComponent();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;


private:

	void MainMenu();

};

#endif //HUDComponent_h__
