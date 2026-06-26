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
    Night
  };

  inline std::string getDayPhaseName(DayPhase phase)
  {
    switch (phase)
    {
    case DayPhase::Morning: return "morning";
    case DayPhase::Day: return "day";
    case DayPhase::Evening: return "evening";
    case DayPhase::Night: return "night";
    }
  }
}