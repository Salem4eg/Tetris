#pragma once
#include <thread>
#include <vector>
#include <fstream>
#include "Player.cpp"
#include "GameField.cpp"
#include "menu.cpp"

class Game
{
private:
	Field field;
	Player player;
	Menu menu;
	int score;
	std::vector<int> records;
	enum gameSpeed { firstSpeed = 400, secondSpeed = 350, thirdSpeed = 300, fourthSpeed = 250, FifthSpeed = 200 };
public:
	Game() : player(field)
	{
		player.obtainNewBlock(field);

	}

	void Run()
	{

		if (!loadSettings())
		{
			menu.chooseLanguage();
		}
		bool playAgain = true;
		bool repeatProgram = true;

		while (repeatProgram)
		{
			repeatProgram = showStartingMenu();

			while (repeatProgram)
			{
				playAgain = actualGame();
				saveSettings();
				if (!playAgain)
					break;
			}
		}


	}

	bool showStartingMenu()
	{
		int action = menu.ShowMainMenu();

		if (action == -1)
			return false;

		while (action != 0)
		{
			switch (action)
			{
			case 1:
				menu.showScoreboard(records);
				action = menu.ShowMainMenu();
				break;
			case 2:
				menu.showSettings();
				action = menu.ShowMainMenu();
				break;
			case -1:
				return false;
			}
		}
		return true;
	}

	bool actualGame()
	{
		score = 0;
		field.resetField();
		player.obtainNewBlock(field);
		int updateSpeed = firstSpeed;
		int ticksToFall = updateSpeed / 25;
		int gameTick = 0;
		int neededScoreToIncreaseSpeed = 10000;
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(25));

			if (gameTick % 2 == 0)
				player.handleInput(field);


			if (gameTick % ticksToFall == 0 && field.isCollide(player.getBlock()))
			{
				if (player.getBlock()[0].first >= 1 && player.getBlock()[0].first <= 3) // died
				{
					return menu.playAgainAfterDeath(records, score);
				}
				else
				{
					getAnotherBlock();

					field.isCompletedRow(score);
					if (score >= neededScoreToIncreaseSpeed && updateSpeed > FifthSpeed)
					{
						updateSpeed -= 50;
						neededScoreToIncreaseSpeed += 10000;
					}
				}

			}

			if (gameTick % ticksToFall == 0)
				player.gravity();

			field.renderField(player.getBlock(), score);

			gameTick++;
		}
		return false;
	}

	void saveSettings()
	{

		std::ofstream toFile("info.txt");
		std::string lang;
		if (menu.getLanguage() == english)
			lang = "eng";
		else
			lang = "ukr";
		toFile << lang << std::endl;
		toFile << menu.getColors() << std::endl;
		for (int record : records)
			toFile << record << " ";

	}

	bool loadSettings()
	{
		std::ifstream inProg("info.txt");


		std::string temp;
		inProg >> temp;

		if (temp == "")
			return false;


		if (temp == "eng")
			menu.setLang(english);
		else
			menu.setLang(ukrainian);
		inProg >> temp;
		menu.setColors(temp);

		int number;
		while (inProg >> number)
			records.push_back(number);

		return true;
	}

	void getAnotherBlock()
	{
		field.drawBlockInField(player.getBlock());

		player.obtainNewBlock(field);
	}


};