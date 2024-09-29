#include <vector>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

export module Wave;

import Spawner;
import Enemy;
import LowTierEnemy;
import MidTierEnemy;
import HighTierEnemy;

using namespace sf;

export class wave {
public:
	static bool firstSpawnDone;
	static bool secondSpawnDone;
	static bool thirdSpawnDone;
	static bool fourthSpawnDone;
	static bool fifthSpawnDone;
	static bool sixthSpawnDone;
	static bool seventhSpawnDone;
	static bool eighthSpawnDone;
	static bool ninthSpawnDone;
	static bool tenthSpawnDone;
	static sf::Time spawnCooldown;
	static int enemiesSpawned;
	static bool levelCompleted;
	static sf::Clock waveSpawnTimer;

	friend class enemy;
	friend class lowTierEnemy;

	static void createWave1(std::vector<spawner>& spawners, std::vector<enemy*>& enemies,
		float soundVolume) {
		sf::Time elapsed = waveSpawnTimer.getElapsedTime();

		if (!firstSpawnDone && elapsed.asSeconds() > 5) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			firstSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (firstSpawnDone && !secondSpawnDone && elapsed.asSeconds() > 13) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			secondSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (secondSpawnDone && !thirdSpawnDone && elapsed.asSeconds() > 10) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			thirdSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (thirdSpawnDone && !fourthSpawnDone && elapsed.asSeconds() > 10) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fourthSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (fourthSpawnDone && !fifthSpawnDone && elapsed.asSeconds() > 1) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fifthSpawnDone = true;
			enemiesSpawned += 1;
		}

		if (enemiesSpawned == 5 && enemies.empty()) {
			wave::levelCompleted = true;
			firstSpawnDone = false;
			secondSpawnDone = false;
			thirdSpawnDone = false;
			fourthSpawnDone = false;
			fifthSpawnDone = false;
			enemiesSpawned = 0;
		}
	}

	static void createWave2(std::vector<spawner>& spawners, std::vector<enemy*>& enemies,
		float soundVolume) {
		sf::Time elapsed = waveSpawnTimer.getElapsedTime();

		if (!firstSpawnDone && elapsed.asSeconds() > 30) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			firstSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (firstSpawnDone && !secondSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			secondSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (secondSpawnDone && !thirdSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			thirdSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (thirdSpawnDone && !fourthSpawnDone && elapsed.asSeconds() > 13) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fourthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (fourthSpawnDone && !fifthSpawnDone && elapsed.asSeconds() > 15) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fifthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (fifthSpawnDone && !sixthSpawnDone && elapsed.asSeconds() > 15) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			sixthSpawnDone = true;
			enemiesSpawned += 5;
		}

		if (enemiesSpawned == 12 && enemies.empty()) {
			wave::levelCompleted = true;
			firstSpawnDone = false;
			secondSpawnDone = false;
			thirdSpawnDone = false;
			fourthSpawnDone = false;
			fifthSpawnDone = false;
			sixthSpawnDone = false;
			enemiesSpawned = 0;
		}
	}

	static void createWave3(std::vector<spawner>& spawners, std::vector<enemy*>& enemies,
		float soundVolume) {
		sf::Time elapsed = waveSpawnTimer.getElapsedTime();

		if (!firstSpawnDone && elapsed.asSeconds() > 18) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			firstSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (firstSpawnDone && !secondSpawnDone && elapsed.asSeconds() > 30) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			secondSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (secondSpawnDone && !thirdSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			thirdSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (thirdSpawnDone && !fourthSpawnDone && elapsed.asSeconds() > 13) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fourthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (fourthSpawnDone && !fifthSpawnDone && elapsed.asSeconds() > 14) {
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fifthSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (fifthSpawnDone && !sixthSpawnDone && elapsed.asSeconds() > 14) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			sixthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (sixthSpawnDone && !seventhSpawnDone && elapsed.asSeconds() > 11) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			seventhSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (seventhSpawnDone && !eighthSpawnDone && elapsed.asSeconds() > 31) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			eighthSpawnDone = true;
			enemiesSpawned += 6;
		}

		if (enemiesSpawned == 16 && enemies.empty()) {
			wave::levelCompleted = true;
			firstSpawnDone = false;
			secondSpawnDone = false;
			thirdSpawnDone = false;
			fourthSpawnDone = false;
			fifthSpawnDone = false;
			sixthSpawnDone = false;
			seventhSpawnDone = false;
			eighthSpawnDone = false;
			enemiesSpawned = 0;
		}
	}

	static void createWave4(std::vector<spawner>& spawners, std::vector<enemy*>& enemies,
		float soundVolume) {
		sf::Time elapsed = waveSpawnTimer.getElapsedTime();

		if(!firstSpawnDone && elapsed.asSeconds() > 25) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			firstSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if(firstSpawnDone && !secondSpawnDone && elapsed.asSeconds() > 27) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			secondSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if(secondSpawnDone && !thirdSpawnDone && elapsed.asSeconds() > 24) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			thirdSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if(thirdSpawnDone && !fourthSpawnDone && elapsed.asSeconds() > 15) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fourthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (fourthSpawnDone && !fifthSpawnDone && elapsed.asSeconds() > 16) {
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fifthSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (fifthSpawnDone && !sixthSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			sixthSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if(sixthSpawnDone && !seventhSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			seventhSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (seventhSpawnDone && !eighthSpawnDone && elapsed.asSeconds() > 16) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			eighthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if(eighthSpawnDone && !ninthSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			ninthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (ninthSpawnDone && !tenthSpawnDone && elapsed.asSeconds() > 34) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			tenthSpawnDone = true;
			enemiesSpawned += 8;
		}

		if (enemiesSpawned == 21 && enemies.empty()) {
			wave::levelCompleted = true;
			firstSpawnDone = false;
			secondSpawnDone = false;
			thirdSpawnDone = false;
			fourthSpawnDone = false;
			fifthSpawnDone = false;
			sixthSpawnDone = false;
			seventhSpawnDone = false;
			eighthSpawnDone = false;
			ninthSpawnDone = false;
			tenthSpawnDone = false;
			enemiesSpawned = 0;
		}
	}

	static void createWave5(std::vector<spawner>& spawners, std::vector<enemy*>& enemies,
		float soundVolume) {
		sf::Time elapsed = waveSpawnTimer.getElapsedTime();

		if (!firstSpawnDone && elapsed.asSeconds() > 25) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			firstSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (firstSpawnDone && !secondSpawnDone && elapsed.asSeconds() > 27) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			secondSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (secondSpawnDone && !thirdSpawnDone && elapsed.asSeconds() > 24) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			thirdSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (thirdSpawnDone && !fourthSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new highTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fourthSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (fourthSpawnDone && !fifthSpawnDone && elapsed.asSeconds() > 16) {
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			fifthSpawnDone = true;
			enemiesSpawned += 1;
		}
		else if (fifthSpawnDone && !sixthSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			sixthSpawnDone = true;
			enemiesSpawned += 3;
		}
		else if (sixthSpawnDone && !seventhSpawnDone && elapsed.asSeconds() > 25) {
			enemies.push_back(new highTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			seventhSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (seventhSpawnDone && !eighthSpawnDone && elapsed.asSeconds() > 16) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			eighthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (eighthSpawnDone && !ninthSpawnDone && elapsed.asSeconds() > 20) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			ninthSpawnDone = true;
			enemiesSpawned += 2;
		}
		else if (ninthSpawnDone && !tenthSpawnDone && elapsed.asSeconds() > 34) {
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new highTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new highTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			waveSpawnTimer.restart();
			tenthSpawnDone = true;
			enemiesSpawned += 6;
		}

		if (enemiesSpawned == 20 && enemies.empty()) {
			wave::levelCompleted = true;
			firstSpawnDone = false;
			secondSpawnDone = false;
			thirdSpawnDone = false;
			fourthSpawnDone = false;
			fifthSpawnDone = false;
			sixthSpawnDone = false;
			seventhSpawnDone = false;
			eighthSpawnDone = false;
			ninthSpawnDone = false;
			tenthSpawnDone = false;
			enemiesSpawned = 0;
		}
	}

	static void createSurvivalWave(std::vector<spawner>& spawners, std::vector<enemy*>& enemies,
		float soundVolume) {
		sf::Time elapsed = waveSpawnTimer.getElapsedTime();

		if (elapsed.asMilliseconds() > spawnCooldown.asMilliseconds()) {
			enemiesSpawned += 1;

			if(spawnCooldown.asMilliseconds() > 500)
				spawnCooldown = sf::milliseconds(spawnCooldown.asMilliseconds() * 0.95);
			//std::cout<<"Spawn cooldown: "<<spawnCooldown.asMilliseconds()<<std::endl;

			if (enemiesSpawned % 25 == 0) 
				enemies.push_back(new highTierEnemy(spawners, soundVolume * 100));
			else if(enemiesSpawned % 5 == 0)
				enemies.push_back(new midTierEnemy(spawners, soundVolume * 100));
			else
				enemies.push_back(new lowTierEnemy(spawners, soundVolume * 100));

			waveSpawnTimer.restart();
		}
	}

};