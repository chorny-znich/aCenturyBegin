#pragma once
#include <string>
#include <string_view>
#include <SFML/System/Vector2.hpp>
#include<SFML/System/String.hpp>

/**
 * @brief Single location on the adventure map
 */
class Location
{
public:
  Location(const std::string& id);
  void setMapPosition(sf::Vector2f centerPos, float radius);
  sf::Vector2f getCenter() const;
  float getRadius() const;
  void setName(sf::String locName);
  void setHoverStatus(bool status);
  bool isHovered() const;
private:
  std::string mId;
  sf::Vector2f mCenter;
  float mRadius;
  sf::String mName;
  bool mHovered;
};