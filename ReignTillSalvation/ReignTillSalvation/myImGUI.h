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
#define MS_PER_UPDATE 2
#pragma endregion define

int imGUImain();
void globalInformation(sf::RenderWindow &, RTS&, bool*);
void individualWindow(sf::RenderWindow &, RTS&, bool*);
void showIndividual(Individual&, const char*, int);
void elementWindow(sf::RenderWindow &, RTS&, bool*,char*);
void showElement(Element&, int);
void parseXML(Map &map)