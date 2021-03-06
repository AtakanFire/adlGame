#ifndef adl_render_manager_h__
#define adl_render_manager_h__

#include "engine/adlShared_types.h"
#include "engine/adl_math/adlMath.h"
#include "adlCamera.h"
#include "engine/adl_renderer/adlColor.h"
#include "engine/adl_entities/adlEntity.h"

class adlRender_manager
{
public:
	static adlRender_manager& get()
	{
		static adlRender_manager instance;
		return instance;
	}

	void prepare();
	void render(adlEntity_shared_ptr entity);
	void render(adlTerrain_shared_ptr terrain);
	void render(adlCube_map_shared_ptr cube_map);
	void render_text(const std::string& text, adlFont_shared_ptr font, float x, float y, float scale, adlColor color);
	void toggle_wire_frame_mode();

	void set_camera(adlCamera* camera);
	void set_sun(adlEntity_shared_ptr sun);
	void set_lights(const std::vector<adlEntity_shared_ptr>& point_lights);

	void set_projection(adlMat4 projection_matrix);
	adlMat4 get_projection_matrix();

private:
	adlRender_manager();

	void init();

	bool is_wire_frame_mode_;

	adlMat4 projection_matrix_;

	adlCamera* camera_;
	adlEntity_shared_ptr sun_;
	std::vector<adlEntity_shared_ptr> point_lights_;
};

#endif // adl_render_manager_h__