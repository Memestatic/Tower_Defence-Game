#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

export module Missile;

export class missile : public sf::Drawable {
	int damage;
	sf::CircleShape missileShape;
	const float missileRadius{ 6.0f };
	const float missileVelocity{ 500.0f };
	sf::Vector2f velocity{ missileVelocity, 0.0f };
public:
	static sf::SoundBuffer buffer;
	static sf::Sound missileDestroyedSound;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->missileShape, states);
	}

	~missile() {
	}

	missile(int damage, int xPos, int yPos, float soundVolume) {
		this->damage = damage;

		this->missileShape.setRadius(missileRadius);
		this->missileShape.setFillColor(sf::Color::Magenta);
		this->missileShape.setOutlineColor(sf::Color::White);
		this->missileShape.setOutlineThickness(2);
		this->missileShape.setOrigin(missileRadius, missileRadius);
		this->missileShape.setPosition(xPos, yPos);

		missile::missileDestroyedSound.setBuffer(missile::buffer);
		missile::missileDestroyedSound.setVolume(soundVolume);
	}

    void update(float screenWidth, float dt) {
        this->missileShape.move(this->velocity.x * dt, this->velocity.y);
    }

	float right() {
		return this->missileShape.getPosition().x + this->missileRadius;
	}

	auto getGlobalBounds() {
		return this->missileShape.getGlobalBounds();
	}

	int getDamage() {
		return this->damage;
	}

	void playSound() {
		this->missileDestroyedSound.play();
		//std::cout << "Missile destroyed" << std::endl;
	}
};