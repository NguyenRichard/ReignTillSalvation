#include "Renderable.h"

void Renderable::render(sf::RenderWindow& window) {
	for (const auto& drawable : drawables) {
		window.draw(*drawable.first);
	}
}

void Renderable::updateAnimation() {
	if (animcount == -1) {
		return;
	}


}