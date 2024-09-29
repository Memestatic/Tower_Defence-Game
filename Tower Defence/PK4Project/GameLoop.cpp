#include "Game.h";
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

const int meleeAlly::resourceCost = 150;
const int rangeAlly::resourceCost = 100;
const int supportAlly::resourceCost = 50;
const int tankAlly::resourceCost = 50;

int rangeAlly::maxEnemyPosition;

sf::SoundBuffer slot::allyPlacedbuffer;
sf::Sound slot::allyPlacedSound;

bool enemy::canCountPoints;

bool wave::levelCompleted;
int wave::enemiesSpawned = 0;
sf::Clock wave::waveSpawnTimer;
bool wave::firstSpawnDone;
bool wave::secondSpawnDone;
bool wave::thirdSpawnDone;
bool wave::fourthSpawnDone;
bool wave::fifthSpawnDone;
bool wave::sixthSpawnDone;
bool wave::seventhSpawnDone;
bool wave::eighthSpawnDone;
bool wave::ninthSpawnDone;
bool wave::tenthSpawnDone;

sf::Time wave::spawnCooldown = sf::milliseconds(15000);

sf::Clock gameClock;

void game::gameLoop(int x, int y) {
    wave::waveSpawnTimer.restart();
    game::generationTimer.restart();
    wave::levelCompleted = false;

    //score
    sf::RectangleShape currentScoreBox;
    sf::Text currentScoreText;

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // handle font loading error
    }

    currentScoreBox.setSize(sf::Vector2f(100, 50));
    currentScoreBox.setFillColor(sf::Color::White);
    currentScoreBox.setOutlineColor(sf::Color::Black);
    currentScoreBox.setOutlineThickness(2.0f);
    currentScoreBox.setPosition(game::gameWindowSize.first - 120, 20);

    currentScoreText.setFont(font);
    currentScoreText.setCharacterSize(24);
    currentScoreText.setFillColor(sf::Color::Black);
    currentScoreText.setPosition(game::gameWindowSize.first + 10 - 120, 20 + 10);


    missile::buffer.loadFromFile("sounds/missileDestroyed.mp3");

    RenderWindow window(VideoMode(x, y), "Game", sf::Style::Close);

    std::vector<allyCard> allyCards;
    std::vector<std::vector<slot>> slots;
    std::vector<spawner> spawners;
    std::vector<missile*> missiles;
    std::vector<enemy*> enemies;
    
    game::createCards(allyCards);

    for (auto& i : allyCards) {
        i.sprite.setTexture(*TextureManager::getTexture(i.getType()));
    }

    int rowsAmount;
    int startResources;

    if (game::currentLevel == 1) {
        rowsAmount = 1;
        startResources = 100;
    }
    else if (game::currentLevel == 2 || game::currentLevel == 3) {
        rowsAmount = 3;
        startResources = 50;
    }
    else if (game::currentLevel == 7) {
        rowsAmount = 5;
        startResources = 500;
    }
    else {
        rowsAmount = 5;
        startResources = 50;
    }

    resource resourcesAmount(startResources, gameSoundVolume * 100, 20, 150);


    for (int i = 0; i < rowsAmount; i++) {
        std::vector<slot> row;
        for (int j = 0; j < 9; j++) {
            slot newSlot(100, 100, 200 + 100 * j, 400 + 100 * i, gameSoundVolume * 100);
            row.push_back(newSlot);
        }
        slots.push_back(row);
    }

    for (int i = 0; i < rowsAmount; i++) {
        slots[i][8].getXPosition();
        spawner newSpawner(50, 50, slots[i][8].getXPosition() + 150, slots[i][8].getYPosition());
        spawners.push_back(newSpawner);
    }

    rangeAlly::maxEnemyPosition = slots[0][8].getXPosition() + (slots[0][8].getShapeBounds().getSize().x);

    RectangleShape house(Vector2f(10.f, 550.f));
    house.setOrigin(house.getSize().x / 2, house.getSize().y / 2);
    house.setPosition(slots[slots.size() / 2][0].getXPosition() - 50, slots[slots.size() / 2][0].getYPosition());
   
    allyCard* selectedCard = nullptr;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                wave::firstSpawnDone = false;
                wave::secondSpawnDone = false;
                wave::thirdSpawnDone = false;
                wave::fourthSpawnDone = false;
                wave::fifthSpawnDone = false;
                wave::sixthSpawnDone = false;
                wave::seventhSpawnDone = false;
                wave::eighthSpawnDone = false;
                wave::ninthSpawnDone = false;
                wave::tenthSpawnDone = false;
                wave::enemiesSpawned = 0;
                window.close();
            } 
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
					if (selectedCard == nullptr) {
                        for (auto& i : allyCards) {
						    if (i.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                                selectedCard = &i;
								//std::cout << "Selected card: " << selectedCard->getType() << "\n";
                                selectedCard->changeScaleToClicked();
                                break;
						    }   
                        }
                    }
                    else {
                        for (auto& row : slots) {
                            for (auto& slot : row) {
                                if (slot.getShapeBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
									if (!slot.isOccupied()) {
                                        if(resourcesAmount >= selectedCard->getAllyCost()){
                                            //std::cout << "Current resources: " << resourcesAmount.getAmount() << "\n";
                                            //std::cout<<"Ally cost: "<<selectedCard->getAllyCost()<<"\n";
									        slot.setAlly(selectedCard->createAlly(gameSoundVolume * 100));
									        //std::cout << "Ally placed on slot\n";
                                            resourcesAmount -= selectedCard->getAllyCost();
                                            //std::cout<<"Resources after purchase: "<<resourcesAmount.getAmount()<<"\n";
                                        }
                                        else {
                                            //std::cout << "Not enough resources\n";
                                        }
                                    }
									else {
										//std::cout << "Slot is occupied\n";
									}
                                    break;
                                }
                            }
                        }
                        selectedCard->changeScaleToNormal();
                        selectedCard = nullptr;
                    }
                }
            }
        }

        window.clear(sf::Color(0xCFCBCA));

        //draw score
        //if can count pints
        if(enemy::canCountPoints){
            currentScoreText.setString(std::to_string(game::currentPlayer.getCurrentScore()));
            window.draw(currentScoreBox);
            window.draw(currentScoreText);
        }


        srand((unsigned)time(0));
        switch (currentLevel)
        {
        case 1:
            enemy::canCountPoints = false;
            wave::createWave1(spawners, enemies, gameSoundVolume);
            break;
        case 2:
            enemy::canCountPoints = false;
            wave::createWave2(spawners, enemies, gameSoundVolume);
			break;
        case 3:
            enemy::canCountPoints = false;
			wave::createWave3(spawners, enemies, gameSoundVolume);
            break;
		case 4:
            enemy::canCountPoints = false;
            wave::createWave4(spawners, enemies, gameSoundVolume);
			break;
        case 5:
            enemy::canCountPoints = false;
            wave::createWave5(spawners, enemies, gameSoundVolume);
			break;
        case 7:
            enemy::canCountPoints = true;
            wave::createSurvivalWave(spawners, enemies, gameSoundVolume);
            break;
        default:
            break;
        }


        //draw slots and allies
        for (auto& i : slots) {
            for (auto& j : i) {
                window.draw(j);
                if (j.isOccupied()) {
                    window.draw(*j.getAlly());
                    if (typeid(*j.getAlly()) == typeid(supportAlly)) {
                        j.getAlly()->attack(j.getEffectiveAllyRange() * j.getAlly()->getAttackRange(), missiles, enemies, resourcesAmount);
                    }
                    else if ((typeid(*j.getAlly()) == typeid(rangeAlly)) || (typeid(*j.getAlly()) == typeid(meleeAlly))) {
                        if (!enemies.empty()) {
                            j.getAlly()->attack(j.getEffectiveAllyRange() * j.getAlly()->getAttackRange(), missiles, enemies, resourcesAmount);
                        }
                    } 
                }
            }
        }

        //colision between allies and enemies
        for(auto& i : slots){
            for (auto& j : i) {
                if (j.isOccupied()) {
                    for (auto& k : enemies) {
                        if(k != nullptr){
                            if (k->getGlobalBounds().intersects(j.getAlly()->getGlobalBounds()) && k->canAttack()) {
                                k->stop();
                                j.getAlly()->takeDamageFromEnemy(k);
                            }
                        }
                    }

                    if (j.getAlly()->isDead()) {
                        j.destroyAllyInSlot();

                    }
                }
            }
        }

        //restoring velocity if not attacking ally
        for (auto& i : slots) {
            for (auto& j : i) {
                if (!j.isOccupied()) {
                    for (auto& k : enemies) {
                        if (k != nullptr) {
                            if (k->getGlobalBounds().intersects(j.getShapeBounds())) {
                                k->run();
                                //k->setVelocity(sf::Vector2f(-0.02, 0));
                            }
                        }
                    }
                }
            }
        }



        //passive income
        game::passiveResourceGeneration(resourcesAmount, gameSoundVolume * 100);

        //missiles colision with enemies
        if (!missiles.empty()) {
            for (int i = 0; i < missiles.size(); i++) {
                if (missiles[i] != nullptr) {
                    for (int j = 0; j < enemies.size(); j++) {
                        if (enemies[j] != nullptr) {
                            if (missiles[i]->getGlobalBounds().intersects(enemies[j]->getGlobalBounds())) {
                                enemies[j]->takeDamage(missiles[i]->getDamage());
                                missiles[i]->playSound();
                                delete missiles[i];
                                missiles[i] = nullptr;
                                missiles.erase(missiles.begin() + i);
                                break;
                            }
                        }
                    }
                }
            }

            //missiles colision with map end
            for (int j = 0; j < missiles.size(); j++) {
                if (missiles[j]->right() > x) {
                    delete missiles[j];
                    missiles[j] = nullptr;
                    //delete missiles[0];
                    missiles.erase(missiles.begin() + j);
                }
            }
        }

        //are enemies dead
        for (int j = 0; j < enemies.size(); j++) {
            if (enemies[j]->isDead()) {
                if(enemy::canCountPoints)
                    currentPlayer+=enemies[j]->getPoints();
                //std::cout<<"Current player points: "<<currentPlayer.getCurrentScore()<<"\n";
                delete enemies[j];
                enemies[j] = nullptr;
                enemies.erase(enemies.begin() + j);
            }
        }

        //enemies colision with house
        if (!enemies.empty()) {
            for (int i = 0; i < enemies.size(); i++) {
                if (enemies[i]->middle() <= house.getPosition().x) {
                    game::deleteAllDynamic(slots, enemies, missiles);
                    if (enemy::canCountPoints) {
                        currentPlayer.overwritePlayerData();
                    }
                    game::endGame();
                    return;
                }
            }
        }

        //drawing spawners
        for (auto& i : spawners) {
            window.draw(i);
        }

        //draw house
        window.draw(house);

        //ensure that the game is running at the same speed on every computer
        //using deltaTime as a multiplier for moving objects' velocity
        sf::Time dt = gameClock.restart();
        float deltaTime = dt.asSeconds();

        //draw and update missiles
        for (auto& i : missiles) {
            if (i != nullptr) {
                window.draw(*i);
                i->update(x, deltaTime);
            }
        }

        //drawing enemies
        for (auto& i : enemies) {
            window.draw(*i);
            i->update(x, deltaTime);
        }

        //drawing cards
        for (auto& i : allyCards) {
            window.draw(i);
        }

        //drawing resources
        window.draw(resourcesAmount);

        //level completition statement
        if (wave::levelCompleted) {
            game::deleteAllDynamic(slots, enemies, missiles);
            wave::levelCompleted = false;

            std::cout << game::currentPlayer.getLevelsCompleted() + 1 << std::endl;
            std::cout << game::currentLevel << std::endl;

            if(game::currentLevel == game::currentPlayer.getLevelsCompleted() + 1){
                game::currentPlayer.completeLevel();
            }
            game::currentPlayer.overwritePlayerData();
            window.close();
            game::levelCompletedScreen();
        }

        window.display();
    }
}

void game::deleteAllDynamic(std::vector<std::vector<slot>>& slots, std::vector<enemy*>& enemies, std::vector<missile*>& missiles) {
	for (auto& row : slots) {
		for(auto& slot : row) {
            slot.destroyAllyInSlot();
		}
	}

	for (auto& i : enemies) {
		delete i;
		i = nullptr;
	}

	for (auto& i : missiles) {
		delete i;
		i = nullptr;
	}
}

void game::endGame() {
    RenderWindow window(VideoMode(800, 600), "Game Over", sf::Style::Close);
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // handle font loading error
    }

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("YOU HAVE LOST");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(250, 250);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(gameOverText);
        window.display();
    }
}

void game::levelCompletedScreen() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Level Completed");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // handle font loading error
    }

    sf::Text levelCompletedText;
    levelCompletedText.setFont(font);
    levelCompletedText.setString("YOU HAVE WON");
    levelCompletedText.setCharacterSize(48);
    levelCompletedText.setFillColor(sf::Color::Green);
    levelCompletedText.setPosition(250, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(levelCompletedText);
        window.display();
    }
}