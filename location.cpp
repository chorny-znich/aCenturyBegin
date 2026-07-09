#include "location.h"

/**
 * @brief 
 * @param id unique identifier for the location 
 */
Location::Location(const std::string& id) :
  mId(id),
  mCenter({0.f, 0.f}),
  mRadius(0.f),
  mHovered(false)
{
}

std::string_view Location::getId() const
{
    return mId;
}

/**
 * @brief set the position of the location on the adventure map
 * @param centerPos position of the
 * @param radius 
 */
void Location::setMapPosition(sf::Vector2f centerPos, float radius)
{
  mCenter = centerPos;
  mRadius = radius;
}

/**
 * @brief 
 * @return 
 */
sf::Vector2f Location::getCenter() const
{
  return mCenter;
}

/**
 * @brief 
 * @return 
 */
float Location::getRadius() const
{
  return mRadius;
}

/**
 * @brief 
 * @param locName 
 */
void Location::setName(sf::String locName)
{
  mName = locName;
}

sf::String Location::getName() const
{
  return mName;
}

void Location::setDescription(sf::String text)
{
  mDescription = text;
}

sf::String Location::getDescription() const
{
  return mDescription;
}

/**
 * @brief 
 * @param status 
 */
void Location::setHoverStatus(bool status)
{
  mHovered = status;
}

/**
 * @brief 
 * @return 
 */
bool Location::isHovered() const
{
  return mHovered;
}

/**
 * @brief add a location that connected with this and time to reach connected location
 * @param loc - location connected with this 
 * @param time - time to reach the connected location
 */
void Location::addConnection(const std::string& loc, uint16_t time)
{
  mConnections.push_back({ loc, time });
}