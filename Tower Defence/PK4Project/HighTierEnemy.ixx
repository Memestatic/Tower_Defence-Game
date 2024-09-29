#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

export module HighTierEnemy;

import Enemy;
import Spawner;

export class highTierEnemy : public enemy {
public:
	friend class wave;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->enemyShape, states);
	}

	highTierEnemy(std::vector<spawner> spawners, float soundVolume) {
		this->attackDamage = 1;
		this->attackSpeed = 2;
		this->attackRange = 0.5;
		this->health = 10;
		this->defense = 6.5;
		this->hitPoints = health * defense;
		this->speed = 15;
		this->scorePoints = 25;

		this->enemyShape.setPointCount(10);
		this->enemyShape.setRadius(10);
		this->enemyShape.setFillColor(sf::Color(204, 0, 0));
		this->enemyShape.setOutlineColor(sf::Color::White);
		this->enemyShape.setOutlineThickness(2);
		this->enemyShape.setOrigin(10, 10);


		this->velocity = sf::Vector2f(-this->getSpeed(), 0);
		this->stopVelocity = sf::Vector2f(0, 0);

		srand((unsigned)time(0));
		int i;
		i = (rand() % spawners.size());
		this->setSlotNumber(i);


		this->enemyShape.setPosition(spawners[this->getSlotNumber()].getXPosition(), spawners[this->getSlotNumber()].getYPosition());
	}
};