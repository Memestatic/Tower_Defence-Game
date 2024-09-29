#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

export module Resources;

export class resource : public sf::Drawable {
    int amount;
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;
    sf::SoundBuffer buffer;
    sf::Sound resourceGainedSound;

public:
    resource() = default;
    resource(int amount, float soundVolume, int xPos, int yPos){
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Error loading font file" << std::endl;
        }

        this->amount = amount;

        box.setSize(sf::Vector2f(100, 50));
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2.0f);
        box.setPosition(xPos, yPos);

        text.setString(std::to_string(amount));
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(xPos + 10, yPos + 10);

        if (!buffer.loadFromFile("sounds/resourceGained.mp3")) {
            std::cout << "Error loading sound resources file" << std::endl;
        }
        resourceGainedSound.setBuffer(buffer);
        resourceGainedSound.setVolume(soundVolume);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(box, states);
        target.draw(text, states);
    }

    int getAmount() {
        return amount;
    }

    void setAmount(int amount) {
        this->amount = amount;
        text.setString(std::to_string(amount));
    }

    void addAmount(int amount) {
        this->amount += amount;
        text.setString(std::to_string(this->amount));
    }

    void subtractAmount(int amount) {
        this->amount -= amount;
        text.setString(std::to_string(this->amount));
    }

    void operator+=(int amount) {
        this->amount += amount;
        text.setString(std::to_string(this->amount));
        resourceGainedSound.play();
    }

    void operator-=(int amount) {
        this->amount -= amount;
        text.setString(std::to_string(this->amount));
    }

    int operator>=(int amount) {
        return this->amount >= amount;
    }

    int operator<=(int amount) {
        return this->amount <= amount;
    }
};