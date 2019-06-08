#include "Game.h"
#include "OtherFunctions.h"
#include "LawMenu.h"

#pragma region GameFunctions

Game::Game(int width, int height) :
	RTSState(width, height),
	map(std::make_unique<Map>())
{}

#pragma endregion GameFunctions

#pragma region RTSStateFunctions

Game::Game(const RTSState& state) :
	RTSState(state),
	map(std::make_unique<Map>()) 
{}

Game::Game(const Game & state, std::unique_ptr<Map> new_map) :
	RTSState(state), 
	map(std::move(new_map))
{

}

#pragma endregion RTSStateFunctions