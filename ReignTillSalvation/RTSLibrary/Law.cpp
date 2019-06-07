#include "Law.h"
#include "Value.h"

Law::Law(Element* element, LawType type) : element(element), type(type) {}

void Law::updateElement() {

	switch (type) {
	case attraction:
		if (element->getPower() < MAX_POWER) {
			element->changePower(MAX_POWER / LAW_PROPORTION);
		}
		break;
	case repulsion:
		if (element->getPower() > -MAX_POWER) {
			element->changePower(-MAX_POWER / LAW_PROPORTION);
		}
		break;
	case cancel:
		if (element->getPower() > 2*MAX_POWER/LAW_PROPORTION) {
			element->changePower(-MAX_POWER / LAW_PROPORTION);
		}
		else if (element->getPower() < -2 * MAX_POWER / LAW_PROPORTION) {
			element->changePower(MAX_POWER / LAW_PROPORTION);
		}
		break;
	}


}

bool Law::done() {
	return (element->getPower() < 2 * MAX_POWER / LAW_PROPORTION) && (element->getPower() > -2 * MAX_POWER / LAW_PROPORTION);
}