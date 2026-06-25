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
private:
  std::string mCurrentTimeOfDay{ "day" };
  std::string mCurrentWeather{ "sunny" };
  uint32_t mTotalTime{ 480 }; // In minutes
};

