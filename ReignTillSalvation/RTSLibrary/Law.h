#pragma once
#include "Element.h"


enum LawType { Attraction, Repulsion, Cancel };

class Law {
private:
	Element* element;
	LawType type;
	

public:
	Law(Element*, LawType);
	void updateElement();
	bool done();
	Element* getElement() { return element; };
	LawType getType() { return type; };

};