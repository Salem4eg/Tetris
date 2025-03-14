#pragma once
#include <vector>
#include <string>
#include <Windows.h>

#include "GameField.cpp"




class Player
{
private:
	std::vector<std::pair<int, int>> block;
	TypesOfBlock blockType;
	int stateOfRotate;

public:
	Player(Field& field)
	{
		field.setNewNextBlock(getRandomNumber(7));
	}
	void rotateBlock(Field& field)
	{

		std::vector<std::vector<std::pair<int, int>>> coords;
		auto temp = block;

		switch (blockType)
		{
		case L:
			coords.push_back({ {1,1}, {1,-1}, {-1,-1}, {-1,1} });
			coords.push_back({ {0,0}, {0,0}, {0,0}, {0,0} });
			coords.push_back({ {-1,-1}, {-1,1}, {1,1}, {1,-1} });
			coords.push_back({ {0, -2}, {-2, 0}, {0,2}, {2,0} });
			break;

		case reverseL:
			coords.push_back({ {1,1}, {1,-1}, {-1,-1}, {-1,1} });
			coords.push_back({ {0,0}, {0,0}, {0,0}, {0,0} });
			coords.push_back({ {-1,-1}, {-1,1}, {1,1}, {1,-1} });
			coords.push_back({ { -2,0}, {0,2}, {2,0}, {0,-2} });
			break;

		case stick:
			coords.push_back({ {2,-1}, {-2,1},{2,-1}, {-2,1} });
			coords.push_back({ {1,0},{-1,0},{1,0},{-1,0} });
			coords.push_back({ {0,1},{0,-1},{0,1},{0,-1} });
			coords.push_back({ {-1,2},{1,-2},{-1,2},{1,-2} });
			break;

		case cube:
			coords.push_back({ {0,0},{0,0},{0,0},{0,0} });
			coords.push_back({ {0,0},{0,0},{0,0},{0,0} });
			coords.push_back({ {0,0},{0,0},{0,0},{0,0} });
			coords.push_back({ {0,0},{0,0},{0,0},{0,0} });
			break;

		case z:
			coords.push_back({ {1,0}, {-1,0}, {1,0}, {-1,0} });
			coords.push_back({ {0,-1}, {0, 1}, {0,-1}, {0,1} });
			coords.push_back({ {-1,0}, {1,0}, {-1,0}, {1,0} });
			coords.push_back({ {-2,-1},{2,1},{-2,-1},{2,1} });
			break;

		case reverseZ:
			coords.push_back({ {1,-1}, {-1,1},{1,-1}, {-1,1} });
			coords.push_back({ {0,0},{0,0},{0,0},{0,0} });
			coords.push_back({ {-1,-1},{1,1},{-1,-1},{1,1} });
			coords.push_back({ {-2,0},{2,0},{-2,0},{2,0} });
			break;
		case piramid:
			coords.push_back({ {1,1}, {1,-1}, {-1,-1}, {-1,1} });
			coords.push_back({ {-1,1}, {1, -1},{-1,1}, {1, -1} });
			coords.push_back({ {0,0},{0,0},{0,0},{0,0} });
			coords.push_back({ {1,-1},{-1,1},{1,-1},{-1,1} });
			break;
		}


		for (int i = 0; i < 4; i++)
		{
			temp[i].first += coords[i][stateOfRotate].first;
			temp[i].second += coords[i][stateOfRotate].second;
		}

		if (!field.isCollide(temp))
		{
			block = temp;
			stateOfRotate = ++stateOfRotate % 4;
		}


	}

	void handleInput(Field& field)
	{

		if (GetAsyncKeyState('W')) // rotate clockwise
		{
			rotateBlock(field);
		}
		else if (GetAsyncKeyState('A')) // go left
		{
			if (!field.isCollideLeftOrRight(block,left))
				for (auto& coords : block)
					coords.second--;
		}
		else if (GetAsyncKeyState('D')) // go right
		{
			if (!field.isCollideLeftOrRight(block, right))
				for (auto& coords : block)
					coords.second++;
		}
		else if (GetAsyncKeyState('S'))
		{
			if (!field.isCollide(block))
				gravity();
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			while (!field.isCollide(block))
				gravity();
		}
	}

	void gravity()
	{
		int force = 1;
		for (auto& coords : block)
			coords.first += force;
	}

	void obtainNewBlock(Field& field)
	{
		block.clear();

		switch (field.getNextBlock())
		{
		case 0: // stick
			block.emplace_back(1, 10);
			block.emplace_back(2, 10);
			block.emplace_back(3, 10);
			block.emplace_back(4, 10);
			blockType = stick;
			break;
		case 1: // cube
			block.emplace_back(1, 10);
			block.emplace_back(1, 11);
			block.emplace_back(2, 10);
			block.emplace_back(2, 11);
			blockType = cube;
			break;
		case 2: // L

			block.emplace_back(1, 10);
			block.emplace_back(2, 10);
			block.emplace_back(3, 10);
			block.emplace_back(3, 11);
			blockType = L;
			break;
		case 3: // reverse L
			block.emplace_back(1, 10);
			block.emplace_back(2, 10);
			block.emplace_back(3, 10);
			block.emplace_back(3, 9);
			blockType = reverseL;
			break;
		case 4: // Z
			block.emplace_back(1, 10);
			block.emplace_back(1, 11);
			block.emplace_back(2, 11);
			block.emplace_back(2, 12);
			blockType = z;
			break;
		case 5: // reverse Z
			block.emplace_back(1, 11);
			block.emplace_back(1, 10);
			block.emplace_back(2, 10);
			block.emplace_back(2, 9);
			blockType = reverseZ;
			break;
		case 6: // piramid
			block.emplace_back(1, 10);
			block.emplace_back(2, 9);
			block.emplace_back(2, 10);
			block.emplace_back(2, 11);
			blockType = piramid;
			break;
		}

		field.setNewNextBlock(getRandomNumber(7));

		stateOfRotate = 0;
	}



	int getRandomNumber(int max)
	{
		// get the current time
		const auto now = std::chrono::system_clock::now();

		// transform the time into a duration since the epoch
		const auto epoch = now.time_since_epoch();

		// cast the duration into seconds
		const auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
		return seconds.count() % max;
	}

	std::vector<std::pair<int, int>>& getBlock()
	{
		return block;
	}
};