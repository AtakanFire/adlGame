#ifndef MovementComponent_h__
#define MovementComponent_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "game/GameGeneric/GameGenericTypedef.h"

class MovementComponent : public adlEntity_component { // Moveable(Movable)

public:

	MovementComponent();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;

	void move(adlVec3 targetPos);

private:

	bool isMovable = true; // Movable by Player

};

#endif //MovementComponent_h__
