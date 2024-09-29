#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

export module Enemy;


export class enemy : public sf::Drawable {
	int attackDamage;
	float attackSpeed;
	int attackRange;
	int health;
	float defense;
	float hitPoints;
	float speed;
	int slotNumber;
	int scorePoints;
	sf::Clock attackTimer;

	sf::CircleShape enemyShape;
	sf::Vector2f velocity;
	sf::Vector2f stopVelocity;
public:
	static bool canCountPoints;
	friend class ally;
	friend class lowTierEnemy;
	friend class midTierEnemy;
	friend class highTierEnemy;

	enemy() = default;
	int getAttackDamage() {
		return attackDamage;
	}
	float getAttackSpeed() {
		return attackSpeed;
	}
	int getAttackRange() {
		return attackRange;
	}
	int getHealth() {
		return health;
	}
	float getDefense() {
		return defense;
	}
	int getHitPoints() {
		return hitPoints;
	}
	float getSpeed() {
		return speed;
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
	void setDefense(float defense) {
		this->defense = defense;
	}
	void setHitPoints(int hitPoints) {
		this->hitPoints = hitPoints;
	}
	void setSpeed(float speed) {
		this->speed = speed;
	}
	void takeDamage(int damage) {
		this->hitPoints -= damage;
	}
	bool isDead() {
		return this->hitPoints <= 0;
	}
	void setSlotNumber(int number) {
		this->slotNumber = number;
	}

	int getSlotNumber() {
		return this->slotNumber;
	}

	bool canAttack() {
		sf::Time elapsed = attackTimer.getElapsedTime();
		if (elapsed.asSeconds() >= 0.67) {
			attackTimer.restart();
			return true;
		}
		return false;
	}

	void update(float screenWidth, float dt) {
		this->enemyShape.move(this->velocity.x * dt, this->velocity.y);
	}

	int getXPosition() {
		return this->enemyShape.getPosition().x;
	}

	int getYPosition() {
		return this->enemyShape.getPosition().y;
	}

	void setPosition(int x, int y) {
		this->enemyShape.setPosition(x, y);
	}

	float left() {
		return this->enemyShape.getPosition().x - this->enemyShape.getRadius();
	}

	float right() {
		return this->enemyShape.getPosition().x + this->enemyShape.getRadius();
	}

	float middle() {
		return this->enemyShape.getPosition().x;
	}

	sf::FloatRect getGlobalBounds() {
		return this->enemyShape.getGlobalBounds();
	}

	void setVelocity(sf::Vector2f velocity) {
		this->velocity = velocity;
	}

	sf::Vector2f getVelocity() {
		return this->velocity;
	}

	void stop() {
		this->velocity = this->stopVelocity;
	}

	void run() {
		this->velocity = sf::Vector2f(-this->getSpeed(), 0);
	}

	int getPoints() {
		return this->scorePoints;
	}
};