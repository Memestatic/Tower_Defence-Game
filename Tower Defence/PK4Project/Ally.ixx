#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ranges>
#include <iostream>

export module Ally;

import Enemy;
import Missile;
import Resources;

export class ally : public sf::Drawable {
	int attackDamage;
	float attackSpeed;
	float attackRange;
	int health;
	sf::SoundBuffer damageTakenbuffer;
	sf::Sound damageTakenSound;
public:
	static int maxEnemyPosition;
	friend class meleeAlly;
	friend class rangeAlly;
	friend class supportAlly;
	friend class tankAlly;
	ally() = default;
	ally(int attackDamage, float attackSpeed, int attackRange, int health) {
		this->attackDamage = attackDamage;
		this->attackSpeed = attackSpeed;
		this->attackRange = attackRange;
		this->health = health;
	}
	int getAttackDamage() {
		return attackDamage;
	}
	float getAttackSpeed() {
		return attackSpeed;
	}
	float getAttackRange() {
		return attackRange;
	}
	int getHealth() {
		return health;
	}
	void setAttackDamage(int attackDamage) {
		this->attackDamage = attackDamage;
	}
	void setAttackSpeed(float attackSpeed) {
		this->attackSpeed = attackSpeed;
	}
	void setAttackRange(int attackRange) {
		this->attackRange = attackRange;
	}
	void setHealth(int health) {
		this->health = health;
	}
	void takeDamageFromEnemy(enemy* enemy) {
		int damage = enemy->getAttackDamage();
		this->damageTakenSound.play();
		this->takeDamage(damage);
	}
	void takeDamage(int damage) {
		//std::cout << "Ally health: " << health << std::endl;
		this->health -= damage;
	}
	bool isDead() {
		return this->health <= 0;
	}
	void setSoundVolume(float volume) {
		if (!this->damageTakenbuffer.loadFromFile("sounds/enemyChomp.mp3")) {
			std::cout << "Error loading sound enemychomp file" << std::endl;
		}
		this->damageTakenSound.setBuffer(this->damageTakenbuffer);
		this->damageTakenSound.setVolume(volume);
	}

	virtual void attack(float effectiveAttackRange, std::vector<missile*>& missiles, std::vector<enemy*>& enemies, resource& resources) = 0;

	bool isWithinRange(enemy* target, float effectiveAttackRange) {
		//std::cout<< static_cast<int>(effectiveAttackRange) << " " << target->getXPosition() - this->getXPosition() << " " << this->getYPosition() << " " << target->getYPosition() << std::endl;
		if(target == nullptr)
		{
			return false;
		}
		return ( (static_cast<int>(effectiveAttackRange) >= (target->getXPosition() - this->getXPosition())) && ((target->getXPosition() - this->getXPosition()) > 0) && (this->getYPosition() == target->getYPosition()));
	}

    enemy* findClosestEnemy(std::vector<enemy*> enemies) {
        enemy* closestEnemy = nullptr;
        std::ranges::sort(enemies, [](enemy* a, enemy* b) {
            return a->getXPosition() < b->getXPosition();
        });

		auto sameYEnemies = enemies | std::views::filter([this](enemy* enemy) {return this->getYPosition() == enemy->getYPosition(); })
									| std::views::filter([this](enemy* enemy) {return this->getXPosition() <= enemy->getXPosition(); });

		if (!sameYEnemies.empty()) {
			closestEnemy = sameYEnemies.front();
		}
        
        return closestEnemy;
    }

	virtual void setPosition(int x, int y) = 0;

	virtual int getXPosition() = 0;
	virtual int getYPosition() = 0;

	virtual sf::FloatRect getGlobalBounds() const = 0;
};