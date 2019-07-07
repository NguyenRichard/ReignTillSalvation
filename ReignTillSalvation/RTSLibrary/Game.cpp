#include "Game.h"
#include "OtherFunctions.h"
#include "LawMenu.h"

#pragma region GameFunctions

Game::Game(int width, int height, std::unique_ptr<sf::Music> old_music) :
	RTSState(width, height, std::move(old_music)),
	map(std::make_unique<Map>()),
	time(std::make_unique<sftools::Chronometer>(sf::Time::Zero))
{}

#pragma endregion GameFunctions

#pragma region RTSStateFunctions

Game::Game(const RTSState& state, std::unique_ptr<sf::Music> old_music) :
	RTSState(state, std::move(old_music)),
	map(std::make_unique<Map>()),
	time(std::make_unique<sftools::Chronometer>(sf::Time::Zero))
{}

Game::Game(const Game & state, std::unique_ptr<Map> new_map, std::unique_ptr<sftools::Chronometer> new_time,
	std::unique_ptr<sf::Music> old_music) :
	RTSState(state, std::move(old_music)), 
	map(std::move(new_map)),
	time(std::move(new_time))
{}

void Game::renderGame(sf::RenderWindow& window) {
	map->render(window);
	for (auto & renderable : renderables) {
		renderable->render(window);
	}
}

void Game::renderAnimation(sf::RenderWindow& window) {
	if (time->getElapsedTime().asMilliseconds() - last_anim_update.asMilliseconds() > MS_PER_ANIM) {
		for (auto & renderable : renderables) {
			renderable->updateAnimation();
		}
	}
}

#pragma endregion RTSStateFunctions