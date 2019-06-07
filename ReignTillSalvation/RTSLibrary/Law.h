#pragma once
#include "Element.h"


enum LawType { attraction, repulsion, cancel };

class Law {
private:
	Element* element;
	LawType type;
	

public:
	Law(Element*, LawType);
	void updateElement();

};