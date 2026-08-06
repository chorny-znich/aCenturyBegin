#pragma once
#include "clue.h"
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <SFML/System/Vector2.hpp>
#include<SFML/System/String.hpp>

/**
 * @brief Single location on the adventure map
 */
class Location
{
public:
  Location(const std::string& id);
  std::string_view getId() const;
  void setMapPosition(sf::Vector2f centerPos, float radius);
  sf::Vector2f getCenter() const;
  float getRadius() const;
  void setName(sf::String locName);
  sf::String getName() const;
  void setDescription(sf::String text);
  sf::String getDescription() const;
  void setHoverStatus(bool status);
  bool isHovered() const;
  void setTransitStatus(bool status);
  bool isTransit() const;

  void addConnection(const std::string& loc, uint32_t time);
  const std::unordered_map<std::string, uint32_t>& getConnections() const;

  void addClue();
  bool hasClue() const;
private:
  std::string mId;
  sf::Vector2f mCenter;
  float mRadius;
  sf::String mName;
  sf::String mDescription;
  bool mHovered;
  bool mTransit;
  std::unordered_map<std::string, uint32_t> mConnections;
  std::vector<Clue> mClues;
};