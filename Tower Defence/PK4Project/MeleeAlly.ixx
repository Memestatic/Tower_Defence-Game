#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

export module MeleeAlly;

import Ally;
import Enemy;

export class meleeAlly : public ally {
	sf::CircleShape meleeAllyShape;
	std::chrono::milliseconds attackCooldown;
	std::chrono::steady_clock::time_point lastAttackTime;
	sf::SoundBuffer buffer;
	sf::Sound meleeChompSound;
public:
	static const int resourceCost;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->meleeAllyShape, states);
	}

	meleeAlly() = default;

	meleeAlly(float soundVolume) {
		this->attackDamage = 120;
		this->attackRange = 1.5;
		this->health = 6;
		//this->resourceCost = 150;

		this->attackCooldown = std::chrono::seconds(18);
		this->lastAttackTime = std::chrono::steady_clock::now();

		this->meleeAllyShape.setPointCount(5);
		this->meleeAllyShape.setRadius(15);
		this->meleeAllyShape.setFillColor(sf::Color::Red);
		this->meleeAllyShape.setOutlineColor(sf::Color::White);
		this->meleeAllyShape.setOutlineThickness(2);
		this->meleeAllyShape.setOrigin(15, 15);

		if (!this->buffer.loadFromFile("sounds/meleeChomp.mp3")) {
			std::cout << "Error loading sound meleeChomp file" << std::endl;
		}

		this->meleeChompSound.setBuffer(this->buffer);
		this->meleeChompSound.setVolume(soundVolume);

		this->setSoundVolume(soundVolume);
	}

	void attack(float effectiveAttackRange, std::vector<missile*>& missiles, std::vector<enemy*>& enemies, resource& resources) {
		enemy* closestTarget = nullptr;
		auto now = std::chrono::steady_clock::now();
		auto timeSinceLastAttack = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->lastAttackTime);
		if (timeSinceLastAttack > this->attackCooldown) {
			//std::cout << this->attackRange << std::endl;
			//std::cout << "timeSinceLastShot: " << timeSinceLastAttack << std::endl;
			//std::cout << "cooldown: " << this->attackCooldown << std::endl;
			if (!enemies.empty()) {
				//std::cout << "Range Ally attacking" << std::endl;
				closestTarget = this->findClosestEnemy(enemies);
				if (this->isWithinRange(closestTarget, effectiveAttackRange)) {
					//std::cout<<"Range Ally attacking"<<std::endl;
					this->meleeChompSound.play();
					closestTarget->takeDamage(this->attackDamage);
					//std::cout <<"Target health: " << closestTarget->getHitPoints() << std::endl;
				}
			}
			else {
				//testing
				this->lastAttackTime = now;
			}
			this->lastAttackTime = now;
		}
	}

	void setPosition(int x, int y) {
		this->meleeAllyShape.setPosition(x, y);
	}

	int getXPosition() {
		return this->meleeAllyShape.getPosition().x;
	}

	int getYPosition() {
		return this->meleeAllyShape.getPosition().y;
	}

	sf::FloatRect getGlobalBounds() const {
		return this->meleeAllyShape.getGlobalBounds();
	}
};