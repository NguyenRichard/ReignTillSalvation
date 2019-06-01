#include "myImGUI.h"


int imGUImain(){

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

		ImGui::ShowTestWindow();
		globalInformation(window, rts);
		individualWindow(window, rts);

		window.clear(bgColor); // fill background with color
		ImGui::SFML::Render(window);
		rts.render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return EXIT_SUCCESS;

}

void globalInformation(sf::RenderWindow & window, RTS& rts) {

	ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
		x / 7, window.getSize().y / 5), 0);
	ImGui::Begin("Global Information"); // begin window
	ImGui::SetWindowFontScale(window.getSize().y / 500);

	ImGui::Text("Mouse position:");
	std::string string = "x: " + std::to_string(sf::Mouse::getPosition(window).x);
	ImGui::Text(string.c_str());
	string = "y: " + std::to_string(sf::Mouse::getPosition(window).y);
	ImGui::Text(string.c_str());

	if (ImGui::Button("Change State")) {
		// this code gets if user clicks on the button
		// yes, you could have written if(ImGui::InputText(...))
		// but I do this to show how buttons work :)
		rts.changeState();
	}
	ImGui::End(); // end window
}

void individualWindow(sf::RenderWindow & window, RTS& rts) {
	ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
		x / 5, window.getSize().y/2), 0);
	//ImGui::SetNextWindowPos(sf::Vector2f(0, window.getSize().y / 5));
	ImGui::Begin("List of individuals");
	ImGui::SetWindowFontScale(window.getSize().y / 500);
	if (dynamic_cast<Game*>(rts.getState())) {
		Game* game = static_cast<Game*>(rts.getState());
		std::vector<std::unique_ptr<Individual>>& leaders = game->getMap()->getLeaders();
		sf::Vector2f coord;
		for (const auto & leader : leaders) {
			coord = leader.get()->getCoord();
			std::string string = "x: " + std::to_string(coord.x);
			ImGui::Text(string.c_str());
			string = "y: " + std::to_string(coord.y);
			ImGui::Text(string.c_str());
		}
		if(ImGui::Button("add")){
			game->getMap()->createIndividual(sf::Vector2f(20, 20));
		}

	}

	ImGui::End();

}