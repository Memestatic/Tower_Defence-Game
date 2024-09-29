#include <SFML/Graphics.hpp>

export module Spawner;

import Enemy;

export class spawner : public sf::Drawable {
	sf::RectangleShape spawnerShape;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->spawnerShape, states);
	}

	spawner(int xWidth, int yHeight) {

		this->spawnerShape.setSize(sf::Vector2f(xWidth, yHeight)); // (x, y)
		this->spawnerShape.setPosition(0, 0);
		this->spawnerShape.setOutlineColor(sf::Color::White);
		this->spawnerShape.setFillColor(sf::Color::Transparent);
		this->spawnerShape.setOutlineThickness(2);
		this->spawnerShape.setOrigin(xWidth / 2, yHeight / 2);
	}

	spawner(int xWidth, int yHeight, int xPos, int yPos) {

		this->spawnerShape.setSize(sf::Vector2f(xWidth, yHeight)); // (x, y)
		this->spawnerShape.setPosition(xPos, yPos);
		this->spawnerShape.setOutlineColor(sf::Color::White);
		this->spawnerShape.setFillColor(sf::Color::Transparent);
		this->spawnerShape.setOutlineThickness(2);
		this->spawnerShape.setOrigin(xWidth / 2, yHeight / 2);
	}

	int getXWidth() {
		return this->spawnerShape.getSize().x;
	}

	int getYHeight() {
		return this->spawnerShape.getSize().y;
	}

	int getXPosition() {
		return this->spawnerShape.getPosition().x;
	}

	int getYPosition() {
		return this->spawnerShape.getPosition().y;
	}
};