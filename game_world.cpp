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
