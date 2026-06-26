#include "world_state_manager.h"

/**
 * @brief 
 * @param minutes 
 */
void WorldStateManager::advanceTime(uint32_t minutes)
{
	mTotalTime += minutes;
	mCurrentDayPhase = calculateDayPhase(getHours());
}

std::string_view WorldStateManager::getCurrentTimeOfday() const
{
	return gd::getDayPhaseName(mCurrentDayPhase);
}

std::string_view WorldStateManager::getCurrentWeather() const
{
	return gd::getWeather(mCurrentWeather);
}

/**
 * @brief 
 * @param hours 
 * @return 
 */
gd::DayPhase WorldStateManager::calculateDayPhase(uint32_t hours)
{
	if (hours >= 0 && hours < 6) return gd::DayPhase::Night;
	if (hours >= 6 && hours < 12) return gd::DayPhase::Morning;
	if (hours >= 12 && hours < 18) return gd::DayPhase::Day;
	if (hours >= 18 && hours <= 23) return gd::DayPhase::Evening;
	return gd::DayPhase::Unknown;
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
	return (mTotalTime / 60) % 24;
}

/**
 * @brief 
 * @return 
 */
uint32_t WorldStateManager::getMinutes() const
{
	return mTotalTime % 60;
}
