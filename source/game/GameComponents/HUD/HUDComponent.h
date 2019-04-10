#ifndef HUDComponent_h__
#define HUDComponent_h__

#include "engine/adl_entities/adlEntity_component.h"

#include "engine/adl_editor/adlEditor_manager.h"
#include "engine/adlWindow.h"

#include "game/GameGeneric/GameGenericTypedef.h"
#include "game/GameComponents/Player/PlayerAttributes.h"

class HUDComponent : public adlEntity_component { 

public:

	static HUDComponent& get()
	{
		static HUDComponent instance;
		return instance;
	}

	HUDComponent();

	virtual bool init(const rapidjson::Value& json_object) override;
	virtual void post_init() override;
	virtual void update(float dt) override;
	virtual void destroy() override;
	virtual void editor() override;


private:

	ImGuiStyle defaultStyle;	
	adlEditor_manager* editorMan;
	PlayerAttributes* player;

	void mainMenu();
	void mainLayout();

	void humanAttributes();
	void resourceAttributes();
	void constructionAttributes();

};

#endif //HUDComponent_h__
