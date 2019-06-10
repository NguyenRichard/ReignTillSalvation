#include "pch.h"
#include "../RTSLibrary/Individual.h"
#include "../RTSLibrary/Strong.h"
#include "../RTSLibrary/Weak.h"
#include "SFML/Graphics.hpp"
#include "gtest/gtest.h"

TEST(TestIndividual_ChangeState, WeaktoStrong) {
	std::pair<sf::Texture, sf::Texture> textures;

	textures.first.loadFromFile("res/sprite/orange.png");
	textures.second.loadFromFile("res/sprite/orangeleader.png");

	std::unique_ptr<Individual> individual = std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(20, 300));
	individual->setTextures(&textures);
	Weak* weak = dynamic_cast<Weak*>(individual->getState());
	sf::Vector2f coord_before = weak->getCoord();
	ASSERT_TRUE(weak != NULL);

	individual->changeState(weak->changeState());
	Strong* strong = dynamic_cast<Strong*>(individual->getState());
	sf::Vector2f coord_after = strong->getCoord();

	EXPECT_TRUE(strong != NULL);
	EXPECT_TRUE(coord_after.x > coord_before.x - 0.1);
	EXPECT_TRUE(coord_after.x < coord_before.x + 0.1);
	EXPECT_TRUE(coord_after.y > coord_before.y - 0.1);
	EXPECT_TRUE(coord_after.y < coord_before.y + 0.1);

}

TEST(TestIndividual_ChangeState, StrongtoWeak) {
	std::pair<sf::Texture, sf::Texture> textures;

	textures.first.loadFromFile("res/sprite/orange.png");
	textures.second.loadFromFile("res/sprite/orangeleader.png");

	std::unique_ptr<Individual> individual = std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(20, 300));
	std::unique_ptr<Individual> new_leader = std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(40, 300));
	individual->setTextures(&textures);
	new_leader->setTextures(&textures);
	Strong* strong = dynamic_cast<Strong*>(individual->getState());
	sf::Vector2f coord_before = strong->getCoord();
	ASSERT_TRUE(strong != NULL);

	individual->changeState(strong->changeState(new_leader.get()));
	Weak* weak = dynamic_cast<Weak*>(individual->getState());
	sf::Vector2f coord_after = weak->getCoord();

	EXPECT_TRUE(strong != NULL);
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
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1001+ GROUP_LEAD_RANGE))));//dist 61
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(910, 1080))));//dist 63 

	Individual individual2{ std::make_unique<Strong>(), sf::Vector2f(1200,1070) };
	Individual individual1{ std::make_unique<Weak>(), sf::Vector2f(1000,1020+ GROUP_LEAD_RANGE) };

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
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1000 + GROUP_LEAD_RANGE))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(940, 1020))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1020 + GROUP_LEAD_RANGE))));

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
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(),
		sf::Vector2f(1000+ (1 / 6)*GROUP_LEAD_RANGE, 1010+ GROUP_LEAD_RANGE))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), 
		sf::Vector2f(1000+(1 / 3)*GROUP_LEAD_RANGE, 1000+ STRONG_SPRITE_SIZE * GROUP_LEAD_RANGE))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), 
		sf::Vector2f(1000, 1001+ GROUP_LEAD_RANGE))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), 
		sf::Vector2f(1000+ GROUP_LEAD_RANGE, 990+ GROUP_LEAD_RANGE))));
	subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), 
		sf::Vector2f(1000, 1010+GROUP_LEAD_RANGE))));

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
	Weak* weak;
	for (const auto & subordinate : subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
		weak->setLeader(master.get());
	}

	std::unique_ptr<Individual> old_master (std::make_unique<Individual>(std::make_unique<Strong>(), sf::Vector2f(1030,1030)));
	Strong* strong2 = static_cast<Strong*>(old_master->getState());
	std::vector<std::unique_ptr<Individual>>& old_subordinates = strong2->getSubordinates();
	old_subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 971))));  //dist 29
	old_subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(960, 990))));//dist 41.2
	old_subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1030, 1045))));//dist 54
	old_subordinates.push_back(std::move(std::make_unique<Individual>(std::make_unique<Weak>(), sf::Vector2f(1000, 1070)))); //dist 70 
	
	for (const auto & subordinate : old_subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
		weak->setLeader(old_master.get());
	}
	
	//Checking initialization.
	ASSERT_EQ(4, subordinates.size());
	for (const auto & subordinate : subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
		ASSERT_EQ(master.get(), weak->getLeader());
	}
	ASSERT_EQ(4, old_subordinates.size());
	for (const auto & subordinate : old_subordinates) {
		weak = static_cast<Weak*>(subordinate->getState());
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
		EXPECT_EQ(master.get(), weak->getLeader());
		distToLeader = nextDistToLeader;
	}
}
