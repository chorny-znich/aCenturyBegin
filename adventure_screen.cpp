#include "adventure_screen.h"
#include "location_manager.h"
#include "world_state_manager.h"
#include "game_world.h"
#include "location_screen.h"
#include <format>
#include <imgui.h>
#include <imgui-SFML.h>

/**
 * @brief For handling Events in handleInput method
 */
struct AdventureScreen::ScreenInputVisitor
{
	AdventureScreen& screen;
	sf::RenderWindow& window;

	void clearUI()
	{
		window.setMouseCursor(dr::CursorManager::get("arrow"));
	}

	void operator()(const sf::Event::MouseMoved& mouseMoved)
	{
		sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseMoved.position);
		if (GameWorld::instance().getLocationManager().updateHoverStatus(mouseViewCoords))
		{
			window.setMouseCursor(dr::CursorManager::get("hand"));
			LocationManager& locManager = GameWorld::instance().getLocationManager();
			screen.mCurrentPath = GameWorld::instance().getLocationManager().findPath(GameWorld::instance().getPlayerLocation(),
				locManager.getCurrentLocationId().data());
		}
		else
		{
			window.setMouseCursor(dr::CursorManager::get("arrow"));
			screen.mCurrentPath.clear();
		}
	}

	/**
	 * @brief Mouse button clicked event
	 * @param
	 */
	void operator()(const sf::Event::MouseButtonPressed mouseButton)
	{
		
		if (mouseButton.button == sf::Mouse::Button::Left && GameWorld::instance().getLocationManager().isOverlap())
		{
			sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseButton.position);
			LocationManager& locManager = GameWorld::instance().getLocationManager();
			const Location& loc = locManager.getCurrentLocation();

			GameWorld::instance().getLocationManager().findPath(GameWorld::instance().getPlayerLocation(),
				locManager.getCurrentLocationId().data());

			GameWorld::instance().getWorldStateManager().advanceTime(240);
			GameWorld::instance().setPlayerLocation(loc.getId().data());
			dr::ScreenManager::addScreen<LocationScreen>("location_screen");
		}
	}

	void operator()(const auto&) {};
};

/**
 * @brief Initialize screen resources
 */
void AdventureScreen::init()
{
	ImGui::SFML::Init(dr::ImguiHelper::getWindow());
	GameWorld::instance().init();

	mPlayerMarker.setOrigin({ 70.f, 70.f });
	const Location& loc = GameWorld::instance().getLocationManager().getLocation(GameWorld::instance().getPlayerLocation());
	mPlayerMarker.setPosition(loc.getCenter());
	mPlayerMarker.setFillColor({ 255, 0, 0, 120 });
}

void AdventureScreen::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
	ImGui::SFML::ProcessEvent(window, event);
	event.visit(ScreenInputVisitor{ *this, window });
}

/**
 * @brief 
 * @param dt 
 */
void AdventureScreen::update(float dt)
{
	ImGui::SFML::Update(dr::ImguiHelper::getWindow(), dr::ImguiHelper::getTime());
	sf::RenderWindow& window = dr::ImguiHelper::getWindow();
	sf::Vector2f mouseViewCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	ImGui::Begin("Debug input");
	ImGui::Text(std::format("x: {}", mouseViewCoords.x).c_str());
	ImGui::Text(std::format("y: {}", mouseViewCoords.y).c_str());
	ImGui::End();

	std::string dayPhase = GameWorld::instance().getWorldStateManager().getCurrentTimeOfday().data();
	ImGui::Begin("World state");
	ImGui::Text(std::format("Phase of day: {}", dayPhase).c_str());
	ImGui::End();

	std::string text = "";
	for (const auto& loc : mCurrentPath)
	{
		text += loc + "\n";
	}
	ImGui::Begin("Pathfinding");
	ImGui::Text(text.c_str());
	ImGui::End();

	const Location& loc = GameWorld::instance().getLocationManager().getLocation(GameWorld::instance().getPlayerLocation());
	mPlayerMarker.setPosition(loc.getCenter());
}

/**
 * @brief 
 * @param window 
 */
void AdventureScreen::render(sf::RenderWindow& window)
{
	window.setView(mMainView);
	window.draw(mAdventureMap);

	// Draw nodes like location and transit location
	const auto locations = GameWorld::instance().getLocationManager().getLocations();
	for (const auto& [id, loc] : locations)
	{
		float radius = loc.getRadius() / 2;
		sf::CircleShape circle(radius);
		circle.setOrigin({ radius, radius });
		circle.setPosition(loc.getCenter());
		if (loc.isTransit())
		{
			circle.setFillColor({ 248, 248, 255, 150 });
		}
		else
		{
			circle.setFillColor({ 230, 240, 90, 150 });
		}

		// temporary check for path visualization
		if (std::find(mCurrentPath.begin(), mCurrentPath.end(), loc.getId()) != mCurrentPath.end())
		{
			circle.setFillColor(sf::Color::Blue);
		}

		window.draw(circle);
	}

	// draw a circle over the hovered location
	for (const auto& loc : GameWorld::instance().getLocationManager().getLocations())
	{
		if (loc.second.isHovered())
		{
			sf::CircleShape circle(loc.second.getRadius());
			circle.setOrigin({ loc.second.getRadius(), loc.second.getRadius() });
			circle.setPosition(loc.second.getCenter());
			circle.setFillColor({ 230, 240, 90, 120 });
			window.draw(circle);
		}
	}

	// Draw player's marker
	window.draw(mPlayerMarker);

	ImGui::SFML::Render(window);
}
