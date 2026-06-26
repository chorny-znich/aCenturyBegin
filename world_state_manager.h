#pragma once
#include <string>
#include <vector>

/**
 * @brief 
 */
class WorldStateManager
{
private:
  WorldStateManager() = default;
  
  const std::vector<std::string> PhaseOfDay{ "morning", "day", "evening", "night" };
  const std::vector<std::string> Weather{ "sunny", "rain", "foggy" };
public:
  WorldStateManager(const WorldStateManager&) = delete;
  WorldStateManager& operator=(const WorldStateManager&) = delete;
  static WorldStateManager& instance()
  {
    static WorldStateManager manager;
    return manager;
  }

  void advancetime(uint32_t minutes);
  std::string_view getCurrentTimeOfday() const;
  std::string_view getCurrentWeather() const;
private:
  std::string mCurrentTimeOfDay{ "day" };
  std::string mCurrentWeather{ "sunny" };
  uint32_t mTotalTime{ 480 }; // In minutes

  uint32_t getDay() const;
  uint32_t getHours() const;
  uint32_t getMinutes() const;

};

