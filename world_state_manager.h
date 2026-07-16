#pragma once
#include "world_types.h"
#include <string>
#include <vector>

/**
 * @brief 
 */
class WorldStateManager
{  
public:
  WorldStateManager() = default;
  WorldStateManager(const WorldStateManager&) = delete;
  WorldStateManager& operator=(const WorldStateManager&) = delete;

  void advanceTime(uint32_t minutes);
  std::string_view getCurrentTimeOfday() const;
  std::string_view getCurrentWeather() const;

  uint32_t getDay() const;
  uint32_t getHours() const;
  uint32_t getMinutes() const;
private:
  gd::DayPhase mCurrentDayPhase{gd::DayPhase::Morning};
  gd::Weather mCurrentWeather{ gd::Weather::Clear };
  uint32_t mTotalTime{ 480 }; // In minutes

  gd::DayPhase calculateDayPhase(uint32_t hours);
};