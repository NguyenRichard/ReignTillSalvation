#include "myImGUI.h"


int imGUImain(){

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ReignTillSalvation");
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
		x / 7, window.getSize().y / 5));
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
	Game* game = static_cast<Game*>(rts.getState());
	if (dynamic_cast<Game*>(rts.getState())) {
		ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
			x / 4, window.getSize().y / 5));
		ImGui::Begin("List of individuals");
		ImGui::SetWindowFontScale(window.getSize().y / 600);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
		ImGui::Columns(2);
		ImGui::Separator();
		std::vector<std::unique_ptr<Individual>>& leaders = game->getMap()->getLeaders();
		int i = 1;
		for (auto & leader : leaders) {
			showIndividual(*leader, "Leader", i);
			i++;
		}
		ImGui::Columns(1);
		ImGui::Separator();
		ImGui::PopStyleVar();
		if (ImGui::Button("Add individuals")) {
			while (!(sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) {
					ImGui::End();
					return;
				}
			}
			sf::Vector2i mousePixelPosition = sf::Mouse::getPosition(window);
			sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePixelPosition);
			if (0 < mouseWorldPosition.x && mouseWorldPosition.x < window.getSize().x
				&& 0 < mouseWorldPosition.y && mouseWorldPosition.y < window.getSize().y) {
				game->getMap()->createIndividual(mouseWorldPosition);
			}
		}
		ImGui::End();
	}

}

void showIndividual(Individual& individual, const char* prefix, int uid)
{
	ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
	ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
	bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
	ImGui::NextColumn();
	ImGui::AlignTextToFramePadding();
	ImGui::NextColumn();
	if (node_open)
	{
		if (dynamic_cast<Strong*>(individual.getState())) {
			Strong* strong = dynamic_cast<Strong*>(individual.getState());
			std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinate();
			int i = 1;
			for (auto& subordinate : subordinates)
			{
				ImGui::PushID(i); // Use field index as identifier.
				showIndividual(*subordinate, "Subordinate", 424242);
				i++;
				ImGui::PopID();
			}
		}
		float* information[2];
		sf::Vector2f& coord = individual.getCoord();
		information[0] = &coord.x;
		information[1] = &coord.y;
		for (int i = 0; i < 2; i++) {
			ImGui::PushID(i);
			// Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
			ImGui::AlignTextToFramePadding();
			ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Field_%d", i);
			ImGui::NextColumn();
			ImGui::SetNextItemWidth(-1);

			ImGui::InputFloat("x: ", information[i], 1.0f);
			ImGui::NextColumn();
			ImGui::PopID();
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
}