// ReignTillSalvation.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

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

int main()
{
	/*Individual one{ std::make_unique<Strong>("Roger") };
	one.action();
	one.changeState();
	one.action();*/

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "");
	RTS rts { std::make_unique<MainMenu>(window.getSize().x,window.getSize().y) };	
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	// let's use char array as buffer, see next part
	// for instructions on using std::string with ImGui
	char windowTitle[255] = "ImGui + SFML = <3";

	window.setTitle(windowTitle);

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			rts.processInput(window);
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}
		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
			x / 4, window.getSize().y), 0);
		ImGui::Begin("Game State"); // begin window
		ImGui::SetWindowFontScale(window.getSize().y / 500);

		if (ImGui::Button("Change State")) {
			// this code gets if user clicks on the button
			// yes, you could have written if(ImGui::InputText(...))
			// but I do this to show how buttons work :)
			rts.changeState();
		}
		ImGui::End(); // end window

		window.clear(bgColor); // fill background with color
		ImGui::SFML::Render(window);
		rts.render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

}
