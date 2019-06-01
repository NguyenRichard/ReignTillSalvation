#include "pch.h"
#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"
#include "../RTSLibrary/Weak.h"
#include "SFML/Graphics.hpp"


TEST(TestIndividual, TestAddSurbordinates) {

	Individual master{ std::make_unique<Strong>(), sf::Vector2f(20,300) };
	Strong* strong = static_cast<Strong*>(master.getState());
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(200, 300)));
	sf::CircleShape* circle = strong->getSprite();
	EXPECT_EQ(1, strong->getSubordinate().size());
	EXPECT_EQ(CIRCLE_S_COLOR, circle->getFillColor());
	EXPECT_EQ(CIRCLE_S_RADIUS, circle->getRadius());

	std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinate();
	Weak* weak = static_cast<Weak*>(subordinates[0].get()->getState());
	circle = weak->getSprite();
	EXPECT_EQ(CIRCLE_W_COLOR, circle->getFillColor());
	EXPECT_EQ(CIRCLE_W_RADIUS, circle->getRadius());
}