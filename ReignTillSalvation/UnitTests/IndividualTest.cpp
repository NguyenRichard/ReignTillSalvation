#include "pch.h"
#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"
#include "../RTSLibrary/Weak.h"
#include "SFML/Graphics.hpp"
#include "gtest/gtest.h"


TEST(TestIndividual, TestAddSurbordinates) {

	Individual master{ std::make_unique<Strong>(), sf::Vector2f(20,300) };
	Strong* strong = static_cast<Strong*>(master.getState());
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(200, 300)));
	sf::CircleShape* circle_strong = strong->getSprite();
	EXPECT_EQ(1, strong->getSubordinates().size());
	EXPECT_EQ(CIRCLE_S_RADIUS, circle_strong->getRadius());

	std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinates();
	Weak* weak = static_cast<Weak*>(subordinates[0].get()->getState());
	sf::CircleShape* circle_weak = weak->getSprite();
	circle_weak = weak->getSprite();
	EXPECT_EQ(circle_strong->getFillColor(), circle_weak->getFillColor());
	EXPECT_EQ(CIRCLE_W_RADIUS, circle_weak->getRadius());
}

TEST(TestIndividual, TestInsertSubordinates) {
	Individual master{ std::make_unique<Strong>(), sf::Vector2f(20,300) };
	Strong* strong = static_cast<Strong*>(master.getState());
	strong->insertSubordinate(0,std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(200, 300)));
	strong->insertSubordinate(1,std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(200, 300)));
	strong->insertSubordinate(2,std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(200, 300)));
	strong->insertSubordinate(3,std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(200, 300)));
	strong->insertSubordinate(2, std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(59, 0)));
	std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinates();

	EXPECT_TRUE((subordinates[0]->getCoord().x > 199));
	EXPECT_TRUE((subordinates[0]->getCoord().x < 201));
	EXPECT_TRUE((subordinates[0]->getCoord().y > 299));
	EXPECT_TRUE((subordinates[0]->getCoord().y < 301));

	EXPECT_TRUE((subordinates[1]->getCoord().x > 199));
	EXPECT_TRUE((subordinates[1]->getCoord().x < 201));
	EXPECT_TRUE((subordinates[1]->getCoord().y > 299));
	EXPECT_TRUE((subordinates[1]->getCoord().y < 301));

	EXPECT_TRUE((subordinates[3]->getCoord().x > 199));
	EXPECT_TRUE((subordinates[3]->getCoord().x < 201));
	EXPECT_TRUE((subordinates[3]->getCoord().y > 299));
	EXPECT_TRUE((subordinates[3]->getCoord().y < 301));

	EXPECT_TRUE((subordinates[2]->getCoord().x > 58));
	EXPECT_TRUE((subordinates[2]->getCoord().x < 60));
	EXPECT_TRUE((subordinates[2]->getCoord().y > -1));
	EXPECT_TRUE((subordinates[2]->getCoord().y < 1));
}

TEST(TestIndividual, TestchangeStateWeaktoStrong) {
	std::unique_ptr<Individual> individual = std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(20, 300));
	Weak* weak = dynamic_cast<Weak*>(individual->getState());
	sf::CircleShape circle_before = *(weak->getSprite());
	sf::Vector2f coord_before = weak->getCoord();
	ASSERT_TRUE(weak != NULL);

	individual->changeState();
	Strong* strong = dynamic_cast<Strong*>(individual->getState());
	sf::CircleShape circle_after = *(strong->getSprite());
	sf::Vector2f coord_after = strong->getCoord();

	EXPECT_TRUE(strong != NULL);
	EXPECT_EQ(CIRCLE_S_RADIUS, circle_after.getRadius());
	EXPECT_TRUE(coord_after.x > coord_before.x - 0.1);
	EXPECT_TRUE(coord_after.x < coord_before.x + 0.1);
	EXPECT_TRUE(coord_after.y > coord_before.y - 0.1);
	EXPECT_TRUE(coord_after.y < coord_before.y + 0.1);

}

TEST(TestIndividual, TestchangeStateStrongtoWeak) {
	std::unique_ptr<Individual> individual = std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(20, 300));
	Strong* strong = dynamic_cast<Strong*>(individual->getState());
	sf::CircleShape circle_before = *(strong->getSprite());
	sf::Vector2f coord_before = strong->getCoord();
	ASSERT_TRUE(strong != NULL);

	individual->changeState();
	Weak* weak = dynamic_cast<Weak*>(individual->getState());
	sf::CircleShape circle_after = *(weak->getSprite());
	sf::Vector2f coord_after = weak->getCoord();

	EXPECT_TRUE(strong != NULL);
	EXPECT_EQ(CIRCLE_W_RADIUS, circle_after.getRadius());
	EXPECT_TRUE(coord_after.x > coord_before.x - 0.1);
	EXPECT_TRUE(coord_after.x < coord_before.x + 0.1);
	EXPECT_TRUE(coord_after.y > coord_before.y - 0.1);
	EXPECT_TRUE(coord_after.y < coord_before.y + 0.1);

}

TEST(TestMap, findSubPositionSuccess) {
	Individual master{ std::make_unique<Strong>(), sf::Vector2f(1000,1000) };
	Strong* strong = static_cast<Strong*>(master.getState());
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(980, 970))); //dist 36
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(950, 1000))); //dist 50 
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1059))); //dist 59
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(940, 1020))); //dist 63 

	Individual individual1{ std::make_unique<Strong>(), sf::Vector2f(1000,971) }; //dist 29
	Individual individual2{ std::make_unique<Strong>(), sf::Vector2f(960,990) }; //dist 41.2
	Individual individual3{ std::make_unique<Strong>(), sf::Vector2f(1030,1045) }; //dist 54
	Individual individual4{ std::make_unique<Strong>(), sf::Vector2f(1000,1070) }; //dist 70


	EXPECT_EQ(0, strong->findSubPosition(individual1));
	EXPECT_EQ(1, strong->findSubPosition(individual2));
	EXPECT_EQ(2, strong->findSubPosition(individual3));
	EXPECT_EQ(4, strong->findSubPosition(individual4));


}


TEST(TestMap, findSubPositionFailure) {
	Individual master{ std::make_unique<Strong>(), sf::Vector2f(1000,1000) };
	Strong* strong = static_cast<Strong*>(master.getState());
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(980, 970))); //dist 36
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(950, 1000))); //dist 50 
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1060))); //dist 61
	strong->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(940, 1020))); //dist 63 

	Individual individual2{ std::make_unique<Strong>(), sf::Vector2f(1200,1070) }; 
	Individual individual1{ std::make_unique<Strong>(), sf::Vector2f(1000,1070) };

	EXPECT_EQ(-1, strong->findSubPosition(individual1));
	EXPECT_EQ(-1, strong->findSubPosition(individual2));
	//Because individual4 is linked to the group by subordinates[2] but this subordinate is no longer part of the group.
}

TEST(TestMap, stillInGroup) {
	Individual master1{ std::make_unique<Strong>(), sf::Vector2f(1000,1000) };
	Strong* strong1 = static_cast<Strong*>(master1.getState());
	strong1->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(980, 970)));
	strong1->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(950, 1000)));
	strong1->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1060)));
	strong1->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(940, 1020)));
	strong1->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1070)));

	EXPECT_TRUE(strong1->stillInGroup(0));
	EXPECT_TRUE(strong1->stillInGroup(1));
	EXPECT_FALSE(strong1->stillInGroup(2));
	EXPECT_TRUE(strong1->stillInGroup(3));
	EXPECT_FALSE(strong1->stillInGroup(4));

	Individual master2{ std::make_unique<Strong>(), sf::Vector2f(1000,1000) };
	Strong* strong2 = static_cast<Strong*>(master2.getState());
	strong2->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1010, 1070)));
	strong2->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1020, 1060)));
	strong2->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1060)));
	strong2->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1040, 1050)));
	strong2->addSubordinate(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1070)));

	EXPECT_FALSE(strong2->stillInGroup(0));
	EXPECT_FALSE(strong2->stillInGroup(1));
	EXPECT_FALSE(strong2->stillInGroup(2));
	EXPECT_FALSE(strong2->stillInGroup(3));
	EXPECT_FALSE(strong2->stillInGroup(4));

}