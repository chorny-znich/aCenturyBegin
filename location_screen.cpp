#include "location_screen.h"
#include "game_world.h"
#include "world_state_manager.h"
#include <format>
#include <imgui.h>
#include <imgui-SFML.h>

/**
 * @brief For handling Events in handleInput method
 */
struct LocationScreen::ScreenInputVisitor
{
	LocationScreen& screen;
	sf::RenderWindow& window;

	void clearUI()
	{
		window.setMouseCursor(dr::CursorManager::get("arrow"));
		screen.mBackButton.clearOverlap();
	}

	void operator()(const sf::Event::MouseMoved& mouseMoved)
	{
		sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseMoved.position);
		if (screen.mBackButton.isOverlap(mouseViewCoords))
		{
			window.setMouseCursor(dr::CursorManager::get("hand"));
		}
		else
		{
			window.setMouseCursor(dr::CursorManager::get("arrow"));
		}
	}

	/**
	 * @brief Mouse button clicked event
	 * @param
	 */
	void operator()(const sf::Event::MouseButtonPressed mouseButton)
	{
		if (mouseButton.button == sf::Mouse::Button::Left)
		{
			sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseButton.position);
			if (screen.mBackButton.isClicked(mouseViewCoords))
			{
				clearUI();
				dr::ScreenManager::destroyScreen();
				window.setMouseCursor(dr::CursorManager::get("arrow"));
			}
		}
	}

	void operator()(const auto&) {};
};

/**
 * @brief Initialize screen resources
 */
void LocationScreen::init()
{
	LocationManager& locManager = GameWorld::instance().getLocationManager();
	const Location& loc = locManager.getCurrentLocation();
	WorldStateManager& worldManager = GameWorld::instance().getWorldStateManager();
	std::string textureKey = std::format("{}_{}_{}", locManager.getCurrentLocationId(), worldManager.getCurrentTimeOfday(),
		worldManager.getCurrentWeather());
	mBackground.emplace(dr::Textures::get(textureKey));
	mBackground->setPosition({ 0.f, 100.f });

	sf::Text locationtitle = dr::TextManager::get("location_title");
	locationtitle.setPosition({ 800.f, 5.f });
	locationtitle.setString(loc.getName());
	mInfo.push_back(locationtitle);

	sf::Text locDescription = dr::TextManager::get("location_description");
	locDescription.setPosition({ 300.f, 1020.f });
	locDescription.setString(loc.getDescription());
	mInfo.push_back(locDescription);

	mBackButton.setString(dr::StringManager::get("back_button"));
	mBackButton.setPosition({ 1600.f, 800.f });
}

void LocationScreen::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
	event.visit(ScreenInputVisitor{ *this, window });
}

void LocationScreen::update(float dt)
{
	LocationManager& locManager = GameWorld::instance().getLocationManager();
	const Location& loc = locManager.getCurrentLocation();
	WorldStateManager& worldManager = GameWorld::instance().getWorldStateManager();
	std::string dayPhase = GameWorld::instance().getWorldStateManager().getCurrentTimeOfday().data();
	std::string textureKey = std::format("{}_{}_{}", locManager.getCurrentLocationId(), worldManager.getCurrentTimeOfday(),
		worldManager.getCurrentWeather());
	ImGui::Begin("World state");
	ImGui::Text(std::format("Phase of day: {}", dayPhase).c_str());
	ImGui::End();
}

void LocationScreen::render(sf::RenderWindow& window)
{
	window.setView(mMainView);
	window.draw(*mBackground);

	for (const auto& txt : mInfo)
	{
		window.draw(txt);
	}
	mBackButton.render(window);
}