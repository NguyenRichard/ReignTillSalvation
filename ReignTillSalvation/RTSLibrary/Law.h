#pragma once
#include "Element.h"
#include "ObjectLogic.h"


enum LawType { Attraction, Repulsion, Cancel };

class Law : public ObjectLogic {
private:
	Element* element;
	LawType type;
	sf::RectangleShape fillBar;
	sf::RectangleShape bar;

public:
	Law(Element*, LawType);
	void updateElement();
	bool done();
	Element* getElement() { return element; };
	LawType getType() { return type; };
	void render(sf::RenderWindow&);
	void updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>> drawables) override;

};