#pragma once

#pragma region include
#include <iostream>

#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"
#include "../RTSLibrary/Weak.h"
#include "../RTSLibrary/MainMenu.h"
#include "../RTSLibrary/RTS.h"
#include "../RTSLibrary/Game.h"
#include "../RTSLibrary/ViewManager.h"
#include "../RTSLibrary/GameRunning.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "../RTSLibrary/Value.h"
#include "SFMLOrthogonalLayer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <pugixml.hpp>
#pragma endregion include

#pragma region define
#pragma endregion define

int imGUImain();
void globalInformation(sf::RenderWindow &, RTS&, bool*);
void individualWindow(sf::RenderWindow &, RTS&, bool*);
void showIndividual(Individual&, const char*, int);
void elementWindow(sf::RenderWindow &, RTS&, bool*,char*);
void showElement(Element&, int);
void gameInformation(sf::RenderWindow &, RTS&, bool*);
void showLaw(Law&, int);
void lawWindow(sf::RenderWindow &, RTS&, bool*);
void showDanger(Danger&, int);
void dangerWindow(sf::RenderWindow &, RTS&, bool*, char*);