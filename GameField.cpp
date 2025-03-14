#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <chrono>
enum TypesOfBlock { stick = 0, cube = 1, L = 2, reverseL = 3, z = 4, reverseZ = 5, piramid = 6 };
enum direction { left = 0, right = 1};
class Field
{
private:
	std::vector<std::string> field;
	
	TypesOfBlock nextBlock;
public:
	Field()
	{
		resetField();
	}

	void resetField()
	{
		field.clear();

		field.emplace_back("######################");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |  score: ");
		field.emplace_back("|                    |  next block:");
		field.emplace_back("|                    |   =======");
		field.emplace_back("|                    |   |     |"); // 5
		field.emplace_back("|                    |   |     |"); // 8
		field.emplace_back("|                    |   |     |"); // 6
		field.emplace_back("|                    |   |     |"); // 7
		field.emplace_back("|                    |   =======");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("|                    |");
		field.emplace_back("######################");
	}

	void renderField(std::vector<std::pair<int, int>>& block, int score)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

		std::vector<std::string> f(field);

		for (auto& coords : block)
			f[coords.first][coords.second] = '#';

		f[2] += std::to_string(score);

		for (std::string& str : f)
			std::cout << str << std::endl;
	}

	void drawBlockInField(std::vector<std::pair<int, int>>& block)
	{
		for (auto& coords : block)
			field[coords.first][coords.second] = '#';
	}

	const std::vector<std::string>& getBody()
	{
		return field;
	}

	void isCompletedRow(int& score)
	{
		int completedRows = 0;
		int max = INT_MIN;

		for (int i = field.size() - 2; i > 1; i--)
		{
			bool completeRow = true;
			for (int j = 1; j < 21; j++)
			{
				if (field[i][j] != '#')
				{
					completeRow = false;
					break;
				}

			}
			if (completeRow)
			{
				if (i > max)
					max = i;
				completedRows++;
				for (int index = max; index > 2; index--)
				{
					for (int j = 1; j < 22; j++)
						field[index][j] = field[index - 1][j];
				}
				i++;
			}

		}

		score += completedRows == 4 ? 1500 : completedRows * 250;
	}

	void setNewNextBlock(int type)
	{
		nextBlock = TypesOfBlock(type);

		for (int i = 5; i < 9; i++)
			for (int j = 26; j < 31; j++)
				field[i][j] = ' ';

		switch (nextBlock)
		{
		case stick:
			field[5][28] = '#';
			field[6][28] = '#';
			field[7][28] = '#';
			field[8][28] = '#';
			break;
		case L:
			field[5][28] = '#';
			field[6][28] = '#';
			field[7][28] = '#';
			field[7][29] = '#';
			break;
		case reverseL:
			field[5][28] = '#';
			field[6][28] = '#';
			field[7][28] = '#';
			field[7][27] = '#';
			break;
		case z:
			field[6][28] = '#';
			field[6][29] = '#';
			field[7][29] = '#';
			field[7][30] = '#';
			break;
		case reverseZ:
			field[6][28] = '#';
			field[6][29] = '#';
			field[7][28] = '#';
			field[7][27] = '#';
			break;
		case piramid:
			field[5][28] = '#';
			field[6][27] = '#';
			field[6][28] = '#';
			field[6][29] = '#';
			break;
		case cube:
			field[5][27] = '#';
			field[5][28] = '#';
			field[6][27] = '#';
			field[6][28] = '#';
			break;
		}
	}

	TypesOfBlock& getNextBlock()
	{
		return nextBlock;
	}

	bool isCollide(std::vector<std::pair<int, int>>& block)
	{
		for (auto& coords : block)
		{
			if (field[coords.first + 1][coords.second] == '#' || field[coords.first + 1][coords.second] == '|')
				return true;
		}
		return false;
	}

	bool isCollideLeftOrRight(std::vector<std::pair<int,int>>& block, direction dir)
	{
		int number = 1;
		if (dir == left)
			number = -1;

		for (auto& coords : block)
		{
			if (field[coords.first][coords.second + number] == '#' || field[coords.first][coords.second + number] == '|')
				return true;
		}
		return false;
	}


};