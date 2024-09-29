#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <iostream>
#include <vector>


export module TankAlly;

import Ally;
import Enemy;
import Missile;

export class tankAlly : public ally {
	sf::CircleShape tankAllyShape;
public:
	static const int resourceCost;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->tankAllyShape, states);
	}

	tankAlly() = default;

	tankAlly(float soundVolume) {
		this->attackDamage = 1;
		this->attackSpeed = 1;
		this->attackRange = 1;
		this->health = 72;	//ToDo
		//this->resourceCost = 50;

		this->tankAllyShape.setPointCount(4);
		this->tankAllyShape.setRadius(15);
		this->tankAllyShape.setFillColor(sf::Color::Green);
		this->tankAllyShape.setOutlineColor(sf::Color::White);
		this->tankAllyShape.setOutlineThickness(2);
		this->tankAllyShape.setOrigin(15, 15);

		this->setSoundVolume(soundVolume);

	}

	void attack(float effectiveAttackRange, std::vector<missile*>& missiles, std::vector<enemy*>& enemies, resource& resources) {
		
	}

	void setPosition(int x, int y) {
		this->tankAllyShape.setPosition(x, y);
	}

	int getXPosition() {
		return this->tankAllyShape.getPosition().x;
	}

	int getYPosition() {
		return this->tankAllyShape.getPosition().y;
	}

	sf::FloatRect getGlobalBounds() const {
		return this->tankAllyShape.getGlobalBounds();
	}
};