#pragma once
#include <string>
#include <cstdint>
#include <SFML/System/String.hpp>

/**
 * @brief 
 */
class Clue
{
public:
  const sf::String& getDescription() const;
private:
  std::string mId;
  sf::String mDescription;
  sf::String mSuccess;
  sf::String mFail;
  uint8_t mCheckDifficulty{};
  bool mIsFound{ false };
};