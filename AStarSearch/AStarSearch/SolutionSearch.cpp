#include "SolutionSearch.h"


SolutionSearch::SolutionSearch(void)
{
	int ii = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			goalstate.board[i][j] = ii++;
		}

}


SolutionSearch::~SolutionSearch(void)
{
}

bool isLowerFunctionValue(board_state a, board_state b) 
{
	return a.f < b.f;
}

bool SolutionSearch::AStarSearch(int *data, vector<int> &solution)
{
	board_state current;
	board_state start;

	if (!isAvailable(data))
		return false;

	int ii = 0;
	for (int i = 0 ; i < 3 ; i++)
		for (int j = 0; j < 3; j++)
		{
			start.board[i][j] = data[ii++];
		}

	start.moveBlock = -1; // no move from the prev state...
	start.g = 0;
	start.f = start.g + board_state::heuristic(start, goalstate);

	openset.push_back(start);

	while (!openset.empty()) {

		sort(openset.begin(), openset.end(), isLowerFunctionValue);

		current = openset[0]; //select the state having lowest fscore value.

		if (current == goalstate) {
			constructPath(current, solution);
			return true;
		}

		openset.erase(openset.begin());
		closedset.push_back(current);

		addChildren(current);
	}

	return false;
}

void SolutionSearch::addChildren(board_state current) 
{
	int i, j, blankPosI, blankPosJ;

	//Find the position of '8'
	for (i = 0; i< 3; i++)
		for (j = 0; j < 3; j++)
			if (current.board[i][j] == 8)
			{
				blankPosI = i;
				blankPosJ = j;
			}

	i = blankPosI; j = blankPosJ;

	// move the blank to Up...
	if ((i - 1) >= 0) {
		addChild(current, (i - 1), j, blankPosI, blankPosJ);
	}

	// move the blank to Bottom...
	if ((i + 1) < 3) {
		addChild(current, (i + 1), j, blankPosI, blankPosJ);
	}

	// move the blank to Left...
	if ((j - 1) >= 0) {
		addChild(current, i, (j - 1), blankPosI, blankPosJ);
	}

	// move the blank to Right...
	if ((j + 1) < 3) {
		addChild(current, i, (j + 1), blankPosI, blankPosJ);
	}
}

void SolutionSearch::addChild(board_state current, int newI, int newJ, int blankPosI, int blankPosJ)
{
	board_state newstate = current;
	
	int temp;
	temp = newstate.board[newI][newJ];
	newstate.board[newI][newJ] = newstate.board[blankPosI][blankPosJ];
	newstate.board[blankPosI][blankPosJ] = temp;
	newstate.moveBlock = newI * 3 + newJ;
	//newstate.moveBlock = blankPosI * 3 + blankPosJ;

	if (!isIncluded(newstate, closedset)) {

		int gscore = current.g + 1;

		if (!isIncluded(newstate, openset) || gscore < newstate.g) {

			newstate.g = gscore;
			newstate.f = newstate.g + board_state::heuristic(newstate, goalstate);

			board_state *temp = new board_state();
			*temp = current;
			newstate.prevstate = temp;
			openset.push_back(newstate);
		}
	}
}

bool SolutionSearch::isIncluded(board_state currstate, vector<board_state> statelist) 
{
	for (int i = 0; i < statelist.size(); i++)
		if (currstate == statelist[i])
			return true;

	return false;
}

void SolutionSearch::constructPath(board_state current, vector<int> &path) {
	board_state *temp = &current;
	while (temp != NULL) 
	{
		if (temp->moveBlock != -1)
			path.insert(path.begin(), temp->moveBlock);
			
		temp = temp->prevstate;
	}

	
}

// check if the problem is solvable....
bool SolutionSearch::isAvailable(int *data)
{
	int reverse_sum = 0;
	int reverse_count;

	for (int i = 0; i < 9; i++) 
	{
		reverse_count = 0;
		for (int j = i; j < 9; j++) 
		{
			if ((data[j] < data[i]) && (data[j] != 8))
				reverse_count++;
		}
		reverse_sum += reverse_count;
	}

	if (reverse_sum % 2 == 0)
		return true;
	else
		return false;

	return true;
}

