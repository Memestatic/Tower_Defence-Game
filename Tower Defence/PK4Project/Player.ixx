#include <SFML/Graphics.hpp>
#include <string>;
#include <ranges>;
#include <algorithm>;
#include <filesystem>;
#include <iostream>
#include <fstream>;
#include <regex>;

export module Player;

import PopUp;

export class player {
	std::string userName;
	int totalScore;
	int currentScore;
	int levelsCompleted;
public:
	static inline std::filesystem::path playersDataPath = std::filesystem::current_path() / "players.txt";

	player(std::string name) {
		this->userName = name;
		this->totalScore = 0;
		this->currentScore = 0;
		this->levelsCompleted = 0;

	}

	player() = default;

	bool saveToFile() {
		//if regex - name have to start with big letter
		std::regex nameRegex("^[A-Z][a-z]*$");
		if(std::regex_match(this->userName, nameRegex)){
			if (!this->doesPlayerExist()) {
				std::ofstream file(playersDataPath, std::ios::app);
				if (file.is_open()) {
					file << this->userName << " " << this->totalScore << " " << this->levelsCompleted << "\n";
					return true;
				}
			}
			else {
				popUp popUp("Player already exists!", "Info");
			}
		}
		else {
			popUp popUp("Name has to start with big letter and consist of only letters!", "Info");
		}
		return false;
	}

	static player loadFromFile(std::string name) {
		std::ifstream file(playersDataPath);
		std::string userName;
		int totalScore;
		int levelsCompleted;
		while (file >> userName >> totalScore >> levelsCompleted) {
			if (player::arePlayersNamesEqual(name, userName)) {
				player newPlayer(userName);
				newPlayer.totalScore = totalScore;
				newPlayer.levelsCompleted = levelsCompleted;
				return newPlayer;
			}
		}
		popUp popUp("Player not found!", "Info");
		return player("null");
	}

	void overwritePlayerData() {
		std::ifstream file(playersDataPath);
		std::ofstream tempFile("temp.txt");
		std::string tempUserName;
		int tempTotalScore;
		int tempLevelsCompleted;
		bool playerFound = false;

		while (file >> tempUserName >> tempTotalScore >> tempLevelsCompleted) {
			if (player::arePlayersNamesEqual(tempUserName, this->userName)) {
				playerFound = true;
				if (this->currentScore > this->totalScore)
					this->totalScore = this->currentScore;
				tempFile << this->userName << " " << this->totalScore << " " << this->levelsCompleted << "\n";
			}
			else {
				tempFile << tempUserName << " " << tempTotalScore << " " << tempLevelsCompleted << "\n";
			}
		}

		if (!playerFound) {
			// Jeœli gracz nie zosta³ znaleziony w pliku, dodajemy go na koñcu.
			tempFile << this->userName << " " << this->totalScore << " " << this->levelsCompleted << "\n";
		}

		file.close();
		tempFile.close();
		std::filesystem::remove(playersDataPath);
		std::filesystem::rename("temp.txt", playersDataPath);
	}

	std::string getUserName() {
		return this->userName;
	}

	static bool arePlayersNamesEqual(std::string name, std::string userName) {
		return std::ranges::equal(name, userName);
	}

	void completeLevel() {
		this->levelsCompleted++;
	}

	bool doesPlayerExist() {
		std::ifstream file(playersDataPath);
		std::string userName;
		int totalScore;
		int levelsCompleted;
		while (file >> userName >> totalScore >> levelsCompleted) {
			if (player::arePlayersNamesEqual(this->userName, userName)) {
				return true;
			}
		}
		return false;
	}

	int getLevelsCompleted() {
		return this->levelsCompleted;
	}

	int getTotalScore() {
		return this->totalScore;
	}

	bool lvlGreaterThan(int lvl) {
		return this->levelsCompleted >= lvl;
	}

    static std::vector<player> getAllPlayers() {
        std::vector<player> players;
        std::ifstream file(playersDataPath);
        std::string userName;
        int totalScore;
        int levelsCompleted;
        while (file >> userName >> totalScore >> levelsCompleted) {
            player newPlayer(userName);
            newPlayer.totalScore = totalScore;
            newPlayer.levelsCompleted = levelsCompleted;
            players.push_back(newPlayer);
        }
        return players;
    }

	void operator+=(int score) {
		this->currentScore += score;
	}

	int getCurrentScore() {
		return this->currentScore;
	}
};