#include "TextureManager.h"

TextureManager::TextureManager() {

	loadIndividualsSprite();
	loadElementSprite();
	map.loadFromFile("res/sprite/background/png");
}

void TextureManager::loadIndividualsSprite() {
	std::pair<sf::Texture, sf::Texture> textures;

	if (!textures.first.loadFromFile("res/sprite/red.png")) {
		printf("cannot load red.png texture");
	}
	if (!textures.second.loadFromFile("res/sprite/redleader.png")) {
		printf("cannot load redleader.png texture");
	}
	individuals.insert({ "fireelement",textures });

	if (!textures.first.loadFromFile("res/sprite/purple.png")) {
		printf("cannot load purple.png texture");
	}
	if (!textures.second.loadFromFile("res/sprite/purpleleader.png")) {
		printf("cannot load purple.png texture");
	}
	individuals.insert({ "darkelement",textures });

	if (!textures.first.loadFromFile("res/sprite/green.png")) {
		printf("cannot load green.png texture");
	}
	if (!textures.second.loadFromFile("res/sprite/greenleader.png")) {
		printf("cannot load greenleader.png texture");
	}
	individuals.insert({ "plantelement",textures });

	if (!textures.first.loadFromFile("res/sprite/blue.png")) {
		printf("cannot load blue.png texture");
	}
	if (!textures.second.loadFromFile("res/sprite/blueleader.png")) {
		printf("cannot load blueleader.png texture");
	}
	individuals.insert({ "waterelement",textures });
}

void TextureManager::loadElementSprite() {
	sf::Texture texture;

	if (!texture.loadFromFile("res/sprite/waterelement.png")) {
		printf("cannot load waterelement.png texture");
	}
	elements.insert({ "waterelement",texture });

	if (!texture.loadFromFile("res/sprite/fireelement.png")) {
		printf("cannot load fireelement.png texture");
	}
	elements.insert({ "fireelement",texture });

	if (!texture.loadFromFile("res/sprite/darkelement.png")) {
		printf("cannot load darkelement.png texture");
	}
	elements.insert({ "darkelement",texture });

	if (!texture.loadFromFile("res/sprite/plantelement.png")) {
		printf("cannot load plantelement.png texture");
	}
	elements.insert({ "plantelement",texture });


}