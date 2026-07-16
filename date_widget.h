#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <optional>

/**
 * @brief GUI element. Display current date (day, hours:minutes)
 *        need coordinates for widget in init() method
 */
class DateWidget
{
public:
  void init(sf::Vector2f pos, const std::string& textStyle);
  void update(float dt);
  void render(sf::RenderWindow& window);
private:
  std::optional<sf::Text> mCurrentDay;
  std::optional<sf::Text> mCurrentTime;
};