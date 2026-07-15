#include "location_manager.h"
#include "string_manager.h"
#include "game_data.h"
#include <disreality_engine.h>
#include <queue>
#include <format>
#include <cassert>

/**
 * @brief 
 * @param filename 
 */
void LocationManager::init(int id)
{
  const std::string FILENAME_LOC = std::format("{}{}.ini", gd::path::LocationPath, id);
  const std::string FILENAME_DIST = std::format("{}{}.ini", gd::path::DistancePath, id);

  dr::IniDocument docLoc = dr::loadIniDocument(FILENAME_LOC);
  dr::IniDocument docDist = dr::loadIniDocument(FILENAME_DIST);
  dr::Section generalSection = docLoc.getSection("general");
  size_t locAmount = std::stoul(generalSection.at("size"));

  for (size_t i{ 0 }; i < locAmount; i++) {
    std::string sectionName = "location_" + std::to_string(i);
    dr::Section section = docLoc.getSection(sectionName);
    std::string id = section.at("id");
    Location loc(id);
    loc.setName(dr::StringManager::get(section.at("name")));
		loc.setDescription(dr::StringManager::get(section.at("description")));
    loc.setMapPosition({ std::stof(section.at("x")), std::stof(section.at("y")) }, std::stof(section.at("radius")));
		loc.setTransitStatus(std::stoi(section.at("transit")));

		if (docDist.hasSection(id))
		{
			for (const auto& rec : docDist.getSection(id))
			{
				loc.addConnection(rec.first, std::stoi(rec.second));
			}
		}

    mLocations.insert({ id, std::move(loc) });
  }
}

/**
 * @brief 
 * @return 
 */
const std::map<std::string, Location>& LocationManager::getLocations() const
{
  return mLocations;
}

/**
 * @brief Check if the mouse cursor overlaps with locations
 */
bool LocationManager::updateHoverStatus(sf::Vector2f mouseCoords)
{
	bool isOverlap = false;
	for (auto& loc : mLocations)
	{
		float dx = mouseCoords.x - loc.second.getCenter().x;
		float dy = mouseCoords.y - loc.second.getCenter().y;
		float distance = dx * dx + dy * dy;
		float radius = loc.second.getRadius() * loc.second.getRadius();

		if (distance <= radius)
		{
			loc.second.setHoverStatus(true);
			mCurrentLocationId = loc.second.getId();
			isOverlap = true;
		}
		else
		{
			loc.second.setHoverStatus(false);
		}
	}
	mOverlap = isOverlap;
	return isOverlap;
}

std::string_view LocationManager::getCurrentLocationId() const
{
	return mCurrentLocationId;
}

void LocationManager::setCurrentLocationId(const std::string& id)
{
	mCurrentLocationId = id;
}

const Location& LocationManager::getCurrentLocation() const
{
	return mLocations.at(mCurrentLocationId);
}

/**
 * @brief Get location by its id
 * @param id 
 * @return 
 */
const Location& LocationManager::getLocation(const std::string& id) const
{
	auto iter = mLocations.find(id);
	assert(iter != mLocations.end());
	return iter->second;
}

bool LocationManager::isOverlap() const
{
	return mOverlap;
}

/**
 * @brief find a path to a clicked or hovered location
 * @param startNode 
 * @param finishNode 
 * @return list of nodes to reach a destination node
 */
std::vector<std::string> LocationManager::findPath(const std::string startNode, const std::string finishNode)
{
	std::vector<std::string> result;
	std::queue<std::string> nodes;
	nodes.push(startNode);
	std::map<std::string, std::string> path = { {startNode, ""} };

	// Find the destination location
	while (!nodes.empty())
	{
		std::string currentNode = nodes.front();
		nodes.pop();

		if (currentNode == finishNode) break;
		Location loc = mLocations.at(currentNode);
		for (const auto& node : loc.getConnections())
		{
			if (!path.contains(node.first))
			{
				nodes.push(node.first);
				path[node.first] = currentNode;
			}
		}
	}

	// Build a reverse path from destination to start
	std::string currentNode = finishNode;
	while (currentNode != "")
	{
		result.push_back(currentNode);
		currentNode = path.at(currentNode);
	}

	std::reverse(result.begin(), result.end());
	return result;
}
