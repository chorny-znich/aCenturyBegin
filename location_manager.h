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
public:
  LocationManager(LocationManager&) = delete;
  LocationManager& operator=(LocationManager&) = delete;

  static void init(int id);
  static std::map<std::string, Location>& getLocations();
private:
  LocationManager() = default;
  static LocationManager& instance()
  {
    static LocationManager manager;
    return manager;
  }
  std::map<std::string, Location> mLocations;
};

