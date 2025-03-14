#pragma once
#include <Windows.h>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum Lang { english = 0, ukrainian = 1 };

class Menu
{
private:
	std::vector<std::string> menu;
	Lang language;
	std::string backgroundColor;
	std::string textColor;
	void createBasicMenu()
	{
		system("cls");
		menu.clear();

		menu.emplace_back(R"(######################)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(|                    |)");
		menu.emplace_back(R"(######################)");
	}

	int chooseParameter(std::vector<std::string>& buttonsWithArrow, std::vector<std::string>& buttonsWithoutArrow, std::vector<int> positionOfButtons)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		int button = 0;
		int exitButtonIndex = positionOfButtons.size() - 1;

		menu[positionOfButtons[0]] = buttonsWithArrow[0];

		renderMenu();
		while (!GetAsyncKeyState(VK_RETURN))
		{
			if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState('S') & 0x8000)
			{
				if (GetAsyncKeyState('W') & 0x8000) // up
					button--;
				else if (GetAsyncKeyState('S') & 0x8000) // down
					button++;

				if (button < 0)
					button = exitButtonIndex;
				else if (button > exitButtonIndex)
					button = 0;

				for (int index = 0; index < positionOfButtons.size(); index++)
					menu[positionOfButtons[index]] = buttonsWithoutArrow[index];

				menu[positionOfButtons[button]] = buttonsWithArrow[button];

				renderMenu();
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}

		return button;
	}

	int chooseColor(int backgroundOrText)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::vector<std::string> buttonsWithArrow;
		std::vector<std::string> buttonsWithoutArrow;
		createBasicMenu();

		if (language == english)
		{
			if (backgroundOrText == 0)
				menu[2] = "| Background color 1 |";
			else
				menu[2] = "|  Color of text 1   |";

			menu[4] = "|====================|";
			menu[7] = "|        Black       |"; // 7
			menu[8] = "|        Blue        |"; // 8
			menu[10] = "|        Green       |"; // 10
			menu[11] = "|        Agua        |"; // 11
			menu[13] = "|        Red         |"; // 13
			menu[14] = "|        Purple      |"; // 14
			menu[16] = "|        Yellow      |"; // 16
			menu[17] = "|        White       |"; // 17

			menu[19] = "|        Next        |"; // 19
			menu[20] = "|        Back        |"; // 20

			buttonsWithArrow.emplace_back("|       >Black       |");
			buttonsWithArrow.emplace_back("|       >Blue        |");
			buttonsWithArrow.emplace_back("|       >Green       |");
			buttonsWithArrow.emplace_back("|       >Agua        |");
			buttonsWithArrow.emplace_back("|       >Red         |");
			buttonsWithArrow.emplace_back("|       >Purple      |");
			buttonsWithArrow.emplace_back("|       >Yellow      |");
			buttonsWithArrow.emplace_back("|       >White       |");
			buttonsWithArrow.emplace_back("|       >Next        |");
			buttonsWithArrow.emplace_back("|       >Back        |");
		}
		else
		{
			if (backgroundOrText == 0)
				menu[2] = "|     Колір фону 1   |";
			else
				menu[2] = "|    Колір тексту 1  |";

			menu[4] = "|====================|";
			menu[7] = "|        Чорний      |"; // 7
			menu[8] = "|        Синій       |"; // 8
			menu[10] = "|        Зелений     |"; // 10
			menu[11] = "|        Водянистий  |"; // 11
			menu[13] = "|        Червоний    |"; // 13
			menu[14] = "|        Пурпуровий  |"; // 14
			menu[16] = "|        Жовтий      |"; // 16
			menu[17] = "|        Білий       |"; // 17

			menu[19] = "|        Вперед      |"; // 19
			menu[20] = "|        Назад       |"; // 20

			buttonsWithArrow.emplace_back("|       >Чорний      |");
			buttonsWithArrow.emplace_back("|       >Синій       |");
			buttonsWithArrow.emplace_back("|       >Зелений     |");
			buttonsWithArrow.emplace_back("|       >Водянистий  |");
			buttonsWithArrow.emplace_back("|       >Червоний    |");
			buttonsWithArrow.emplace_back("|       >Пурпуровий  |");
			buttonsWithArrow.emplace_back("|       >Жовтий      |");
			buttonsWithArrow.emplace_back("|       >Білий       |");
			buttonsWithArrow.emplace_back("|       >Вперед      |");
			buttonsWithArrow.emplace_back("|       >Назад       |");
		}


		std::vector<int> buttonPositions { 7, 8, 10, 11, 13, 14, 16, 17, 19, 20 };
		for (int index : buttonPositions)
			buttonsWithoutArrow.push_back(menu[index]);


		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		int button = 0;
		int exitButtonIndex = buttonPositions.size() - 1;
		char color;

		menu[7] = buttonsWithArrow[0];

		renderMenu();
		while (!GetAsyncKeyState(VK_RETURN) || button < exitButtonIndex - 1)
		{
			if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				if (GetAsyncKeyState(VK_RETURN) & 0x8000 && button < exitButtonIndex - 1)
				{
					color = button + 48;

					if (backgroundOrText == 0) // background
						backgroundColor = color;
					else // text
						textColor = color;

					std::string setColourCommand = "color " + backgroundColor + textColor;
					system(setColourCommand.c_str());
				}
				else if (GetAsyncKeyState('W') & 0x8000) // up
					button--;
				else if (GetAsyncKeyState('S') & 0x8000) // down
					button++;

				if (button < 0)
					button = exitButtonIndex;
				else if (button > exitButtonIndex)
					button = 0;

				for (int index = 0; index < buttonsWithoutArrow.size(); index++)
					menu[buttonPositions[index]] = buttonsWithoutArrow[index];

				menu[buttonPositions[button]] = buttonsWithArrow[button];

				renderMenu();
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}

		return button == buttonPositions.size() - 1 ? 1 : 0;
	}
	void chooseColorLastPage(int backgroundOrText)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::vector<std::string> buttonsWithArrow;
		std::vector<std::string> buttonsWithoutArrow;
		createBasicMenu();

		if (language == english)
		{
			if (backgroundOrText == 0)
				menu[2] = "| Background color 2 |";
			else
				menu[2] = "|  Color of text 2   |";

			menu[4] = "|====================|";
			menu[7] = "|        Gray        |"; // 7
			menu[8] = "|     Light Blue     |"; // 8
			menu[10] = "|     Light green    |"; // 10
			menu[11] = "|     Light agua     |"; // 11
			menu[13] = "|     light red      |"; // 13
			menu[14] = "|     light purple   |"; // 14
			menu[16] = "|     light yellow   |"; // 16
			menu[17] = "|     bright white   |"; // 17
			menu[20] = "|        Back        |"; // 20

			buttonsWithArrow.emplace_back("|       >Gray        |");
			buttonsWithArrow.emplace_back("|    >Light Blue     |");
			buttonsWithArrow.emplace_back("|    >Light green    |");
			buttonsWithArrow.emplace_back("|    >Light agua     |");
			buttonsWithArrow.emplace_back("|    >light red      |");
			buttonsWithArrow.emplace_back("|    >light purple   |");
			buttonsWithArrow.emplace_back("|    >light yellow   |");
			buttonsWithArrow.emplace_back("|    >bright white   |");
			buttonsWithArrow.emplace_back("|       >Back        |");
		}
		else
		{
			if (backgroundOrText == 0)
				menu[2] = "|     Колір фону 2   |";
			else
				menu[2] = "|    Колір тексту 2  |";
			menu[4] = "|====================|";
			menu[7] = "|        Сірий       |"; // 7
			menu[8] = "|      Блакитний     |"; // 8
			menu[10] = "|    Світло-зелений  |"; // 10
			menu[11] = "|  Світло-водянистий |"; // 11
			menu[13] = "|   Світло-червоний  |"; // 13
			menu[14] = "|   Світло-червоний  |"; // 14
			menu[16] = "|    Світло-жовтий   |"; // 16
			menu[17] = "|    Яскраво-білий   |"; // 17
			menu[20] = "|        Назад       |"; // 20

			buttonsWithArrow.emplace_back("|       >Сірий       |");
			buttonsWithArrow.emplace_back("|     >Блакитний     |");
			buttonsWithArrow.emplace_back("|   >Світло-зелений  |");
			buttonsWithArrow.emplace_back("| >Світло-водянистий |");
			buttonsWithArrow.emplace_back("|  >Світло-червоний  |");
			buttonsWithArrow.emplace_back("|  >Світло-червоний  |");
			buttonsWithArrow.emplace_back("|   >Світло-жовтий   |");
			buttonsWithArrow.emplace_back("|   >Яскраво-білий   |");
			buttonsWithArrow.emplace_back("|       >Назад       |");
		}

		std::vector<int> buttonPositions { 7, 8, 10, 11, 13, 14, 16, 17, 20 };
		for (int index : buttonPositions)
			buttonsWithoutArrow.push_back(menu[index]);


		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		int button = 0;
		int exitButtonIndex = buttonPositions.size() - 1;
		char color;

		menu[7] = buttonsWithArrow[0];

		renderMenu();
		while (!GetAsyncKeyState(VK_RETURN) || button != exitButtonIndex)
		{
			if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				if (GetAsyncKeyState(VK_RETURN) & 0x8000 && button != exitButtonIndex)
				{
					int temp = button + 8;
					if (temp < 10)
						color = temp + 48;
					else
						color = temp + 55;

					if (backgroundOrText == 0) // background
						backgroundColor = color;
					else // text
						textColor = color;

					std::string setColourCommand = "color " + backgroundColor + textColor;
					system(setColourCommand.c_str());
				}
				else if (GetAsyncKeyState('W') & 0x8000) // up
					button--;
				else if (GetAsyncKeyState('S') & 0x8000) // down
					button++;

				if (button < 0)
					button = exitButtonIndex;
				else if (button > exitButtonIndex)
					button = 0;

				for (int index = 0; index < buttonsWithoutArrow.size(); index++)
					menu[buttonPositions[index]] = buttonsWithoutArrow[index];

				menu[buttonPositions[button]] = buttonsWithArrow[button];

				renderMenu();
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}



	}

public:
	Menu() : backgroundColor("0"), textColor("7")
	{
		SetConsoleOutputCP(1251);

		//prevents resizing window
		HWND consoleWindow = GetConsoleWindow();
		SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

		RECT r;
		GetWindowRect(consoleWindow, &r);

		MoveWindow(consoleWindow, r.left, r.top, 350, 500, TRUE);
	}

	int ShowMainMenu()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::vector<std::string> buttonsWithArrow;
		std::vector<std::string> buttonsWithoutArrow;

		createBasicMenu();

		if (language == english)
		{
			menu[2] = "| ___ __ ___ _  *  _ |";
			menu[3] = "|  | |__  | |_| | |  |";
			menu[4] = "|  | |__  | | \\ | |_ |";

			menu[10] = "|        Play        |";
			menu[12] = "|      Scoreboard    |";
			menu[14] = "|       Settings     |";
			menu[16] = "|        Exit        |";
		}
		else
		{
			menu[2] = "| ___ __ ___ _  *  _ |"; // 2
			menu[3] = "|  | |__  | |_| | |  |"; // 3
			menu[4] = "|  | |__  | |   | |_ |"; // 4

			menu[10] = "|        Грати       |"; // 10
			menu[12] = "|     Твої рекорди   |"; // 12
			menu[14] = "|     Налаштування   |"; // 14
			menu[16] = "|        Вихід       |"; // 16
		}

		if (language == english)
		{
			buttonsWithArrow.emplace_back("|       >Play        |");
			buttonsWithArrow.emplace_back("|     >Scoreboard    |");
			buttonsWithArrow.emplace_back("|      >Settings     |");
			buttonsWithArrow.emplace_back("|       >Exit        |");
		}
		else
		{
			buttonsWithArrow.emplace_back("|       >Грати       |");
			buttonsWithArrow.emplace_back("|    >Твої рекорди   |");
			buttonsWithArrow.emplace_back("|    >Налаштування   |");
			buttonsWithArrow.emplace_back("|       >Вихід       |");
		}

		buttonsWithoutArrow.push_back(menu[10]);
		buttonsWithoutArrow.push_back(menu[12]);
		buttonsWithoutArrow.push_back(menu[14]);
		buttonsWithoutArrow.push_back(menu[16]);


		int button = chooseParameter(buttonsWithArrow, buttonsWithoutArrow, { 10,12,14,16 });


		switch (button)
		{
		case 0:
			return 0; // play
		case 1:
			return 1; // scoreboard
		case 2:
			return 2; // settings
		case 3:
			return -1; // exit
		}

		return -1;
	}


	void showSettings()
	{
		int button = 0;
		while (button != 4)
		{
			createBasicMenu();

			std::vector<std::string> buttonsWithArrow;
			std::vector<std::string> buttonsWithoutArrow;

			if (language == english)
			{
				menu[2] = "|       Settings     |"; // 2
				menu[4] = "|====================|"; // 4

				menu[9] =  "|  Background color  |"; // 9
				menu[11] = "|     text color     |"; // 11
				menu[13] = "|     How to play    |"; // 13
				menu[15] = "|   Change language  |"; // 15
				menu[17] = "|        Menu        |"; // 17

				buttonsWithArrow.emplace_back("| >Background color  |");
				buttonsWithArrow.emplace_back("|    >text color     |");
				buttonsWithArrow.emplace_back("|    >How to play    |");
				buttonsWithArrow.emplace_back("|  >Change language  |");
				buttonsWithArrow.emplace_back("|       >Menu        |");
			}
			else
			{
				menu[2] = "|    Налаштування    |"; // 2
				menu[4] = "|====================|"; // 4

				menu[9] =  "|     Колір фону     |"; // 9
				menu[11] = "|    Колір тексту    |"; // 11
				menu[13] = "|      Посібник      |"; // 13
				menu[15] = "|    Змінити мову    |"; // 15
				menu[17] = "|        Меню        |"; // 17

				buttonsWithArrow.emplace_back("|    >Колір фону     |");
				buttonsWithArrow.emplace_back("|   >Колір тексту    |");
				buttonsWithArrow.emplace_back("|     >Посібник      |");
				buttonsWithArrow.emplace_back("|   >Змінити мову    |");
				buttonsWithArrow.emplace_back("|       >Меню        |");
			}

			buttonsWithoutArrow.push_back(menu[9]);
			buttonsWithoutArrow.push_back(menu[11]);
			buttonsWithoutArrow.push_back(menu[13]);
			buttonsWithoutArrow.push_back(menu[15]);
			buttonsWithoutArrow.push_back(menu[17]);

			button = chooseParameter(buttonsWithArrow, buttonsWithoutArrow, { 9,11,13,15,17 });

			switch (button)
			{
			case 0:
				showBackgroundColor1();
				break;
			case 1:
				showTextColor1();
				break;
			case 2:
				howToPlay1();
				break;
			case 3:
				chooseLanguage();
				break;
			}
		}
	}

	int playAgainAfterDeath(std::vector<int>& records, int score)
	{
		int position = 0;

		if (score != 0 && records.size() < 10 || records.size() >= 10 && records[9] < score)
		{
			records.push_back(score);
			std::sort(records.begin(), records.end(), std::greater<int>());
			if (records.size() > 10)
				records.pop_back();
		}

		if (score == 0) // if played awfully
		{
			position = -1;
		}
		else if (records.size() > 9 && records[9] >= score) // if did not make it to scoreboard
		{
			position = -2;
		}
		else
		{
			position = records.size() - 1;
			while (score != records[position])
				position--;
		}



		createBasicMenu();
		std::vector<std::string> buttonsWithArrow;
		std::vector<std::string> buttonsWithoutArrow;

		int firstIndex;
		int lastIndex;

		if (position == 0 || position == -1)
		{
			firstIndex = 0;
			lastIndex = 2;
		}
		else if (position == 9 || position == -2)
		{
			firstIndex = 7;
			lastIndex = 9;
		}
		else
		{
			if (position == records.size() - 1)
			{
				lastIndex = position;
				firstIndex = position - 2 < 0 ? 0 : position - 2;
			}
			else
			{
				firstIndex = position - 1;
				lastIndex = position + 1;
			}
		}

		for (int i = firstIndex; position != -1 && i <= lastIndex && i < records.size(); i++)
		{
			std::string temp = std::to_string(records[i]);
			int sizeOfRecord = temp.size();
			int spacesToAdd = (22 - sizeOfRecord) / 2;
			std::string str = "|";
			while (spacesToAdd > 0)
			{
				str += " ";
				spacesToAdd--;
			}
			if (position == i)
				str[str.size() - 5] = '>';
			else if (position == i && i == 9)
				str[str.size() - 6] = '>';

			if (i == 9)
			{
				str[str.size() - 3] = '.';
				str[str.size() - 4] = '0';
				str[str.size() - 5] = '1';
			}else
			{
				str[str.size() - 3] = '.';
				str[str.size() - 4] = '1' + i;
			}

			str += temp;
			while (str.size() < 21)
				str += " ";
			str += "|";

			menu[10 + i - firstIndex] = str;
		}

		if (language == english)
		{
			menu[2] = "|   __  _        __  |"; // 2
			menu[3] = "|  | _ |_| |\\/| |__  |"; // 3
			menu[4] = "|  |_/ | | |  | |__  |"; // 4
			menu[5] = "|   _  _  _  _  _    |"; // 5
			menu[6] = "|  | | \\\\// |_ |_|   |"; // 6
			menu[7] = "|  |_|  \\/  |_ | \\   |"; // 7
			menu[8] = "|                    |"; // 8
			menu[14] = "|   Your score is    |"; // 14
			menu[16] = "|  it is your " + std::to_string(position + 1) + "   "; // 16
			menu[17] = "| best record so far |"; // 17
			menu[19] = "|     Play again     |"; // 18
			menu[20] = "|        Menu        |"; // 19

			if (position == -1)
			{
				menu[14] = "|    How did you..   |"; // 14
				menu[16] = "|    Gidgud okay?  "; // 16
				menu[17] = "|  That was so bad.  |"; // 17
			}else if (position == -2)
			{
				menu[14] = "|   With this score  |"; // 14
				menu[16] = "|  you didn't beat "; // 16
				menu[17] = "|   any records. :(  |"; // 17
			}

			buttonsWithArrow.emplace_back("|    >Play again     |");
			buttonsWithArrow.emplace_back("|       >Menu        |");
		}
		else
		{
			menu[5] = "|           _        |"; // 2
			menu[2] = "| |/ | |_| |_ | | |_ |"; // 3
			menu[3] = "| |\\ | | | |_ |_\\ |/ |"; // 4
			menu[4] = "|     __  _      |   |"; // 5
			menu[5] = "|     |  |_| | /|    |"; // 6
			menu[6] = "|     |  |   |/ |    |"; // 7
			menu[8] = "|                    |"; // 8
			menu[14] = "|      Ти набрав     |"; // 14
			menu[16] = "|  очок, це " + std::to_string(position + 1) + " місце"; // 16
			menu[17] = "|    в списку очок   |"; // 17
			menu[19] = "|    Зіграти знову   |"; // 18
			menu[20] = "|        Меню        |"; // 19

			buttonsWithArrow.emplace_back("|   >Зіграти знову   |");
			buttonsWithArrow.emplace_back("|       >Меню        |");

			if (position == -1)
			{
				menu[14] = "|     Як ти це...    |"; // 14
				menu[16] = "|   Зіграй ще раз  "; // 16
				menu[17] = "|   І не облажайся.  |"; // 17
			}else if (position == -2)
			{
				menu[14] = "|   З цим рахунком   |"; // 14
				menu[16] = "| Ти не зміг увійти"; // 16
				menu[17] = "| в свої рекорди. :( |"; // 17
			}
		}
		if (position == 9)
			menu[16] += " |";
		else
			menu[16] += "  |";

		// placing score in the middle of menu[15] string
		std::string temp = std::to_string(score);
		int sizeOfRecord = temp.size();
		int spacesToAdd = (22 - sizeOfRecord) / 2;
		std::string str = "|";
		while (spacesToAdd > 0)
		{
			str += " ";
			spacesToAdd--;
		}
		str += temp;
		while (str.size() < 21)
			str += " ";
		str += "|";
		menu[15] = str;


		buttonsWithoutArrow.push_back(menu[19]);
		buttonsWithoutArrow.push_back(menu[20]);

		int button = chooseParameter(buttonsWithArrow, buttonsWithoutArrow, { 19,20 });

		return button == 0 ? true : false;
	}

	void howToPlay1()
	{
		int button = 0;
		while (button != 1)
		{
			createBasicMenu();
			std::vector<std::string> buttonsWithArrow;
			std::vector<std::string> buttonsWithoutArrow;


			if (language == english)
			{
				menu[2] = "|     How to play    |"; // 2
				menu[3] = "|          1         |"; // 3
				menu[4] = "|====================|"; // 4
				menu[6] = "| Use A,D to move    |"; // 6
				menu[7] = "| blocks to left or  |"; // 7
				menu[8] = "| right.             |"; // 8
				menu[9] = "| Use S to move down |"; // 9
				menu[10] = "| block faster.      |"; // 10
				menu[11] = "| Use W to rotate    |"; // 11
				menu[12] = "| your block.        |"; // 12
				menu[13] = "| Use Space to move  |"; // 13
				menu[14] = "| block to the       |"; // 14
				menu[15] = "| bottom in no time. |"; // 15

				menu[16] = "|        Next        |"; // 16
				menu[17] = "|        Back        |"; // 17

				buttonsWithArrow.emplace_back("|       >Next        |");
				buttonsWithArrow.emplace_back("|       >Back        |");
			}
			else
			{
				menu[2] = "|       Як грати     |"; // 2
				menu[3] = "|          1         |"; // 3
				menu[4] = "|====================|"; // 4
				menu[6] = "| Натискайте A або D |"; // 6
				menu[7] = "| щоб переміщувати   |"; // 7
				menu[8] = "| блок вліво/вправо  |"; // 8
				menu[9] = "| Натискайте S, щоб  |"; // 9
				menu[10] = "| блок швидше падав. |"; // 10
				menu[11] = "| Щоб крутити блок   |"; // 11
				menu[12] = "| натискайте W       |"; // 12
				menu[13] = "| Щоб миттєво        |"; // 13
				menu[14] = "| опустити блок вниз |"; // 14
				menu[15] = "| натисність Пробіл  |"; // 15

				menu[16] = "|       Наступна     |"; // 16
				menu[17] = "|       Назад        |"; // 17

				buttonsWithArrow.emplace_back("|      >Наступна     |");
				buttonsWithArrow.emplace_back("|      >Назад        |");
			}

			buttonsWithoutArrow.push_back(menu[16]);
			buttonsWithoutArrow.push_back(menu[17]);

			button = chooseParameter(buttonsWithArrow, buttonsWithoutArrow, { 16,17 });

			switch (button)
			{
			case 0:
				howToPlay2();
				break;
				// case 1 : repeat
			}
		}

	}

	void howToPlay2()
	{
		createBasicMenu();
		std::vector<std::string> buttonsWithArrow;
		std::vector<std::string> buttonsWithoutArrow;

		if (language == english)
		{
			menu[2] = "|     How to play    |"; // 2
			menu[3] = "|          2         |"; // 3
			menu[4] = "|====================|"; // 4
			menu[6] = "| For filling the    |"; // 6
			menu[7] = "| row you earn 250   |"; // 7
			menu[8] = "| points, and for    |"; // 8
			menu[9] = "| filling 4 rows in  |"; // 9
			menu[10] = "| one go, you earn   |"; // 10
			menu[11] = "| 1500 points.       |"; // 11
			menu[13] = "| You lose when      |"; // 13
			menu[14] = "| there is no space  |"; // 14
			menu[15] = "| for block in       |"; // 15
			menu[16] = "| spawn area         |"; // 16
			menu[20] = "|        Back        |"; // 20
			buttonsWithArrow.emplace_back("|       >Back        |");
		}
		else
		{
			menu[2] = "|       Як грати     |"; // 2
			menu[3] = "|          2         |"; // 3
			menu[4] = "|====================|"; // 4
			menu[6] = "| Заповнюючи рядок   |"; // 6
			menu[7] = "| ти отримуєш 250    |"; // 7
			menu[8] = "| очків. Заповнивши  |"; // 8
			menu[9] = "| 4 рядки водночас   |"; // 9
			menu[10] = "| ти отримаєш 1500   |"; // 10
			menu[11] = "| очків загалом.     |"; // 11
			menu[13] = "| Програш настає     |"; // 13
			menu[14] = "| коли минулі блоки  |"; // 14
			menu[15] = "| перекривають місце |"; // 15
			menu[16] = "| появи нових блоків |"; // 16
			menu[20] = "|        Назад       |"; // 20
			buttonsWithArrow.emplace_back("|       >Назад       |");
		}
		buttonsWithoutArrow.push_back(menu[20]);

		chooseParameter(buttonsWithArrow, buttonsWithoutArrow, { 20 });

	}

	void showBackgroundColor1()
	{
		int button = 0;
		while (button == 0)
		{
			button = chooseColor(0);
			if (button == 0)
				showBackgroundColor2();
		}
	}


	void showScoreboard(std::vector<int>& records)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		createBasicMenu();


		if (language == english)
		{
			menu[2] = "|     Scoreboard     |";
			menu[4] = "|====================|";
			menu[20] = "|       >Back        |";
		}
		else
		{
			menu[2] = "|    Твої рекорди    |";
			menu[4] = "|====================|";
			menu[20] = "|       >Назад       |";
		}

		for (int i = 0; i < records.size(); i++)
		{
			std::string temp = std::to_string(records[i]);
			int sizeOfRecord = temp.size();
			int spacesToAdd = (22 - sizeOfRecord) / 2;
			std::string str = "|";
			while (spacesToAdd > 0)
			{
				str += " ";
				spacesToAdd--;
			}
			str += temp;
			while (str.size() < 21)
				str += " ";
			str += "|";

			menu[i + 6] = str;
		}
		renderMenu();
		while (!GetAsyncKeyState(VK_RETURN))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}

	}

	void showBackgroundColor2()
	{
		chooseColorLastPage(0);

	}

	void showTextColor1()
	{
		int button = 0;
		while (button == 0)
		{
			button = chooseColor(1);
			if (button == 0)
				showTextColor2();
		}
	}

	void showTextColor2()
	{
		chooseColorLastPage(1);
	}

	void chooseLanguage()
	{
		createBasicMenu();

		menu[11] = "|      English       |";
		menu[12] = "|      Українська    |";

		std::vector<std::string> buttonsWithArrow;
		std::vector<std::string> buttonsWithoutArrow;
		buttonsWithArrow.emplace_back("|     >English       |");
		buttonsWithArrow.emplace_back("|     >Українська    |");
		buttonsWithoutArrow.push_back(menu[11]);
		buttonsWithoutArrow.push_back(menu[12]);

		int button = chooseParameter(buttonsWithArrow, buttonsWithoutArrow, { 11,12 });

		switch (button)
		{
		case 0:
			language = english;
			break;
		case 1:
			language = ukrainian;
			break;
		}

	}

	void setColors(std::string colors)
	{
		backgroundColor = colors[0];
		textColor = colors[1];
		colors = "color " + colors;
		system(colors.c_str());
	}

	void setLang(Lang l)
	{
		language = l;
	}

	std::string getColors()
	{
		return backgroundColor + textColor;
	}
	Lang getLanguage()
	{
		return language;
	}

	void renderMenu()
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

		for (auto& str : menu)
			std::cout << str << std::endl;
	}
};