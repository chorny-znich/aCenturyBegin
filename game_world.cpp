#include "game_world.h"

void GameWorld::init()
{
	mLocationManager.init(0);
}

LocationManager& GameWorld::getLocationManager()
{
	return mLocationManager;
}

const LocationManager& GameWorld::getLocationManager() const
{
	return mLocationManager;
}

WorldStateManager& GameWorld::getWorldStateManager()
{
	return mWorldStateManager;
}

const WorldStateManager& GameWorld::getWorldStateManager() const
{
	return mWorldStateManager;
}

void GameWorld::setPlayerLocation(const std::string& loc)
{
	mPlayerLocation = loc;
}

const std::string& GameWorld::getPlayerLocation() const
{
	return mPlayerLocation;
}