#ifndef SelectableComponent_h__
#define SelectableComponent_h__

#include "engine/adl_entities/adlPhysics_component.h"
#include "engine/adlShared_types.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameComponents/Player/PlayerAttributes.h"

class SelectableComponent : public adlPhysics_component { 

public:

	SelectableComponent();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	virtual void on_mouse_hover_start() override;
	virtual void under_mouse() override;
	virtual void on_mouse_hover_end() override;

	Entity getOwner() {
		return owner;
	};

	SelectableComponent* getTarget();
	void setTarget(SelectableComponent* newTarget);

private:

	SharedPointer<PlayerAttributes> player;

	SelectableComponent* target = nullptr;

};

#endif //SelectableComponent_h__
