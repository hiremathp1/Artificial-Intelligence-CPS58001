//
//  MDP.cpp
//  AI_GridWorld
//

//

#include <stdio.h>

#include "MDP.h"


/*************************************************************** Below are the two functions you need to implement ****************************************************/


/*Compute a Q-value for a given state and its action
  Input: state variable s; action (go to East/North/West/South), the corresponding interger value for each action is defined in the "MDP.h" Macros definition on the top
  Output: you need to update the corresponding q_values of the input state variable s
 */
void MDP::computeQValue(State &s, const int action)
{
	auto getDelta = [](int action) -> Point{
		switch (action)
		{
		case ACTION_EAST:
			return Point(1, 0);
		case ACTION_SOUTH:
			return Point(0, -1);
		case ACTION_WEST:
			return Point(-1, 0);
		case ACTION_NORTH:
			return Point(0, 1);
		}
	};

	auto T = [getDelta](const State& s, const int action, const State& s1) -> float {
		Point d = s1.location - s.location;

		if (getDelta(action) == d)
			return TRANSITION_SUCCEED;
		else
			if (getDelta(action) == -1 * d)
				return 0;
			else
				return TRANSITION_FAIL / 2;
	};

	auto getState = [getDelta, this](const State& s, int action) -> State {
		Point d = getDelta(action);
		Point pos = s.location + d;
		if (pos.x < 0 || pos.y < 0 || pos.x > 3 || pos.y > 2 || pos == Point(1, 1))
			pos = s.location;

		return states[pos.y][pos.x];
	};

	auto reward = [](const State& s1) -> float {
		float output = ACTION_REWARD;

		if (s1.location == Point(1, 3))
			output += 1;
		if (s1.location == Point(2, 3))
			output -= 1;

		return output;
	};

	float res = 0;

	for (int i = 0; i < 4; i++)
	{
		State s1 = getState(s, i);
		//State s1 = states[s1_p.x][s1_p.y];
		res += T(s, i, s1)*(reward(s1) + GAMMA * s1.q_values[i]);
	}

	s.q_values[action] = res;
}



/*There is no return value, actually you need to use the computing result to update the state values of all the states defined as data member "State states[3][4]". Of course, you don't need to update the wall state: states[1][1], the diamond state: states[0][3], and pitfall state: states[1][3] */
void MDP::valueIteration()
{
	for (auto &row : states)
	{
		for (auto &el : row)
		{
			for (int i = 0; i < 4; i++)
				computeQValue(el, i);
		}
	}
}


/**********************************************************************	End of Assignment *********************************************************************/


MDP::MDP()
{
    /*Initialize all the state with 0.0 state_value and 0.0 Q_values*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            states[y][x].location.x = x; //specify the location for this state
            states[y][x].location.y = y;

            states[y][x].state_value = 0.0; //define the state value
            states[y][x].q_values[0] = 0.0; //define the Q value
            states[y][x].q_values[1] = 0.0;
            states[y][x].q_values[2] = 0.0;
            states[y][x].q_values[3] = 0.0;
        }
    }

    /* Reset the values for the two special states: diamonds (0, 3), pitfall (1, 3). Actually there are no Q-values for these two states as these two states represents the final state of the game. Similarly, for the wall (1, 1), it does not have any state value or Q values. So make sure not to update these three states during your program*/
    states[0][3].state_value = 1.0;
    states[1][3].state_value = -1.0;



    /*Set the current convergence to a big number initially*/
    cur_convergence = 100; //the reason this value is set to a big value is to ensure


}


MDP::~MDP()
{

}

/*Reset the current computed state and Q values*/
void MDP::resetData()
{
    /*Initialize all the state with 0.0 state_value and 0.0 Q_values*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            states[y][x].location.x = x; //specify the location for this state
            states[y][x].location.y = y;

            states[y][x].state_value = 0.0; //define the state value
            states[y][x].q_values[0] = 0.0; //define the Q value
            states[y][x].q_values[1] = 0.0;
            states[y][x].q_values[2] = 0.0;
            states[y][x].q_values[3] = 0.0;
        }
    }

    /* Reset the values for the two special states: diamonds (0, 3), pitfall (1, 3). Actually there are no Q-values for these two states as these two states represents the final state of the game. Similarly, for the wall (1, 1), it does not have any state value or Q values. So make sure not to update these three states during your program*/
    states[0][3].state_value = 1.0;
    states[1][3].state_value = -1.0;



    /*Set the current convergence to a big number initially*/
    cur_convergence = 100; //the reason this value is set to a big value is to ensure


}
