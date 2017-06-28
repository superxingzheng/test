/*
 *  main.cpp
 *  updated on June 27, 2017
 *  updated by Zheng Xing <zxing@robohome.org>
 *  
 *  C++11 required
 */

#include <iostream>
#include <algorithm>
#include <vector>

class state {
public:
	state() {
		capital = 0;
		value = 0.0;
		best_action = 0;
	}
	
	int capital;
	float value;
	int best_action;
};

std::vector<int> generate_action_set(state s) {
	using namespace std;

	int max_stake = min(s.capital, 100 - s.capital);

	vector<int> action_set(max_stake + 1);

	for (int i = 0; i < action_set.size(); i++) {
		action_set[i] = i;
	}

	return action_set;
}

// Update state value using "value iteration".
std::vector<state> update_state_value(const std::vector<state> &current_state_space, float &delta) {
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
	
	vector<state> new_state_space(current_state_space.size());

	vector<int> action_set;

	float max_new_state_value = 0.0;
	
	float state_value_delta = 0.0;
	float max_state_value_delta = 0.0;
	
	// for each state in the state space
	// {1, 2, ... , 99}
	for (int i = 1; i < 100; i++) {
		action_set = generate_action_set(current_state_space[i]);
		
		// for each action in the action_set
		// {0, 1, ... , min(s, 100-s)}
		// where s represents state_space[i]
		for (vector<int>::iterator act = action_set.begin(); act != action_set.end();
				act++) {
			int next_state_head_capital = current_state_space[i].capital + *act; // when the coin is head, next state equals current state plus stake (*act)
			int next_state_tail_capital = current_state_space[i].capital - *act; // when the coin is tail, next state equals current state minus stake (*act)
			
			next_state_head_value = current_state_space[next_state_head_capital].value;
			next_state_tail_value = current_state_space[next_state_tail_capital].value;
			
			if (next_state_head_capital != 100) {
				head_reward = zero_reward;
			} else {
				head_reward = winning_reward;
			}
			
			// for this action
			new_state_value = head_probability * (head_reward + next_state_head_value) + tail_probability * (tail_reward + next_state_tail_value);
			
			if (new_state_value >= max_new_state_value) {
				max_new_state_value = new_state_value;
				new_state_space[i].best_action = *act;
				new_state_space[i].value = max_new_state_value;
			} else {
				// when the action does not bring higher state value, ignore that action
				// this can be changed to encourage exploration
			}
		}
		
		state_value_delta = abs(current_state_space[i].value - new_state_space[i].value);
		
		if (state_value_delta >= max_state_value_delta) {
			max_state_value_delta = state_value_delta;
		}
	}
	
	// return delta by reference
	delta = max_state_value_delta;

	return new_state_space;
}

int value_iteration(std::vector<state> &state_space){
	float delta = 0.0;
	
	/*do {
		state_space = update_state_value(state_space, delta);
	} while (delta >= 0.1);*/
	
	for (int i = 0; i < 10; i++) {
		state_space = update_state_value(state_space, delta);
	}
	
	return 0;
}

int main(int argc, char** argv) {
	using namespace std;

	// Generating the state space.
	// {1, 2, ... , 99} plus two dummy state 0 and 100
	vector<state> state_space(101);
	
	state_space[0].capital = 0;
	state_space[0].value = 0;
	state_space[0].best_action = 0;
	
	state_space[100].capital = 100;
	state_space[100].value = 1;
	state_space[100].best_action = 0;
	
	for (int i = 1; i <= 99; i++) {
		state_space[i].capital = i;
		state_space[i].value = 0; // initializing state values to zeros
		state_space[i].best_action = 0; // start with putting 0 stake on all states as the initial policy
	}

	// Create the state values and initialize every one to zero.
	//vector<float> value(99);
	//fill(value.begin(), value.end(), 0);

	value_iteration(state_space);
	
	for (int i = 1; i < 100; i++) {
		cout << state_space[i].best_action << endl;
	}
	
	return 0;
}
