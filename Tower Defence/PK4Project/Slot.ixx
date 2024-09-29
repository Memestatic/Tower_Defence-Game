#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

export module Slot;

import Ally;
import Missile;

export class slot : public sf::Drawable {
	ally* allyInSlot;
	float effectiveAllyRange;
	sf::RectangleShape slotShape;
	static sf::SoundBuffer allyPlacedbuffer;
	static sf::Sound allyPlacedSound;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->slotShape, states);
	}

	slot(int xWidth, int yHeight) {

		this->slotShape.setSize(sf::Vector2f(xWidth, yHeight)); // (x, y)
		this->slotShape.setPosition(0, 0);
		this->slotShape.setOutlineColor(sf::Color::Black);
		this->slotShape.setFillColor(sf::Color::Transparent);
		this->slotShape.setOutlineThickness(2);
		this->slotShape.setOrigin(xWidth / 2, yHeight / 2);
	}

	slot(int xWidth, int yHeight, int xPos, int yPos, float volume) {

		this->slotShape.setSize(sf::Vector2f(xWidth, yHeight)); // (x, y)
		this->slotShape.setPosition(xPos, yPos);
		this->slotShape.setOutlineColor(sf::Color::Black);
		this->slotShape.setFillColor(sf::Color::Transparent);
		this->slotShape.setOutlineThickness(2);
		this->slotShape.setOrigin(xWidth / 2, yHeight / 2);

		if (!slot::allyPlacedbuffer.loadFromFile("sounds/allyPlaced.mp3")) {
			std::cout << "Error loading sound file" << std::endl;
		}
		slot::allyPlacedSound.setBuffer(slot::allyPlacedbuffer);
		slot::allyPlacedSound.setVolume(volume);
	}


	slot() = delete;

	~slot() {
		this->allyInSlot = nullptr;
	}

	ally* getAlly() {
		return allyInSlot;
	}
	void setAlly(ally* ally) {
		this->playMusic();

		allyInSlot = ally;
		this->updateEffectiveAllyRange();
	}

	void playMusic() {
		slot::allyPlacedSound.play();
	}

	void destroyAllyInSlot() {
		if (allyInSlot != nullptr) {
			delete allyInSlot; // Delete the ally object to free memory
			allyInSlot = nullptr; // Set the pointer to nullptr
		}
	}

	bool isOccupied() {
		return allyInSlot != nullptr;
	}
	int getXWidth() {
		return this->slotShape.getSize().x;
	}
	int getYHeight() {
		return this->slotShape.getSize().y;
	}
	int getEffectiveAllyRange() {
		return effectiveAllyRange;
	}
	void updateEffectiveAllyRange() {
		this->allyInSlot->setPosition(this->getXPosition(), this->getYPosition());
		this->effectiveAllyRange = allyInSlot->getAttackRange() * this->getXWidth();
	}

	void setPosition(std::pair<int, int> position) {
		this->slotShape.setPosition(position.first, position.second);
	}

	int getXPosition() {
		return this->slotShape.getPosition().x;
	}

	int getYPosition() {
		return this->slotShape.getPosition().y;
	}

	auto getShapeBounds() {
		return this->slotShape.getGlobalBounds();
	}
};