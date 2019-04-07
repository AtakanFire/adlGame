#ifndef physics_listener_h__
#define physics_listener_h__

#include "../engine/adlPhysics_observer.h" 
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_entities/adlTransform_component.h"

#include "game/GameGeneric/GameFunctions.h"

#include "game/GameComponents/Misc/SelectableComponent.h"
#include "game/GameComponents/Player/PlayerAttributes.h"
#include "game/GameComponents/Humans/HumanAttributes.h"

class Physics_listener : public adlPhysics_observer
{
public:
	Physics_listener() {};
	~Physics_listener() {};

	virtual void on_collision_start(adlEntity_shared_ptr entity1, adlEntity_shared_ptr entity2) override
	{
		//std::cout << "collision start" << std::endl;
	}

	virtual void on_collision_end(adlEntity_shared_ptr entity1, adlEntity_shared_ptr entity2)
	{
	}

	virtual void on_terrain_collision_start(adlEntity_shared_ptr entity, const adlVec3& collision_point)
	{		
	}

	virtual void on_terrain_collision_end(adlEntity_shared_ptr entity)
	{
	}

	virtual void on_terrain_mouse_ray_collision(const adlVec3& collision_point) 
	{
		if (GameFunctions::CheckImGuiClicked())
		{
			return;
		}

		adlInput* input = &adlInput::get();
		PlayerAttributes* player = &PlayerAttributes::get();

		if (input->get_mouse_down(ADL_BUTTON_LEFT)) {
			player->setSelection(nullptr);
		}
		else if (player->getSelection() != nullptr && input->get_mouse_down(ADL_BUTTON_RIGHT))
		{
			SharedPointer<SelectableComponent> selected(player->getSelection()->get_component<SelectableComponent>("SelectableComponent"));
			selected->setTarget(nullptr);
			if (selected->getOwner()->has_component("HumanAttributes"))
			{
				SharedPointer<HumanAttributes> human(selected->getOwner()->get_component<HumanAttributes>("HumanAttributes"));
				human->movement(collision_point);
			}
		}
	}

	virtual void on_mouse_collision_start(adlEntity_shared_ptr  entity)
	{
	}
};

#endif //physics_listener_h__