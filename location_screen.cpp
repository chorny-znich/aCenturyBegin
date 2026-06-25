#include "location_screen.h"
#include "location_manager.h"
#include <format>

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
	const Location& loc = LocationManager::instance().getCurrentLocation();
	LocationManager& manager = LocationManager::instance();
	std::string textureKey = std::format("{}_{}_{}", manager.getCurrentLocationId(), manager.getCurrentTimeOfday(),
		manager.getCurrentWeather());
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