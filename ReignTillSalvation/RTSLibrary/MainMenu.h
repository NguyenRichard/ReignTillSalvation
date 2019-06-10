#pragma once
#include "Menu.h"
#include "RTSState.h"

class MainMenu : public Menu, public RTSState {
public:
	MainMenu(int width, int height);
	MainMenu(const RTSState & state);
	void render(sf::RenderWindow& window) override;
	void init() override;
	void changeState(RTS* rts) override;

private:
	void handleMouseEventClick(RTS*,sf::RenderWindow& window, sf::Event&) override;
	void handleKeyEventAction(RTS*,sf::RenderWindow& window) override;
	void processInput(RTS*,sf::RenderWindow& window, sf::Event&) override;
	std::unique_ptr<RTSState> changeStateToGameRunning();
	sf::Sprite background;
	sf::Texture texture;

};
