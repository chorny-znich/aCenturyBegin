#include "location_manager.h"
#include "game_data.h"
#include <disreality_engine.h>
#include <format>

/**
 * @brief 
 * @param filename 
 */
void LocationManager::init(int id)
{
  auto& manager = instance();
  const std::string FILENAME = std::format("{}{}.ini", gd::path::LocationPath, id);
  dr::IniDocument doc = dr::loadIniDocument(FILENAME);
  dr::Section generalSection = doc.getSection("general");
  size_t locAmount = std::stoul(generalSection.at("size"));

  for (size_t i{ 0 }; i < locAmount; i++) {
    std::string sectionName = "location_" + std::to_string(i);
    dr::Section section = doc.getSection(sectionName);
    std::string id = section.at("id");
    Location loc(id);
    loc.setName(dr::StringManager::get(section.at("name")));
    loc.setMapPosition({ std::stof(section.at("x")), std::stof(section.at("y")) }, std::stof(section.at("radius")));
    
    manager.mLocations.insert({ id, std::move(loc) });
  }
}

/**
 * @brief 
 * @return 
 */
std::map<std::string, Location>& LocationManager::getLocations()
{
  return instance().mLocations;
}
