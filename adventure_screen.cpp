#include "adventure_screen.h"
#include "location_manager.h"
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
		if (LocationManager::instance().updateHoverStatus(mouseViewCoords))
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

	LocationManager::instance().init(0);
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
	for (const auto& loc : LocationManager::instance().getLocations())
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
	ImGui::SFML::Render(window);
}
