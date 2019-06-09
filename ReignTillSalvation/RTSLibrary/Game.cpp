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
	std::vector<std::unique_ptr<Individual>>& leaders = map->getLeaders();
	std::vector<std::unique_ptr<Element>>& elements = map->getElements();
	std::vector<std::unique_ptr<Danger>>& dangers = map->getDangers();
	std::vector<std::unique_ptr<Law>>& laws = map->getLaws();
	
	map->render(window);
	
	for (const auto & element : elements) {
		element->render(window);
	}

	if (time->getElapsedTime().asMilliseconds() - last_render.asMilliseconds() > MS_PER_RENDER) {
		for (const auto & leader : leaders) {
			leader->render_and_update(window);
		}
		last_render = time->getElapsedTime();
	}
	else {
		for (const auto & leader : leaders) {
			leader->render(window);
		}
	}


	sf::Shape* danger_shape;
	for (const auto &danger : dangers) {
		danger_shape = &danger->getShape();
		window.draw(*danger_shape);
	}

	for (const auto & law : laws) {
		law->render(window);
	}
}

#pragma endregion RTSStateFunctions