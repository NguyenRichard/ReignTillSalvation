#pragma once
#include "Element.h"
#include "ObjectLogic.h"


enum LawType { Attraction, Repulsion, Cancel };

class Law : public ObjectLogic {
private:
	Element* element;
	LawType type;

public:
	Law(Element*, LawType);
	void updateElement();
	bool done();
	Element* getElement() { return element; };
	LawType getType() { return type; };

	void updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>>&) override;

};