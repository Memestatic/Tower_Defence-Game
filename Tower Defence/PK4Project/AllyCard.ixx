#include <SFML/Graphics.hpp>
#include <iostream>

export module AllyCard;

import Ally;
import RangeAlly;
import MeleeAlly;
import TankAlly;
import SupportAlly;

export class allyCard : public sf::Drawable {
    sf::Texture texture;
    std::string allyType;
public:
    sf::Sprite sprite;

    allyCard(std::string allyType, int x, int  y) {
        this->allyType = allyType;
        this->sprite.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->sprite, states);
    }

    ally* createAlly(float gameSoundVolume) {
        if (allyType == "Range") {
            return new rangeAlly(gameSoundVolume);
        }
        else if (allyType == "Melee") {
            return new meleeAlly(gameSoundVolume);
        }
        else if (allyType == "Tank") {
            return new tankAlly(gameSoundVolume);
        }
        else if (allyType == "Support") {
            return new supportAlly(gameSoundVolume);
        }
        else {
            return nullptr;
        }
    }

    auto getTexture() {
		return this->texture;
	}

    auto getSprite() {
        return this->sprite;
    }

    auto getType() {
		return this->allyType;
	}

    auto getGlobalBounds() {
        return this->sprite.getGlobalBounds();
    }

	int getAllyCost() {
		if (allyType == "Range") {
			return rangeAlly::resourceCost;
		}
		else if (allyType == "Melee") {
			return meleeAlly::resourceCost;
		}
		else if (allyType == "Tank") {
			return tankAlly::resourceCost;
		}
		else if (allyType == "Support") {
			return supportAlly::resourceCost;
		}
	}

    void changeScaleToClicked() {
		this->sprite.setScale(0.8, 0.8);
	}

    void changeScaleToNormal() {
        this->sprite.setScale(1, 1);
    }
};

