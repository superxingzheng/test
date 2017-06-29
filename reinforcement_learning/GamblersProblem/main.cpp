/*
 *  main.cpp
 *  updated on June 27, 2017
 *  updated by Zheng Xing <zxing@robohome.org>
 *  
 *  C++11 required
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class State {
public:
	State() {
		capital = 0;
		value = 0.0;
		best_action = 0;
	}

	int capital;
	float value;
	int best_action;
};

std::vector<int> generate_action_set(State s) {
	using namespace std;

	int max_stake = min(s.capital, 100 - s.capital);

	vector<int> action_set(max_stake + 1);

	for (int i = 0; i < action_set.size(); i++) {
		action_set[i] = i;
	}

	return action_set;
}

// Update state value using "value iteration".
std::vector<State> update_state_value(
		const std::vector<State> &current_experience, float &delta) {
	using namespace std;

	// in this case, probability p(s',r|s,a) does not depend on which action to take
	float head_probability = 0.4;
	float tail_probability = 0.6;
	float zero_reward = 0.0;
	float winning_reward = 1.0;

	float head_reward = zero_reward;
	float tail_reward = zero_reward;

	float new_state_value = 0.0;
	float next_state_head_value = 0.0;
	float next_state_tail_value = 0.0;

	vector<State> new_experience = current_experience;

	vector<int> action_set;

	// this is used to select the best action for each state (policy improvement)
	float max_new_state_value = 0.0;

	float state_value_delta = 0.0;
	float max_state_value_delta = 0.0;

	// for each state in the state space
	// {1, 2, ... , 99}
	for (int i = 1; i < 100; i++) {
		action_set = generate_action_set(current_experience[i]);

		/*if (i == 50) {
		 cout << "Action Set for Capital = " << current_experience[i].capital
		 << endl;
		 for (vector<int>::iterator it = action_set.begin();
		 it != action_set.end(); ++it) {
		 cout << *it << endl;
		 }
		 }*/

		// reset this to select the best action for this state
		max_new_state_value = 0.0;
		// for each action in the action_set
		// {0, 1, ... , min(s, 100-s)}
		// where s represents experience[i].capital
		for (vector<int>::iterator act = action_set.begin();
				act != action_set.end(); ++act) {
			// when the coin is head, next state equals current state plus stake (*act)
			int next_state_head_capital = current_experience[i].capital + *act;
			// when the coin is tail, next state equals current state minus stake (*act)
			int next_state_tail_capital = current_experience[i].capital - *act;

			//if (i == 50) {
			// cout << "action = " << *act << endl;
			// cout << "next_state_head_capital = " << next_state_head_capital << endl;
			// cout << "next_state_tail_capital = " << next_state_tail_capital << endl;
			// }

			next_state_head_value =
					current_experience[next_state_head_capital].value;
			next_state_tail_value =
					current_experience[next_state_tail_capital].value;

			//if (i == 50) {
			// cout << "action = " << *act << endl;
			// cout << "next_state_head_value = " << next_state_head_value << endl;
			// cout << "next_state_tail_value = " << next_state_tail_value << endl;
			// }
			
			// NOTE: The reward gained by getting to the goal state is +1.
			// but we should not add the reward +1 to the transition if we set
			// the value of the goal state to +1.
			if (next_state_head_capital == 100) {
				head_reward = zero_reward;
				//cout << "next_state_head_capital == 100" << endl;
			} else {
				head_reward = zero_reward;
				// tail_reward is always zero.
			}

			// with taking this action, calculate the new state value
			new_state_value = head_probability
					* (head_reward + next_state_head_value)
					+ tail_probability * (tail_reward + next_state_tail_value);

			//if (i == 50) {
			//if (new_state_value != 0) {
			//	cout << "new_state_value = " << new_state_value << endl;
			//}

			if (new_state_value > max_new_state_value) {
				//cout << "new_state_value > max_new_state_value " << endl;
				//cout << "new_state_value = " << new_state_value << endl;
				max_new_state_value = new_state_value;

				new_experience[i].best_action = *act;
				new_experience[i].value = max_new_state_value;
			} else {
				// when the action does not bring higher state value, ignore that action
				// this can be changed to encourage exploration
			}
		}

		state_value_delta = abs(
				current_experience[i].value - new_experience[i].value);

		if (state_value_delta > max_state_value_delta) {
			max_state_value_delta = state_value_delta;
		}

		//cout << "current_experience[" << i << "].value = "
		//		<< current_experience[i].value << endl;
		//cout << "new_experience[" << i << "].value = "
		//		<< new_experience[i].value << endl;
		//cout << "new_experience[" << i << "].best_action = "
		//		<< new_experience[i].best_action << endl;
	}

	// return delta by reference
	delta = max_state_value_delta;
	cout << "delta = " << delta << endl;

	return new_experience;
}

int value_iteration(std::vector<State> &experience) {
	using namespace std;

	float delta = 0.0;

	/*int i = 1;
	 do {
	 i++;
	 cout << endl << "Value Iteration #" << i << " ......" << endl;
	 experience = update_state_value(experience, delta);
	 } while (delta >= 0.000001);*/

	for (int i = 0; i < 20; i++) {
		cout << endl << "Value Iteration #" << i << " ......" << endl;
		experience = update_state_value(experience, delta);

		/*for (int i = 0; i < 101; i++) {
			cout << experience[i].capital << ' ' << experience[i].value << ' '
					<< experience[i].best_action << endl;
		}*/
	}

	return 0;
}

int updateFile(std::string path, std::vector<State> &s) {
	using namespace std;
	ofstream output;

	output.open(path);

	for (int i = 0; i < 101; i++) {
		output << s[i].capital << ',' << s[i].value << ',' << s[i].best_action
				<< endl;
	}

	output.close();

	return 0;
}

int main(int argc, char** argv) {
	using namespace std;

	// Generating the state space.
	// {1, 2, ... , 99} plus two dummy state 0 and 100
	//
	// With the State class as the type of each element in a vector,
	// The states (capital), the values of the states and the best actions
	// are stored in a 101 by 3 matrix.
	// The state of 0 capital and the state of 100 capital are added as
	// termination state. Their values are always 0 and 1.
	vector<State> experience(101);

	experience[0].capital = 0;
	experience[0].value = 0;
	experience[0].best_action = 0;

	experience[100].capital = 100;
	experience[100].value = 1;
	experience[100].best_action = 0;

	for (int i = 1; i <= 99; i++) {
		experience[i].capital = i;
		// initializing state values to zeros
		experience[i].value = 0;
		// start with putting 0 stake on all states as the initial policy
		experience[i].best_action = 0;

		/*cout << experience[i].capital << ' ' << experience[i].value << ' '
		 << experience[i].best_action << endl;*/
	}

	if (-1 == value_iteration(experience)) {
		cerr << "Error: " << endl;
		exit (EXIT_FAILURE);
	}

	/*for (int i = 0; i < 101; i++) {
	 cout << experience[i].capital << ',' << experience[i].value << ','
	 << experience[i].best_action << endl;
	 }*/

	if (-1 == updateFile("../result.csv", experience)) {
		cerr << "Error: " << endl;
		exit (EXIT_FAILURE);
	}

	return 0;
}
