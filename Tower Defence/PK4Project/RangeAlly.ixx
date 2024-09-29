#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <iostream>
#include <vector>


export module RangeAlly;

import Ally;
import Enemy;
import Missile;

sf::SoundBuffer missile::buffer;
sf::Sound missile::missileDestroyedSound;

export class rangeAlly : public ally {
	sf::CircleShape rangeAllyShape;
	std::chrono::milliseconds attackCooldown;
	std::chrono::steady_clock::time_point lastShotTime;
	sf::SoundBuffer buffer;
	sf::Sound gunShotSound;
public:
	static const int resourceCost;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->rangeAllyShape, states);
	}

	rangeAlly() = default;
	rangeAlly(float soundVolume) {
		this->attackDamage = 1;
		this->attackSpeed = 0.666f;
		this->attackRange = 5;
		this->health = 6;
		//this->resourceCost = 100;
		gunShotSound.setVolume(soundVolume);

		this->attackCooldown = std::chrono::milliseconds(static_cast<int>(1000 / this->attackSpeed));
		this->lastShotTime = std::chrono::steady_clock::now() - this->attackCooldown;

		if (!this->buffer.loadFromFile("sounds/gunShot.mp3")) {
			std::cout << "Error loading sound gunShot file" << std::endl;
		}

		this->gunShotSound.setBuffer(this->buffer);

		this->rangeAllyShape.setPointCount(6);
		this->rangeAllyShape.setRadius(15);
		this->rangeAllyShape.setFillColor(sf::Color::Blue);
		this->rangeAllyShape.setOutlineColor(sf::Color::White);
		this->rangeAllyShape.setOutlineThickness(2);
		this->rangeAllyShape.setOrigin(15, 15);

		this->setSoundVolume(soundVolume);

	}

	void attack(float effectiveAttackRange, std::vector<missile*>& missiles, std::vector<enemy*>& enemies, resource& resources) {
		enemy* closestTarget = nullptr;
		auto now = std::chrono::steady_clock::now();
		auto timeSinceLastShot = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->lastShotTime);
		if (timeSinceLastShot > this->attackCooldown) {
			//std::cout << "timeSinceLastShot: " << timeSinceLastShot << std::endl;
			//std::cout << "cooldown: " << this->attackCooldown << std::endl;
			if (!enemies.empty()) {
				closestTarget = this->findClosestEnemy(enemies);
				if (this->isWithinRange(closestTarget, effectiveAttackRange)) {
					if(closestTarget->getXPosition() <= rangeAlly::maxEnemyPosition){
						//std::cout<<"Range Ally attacking"<<std::endl;
						missiles.push_back(new missile(this->attackDamage, this->getXPosition(), this->getYPosition(), gunShotSound.getVolume()));
						this->gunShotSound.play();
						//this->lastShotTime = now;
					}
				}
			}
			else{
				//testing
				missiles.push_back(new missile(this->attackDamage, this->getXPosition(), this->getYPosition(), gunShotSound.getVolume()));
				this->lastShotTime = now;
			}
			this->lastShotTime = now;
		}
	}

	void setPosition(int x, int y) {
		this->rangeAllyShape.setPosition(x, y);
	}

	int getXPosition() {
		return this->rangeAllyShape.getPosition().x;
	}

	int getYPosition() {
		return this->rangeAllyShape.getPosition().y;
	}

	sf::FloatRect getGlobalBounds() const {
		return this->rangeAllyShape.getGlobalBounds();
	}
};