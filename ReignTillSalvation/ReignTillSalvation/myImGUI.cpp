#include "myImGUI.h"

#define MAX_INPUT_NAME 50

int imGUImain(){

	static bool showIndividualInfo = false;
	static bool showGlobalInfo = false;
	static bool showElementInfo = false;
	static bool showGameInfo = false;
	static bool showLawInfo = false;
	static char input_name[MAX_INPUT_NAME] = "Element";
	char elementName[255] = "Element";
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ReignTillSalvation");

	ViewManager view(window);
	
	RTS rts { std::make_unique<MainMenu>(window.getSize().x,window.getSize().y) };
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);

	tmx::Map map;

	map.load("C:/Users/cypri/Desktop/tmxlite/SFMLExample/assets/demo.tmx");

	MapLayer layerZero(map, 0);
	MapLayer layerOne(map, 1);
	MapLayer layerTwo(map, 2);

	sf::Clock globalClock;

	sf::Clock deltaClock;

	float offset;
	sf::Time time = sf::Time::Time();
	while (window.isOpen()) {
		offset = time.asSeconds();

		sf::Event event;

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			rts.processInput(window);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::Resized) {
				view.set_View(window);
			}

		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
			x / 3, window.getSize().y / 5));
		ImGui::Begin("Main Menu"); // begin window
		ImGui::SetWindowFontScale(window.getSize().y / 450);
		if (ImGui::Button("Show Global Info")) {
			// this code gets if user clicks on the button
			// yes, you could have written if(ImGui::InputText(...))
			// but I do this to show how buttons work :)
			showGlobalInfo = true;
		}
		if (dynamic_cast<Game*>(rts.getState())) {
			if (ImGui::Button("Show Game Info")) {
				showGameInfo = true;
			}
			if (ImGui::Button("Show Individuals Info")) {
				showIndividualInfo = true;
			}
			if (ImGui::Button("Show Element Info")) {
				showElementInfo = true;
			}
			if (ImGui::Button("Show Law Info")) {
				showLawInfo = true;
			}
		}
		else {
			showIndividualInfo = false;
			showElementInfo = false;
			showGameInfo = false;
			showLawInfo = false;
		}

		ImGui::End(); // end window

		window.clear(sf::Color::Black);
		window.draw(layerZero);
		window.draw(layerOne);
		window.draw(layerTwo);

		rts.update();
		rts.render(window);

	//	ImGui::ShowTestWindow(); //Demo to see ImGui functionalities
		if (showGameInfo) gameInformation(window, rts, &showGameInfo);
		if(showIndividualInfo) individualWindow(window, rts, &showIndividualInfo);
		if (showElementInfo) elementWindow(window, rts, &showElementInfo, input_name);
		if (showLawInfo) lawWindow(window, rts,&showLawInfo);
		if (showGlobalInfo) globalInformation(window, rts, &showGlobalInfo);


		sf::Time duration = globalClock.getElapsedTime();
		layerZero.update(duration);

		ImGui::SFML::Render(window);
		window.display();
		offset = time.asSeconds() - offset;
		Sleep(MS_PER_UPDATE - 1000 * offset);
	}

	ImGui::SFML::Shutdown();

	return EXIT_SUCCESS;

}

void globalInformation(sf::RenderWindow & window, RTS& rts, bool* p_open) {


	ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
		x / 7, window.getSize().y / 5));
	if (!ImGui::Begin("Global Info", p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::SetWindowFontScale(window.getSize().y / 450);

	ImGui::Text("Mouse position:");
	sf::Vector2i mousePixelPosition = sf::Mouse::getPosition(window);
	sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePixelPosition);
	std::string string = "x: " + std::to_string(mouseWorldPosition.x);
	ImGui::Text(string.c_str());
	string = "y: " + std::to_string(mouseWorldPosition.y);
	ImGui::Text(string.c_str());

	if (ImGui::Button("Change State")) {
		// this code gets if user clicks on the button
		// yes, you could have written if(ImGui::InputText(...))
		// but I do this to show how buttons work :)
		{
			rts.changeState();
		}
	}
	ImGui::End(); // end window
}

void individualWindow(sf::RenderWindow & window, RTS& rts, bool* p_open) {
	Game* game = static_cast<Game*>(rts.getState());
	ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
		x / 4, window.getSize().y / 5));
	if (!ImGui::Begin("Individuals Info", p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::SetWindowFontScale(window.getSize().y / 550);
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
		sf::Vector2f& coord = individual.getCoord();
		ImGui::PushID(1);
		// Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
		ImGui::AlignTextToFramePadding();
		ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Coordinate");

		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		ImGui::InputFloat("x: ", &coord.x, 1.0f);
		ImGui::SetNextItemWidth(-1);
		ImGui::InputFloat("y: ", &coord.y, 1.0f);
		ImGui::NextColumn();
		ImGui::PopID();

		if (dynamic_cast<Strong*>(individual.getState())) {
			Strong* strong = dynamic_cast<Strong*>(individual.getState());
			std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinates();
			int i = 1;
			for (auto& subordinate : subordinates)
			{
				ImGui::PushID(i); // Use field index as identifier.
				showIndividual(*subordinate, "Subordinate", i);
				i++;
				ImGui::PopID();
			}
		}
		else {
			Weak* weak = dynamic_cast<Weak*>(individual.getState());
			ImGui::PushID(1);
			ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "DistanceToLead");
			ImGui::NextColumn();
			ImGui::SetNextItemWidth(-1);
			std::string string = "d: " + std::to_string(weak->distanceToLeader());
			ImGui::Text(string.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}

	
		ImGui::TreePop();
	}
	ImGui::PopID();
}

void elementWindow(sf::RenderWindow & window, RTS& rts, bool* p_open, char* input_name) {
	Game* game = static_cast<Game*>(rts.getState());
	ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
		x / 4, window.getSize().y / 5));
	if (!ImGui::Begin("Element Info", p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::SetWindowFontScale(window.getSize().y / 550);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	ImGui::Columns(2);
	ImGui::Separator();
	std::vector<std::unique_ptr<Element>>& elements = game->getMap()->getElements();
	int i = 1;
	for (auto & element : elements) {
		showElement(*element, i);
		i++;
	}
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::PopStyleVar();
	ImGui::InputText("name", input_name, MAX_INPUT_NAME);
	if (ImGui::Button("Add element")) {
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
			std::string name(input_name);
			game->getMap()->addElementInMap(name, mouseWorldPosition);
		}
	}
	ImGui::End();

}

void showElement(Element& element, int uid)
{
	ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
	ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
	bool node_open = ImGui::TreeNode("Object", "%s", element.getName().c_str());
	ImGui::NextColumn();
	ImGui::AlignTextToFramePadding();
	ImGui::NextColumn();
	if (node_open)
	{
		ImGui::PushID(1);
		ImGui::AlignTextToFramePadding();
		ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Range");
		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		ImGui::InputFloat("r: ", &element.getRangeMutable(), 1.0f);
		ImGui::SetNextItemWidth(-1);
		ImGui::NextColumn();
		ImGui::PopID();

		ImGui::PushID(1);
		ImGui::AlignTextToFramePadding();
		ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Power");
		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		std::string string = "Power: "+ std::to_string(element.getPower());
		ImGui::Text(string.c_str());
		ImGui::SetNextItemWidth(-1);
		ImGui::NextColumn();
		ImGui::PopID();
		int i = 0;

		std::vector<sf::Vector2f> coords = element.getCoords();
		for (auto& coord : coords)
		{
			ImGui::PushID(i);
			// Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
			ImGui::AlignTextToFramePadding();
			ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Coordinate_%d",i);
			ImGui::NextColumn();
			ImGui::SetNextItemWidth(-1);
			ImGui::InputFloat("x: ", &coords[i].x , 1.0f);
			ImGui::SetNextItemWidth(-1);
			ImGui::InputFloat("y: ", &coords[i].y, 1.0f);
			ImGui::NextColumn();
			ImGui::PopID();

			i++;
		}

		ImGui::TreePop();
	}
	ImGui::PopID();
}

void gameInformation(sf::RenderWindow & window, RTS& rts, bool* p_open) {
	Game* game = static_cast<Game*>(rts.getState());
	ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
		x / 5, window.getSize().y / 5));
	if (!ImGui::Begin("Game Info", p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::SetWindowFontScale(window.getSize().y / 600);


	std::string string = "Number of individuals: " + std::to_string(game->getMap()->individualsNumber());
	ImGui::Text(string.c_str());

	if (ImGui::Button("Change State")) {
		{
			game->changeGameState();
		}
	}

	ImGui::End(); // end window
}

void lawWindow(sf::RenderWindow & window, RTS& rts, bool* p_open) {
	Game* game = static_cast<Game*>(rts.getState());
	ImGui::SetNextWindowSize(sf::Vector2f(window.getSize().
		x / 4, window.getSize().y / 5));
	if (!ImGui::Begin("Law Info", p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::SetWindowFontScale(window.getSize().y / 550);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	ImGui::Columns(2);
	ImGui::Separator();
	std::vector<std::unique_ptr<Law>>& laws = game->getMap()->getLaws();
	int i = 1;
	for (auto & law : laws) {
		showLaw(*law, i);
		i++;
	}
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::PopStyleVar();
	ImGui::End();

}


void showLaw(Law& law, int uid)
{
	ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
	ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
	bool node_open = ImGui::TreeNode("Law","%d",uid);
	ImGui::NextColumn();
	ImGui::AlignTextToFramePadding();
	ImGui::NextColumn();
	if (node_open)
	{
		showElement(*law.getElement(), 0);
		LawType type = law.getType();
		std::string string = "Type: ";
		switch (type) {
		case Attraction:
			string = string + "Attraction";
			break;
		case Repulsion:
			string = string + "Repulsion";
			break;
		case Cancel:
			string = string + "Cancel";
		}
		ImGui::Text(string.c_str());


		ImGui::TreePop();
	}
	ImGui::PopID();
}