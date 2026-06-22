#include "adventure_screen.h"
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
		//screen.mBackButton.clearOverlap();
	}

	void operator()(const sf::Event::MouseMoved& mouseMoved)
	{
		sf::Vector2f mouseViewCoords = window.mapPixelToCoords(mouseMoved.position);
		bool isOverlap = false;
		for (auto& loc : screen.mLocations)
		{
			float dx = mouseViewCoords.x - loc.getCenter().x;
			float dy = mouseViewCoords.y - loc.getCenter().y;
			float distance = dx * dx + dy * dy;
			float radius = loc.getRadius() * loc.getRadius();

			if (distance <= radius)
			{
				loc.setHoverStatus(true);
				isOverlap = true;
			}
			else
			{
				loc.setHoverStatus(false);
			}
		}
		if (isOverlap)
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

	Location loc0("railway_station");
	loc0.setMapPosition({ 885.f, 895.f }, 70.f);
	loc0.setName(dr::StringManager::get("railway_station_title"));
	mLocations.push_back(loc0);

	Location loc1("townhall");
	loc1.setMapPosition({ 705.f, 500.f }, 70.f);
	loc1.setName(dr::StringManager::get("townhall_title"));
	mLocations.push_back(loc1);

	Location loc2("cathedral");
	loc2.setMapPosition({ 1135.f, 215.f }, 70.f);
	loc2.setName(dr::StringManager::get("cathedral_title"));
	mLocations.push_back(loc2);
}

void AdventureScreen::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
	ImGui::SFML::ProcessEvent(window, event);
	event.visit(ScreenInputVisitor{ *this, window });
}

void AdventureScreen::update(float dt)
{
	ImGui::SFML::Update(dr::ImguiHelper::getWindow(), dr::ImguiHelper::getTime());
	sf::RenderWindow& window = dr::ImguiHelper::getWindow();
	sf::Vector2f mouseViewCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	ImGui::Begin("Debug input");
	ImGui::Text(std::format("x: {}", mouseViewCoords.x).c_str());
	ImGui::Text(std::format("y: {}", mouseViewCoords.y).c_str());
	ImGui::End();
}

void AdventureScreen::render(sf::RenderWindow& window)
{
	window.setView(mMainView);
	window.draw(mAdventureMap);
	for (auto& loc : mLocations)
	{
		if (loc.isHovered())
		{
			sf::CircleShape circle(loc.getRadius());
			circle.setOrigin({ loc.getRadius(), loc.getRadius() });
			circle.setPosition(loc.getCenter());
			circle.setFillColor({ 230, 240, 90, 120 });
			window.draw(circle);
		}
	}
	ImGui::SFML::Render(window);
}
