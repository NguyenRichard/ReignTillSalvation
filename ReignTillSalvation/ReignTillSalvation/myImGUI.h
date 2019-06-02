#pragma once

#pragma region include
#include <iostream>

#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"
#include "../RTSLibrary/MainMenu.h"
#include "../RTSLibrary/RTS.h"
#include "../RTSLibrary/Game.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#pragma endregion include

#pragma region define
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1500
#define MS_PER_UPDATE 60
#pragma endregion define

int imGUImain();
void globalInformation(sf::RenderWindow &, RTS&, bool*);
void individualWindow(sf::RenderWindow &, RTS&, bool*);
void showIndividual(Individual&, const char*, int);
void elementWindow(sf::RenderWindow &, RTS&, bool*,char*);
void showElement(Element&, int);