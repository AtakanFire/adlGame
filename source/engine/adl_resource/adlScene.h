#ifndef adl_scene_h__
#define adl_scene_h__

#include <vector>

#include "engine/adlShared_types.h"
#include "engine/adl_renderer/adlCamera.h"

class adlScene
{
public:
	adlScene(const std::string& scene_name);
	adlScene(const std::string& scene_name, std::vector<adlEntity*> entities, std::vector<adlActor*> actors);
	~adlScene();

	void update(float dt);
	void render();
	
	void spawn_point_light(adlPoint_light_shared_ptr point_light, adlVec3 position = adlVec3(0.0f), adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));
	void set_sun(adlSun_shared_ptr sun);
	void set_camera(adlCamera* camera);
	void set_terrain(adlTerrain_shared_ptr terrain);
	void set_cube_map(adlCube_map_shared_ptr cube_map);

	void spawnEntity(adlEntity* entity);
	void spawnActor(adlActor* actor, adlVec3 position = adlVec3(0.0f), adlVec3 rotation = adlVec3(0.0f), adlVec3 scale = adlVec3(1.0f));

	adlCamera* get_camera();
	adlSun_shared_ptr get_sun();
	adlTerrain_shared_ptr get_terrain();
	adlCube_map_shared_ptr get_cube_map();
	std::vector<adlEntity_shared_ptr>& get_all_entities();
	std::vector<adlActor_shared_ptr>& get_all_actors();
	std::vector<adlPoint_light_shared_ptr>& get_all_point_lights();

	std::vector<adlEntity*>& getAllEntities();
	std::vector<adlActor*>& getAllActors();


	const std::string& get_name();

private:

	std::string scene_name_;
	std::vector<adlPoint_light_shared_ptr> point_lights_;

	std::vector<adlEntity*> entities_;
	std::vector<adlActor*> actors_;


	adlSun_shared_ptr sun_;
	adlCamera* camera_;
	adlTerrain_shared_ptr terrain_;
	adlCube_map_shared_ptr cube_map_;
};

#endif // adl_scene_h__