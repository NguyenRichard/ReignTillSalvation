#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>

class RTS;

class RTSState{
public:
	RTSState(int width, int height, std::unique_ptr<sf::Music> old_music) :
		width(width), height(height), music(std::move(old_music)) {};
	RTSState(const RTSState& state, std::unique_ptr<sf::Music> old__music) :
		width(state.getWidth()), height(state.getHeight()), music(std::move(old__music)) {};
	virtual ~RTSState() = default;
	virtual void processInput(RTS*,sf::RenderWindow&, sf::Event&) = 0;
	virtual void render(sf::RenderWindow&) = 0;
	virtual void update(RTS* rts) {};
	virtual void init() = 0;
	int getHeight() const { return height; };
	int getWidth() const { return width; };
	std::unique_ptr<sf::Music>& getMusic() { return music; };
	virtual void changeState(RTS*) = 0;
	const std::string MAIN_MUSIC_PATH = "../ReignTillSalvation/res/musics/main_music.flac";
protected:
	int height;
	int width;
	std::unique_ptr<sf::Music> music;
};