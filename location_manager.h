#pragma once
#include "location.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

/**
 * @brief Manage locations
 * load locations form the ini files
 */
class LocationManager
{
public:
  LocationManager() = default;
  LocationManager(LocationManager&) = delete;
  LocationManager& operator=(LocationManager&) = delete;

  void init(int id);
  const std::map<std::string, Location>& getLocations() const;
  bool updateHoverStatus(sf::Vector2f mouseCoords);
  std::string_view getCurrentLocationId() const;
  void setCurrentLocationId(const std::string& id);
  const Location& getCurrentLocation() const;
  const Location& getLocation(const std::string& id) const;
  bool isOverlap() const;
private:
  std::map<std::string, Location> mLocations;
  std::string mCurrentLocationId{};
  bool mOverlap{ false };
};