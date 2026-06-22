#include "adventure_screen.h"

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
		//screen.mBackButton.clearOverlap();
	}

	void operator()(const sf::Event::MouseMoved& mouseMoved)
	{
		sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseMoved.position);
		for (auto& loc : screen.mLocations)
		{
			float dx = mouseViewCoords.x - loc.getCenter().x;
			float dy = mouseViewCoords.y - loc.getCenter().y;
			float distance = dx * dx + dy * dy;
			float radius = loc.getRadius() * loc.getRadius();

			if (distance <= radius)
			{
				loc.setHoverStatus(true);
				dr::CursorManager::get("hand");
			}
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
		}
	}

	void operator()(const auto&) {};
};

/**
 * @brief Initialize screen resources
 */
void AdventureScreen::init()
{
	Location loc0("railway_station");
	loc0.setMapPosition({ 900.f, 885.f }, 40.f);
	loc0.setName(dr::StringManager::get("railway_station_title"));
	mLocations.push_back(loc0);

	Location loc1("townhall");
	loc1.setMapPosition({ 705.f, 500.f }, 75.f);
	loc1.setName(dr::StringManager::get("townhall_title"));
	mLocations.push_back(loc1);

	Location loc2("cathedral");
	loc2.setMapPosition({ 705.f, 500.f }, 75.f);
	loc2.setName(dr::StringManager::get("cathedral_title"));
	mLocations.push_back(loc2);
}

void AdventureScreen::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
	event.visit(ScreenInputVisitor{ *this, window });
}

void AdventureScreen::update(float dt)
{
}

void AdventureScreen::render(sf::RenderWindow& window)
{
	window.setView(mMainView);

	for (auto& loc : mLocations)
	{
		if (loc.isHovered())
		{
			sf::CircleShape circle(loc.getRadius());
			circle.setPosition(loc.getCenter());
			window.draw(circle);
		}
	}

	window.draw(mAdventureMap);
}
