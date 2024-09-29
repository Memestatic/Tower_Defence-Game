#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <iostream>
#include <vector>


export module SupportAlly;

import Ally;
import Enemy;

export class supportAlly : public ally {
	sf::CircleShape supportAllyShape;
	std::chrono::milliseconds attackCooldown;
	std::chrono::steady_clock::time_point lastProducedTime;
	sf::SoundBuffer buffer;
	sf::Sound resorceProducedSound;

public:
	static const int resourceCost;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->supportAllyShape, states);
	}

	supportAlly() = default;
	supportAlly(float soundVolume) {
		this->attackDamage = 1;
		this->attackCooldown = std::chrono::milliseconds(24000);
		this->attackRange = 1;
		this->health = 6;
		//this->resourceCost = 50;
		this->resorceProducedSound.setVolume(soundVolume);

		this->lastProducedTime = std::chrono::steady_clock::now();

		this->supportAllyShape.setPointCount(3);
		this->supportAllyShape.setRadius(15);
		this->supportAllyShape.setFillColor(sf::Color::Yellow);
		this->supportAllyShape.setOutlineColor(sf::Color::White);
		this->supportAllyShape.setOutlineThickness(2);
		this->supportAllyShape.setOrigin(15, 15);

		this->setSoundVolume(soundVolume);

	}

	void attack(float effectiveAttackRange, std::vector<missile*>& missiles, std::vector<enemy*>& enemies, resource& resources) {
		auto now = std::chrono::steady_clock::now();
		auto timeSinceLastShot = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->lastProducedTime);
		if (timeSinceLastShot > this->attackCooldown) {
			resources += 25;
			this->lastProducedTime = now;
		}
	}

	void setPosition(int x, int y) {
		this->supportAllyShape.setPosition(x, y);
	}

	int getXPosition() {
		return this->supportAllyShape.getPosition().x;
	}

	int getYPosition() {
		return this->supportAllyShape.getPosition().y;
	}

	sf::FloatRect getGlobalBounds() const {
		return this->supportAllyShape.getGlobalBounds();
	}
};