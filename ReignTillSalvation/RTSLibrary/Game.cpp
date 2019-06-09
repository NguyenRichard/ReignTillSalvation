#include "Game.h"
#include "OtherFunctions.h"
#include "LawMenu.h"

#pragma region GameFunctions

Game::Game(int width, int height) :
	RTSState(width, height),
	map(std::make_unique<Map>()),
	time(std::make_unique<sftools::Chronometer>(sf::Time::Zero))
{
	music.openFromFile(MAIN_MUSIC_PATH);
	music.play();
}

#pragma endregion GameFunctions

#pragma region RTSStateFunctions

Game::Game(const RTSState& state) :
	RTSState(state),
	map(std::make_unique<Map>()),
	time(std::make_unique<sftools::Chronometer>(sf::Time::Zero))
{
	music.openFromFile(MAIN_MUSIC_PATH);
	music.setLoop(true);
	music.play();
}

Game::Game(const Game & state, std::unique_ptr<Map> new_map, std::unique_ptr<sftools::Chronometer> new_time) :
	RTSState(state), 
	map(std::move(new_map)),
	time(std::move(new_time))
{
	music.openFromFile(MAIN_MUSIC_PATH);
	music.setLoop(true);
	music.play();
}

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