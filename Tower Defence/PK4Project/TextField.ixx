#include <SFML/Graphics.hpp>

export module TextField;

//using namespace sf;

export class textField {
    sf::RectangleShape box;
    sf::Text text;
    std::string str;
public:
    textField(unsigned int characterSize, sf::Vector2f size, sf::Vector2f position) {
        box.setSize(size);
        box.setPosition(position);
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(3);

        text.setCharacterSize(characterSize);
        text.setPosition(position);
        text.setFillColor(sf::Color::Black);
    }

    void handleInput(sf::Event event) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b' && !str.empty()) { // handle backspace
                str.pop_back();
            }
            else if (event.text.unicode < 128) { // only ASCII
                str += static_cast<char>(event.text.unicode);
            }
            text.setString(str);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(text);
    }

    std::string getString() {
        return str;
    }

    void setFont(sf::Font& font) {
        text.setFont(font);
    }

    auto getGlobalBounds() {
        return this->box.getGlobalBounds();
    }

    void setOutlineColor(sf::Color color) {
        this->box.setOutlineColor(color);
    }

	std::string getText() {
		return text.getString();
	}
};