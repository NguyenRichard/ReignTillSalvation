#pragma once
#include <random>
#include <SFML\Graphics.hpp>

// return int between 0 and n included
int randomint(int const &n);

sf::Color stringToColor(const std::string&);

float distanceBetween(sf::Vector2f, sf::Vector2f);

float magnitude(sf::Vector2f &vector);