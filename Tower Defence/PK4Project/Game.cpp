#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


using namespace sf;

//game static variables
sf::Clock game::generationTimer;
std::pair<int, int> game::windowSize;
std::pair<int, int> game::gameWindowSize;
player game::currentPlayer;
float game::gameSoundVolume;
bool game::settingsConfigured = false;
int game::currentLevel;

//TextureManager static variables
std::map<std::string, sf::Texture*> TextureManager::textures;
std::vector<std::string> TextureManager::order;


void game::gameMenu(int x, int y) {
    windowSize = std::make_pair(x, y);

    TextureManager::loadTexture("leftArrow", "textures/leftArrow.png");
    TextureManager::loadTexture("rightArrow", "textures/rightArrow.png");

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
    }

    //render menu window
    RenderWindow window(VideoMode(windowSize.first, windowSize.second), "Game menu", sf::Style::Close);
    window.setFramerateLimit(60);

    //create text field for username
    textField usernameField(30, sf::Vector2f(200.f, 50.f), sf::Vector2f(20.f, 200.f));
    usernameField.setFont(font);
    
    //create login buttons
    RectangleShape choosePlayer(Vector2f(360.f, 150));
    choosePlayer.setPosition(10.f, 10.f);
    choosePlayer.setFillColor(Color::White);
    choosePlayer.setOutlineThickness(2.f);
    choosePlayer.setOutlineColor(Color::Black);

    RectangleShape loginRect(Vector2f(150.f, 100.f));
    loginRect.setPosition(20.f, 20.f);
    loginRect.setFillColor(Color::Red);

    Text loginText("Login", font, 30);
    loginText.setPosition(loginRect.getPosition().x + 10.f, loginRect.getPosition().y + 15.f);
    loginText.setFillColor(Color::Black);

    RectangleShape registerRect(Vector2f(150.f, 100.f));
    registerRect.setPosition(200.f, 20.f);
    registerRect.setFillColor(Color::Blue);

    Text registerText("Register", font, 30);
    registerText.setPosition(registerRect.getPosition().x + 10.f, registerRect.getPosition().y + 15.f);
    registerText.setFillColor(Color::Black);

    //create menu buttons
    RectangleShape menuRect(Vector2f(400.f, 500.f));
    menuRect.setPosition((windowSize.first - 400.f) / 2, (windowSize.second - 500.f) / 2);
    menuRect.setFillColor(Color::White);
    menuRect.setOutlineThickness(2.f);
    menuRect.setOutlineColor(Color::Black);

    RectangleShape adventureRect(Vector2f(300.f, 50.f));
    adventureRect.setPosition((windowSize.first - 300.f) / 2, (windowSize.second - 50.f) / 2 - 150.f);
    adventureRect.setFillColor(Color::Blue);

    Text adventureText("Adventure", font, 30);
    adventureText.setPosition(adventureRect.getPosition().x + 70.f, adventureRect.getPosition().y + 8.f);
    adventureText.setFillColor(Color::Black);

    RectangleShape survivalRect(Vector2f(300.f, 50.f));
    survivalRect.setPosition((windowSize.first - 300.f) / 2, (windowSize.second - 50.f) / 2 - 80.f);
    survivalRect.setFillColor(Color::Green);

    Text survivalText("Survival", font, 30);
    survivalText.setPosition(survivalRect.getPosition().x + 80.f, survivalRect.getPosition().y + 8.f);
    survivalText.setFillColor(Color::Black);

    RectangleShape optionsRect(Vector2f(300.f, 50.f));
    optionsRect.setPosition((windowSize.first - 300.f) / 2, (windowSize.second - 50.f) / 2 - 10.f);
    optionsRect.setFillColor(Color::Yellow);

    Text optionsText("Options", font, 30);
    optionsText.setPosition(optionsRect.getPosition().x + 80.f, optionsRect.getPosition().y + 8.f);
    optionsText.setFillColor(Color::Black);

    RectangleShape helpRect(Vector2f(300.f, 50.f));
    helpRect.setPosition((windowSize.first - 300.f) / 2, (windowSize.second - 50.f) / 2 + 60.f);
    helpRect.setFillColor(Color::Magenta);

    Text helpText("Help", font, 30);
    helpText.setPosition(helpRect.getPosition().x + 100.f, helpRect.getPosition().y + 8.f);
    helpText.setFillColor(Color::Black);

    RectangleShape exitRect(Vector2f(300.f, 50.f));
    exitRect.setPosition((windowSize.first - 300.f) / 2, (windowSize.second - 50.f) / 2 + 130.f);
    exitRect.setFillColor(Color::Red);

    Text exitText("Exit", font, 30);
    exitText.setPosition(exitRect.getPosition().x + 100.f, exitRect.getPosition().y + 8.f);
    exitText.setFillColor(Color::Black);

    RectangleShape leaderBoardShape(Vector2f(300.f, 50.f));
    leaderBoardShape.setPosition(windowSize.first - 300.f, windowSize.second - 50.f);
    leaderBoardShape.setFillColor(Color::Cyan);

    Text leaderBoardText("Leaderboard", font, 30);
    leaderBoardText.setPosition(leaderBoardShape.getPosition().x + 50.f, leaderBoardShape.getPosition().y + 8.f);
    leaderBoardText.setFillColor(Color::Black);


    bool textBoxClicked;
    

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (adventureRect.getGlobalBounds().contains(mousePos)) {
                        if (player::arePlayersNamesEqual(game::currentPlayer.getUserName(), "null") ||
                            player::arePlayersNamesEqual(game::currentPlayer.getUserName(), "")) {
                            popUp popUp("Please login to play adventure mode", "Info");
                            continue;
                        }
                        else {
                            if (!settingsConfigured)
                                popUp popUp("Please configure settings first", "Info");
                            else
                                game::chooseLevel();
                        }
                    }
                    else if (survivalRect.getGlobalBounds().contains(mousePos)) {
                        if (player::arePlayersNamesEqual(game::currentPlayer.getUserName(), "null") ||
                            player::arePlayersNamesEqual(game::currentPlayer.getUserName(), "")) {
                            popUp popUp("Please login to play survival mode", "Info");
                            continue;
                        }
                        else {
                            if (!settingsConfigured)
                                popUp popUp("Please configure settings first", "Info");
                            else if(/*currentPlayer.getLevelsCompleted() == 6*/true) {
                                game::currentLevel = 7;
                                game::gameLoop(game::gameWindowSize.first, game::gameWindowSize.second);
                            }
							else {
								popUp popUp("Please complete all levels in adventure mode first", "Info");
							}
                        }
                    }
                    else if (optionsRect.getGlobalBounds().contains(mousePos)) {
                        game::gameOptions();
                    }
                    else if (helpRect.getGlobalBounds().contains(mousePos)) {
                        game::gameHelp();
                    }
                    else if (exitRect.getGlobalBounds().contains(mousePos)) {
                        game::gameExit();
                    }
                    else if (loginRect.getGlobalBounds().contains(mousePos)) {
                        game::currentPlayer = game::loginPlayer(usernameField.getText());
                        if (game::currentPlayer.getUserName() != "null" && game::currentPlayer.getUserName() != "") {
                            usernameField.setOutlineColor(Color::Green);
						}
                    }
                    else if (registerRect.getGlobalBounds().contains(mousePos)) {
                        game::registerPlayer(usernameField.getText());
                    }
                    else if (leaderBoardShape.getGlobalBounds().contains(mousePos)) {
                        leaderboard lb;
                        lb.updatePlayres();
                        lb.display();
                    }
                    else if (usernameField.getGlobalBounds().contains(mousePos)) {
						usernameField.setOutlineColor(Color::Blue);
						textBoxClicked = true;
                    }
                    else if(!usernameField.getGlobalBounds().contains(mousePos)) {
                        usernameField.setOutlineColor(Color::Black);
                        textBoxClicked = false;
                    }
                }
            }
			else if (event.type == Event::TextEntered) {
				if (textBoxClicked) {
					usernameField.handleInput(event);
				}
			}
        }

        window.clear(sf::Color(216, 209, 186));
        window.draw(choosePlayer);
        window.draw(loginRect);
        window.draw(loginText);
        window.draw(registerRect);
        window.draw(registerText);
        window.draw(menuRect);
        window.draw(adventureRect);
        window.draw(adventureText);
        window.draw(survivalRect);
        window.draw(survivalText);
        window.draw(optionsRect);
        window.draw(optionsText);
        window.draw(helpRect);
        window.draw(helpText);
        window.draw(exitRect);
        window.draw(exitText);
        usernameField.draw(window);
        window.draw(leaderBoardShape);
        window.draw(leaderBoardText);

        window.display();
    }
}

void game::chooseLevel() {
    RenderWindow window(VideoMode(500, 450), "Choose level", sf::Style::Close);

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
    }

    RectangleShape level1(Vector2f(150.f, 50.f));
    level1.setPosition(175.f, 50.f);
    level1.setFillColor(Color::Blue);
    level1.setOutlineThickness(2.f);
    level1.setOutlineColor(Color::Blue);

    Text level1Text("Level 1", font, 30);
    level1Text.setPosition(175.f, 50.f);
    level1Text.setFillColor(Color::White);

    RectangleShape level2(Vector2f(150.f, 50.f));
    level2.setPosition(175.f, 110.f);
    level2.setFillColor(Color::Blue);
    level2.setOutlineThickness(2.f);
    level2.setOutlineColor(Color::Blue);

    Text level2Text("Level 2", font, 30);
    level2Text.setPosition(175.f, 110.f);
    level2Text.setFillColor(Color::White);

    RectangleShape level3(Vector2f(150.f, 50.f));
    level3.setPosition(175.f, 170.f);
    level3.setFillColor(Color::Blue);
    level3.setOutlineThickness(2.f);
    level3.setOutlineColor(Color::Blue);

    Text level3Text("Level 3", font, 30);
    level3Text.setPosition(175.f, 170.f);
    level3Text.setFillColor(Color::White);

    RectangleShape level4(Vector2f(150.f, 50.f));
    level4.setPosition(175.f, 230.f);
    level4.setFillColor(Color::Blue);
    level4.setOutlineThickness(2.f);
    level4.setOutlineColor(Color::Blue);

    Text level4Text("Level 4", font, 30);
    level4Text.setPosition(175.f, 230.f);
    level4Text.setFillColor(Color::White);

    RectangleShape level5(Vector2f(150.f, 50.f));
    level5.setPosition(175.f, 290.f);
    level5.setFillColor(Color::Blue);
    level5.setOutlineThickness(2.f);
    level5.setOutlineColor(Color::Blue);

    Text level5Text("Level 5", font, 30);
    level5Text.setPosition(175.f, 290.f);
    level5Text.setFillColor(Color::White);

    //RectangleShape level6(Vector2f(150.f, 50.f));
    //level6.setPosition(175.f, 350.f);
    //level6.setFillColor(Color::Blue);
    //level6.setOutlineThickness(2.f);
    //level6.setOutlineColor(Color::Blue);

    //Text level6Text("Level 6", font, 30);
    //level6Text.setPosition(175.f, 350.f);
    //level6Text.setFillColor(Color::White);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed) {
                if(event.mouseButton.button == Mouse::Left){
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					if (level1.getGlobalBounds().contains(mousePos) && currentPlayer.lvlGreaterThan(0)) {
                        game::currentLevel = 1;
                        window.close();
						game::gameLoop(game::gameWindowSize.first, game::gameWindowSize.second);
					}
					else if (level2.getGlobalBounds().contains(mousePos) && currentPlayer.lvlGreaterThan(1)) {
                        game::currentLevel = 2;
                        window.close();
						game::gameLoop(game::gameWindowSize.first, game::gameWindowSize.second);
					}
					else if (level3.getGlobalBounds().contains(mousePos) && currentPlayer.lvlGreaterThan(2)) {
                        game::currentLevel = 3;
                        window.close();
						game::gameLoop(game::gameWindowSize.first, game::gameWindowSize.second);
					}
					else if (level4.getGlobalBounds().contains(mousePos) && currentPlayer.lvlGreaterThan(3)) {
                        game::currentLevel = 4;
                        window.close();
						game::gameLoop(game::gameWindowSize.first, game::gameWindowSize.second);
					}
					else if (level5.getGlobalBounds().contains(mousePos) && currentPlayer.lvlGreaterThan(4)) {
                        game::currentLevel = 5;
                        window.close();
						game::gameLoop(game::gameWindowSize.first, game::gameWindowSize.second);
					}
					//else if (level6.getGlobalBounds().contains(mousePos) && currentPlayer.lvlGreaterThan(5)) {
     //                   game::currentLevel = 6;
     //                   window.close();
					//	game::gameLoop(game::gameWindowSize.first, game::gameWindowSize.second);
					//}
				}
            }
        }

        window.clear(sf::Color(0xCFCBCA));        
        window.draw(level1);
        window.draw(level1Text);
        window.draw(level2);
        window.draw(level2Text);
        window.draw(level3);
        window.draw(level3Text);
        window.draw(level4);
        window.draw(level4Text);
        window.draw(level5);
        window.draw(level5Text);
        //window.draw(level6);
        //window.draw(level6Text);
        window.display();
    }
}

void game::gameOptions() {
	RenderWindow window(VideoMode(800, 500), "Options", sf::Style::Close);

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
    }

    RectangleShape sliderBar(Vector2f(200.f, 20.f));
    sliderBar.setPosition(300.f, 100.f);
    sliderBar.setFillColor(Color::White);
    sliderBar.setOutlineThickness(2.f);
    sliderBar.setOutlineColor(Color::Black);

    RectangleShape sliderButton(Vector2f(20.f, 40.f));
    sliderButton.setPosition(300.f, 90.f);
    sliderButton.setFillColor(Color::Blue);

	Text sliderText("Volume", font, 30);
	sliderText.setPosition(350.f, 50.f);
	sliderText.setFillColor(Color::White);

	RectangleShape resolution2(Vector2f(150.f, 50.f));
	resolution2.setPosition(125.f, 250.f);
	resolution2.setFillColor(Color::Blue);
	resolution2.setOutlineThickness(2.f);
	resolution2.setOutlineColor(Color::Blue);

	Text resolution2Text("1280x1024", font, 30);
	resolution2Text.setPosition(125.f, 250.f);
	resolution2Text.setFillColor(Color::White);

	RectangleShape resolution3(Vector2f(150.f, 50.f));
	resolution3.setPosition(525.f, 250.f);
	resolution3.setFillColor(Color::Blue);
	resolution3.setOutlineThickness(2.f);
	resolution3.setOutlineColor(Color::Blue);

	Text resolution3Text("1600x900", font, 30);
	resolution3Text.setPosition(525.f, 250.f);
	resolution3Text.setFillColor(Color::White);

	RectangleShape saveSettings(Vector2f(200.f, 50.f));
	saveSettings.setPosition(300.f, 420.f);
	saveSettings.setFillColor(Color::Green);
	saveSettings.setOutlineThickness(2.f);
	saveSettings.setOutlineColor(Color::Black);

	Text saveSettingsText("Save", font, 30);
	saveSettingsText.setPosition(350.f, 420.f);
	saveSettingsText.setFillColor(Color::White);

    bool isDragging = false;
	bool isResolution = false;

	game::loadSettings("settings.txt");

	sliderButton.setPosition(gameSoundVolume * (sliderBar.getSize().x - sliderButton.getSize().x) + sliderButton.getPosition().x, sliderButton.getPosition().y);

    if (gameWindowSize.first == 1280) {
        resolution2.setOutlineColor(Color::White);
		isResolution = true;
    }
    else if (gameWindowSize.first == 1600) {
        resolution3.setOutlineColor(Color::White);
		isResolution = true;
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            gameSoundVolume = (sliderButton.getPosition().x - sliderBar.getPosition().x) / (sliderBar.getSize().x - sliderButton.getSize().x);
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (sliderButton.getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                    }
					else if (resolution2.getGlobalBounds().contains(mousePos)) {
                        //resolution1.setOutlineColor(Color::Blue);
                        resolution2.setOutlineColor(Color::White);
                        resolution3.setOutlineColor(Color::Blue);
						gameWindowSize = std::make_pair(1280, 1024);
                        isResolution = true;
					}
					else if (resolution3.getGlobalBounds().contains(mousePos)) {
                        //resolution1.setOutlineColor(Color::Blue);
                        resolution2.setOutlineColor(Color::Blue);
                        resolution3.setOutlineColor(Color::White);
						gameWindowSize = std::make_pair(1600, 900);
                        isResolution = true;
					}
                    else if (saveSettings.getGlobalBounds().contains(mousePos)) {
						if (isResolution)
						    game::saveSettings(gameWindowSize, gameSoundVolume, "settings.txt");
                        settingsConfigured = true;
                        window.close();
                    }
                }
            }
            else if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    isDragging = false;
                }
            }
            else if (event.type == Event::MouseMoved) {
                if (isDragging) {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    float newX = mousePos.x - sliderButton.getSize().x / 2;
                    if (newX < sliderBar.getPosition().x) {
                        newX = sliderBar.getPosition().x;
                    }
                    else if (newX > sliderBar.getPosition().x + sliderBar.getSize().x - sliderButton.getSize().x) {
                        newX = sliderBar.getPosition().x + sliderBar.getSize().x - sliderButton.getSize().x;
                    }
                    sliderButton.setPosition(newX, sliderButton.getPosition().y);
                }
            }
        }

        window.clear();
        window.draw(sliderBar);
        window.draw(sliderButton);
		window.draw(resolution2);
		window.draw(resolution3);
		window.draw(saveSettings);

		window.draw(sliderText);
		window.draw(resolution2Text);
		window.draw(resolution3Text);
		window.draw(saveSettingsText);
        window.display();
    }
}

void game::gameHelp() {
	game::openReadMe();
}

void game::gameExit() {
	exit(0);
}

void game::registerPlayer(std::string playerName) {
    player newPlayer(playerName);

    if(newPlayer.saveToFile())
        popUp popUp("Player registered successfully", "Info");
}

player game::loginPlayer(std::string playerName) {
    player newPlayer = player::loadFromFile(playerName);
    return newPlayer;
}

void game::saveSettings(std::pair<int, int> gameWindowSize, float gameSoundVolume, std::string path) {
	std::ofstream file(path);
	file << gameWindowSize.first << " " << gameWindowSize.second << " " << gameSoundVolume;
	file.close();
}

void game::loadSettings(std::string path) {
	std::ifstream file(path);
	file >> gameWindowSize.first >> gameWindowSize.second >> gameSoundVolume;
}

void game::openReadMe() {
	std::filesystem::path readmePath = std::filesystem::current_path() / "README.txt";

	std::system(("notepad " + readmePath.string()).c_str());
}

void game::passiveResourceGeneration(resource& resourcesAmount, float soundVolume) {
    sf::Time elapsed = generationTimer.getElapsedTime();
    if (elapsed.asSeconds() >= 8) {
        generationTimer.restart();
        resourcesAmount += 25;
    }    
}

void game::createCards(std::vector<allyCard>& allyCards) {
    allyCards.push_back(allyCard("Range", 0, 0));
    TextureManager::loadTexture("Range", "textures/RangeAllyCard.png");
    if (game::currentLevel > 1) {
        allyCards.push_back(allyCard("Support", 100, 0));
        TextureManager::loadTexture("Support", "textures/SupportAllyCard.png");
    }
    if (game::currentLevel > 2) {
        allyCards.push_back(allyCard("Tank", 200, 0));
        TextureManager::loadTexture("Tank", "textures/TankAllyCard.png");
    }
    if (game::currentLevel > 4) {
        allyCards.push_back(allyCard("Melee", 300, 0));
        TextureManager::loadTexture("Melee", "textures/MeleeAllyCard.png");
    }
}