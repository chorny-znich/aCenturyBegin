#pragma once
#include "location_manager.h"
#include "world_state_manager.h"
#include <SFML/Graphics/CircleShape.hpp>

class GameWorld
{
private:
	GameWorld() = default;
public:
	GameWorld(const GameWorld&) = delete;
	GameWorld& operator=(const GameWorld&) = delete;
	static GameWorld& instance()
	{
		static GameWorld world;
		return world;
	}

	void init();
	LocationManager& getLocationManager();
	const LocationManager& getLocationManager() const;
	WorldStateManager& getWorldStateManager();
	const WorldStateManager& getWorldStateManager() const;

	void setPlayerLocation(const std::string& loc);
	const std::string& getPlayerLocation() const;
private:
	LocationManager mLocationManager;
	WorldStateManager mWorldStateManager;
	std::string mPlayerLocation{"railway_station"};
};