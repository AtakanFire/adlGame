#ifndef SelectableComponent_h__
#define SelectableComponent_h__

#include "engine/adl_entities/adlPhysics_component.h"
#include "engine/adlShared_types.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameComponents/Player/PlayerAttributes.h"

#include "game/GameComponents/Humans/HumanAttributes.h"
#include "game/GameComponents/Resources/ResourceAttributes.h"
#include "game/GameComponents/Constructions/ConstructionAttributes.h"
#include "game/GameComponents/Constructions/StorageConstruction.h"

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

	template<typename T> SharedPointer<T> getAttributes();
	template<> SharedPointer<HumanAttributes> getAttributes<HumanAttributes>() { return (this->owner->get_component<HumanAttributes>("HumanAttributes")).lock(); }
	template<> SharedPointer<ResourceAttributes> getAttributes<ResourceAttributes>() { return (this->owner->get_component<ResourceAttributes>("ResourceAttributes")).lock(); }
	template<> SharedPointer<ConstructionAttributes> getAttributes<ConstructionAttributes>() { return (this->owner->get_component<ConstructionAttributes>("ConstructionAttributes")).lock(); }

	std::string getNameFromAttributes() {
		if (this->owner->has_component("HumanAttributes"))
		{
			return (this->owner->get_component<HumanAttributes>("HumanAttributes")).lock()->getProperties().name;
		} else if (this->owner->has_component("ResourceAttributes"))
		{
			return (this->owner->get_component<ResourceAttributes>("ResourceAttributes")).lock()->getProperties().name;
		} else if (this->owner->has_component("ConstructionAttributes"))
		{
			return (this->owner->get_component<ConstructionAttributes>("ConstructionAttributes")).lock()->getProperties().name;
		}
	};

	template<typename T> 
	SharedPointer<T> getComponent() { 
		std::string tname = (typeid(T).name() + sizeof(char) * 6); // "class "...
		//std::cout << "getComponent: |" << tname << "|" << std::endl;
		return owner->get_component<T>(tname).lock();
	};

	template<typename T>
	bool hasComponent() {
		std::string tname = (typeid(T).name() + sizeof(char) * 6); 
		return owner->has_component(tname);
	};


private:	

	SharedPointer<PlayerAttributes> player;

	SelectableComponent* target = nullptr;

};

#endif //SelectableComponent_h__
