#pragma once
#include "location.h"
#include <string>
#include <map>
#include <memory>

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

  std::string_view getCurrentTimeOfday() const;
  std::string_view getCurrentWeather() const;
  std::string_view getCurrentLocationId() const;
  void setCurrentLocationId(const std::string& id);
  const Location& getCurrentLocation() const;
  bool isOverlap() const;
private:
  std::map<std::string, Location> mLocations;
  std::string mCurrentTimeOfDay{"day"};
  std::string mCurrentWeather{"sunny"};
  std::string mCurrentLocationId{};
  bool mOverlap{ false };
};

