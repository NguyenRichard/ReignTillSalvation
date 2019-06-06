#include "pch.h"
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


TEST(TestMap, onlyStrongs) {
	Map map;
	map.createIndividual(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2 + GROUP_LEAD_RANGE));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2 - GROUP_LEAD_RANGE));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 - GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2 + GROUP_LEAD_RANGE));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 - GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2 - GROUP_LEAD_RANGE));
	map.updateGroup();
	EXPECT_EQ(5, map.getLeaders().size());
	for (const std::unique_ptr<Individual> &leader : map.getLeaders())
		EXPECT_EQ(0, dynamic_cast<Strong*>(leader->getState())->getSubordinates().size());
}

TEST(TestMap, SimpleGroup) {
	Map map;
	map.createIndividual(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + GROUP_LEAD_RANGE / 2, WINDOW_HEIGHT / 2 + GROUP_LEAD_RANGE / 2));
	// ^ in the first individual's range
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + GROUP_LEAD_RANGE / 2, WINDOW_HEIGHT / 2 - GROUP_LEAD_RANGE / 2));
	// ^ in the first individual's range
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 - GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2 + GROUP_LEAD_RANGE));
	// ^ independent
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 - GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2 - GROUP_LEAD_RANGE));
	// ^ independent
	map.findStrongerLeader(map.getLeaders()[1], 1);
	map.updateGroup();
	EXPECT_EQ(3, map.getLeaders().size());

	std::vector<std::unique_ptr<Individual>>& leaders = map.getLeaders();
	EXPECT_EQ(2, dynamic_cast<Strong*>(leaders[0]->getState())->getSubordinates().size());
	EXPECT_EQ(0, dynamic_cast<Strong*>(leaders[1]->getState())->getSubordinates().size());
	EXPECT_EQ(0, dynamic_cast<Strong*>(leaders[2]->getState())->getSubordinates().size());

	sf::Vector2f &leader_coord = leaders[0]->getCoord();
	for (std::unique_ptr<Individual> &sub :
			dynamic_cast<Strong*>(leaders[0]->getState())->getSubordinates()) {
		EXPECT_TRUE(sub->distanceToPoint(leader_coord) < GROUP_LEAD_RANGE);
	}
}

TEST(TestMap, ComplexGroup) {
	Map map;
	map.createIndividual(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + (9 / 10) * GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2));
	// ^ in the first individual's range
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + (9 / 10) * GROUP_LEAD_RANGE / 2 + GROUP_SUB_RANGE / 2, WINDOW_HEIGHT / 2));
	// ^ in the second individual's range
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + (9 / 10) * GROUP_LEAD_RANGE + GROUP_SUB_RANGE, WINDOW_HEIGHT / 2));
	// ^ in the third individual's range
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 - GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2 - GROUP_LEAD_RANGE));
	// ^ independent

	map.findStrongerLeader(map.getLeaders()[1], 1);
	map.updateGroup();
	EXPECT_EQ(2, map.getLeaders().size());

	std::vector<std::unique_ptr<Individual>>& leaders = map.getLeaders();
	EXPECT_EQ(3, dynamic_cast<Strong*>(leaders[0]->getState())->getSubordinates().size());
	EXPECT_EQ(0, dynamic_cast<Strong*>(leaders[1]->getState())->getSubordinates().size());
}

TEST(TestMap, LeaderMove) {
	Map map;
	map.createIndividual(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + GROUP_LEAD_RANGE / 2, WINDOW_HEIGHT / 2));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 + GROUP_LEAD_RANGE / 2, WINDOW_HEIGHT / 2));
	map.updateGroup();
	// now only one leader with two subordinates

	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2  - (9 / 10) * GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 - (9 / 10) * GROUP_LEAD_RANGE - GROUP_SUB_RANGE / 2, WINDOW_HEIGHT / 2));
	map.findStrongerLeader(map.getLeaders()[2], 2);

	map.updateGroup();

	EXPECT_EQ(1, map.getLeaders().size());

	std::vector<std::unique_ptr<Individual>>& leaders = map.getLeaders();
	EXPECT_EQ(4, dynamic_cast<Strong*>(leaders[0]->getState())->getSubordinates().size());
}