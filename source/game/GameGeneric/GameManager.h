#ifndef GameManager_h__
#define GameManager_h__

#include "game/GameGeneric/GameGenericTypedef.h"

class GameManager { 

public:

	static GameManager& get()
	{
		static GameManager instance;
		return instance;
	}

	Entity getTaggedEntity(std::string entityTag);
	void setTaggedEntity(std::string entityTag, Entity& entity);

private:
	GameManager();

	std::vector<std::string> taggedEntityNames = {};
	std::vector<Entity> taggedEntities = {};


};

#endif //GameManager_h__
