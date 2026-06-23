#pragma once
#include "location.h"
#include <string>
#include <map>

/**
 * @brief Manage locations
 * load locations form the ini files
 */
class LocationManager
{
private:
  LocationManager() = default;
public:
  LocationManager(LocationManager&) = delete;
  LocationManager& operator=(LocationManager&) = delete;
  
  static LocationManager& instance()
  {
    static LocationManager manager;
    return manager;
  }

  void init(int id);
  const std::map<std::string, Location>& getLocations() const;
  bool updateHoverStatus(sf::Vector2f mouseCoords);
private:
  std::map<std::string, Location> mLocations;
};

