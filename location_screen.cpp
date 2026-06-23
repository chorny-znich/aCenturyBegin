#include "location_screen.h"

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
	sf::Text description = dr::TextManager::get("about_description");
	description.setPosition({ 200.f, 500.f });
	description.setString(dr::StringManager::get("about_game_content"));
	mInfo.push_back(description);

	sf::Text version = dr::TextManager::get("about_version");
	version.setPosition({ 900.f, 600.f });
	version.setString(dr::StringManager::get("about_game_version"));
	mInfo.push_back(version);

	mBackButton.setString(dr::StringManager::get("back_button"));
	mBackButton.setPosition({ 865.f, 1000.f });
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
	window.draw(mBackground);

	for (const auto& txt : mInfo)
	{
		window.draw(txt);
	}
	mBackButton.render(window);
}