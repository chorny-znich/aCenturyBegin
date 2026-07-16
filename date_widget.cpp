#include "date_widget.h"
#include "game_world.h"
#include <disreality_engine.h>
#include <format>

/**
 * @brief Initialize text styles for sf::Text elements
 */
void DateWidget::init(sf::Vector2f pos, const std::string& textStyle)
{
  sf::Vector2f position = pos;
  mCurrentDay = dr::TextManager::get(textStyle);
  mCurrentDay->setPosition(position);
  mCurrentTime = dr::TextManager::get(textStyle);
  mCurrentTime->setPosition({ position.x + 75.f, position.y });
}

/**
 * @brief 
 */
void DateWidget::update(float dt)
{
  WorldStateManager& manager = GameWorld::instance().getWorldStateManager();
  mCurrentDay->setString(dr::StringManager::get("day_date_widget") + " " +
    std::to_string(manager.getDay()));
  std::string resultTime = std::format("{:02}:{:02}", manager.getHours(), 
    manager.getMinutes());
  mCurrentTime->setString(sf::String::fromUtf8(resultTime.begin(), resultTime.end()));
}

/**
 * @brief 
 * @param window 
 */
void DateWidget::render(sf::RenderWindow& window)
{
  window.draw(*mCurrentDay);
  window.draw(*mCurrentTime);
}