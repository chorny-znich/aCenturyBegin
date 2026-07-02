#pragma once
#include <cstdint>
#include <string> 

namespace gd
{
  enum class DayPhase : uint8_t
  {
    Morning,
    Day,
    Evening,
    Night,
    Unknown
  };

  enum class Weather : uint8_t
  {
    Clear,
    Unknown
  };

  inline std::string_view getDayPhaseName(DayPhase phase)
  {
    switch (phase)
    {
    case DayPhase::Morning: return "morning";
    case DayPhase::Day: return "day";
    case DayPhase::Evening: return "evening";
    case DayPhase::Night: return "night";
    }
    return "unknown";
  }

  inline std::string_view getWeather(Weather weather)
  {
    switch (weather)
    {
    case Weather::Clear: return "clear";
    }
    return "unknown";
  }
}