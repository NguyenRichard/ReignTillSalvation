// ReignTillSalvation.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "../RTSLibrary/Menu.h"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1500

int main()
{
	/*Individual one{ std::make_unique<Strong>("Roger") };
	one.action();
	one.changeState();
	one.action();*/

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "");
	Menu menu(window.getSize().x, window.getSize().y);
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	// let's use char array as buffer, see next part
	// for instructions on using std::string with ImGui
	char windowTitle[255] = "ImGui + SFML = <3";

	window.setTitle(windowTitle);
	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
			x / 4, window.getSize().y), 0);
		ImGui::Begin("Sample window"); // begin window
		ImGui::SetWindowFontScale(window.getSize().y / 800);

		// Background color edit
		if (ImGui::ColorEdit3("Background color", color)) {
			// this code gets called if color value changes, so
			// the background color is upgraded automatically!
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}

		// Window title text edit
		ImGui::InputText("Window title", windowTitle, 255);

		if (ImGui::Button("Update window title")) {
			// this code gets if user clicks on the button
			// yes, you could have written if(ImGui::InputText(...))
			// but I do this to show how buttons work :)
			window.setTitle(windowTitle);
		}
		ImGui::End(); // end window

		window.clear(bgColor); // fill background with color
		ImGui::SFML::Render(window);
		menu.draw(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

}
