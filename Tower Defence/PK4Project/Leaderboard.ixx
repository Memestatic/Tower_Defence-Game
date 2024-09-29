#include <vector>
#include <ranges>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

export module Leaderboard;

import Player;
import TextureManager;

export class leaderboard {
	std::vector<player> players;
	int currentPage;
	static inline const int playersPerPage = 10;
public:
	leaderboard() : currentPage(0) {
		this->updatePlayres();
	}

	void updatePlayres() {
		this->players = player::getAllPlayers();
		this->sortPlayers();
	}

	void display() {
		sf::RenderWindow window(sf::VideoMode(800, 600), "Leaderboard");
		sf::Font font;
		font.loadFromFile("arial.ttf");
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Black);

		sf::RectangleShape nextPageButton(sf::Vector2f(100, 50));
		nextPageButton.setPosition(700, 550);
		nextPageButton.setFillColor(sf::Color::Green);

		sf::RectangleShape prevPageButton(sf::Vector2f(100, 50));
		prevPageButton.setPosition(0, 550);
		prevPageButton.setFillColor(sf::Color::Red);


        sf::Sprite leftArrowSprite;
        leftArrowSprite.setTexture(*TextureManager::getTexture("leftArrow"));
        sf::Vector2u leftArrowSize = leftArrowSprite.getTexture()->getSize();
        float leftArrowScale = 50.0f / leftArrowSize.y;
        leftArrowSprite.setScale(leftArrowScale, leftArrowScale);
        leftArrowSprite.setPosition(20, 550);

        sf::Sprite rightArrowSprite;
        rightArrowSprite.setTexture(*TextureManager::getTexture("rightArrow"));
        sf::Vector2u rightArrowSize = rightArrowSprite.getTexture()->getSize();
        float rightArrowScale = 50.0f / rightArrowSize.y;
        rightArrowSprite.setScale(rightArrowScale, rightArrowScale);
        rightArrowSprite.setPosition(715, 550);

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (nextPageButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
							//std::cout << "Next page\n";
							nextPage();
						}
						if (prevPageButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
							//std::cout << "Previous page\n";
							previousPage();
						}
					}
				}
			}

			window.clear(sf::Color(167, 167, 190));
			text.setPosition(10, 10);
			text.setString("Name");
			window.draw(text);
			text.setPosition(300, 10);
			text.setString("Completed Levels");
			window.draw(text);
			text.setPosition(600, 10);
			text.setString("Score - Survival");
			window.draw(text);
			text.setPosition(10, 40); // resetujemy pozycjê tekstu na pocz¹tku ka¿dej strony
			for (int i = currentPage * playersPerPage; i < (currentPage + 1) * playersPerPage && i < players.size(); ++i) {
				text.setPosition(10, 40 + (i % playersPerPage) * 30);
				text.setString(players[i].getUserName());
				window.draw(text);
				text.setPosition(300, 40 + (i % playersPerPage) * 30);
				text.setString(std::to_string(players[i].getLevelsCompleted()));
				window.draw(text);
				text.setPosition(600, 40 + (i % playersPerPage) * 30);
				text.setString(std::to_string(players[i].getTotalScore()));
				window.draw(text);
			}
			window.draw(nextPageButton);
			window.draw(prevPageButton);
			window.draw(leftArrowSprite);
			window.draw(rightArrowSprite);
			window.display();
		}
	}

	void nextPage() {
		if ((currentPage + 1) * playersPerPage < players.size()) {
			++currentPage;
		}
	}

	void previousPage() {
		if (currentPage > 0) {
			--currentPage;
		}
	}

	void sortPlayers() {
		std::ranges::sort(this->players, [](player a, player b) {
			return a.getTotalScore() > b.getTotalScore();
		});
	}
};