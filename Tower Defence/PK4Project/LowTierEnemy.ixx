#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

export module LowTierEnemy;

import Enemy;
import Spawner;

export class lowTierEnemy : public enemy{
public:
	friend class wave;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->enemyShape, states);
	}

	lowTierEnemy(std::vector<spawner> spawners, float soundVolume) {
		this->attackDamage = 1;
		this->attackSpeed = 2;
		this->attackRange = 0.5;
		this->health = 10;
		this->defense = 1;
		this->hitPoints = health * defense;
		this->speed = 20;
		this->scorePoints = 1;

		this->enemyShape.setPointCount(10);
		this->enemyShape.setRadius(10);
		this->enemyShape.setFillColor(sf::Color(153, 255, 51));
		this->enemyShape.setOutlineColor(sf::Color::White);
		this->enemyShape.setOutlineThickness(2);
		this->enemyShape.setOrigin(10, 10);


		this->velocity = sf::Vector2f(-this->getSpeed(), 0);
		this->stopVelocity = sf::Vector2f(0, 0);

		int i;
		i = (rand() % spawners.size());
		this->setSlotNumber(i);


		this->enemyShape.setPosition(spawners[this->getSlotNumber()].getXPosition(), spawners[this->getSlotNumber()].getYPosition());
	}
};