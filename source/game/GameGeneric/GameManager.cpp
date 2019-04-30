#include "GameManager.h"
#include "GameManager.h"

GameManager::GameManager()
{

}

Entity GameManager::getTaggedEntity(std::string entityTag)
{
	std::vector<std::string>::iterator names = std::find(taggedEntityNames.begin(), taggedEntityNames.end(), entityTag);

	if (names != taggedEntityNames.cend()) {
		return taggedEntities[std::distance(taggedEntityNames.begin(), names)];
	} else {
		std::cout << "There is no Tag with '" << entityTag << "'" << std::endl;
	}
}

void GameManager::setTaggedEntity(std::string entityTag, Entity& entity)
{
	taggedEntityNames.push_back(entityTag);
	taggedEntities.push_back(entity);
}



