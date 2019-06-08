#include "Game.h"
#include "OtherFunctions.h"
#include "LawMenu.h"

#pragma region GameFunctions

Game::Game(int width, int height) :
	RTSState(width, height),
	map(std::make_unique<Map>()),
	time(std::make_unique<sftools::Chronometer>(sf::Time::Zero))
{}

#pragma endregion GameFunctions

#pragma region RTSStateFunctions

Game::Game(const RTSState& state) :
	RTSState(state),
	map(std::make_unique<Map>()),
	time(std::make_unique<sftools::Chronometer>(sf::Time::Zero))
{}

Game::Game(const Game & state, std::unique_ptr<Map> new_map, std::unique_ptr<sftools::Chronometer> new_time) :
	RTSState(state), 
	map(std::move(new_map)),
	time(std::move(new_time))
{}

#pragma endregion RTSStateFunctions