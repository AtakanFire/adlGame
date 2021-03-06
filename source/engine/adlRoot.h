#ifndef adl_root_h__
#define adl_root_h__

#include <string>

#include "engine/common.h"
#include "engine/adl_renderer/adlCamera.h"
#include "engine/adl_renderer/adlColor.h"
#include "engine/adlWindow.h"
#include "adlMemory.h"
#include "adl_resource/adlResource_manager.h"
#include "adl_renderer/adlRender_manager.h"
#include "adl_debug/adlLogger.h"
#include "adlInput.h"
#include "adl_helper/adlFPS_manager.h"
#include "adlScene_manager.h"
#include "adl_editor/adlEditor_manager.h"
#include "engine/adl_resource/adlScene.h"
#include "engine/adl_math/adlMouse_picker.h"
#include "engine/adl_renderer/adlDebug_renderer.h"
#include "engine/adl_debug/adlTerrain_debugger.h"
#include "engine/adl_physics/adl_bullet/adlBullet_physics.h"

/*
* Entry point for the engine
* Extend this class and implement init() and update(double dt) methods
*/
class adlRoot
{
public:
	adlRoot();
	~adlRoot();
	
	void start();
	virtual bool init() = 0;
	virtual bool update(float dt) = 0;
	void run();

	void init_window(const std::string& title, int width, int height);

	adlResource_manager* adl_rm;
	adlRender_manager* adl_renderer;
	adlInput* adl_input;
	adlLogger* adl_logger;
	adlWindow* adl_window;
	adlCamera* camera;
	adlScene_manager* adl_scene_manager;
	adlEditor_manager* adl_editor;
	adlMouse_picker* mouse_picker;
	adlDebug_renderer* debug_renderer;
	adlTerrain_debugger* terrain_debugger;
	adlIPhysics* physics_;
protected:
private:
	adlFPS_manager* fps_manager_;

	bool is_running_;
	bool rendering_bounding_boxes_ = false;
	bool rendering_physics_diagnostics_ = false;

	void game_thread();
};


#endif // adl_root_h__