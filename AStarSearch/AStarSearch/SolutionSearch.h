
/* This is the main class that you need to modify. Basically you need to implement the BFS and DFS search algorithms */
/* To make the code compatible, different search algorithms have the same input and output parameters                */

#pragma once

#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>

using namespace std;

class board_state {

public:
	int board[3][3];
	int g, f;
	int moveBlock;

	board_state *prevstate;

	board_state() {
		g = 0;
		f = 0;
		prevstate = NULL;
	}

	static int heuristic(board_state from, board_state to) {
		int i, j, dist = 0;
		for (i = 0; i< 3; i++)
			for (j = 0; j< 3; j++)
				if (from.board[i][j] != to.board[i][j])
					dist++;
		return dist;
	}

	bool operator ==(board_state a) {
		for (int i = 0; i< 3; i++)
			for (int j = 0; j< 3; j++)
				if (this->board[i][j] != a.board[i][j])
					return false;
		return true;
	}
};


class SolutionSearch
{
private:
	board_state goalstate;
	vector<board_state> output;
	vector<board_state> closedset;
	vector<board_state> openset;

private:
	void addChildren(board_state current);
	void addChild(board_state current, int newI, int newJ, int blankPosI, int blankPosJ);
	bool isIncluded(board_state currstate, vector<board_state> statelist);
	void constructPath(board_state current, vector<int> &path);
	bool isAvailable(int *data);
public:
	SolutionSearch(void);
	~SolutionSearch(void);

	bool AStarSearch(int *data, vector<int> &solution);	//Student Implementation: you need to implement this function	
};

