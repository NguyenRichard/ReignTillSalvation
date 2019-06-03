#include "ViewManager.h"


ViewManager::ViewManager(sf::RenderWindow& window) :
	view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
{
	view.setViewport(sf::FloatRect(0.0, 0.0, 1.0f, 1.0f));
	window.setView(view);
};


void ViewManager::set_View(sf::RenderWindow& window) {
	float new_width_window = window.getSize().x;
	float new_height_window = window.getSize().y;
	float width_view = view.getSize().x;
	float height_view = view.getSize().y;

	float ratio_change = (new_width_window / new_height_window) / (width_view / height_view);

	if (ratio_change > 1) {
		//if higher than one, it means the window width has increased more than the height.
		//so we reduce it to match the ratio.
		//for the offset on x, the ratio is half the ratio of the part not covered by our view.
		//(since the view width is shorter than the window width)
		view.setViewport(sf::FloatRect((1-1/ratio_change)/2,0,1/ratio_change,1.0f));
	}
	else {
		view.setViewport(sf::FloatRect(0,(1-ratio_change)/2, 1.0f, ratio_change));
	}
	window.setView(view);
}