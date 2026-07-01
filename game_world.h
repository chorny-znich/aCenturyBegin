#pragma once
#include "location_manager.h"
#include <SFML/Graphics/CircleShape.hpp>

class GameWorld
{
private:
	GameWorld() = default;
public:
	void init();
	LocationManager& getLocationManager();
	const LocationManager& getLocationManager() const;
private:
	LocationManager mLocationManager;
};

