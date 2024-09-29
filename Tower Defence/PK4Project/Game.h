#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <algorithm>
#include <iostream>
#include <ranges>
#include <map>
#include <vector>


import AllyCard;
import Ally;
import MeleeAlly;
import RangeAlly;
import SupportAlly;
import TankAlly;
import Enemy;
import LowTierEnemy;
import Player;
import Spawner;
import Slot;
import Missile;
import Resources;
import TextureManager;
import TextField;
import Wave;
import Leaderboard;
import PopUp;

class game {
public:
	static sf::Clock generationTimer;
	static bool settingsConfigured;
	static std::pair<int, int> windowSize;
	static std::pair<int, int> gameWindowSize;
	static float gameSoundVolume;
	static player currentPlayer;
	static int currentLevel;
	static bool levelCompleted;
	static void gameMenu(int x, int y);
	static void chooseLevel();
	static void gameLoop(int x, int y);
	static void gameOptions();
	static void gameHelp();
	static void gameExit();
	static void registerPlayer(std::string playerName);
	static player loginPlayer(std::string playerName);
	static void saveSettings(std::pair<int, int> windowSize, float soundVolume, std::string path);
	static void loadSettings(std::string path);
	static void openReadMe();
	static void passiveResourceGeneration(resource& resourcesAmount, float soundVolume);
	static void deleteAllDynamic(std::vector<std::vector<slot>>& slots, std::vector<enemy*>& enemies, std::vector<missile*>& missiles);
	static void endGame();
	static void createCards(std::vector<allyCard>& allyCards);
	static void levelCompletedScreen();
};