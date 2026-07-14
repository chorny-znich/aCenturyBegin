#pragma once
#include "game_data.h"
#include <disreality_engine.h>
#include <memory>

struct ScreenInputVisitor;

/**
 * @brief Screen with location's map, player's UI
 */
class AdventureScreen : public dr::Screen
{
	friend struct ScreenInputVisitor;
public:
	void init() override;
	void handleInput(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float dt) override;
	void render(sf::RenderWindow& window) override;
private:
	struct ScreenInputVisitor;
	sf::View mMainView{ sf::FloatRect({0, 0}, {gd::GraphicsResolution.x, gd::GraphicsResolution.y}) };
	sf::Sprite mAdventureMap{dr::Textures::get("adventure_map_0")};

	sf::CircleShape mPlayerMarker{ 70.f };
	std::vector<std::string> mCurrentPath;
};