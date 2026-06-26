#include "world_state_manager.h"

/**
 * @brief 
 * @param minutes 
 */
void WorldStateManager::advancetime(uint32_t minutes)
{
	mTotalTime += minutes;

}

std::string_view WorldStateManager::getCurrentTimeOfday() const
{
	return mCurrentTimeOfDay;
}

std::string_view WorldStateManager::getCurrentWeather() const
{
	return mCurrentWeather;
}

/**
 * @brief How many days had past since start of the game
 * @return Number of days
 */
uint32_t WorldStateManager::getDay() const
{
	return (mTotalTime / 1440) + 1;
}

/**
 * @brief 
 * @return 
 */
uint32_t WorldStateManager::getHours() const
{
	return (mTotalTime % 1440) % 24;
}

/**
 * @brief 
 * @return 
 */
uint32_t WorldStateManager::getMinutes() const
{
	return mTotalTime % 60;
}
