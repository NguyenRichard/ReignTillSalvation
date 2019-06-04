#include "pch.h"
#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"
#include "../RTSLibrary/Weak.h"
#include "../RTSLibrary/Map.h"
#include "SFML/Graphics.hpp"
#include "gtest/gtest.h"

TEST(TestMap, makeLeaderSuccess) {
	Map map;
	std::unique_ptr<Individual> individual = std::make_unique<Individual>( std::make_unique<Weak>(), sf::Vector2f(20,300) );
	Weak* weak = dynamic_cast<Weak*>(individual->getState());
	sf::CircleShape* circle_before = weak->getSprite();
	sf::Vector2f coord_before = weak->getCoord();
	ASSERT_TRUE(weak != NULL);

	map.makeLeader(individual);

	EXPECT_TRUE(individual == NULL);
	std::vector<std::unique_ptr<Individual>>& leaders = map.getLeaders();
	Strong* strong = dynamic_cast<Strong*>(leaders[0]->getState());
	sf::CircleShape* circle_after = strong->getSprite();
	sf::Vector2f coord_after = strong->getCoord();
	EXPECT_TRUE(strong != NULL);
	EXPECT_EQ(CIRCLE_S_RADIUS, circle_after->getRadius());
	EXPECT_TRUE(coord_after.x > coord_before.x - 0.1);
	EXPECT_TRUE(coord_after.x < coord_before.x + 0.1);
	EXPECT_TRUE(coord_after.y > coord_before.y - 0.1);
	EXPECT_TRUE(coord_after.y < coord_before.y + 0.1);

}

TEST(TestMap, makeLeaderFailure) {
	Map map;
	std::unique_ptr<Individual> individual = std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(20, 300));

	map.makeLeader(individual);

	EXPECT_TRUE(individual != NULL);

	std::vector<std::unique_ptr<Individual>>& leaders = map.getLeaders();
	EXPECT_EQ(0, leaders.size());

}


