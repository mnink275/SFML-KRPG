#pragma once

#include <SFML/Graphics.hpp>
#include "World.h"


class Game : private sf::NonCopyable {
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	World mWorld;

	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;
};