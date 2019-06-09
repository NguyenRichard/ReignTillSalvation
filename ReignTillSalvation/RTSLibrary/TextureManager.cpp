#include "TextureManager.h"

TextureManager::TextureManager() {

	std::pair<sf::Texture, sf::Texture> textures;

	if (!textures.first.loadFromFile("res/sprite/red.png")) {
		printf("cannot load red.png texture");
	}
	if (!textures.second.loadFromFile("res/sprite/redleader.png")) {
		printf("cannot load redleader.png texture");
	}
	individuals.insert({ "Poney",textures });

	if (!textures.first.loadFromFile("res/sprite/purple.png")) {
		printf("cannot load purple.png texture");
	}
	if (!textures.second.loadFromFile("res/sprite/purpleleader.png")) {
		printf("cannot load purple.png texture");
	}
	individuals.insert({ "Miku",textures });

	if (!textures.first.loadFromFile("res/sprite/green.png")) {
		printf("cannot load green.png texture");
	}
	if (!textures.second.loadFromFile("res/sprite/greenleader.png")) {
		printf("cannot load greenleader.png texture");
	}
	individuals.insert({ "Arbre",textures });

	if (!textures.first.loadFromFile("res/sprite/blue.png")) {
		printf("cannot load blue.png texture");
	}
	if (!textures.second.loadFromFile("res/sprite/blueleader.png")) {
		printf("cannot load blueleader.png texture");
	}
	individuals.insert({ "Cactus",textures });
}