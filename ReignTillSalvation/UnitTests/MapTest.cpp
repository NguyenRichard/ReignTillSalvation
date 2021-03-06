#include "pch.h"
#include "../RTSLibrary/Weak.h"
#include "../RTSLibrary/Map.h"
#include "SFML/Graphics.hpp"
#include "gtest/gtest.h"

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
	map.update(std::move(std::make_unique<sftools::Chronometer>()));
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
	map.update(std::move(std::make_unique<sftools::Chronometer>()));
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

	map.update(std::move(std::make_unique<sftools::Chronometer>()));
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
	map.update(std::move(std::make_unique<sftools::Chronometer>()));
	// now only one leader with two subordinates

	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2  - (9 / 10) * GROUP_LEAD_RANGE, WINDOW_HEIGHT / 2));
	map.createIndividual(sf::Vector2f(
		WINDOW_WIDTH / 2 - (9 / 10) * GROUP_LEAD_RANGE - GROUP_SUB_RANGE / 2, WINDOW_HEIGHT / 2));

	map.update(std::move(std::make_unique<sftools::Chronometer>()));

	EXPECT_EQ(1, map.getLeaders().size());

	std::vector<std::unique_ptr<Individual>>& leaders = map.getLeaders();
	EXPECT_EQ(4, dynamic_cast<Strong*>(leaders[0]->getState())->getSubordinates().size());
}
