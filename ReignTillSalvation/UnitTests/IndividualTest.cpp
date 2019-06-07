#include "pch.h"
#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"
#include "../RTSLibrary/Weak.h"
#include "SFML/Graphics.hpp"
#include "gtest/gtest.h"


TEST(TestIndividual_ChangeState, WeaktoStrong) {
	std::unique_ptr<Individual> individual = std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(20, 300));
	Weak* weak = dynamic_cast<Weak*>(individual->getState());
	sf::CircleShape circle_before = *(weak->getSprite());
	sf::Vector2f coord_before = weak->getCoord();
	ASSERT_TRUE(weak != NULL);

	individual->changeState(weak->changeState());
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

TEST(TestIndividual_ChangeState, StrongtoWeak) {
	std::unique_ptr<Individual> individual = std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(20, 300));
	std::unique_ptr<Individual> new_leader = std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(40, 300));
	Strong* strong = dynamic_cast<Strong*>(individual->getState());
	sf::CircleShape circle_before = *(strong->getSprite());
	sf::Vector2f coord_before = strong->getCoord();
	ASSERT_TRUE(strong != NULL);

	individual->changeState(strong->changeState(new_leader.get()));
	Weak* weak = dynamic_cast<Weak*>(individual->getState());
	sf::CircleShape circle_after = *(weak->getSprite());
	sf::Vector2f coord_after = weak->getCoord();

	EXPECT_TRUE(strong != NULL);
	EXPECT_EQ(CIRCLE_W_RADIUS, circle_after.getRadius());
	EXPECT_TRUE(coord_after.x > coord_before.x - 0.1);
	EXPECT_TRUE(coord_after.x < coord_before.x + 0.1);
	EXPECT_TRUE(coord_after.y > coord_before.y - 0.1);
	EXPECT_TRUE(coord_after.y < coord_before.y + 0.1);
	EXPECT_EQ(new_leader.get(), weak->getLeader());

}

TEST(TestIndividual_findSubPosition, Success) {

	Individual master{ std::make_unique<Strong>(), sf::Vector2f(1000,1000) };
	Strong* strong = static_cast<Strong*>(master.getState());
	std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinates();
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(980, 970)))); //dist 36
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(950, 1000))));//dist 50
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1059))));//dist 59
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(940, 1020))));//dist 63 

	Individual individual1{ std::make_unique<Strong>(), sf::Vector2f(1000,971) }; //dist 29
	Individual individual2{ std::make_unique<Strong>(), sf::Vector2f(960,990) }; //dist 41.2
	Individual individual3{ std::make_unique<Weak>(), sf::Vector2f(1030,1045) }; //dist 54
	Individual individual4{ std::make_unique<Weak>(), sf::Vector2f(1000,1070) }; //dist 70


	EXPECT_EQ(0, strong->findSubPosition(*individual1.getState()));
	EXPECT_EQ(1, strong->findSubPosition(*individual2.getState()));
	EXPECT_EQ(2, strong->findSubPosition(*individual3.getState()));
	EXPECT_EQ(4, strong->findSubPosition(*individual4.getState()));


}

TEST(TestIndividual_findSubPosition, Failure) {
	Individual master{ std::make_unique<Strong>(), sf::Vector2f(1000,1000) };
	Strong* strong = static_cast<Strong*>(master.getState());
	std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinates();
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(980, 970)))); //dist 36
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(950, 1000))));//dist 50
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1061))));//dist 61
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(940, 1020))));//dist 63 

	Individual individual2{ std::make_unique<Strong>(), sf::Vector2f(1200,1070) };
	Individual individual1{ std::make_unique<Weak>(), sf::Vector2f(1000,1070) };

	EXPECT_EQ(-1, strong->findSubPosition(*individual1.getState()));
	EXPECT_EQ(-1, strong->findSubPosition(*individual2.getState()));
	//Because individual4 is linked to the group by subordinates[2] but this subordinate is no longer part of the group.
}


TEST(TestIndividual_stillInGroup, TestCase1) {
	std::unique_ptr<Individual> master(std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(1000, 1000)));
	Strong* strong = static_cast<Strong*>(master->getState());
	std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinates();
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(980, 970))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(950, 1000))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1060))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(940, 1020))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1070))));

	EXPECT_TRUE(strong->stillInGroup(0));
	EXPECT_TRUE(strong->stillInGroup(1));
	EXPECT_FALSE(strong->stillInGroup(2));
	EXPECT_TRUE(strong->stillInGroup(3));
	EXPECT_FALSE(strong->stillInGroup(4));

}

TEST(TestIndividual_stillInGroup, TestCase2) {

	std::unique_ptr<Individual> master(std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(1000, 1000)));
	Strong* strong = static_cast<Strong*>(master->getState());
	std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinates();
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1010, 1070))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1020, 1060))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1061))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1040, 1050))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1070))));

	EXPECT_FALSE(strong->stillInGroup(0));
	EXPECT_FALSE(strong->stillInGroup(1));
	EXPECT_FALSE(strong->stillInGroup(2));
	EXPECT_FALSE(strong->stillInGroup(3));
	EXPECT_FALSE(strong->stillInGroup(4));

}

TEST(TestIndividual_MakeSubordinate, WeakTransfer) {

	std::unique_ptr<Individual> master(std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(1000, 1000)));
	Strong* strong = static_cast<Strong*>(master->getState());
	std::vector<std::unique_ptr<Individual>>& subordinates = strong->getSubordinates();
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(980, 970)))); //dist 36
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(950, 1000))));//dist 50
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1059))));//dist 59
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(940, 1020))));//dist 63 
	sf::CircleShape* circle_master = strong->getSprite();
	Weak* weak;
	for (const auto & subordinate : subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
		subordinate->changeColor(circle_master->getFillColor());
		weak->setLeader(master.get());
	}

	std::unique_ptr<Individual> old_master (std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(1030,1030)));
	Strong* strong2 = static_cast<Strong*>(old_master->getState());
	std::vector<std::unique_ptr<Individual>>& old_subordinates = strong2->getSubordinates();
	old_subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 971))));  //dist 29
	old_subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(960, 990))));//dist 41.2
	old_subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1030, 1045))));//dist 54
	old_subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1070)))); //dist 70 
	sf::CircleShape* circle_old_master = strong2->getSprite();
	for (const auto & subordinate : old_subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
		subordinate->changeColor(circle_old_master->getFillColor());
		weak->setLeader(old_master.get());
	}
	
	//Checking initialization.
	ASSERT_EQ(4, subordinates.size());
	for (const auto & subordinate : subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
		ASSERT_EQ(circle_master->getFillColor(), weak->getSprite()->getFillColor());
		ASSERT_EQ(master.get(), weak->getLeader());
	}
	ASSERT_EQ(4, old_subordinates.size());
	for (const auto & subordinate : old_subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
		ASSERT_EQ(circle_old_master->getFillColor(), weak->getSprite()->getFillColor());
		ASSERT_EQ(old_master.get(), weak->getLeader());
	}

	//makeSubordinate.
	for (int i = old_subordinates.size() - 1; i >= 0; i--) {
		weak = static_cast<Weak*>(old_subordinates[i]->getState());
		weak->makeSubordinate(old_subordinates[i].get(), old_subordinates, master, i);
	}
	
	//Checking result.
	EXPECT_EQ(8, subordinates.size());
	EXPECT_EQ(0, old_subordinates.size());

	EXPECT_EQ(8, subordinates.size());
	float distToLeader = 0;
	float nextDistToLeader;
	for (const auto & subordinate : subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
		nextDistToLeader = subordinate->distanceToIndividual(*master);
		EXPECT_TRUE(distToLeader < nextDistToLeader);
		EXPECT_EQ(circle_master->getFillColor(), weak->getSprite()->getFillColor());
		EXPECT_EQ(master.get(), weak->getLeader());
		distToLeader = nextDistToLeader;
	}
}
