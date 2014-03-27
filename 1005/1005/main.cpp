#include <iostream>
#include <string>
#include <queue>
#include <tchar.h>

using namespace std;

const string description[7] =
{
	"",
	"fill A",
	"fill B",
	"empty A",
	"empty B",
	"pour A B",
	"pour B A"
};

enum Action
{
	NONE = 0,
	FILL_A,
	FILL_B,
	EMPTY_A,
	EMPTY_B,
	POUR_A_B,
	POUR_B_A
};

struct State
{
	int A;
	int B;
	State * LastState;
	Action LastAction;

	bool operator== (const State & state) const
	{
		return A == state.A && B == state.B;
	}
};

bool IsVisit(State * state, vector< State *> & states)
{
	vector <State *>::iterator ite = states.begin();
	vector <State *>::iterator end = states.end();
	while (ite != end)
	{
		if (*state == *(*ite))
			return true;
		++ite;
	}
	return false;
}

bool IsSuccess(const State * state, int goal)
{
	return state->B == goal;
}

void StoreState(State * last_state, State * state, vector < State *> & visited, queue< State *> & q, Action action)
{
	if (!IsVisit(state, visited))
	{
		state->LastState = last_state;
		state->LastAction = action;
		q.push(state);
		visited.push_back(state);
	}
}

int _tmain(int argc, _TCHAR * argv[])
{
	int A, B, goal;
	vector <State *> visited;
	queue <State *> q;
	while (cin >> A >> B >> goal)
	{
		State * empty_state = new State();
		State * next_state = NULL;
		empty_state->A = empty_state->B = 0;
		empty_state->LastAction = NONE;
		visited.push_back(empty_state);
		q.push(empty_state);

		while (!q.empty())
		{
			State * current_state = q.front();
			q.pop();

			// Fill A
			if (current_state->A < A)
			{
				next_state = new State();
				next_state->A = A;
				next_state->B = current_state->B;
				StoreState(current_state, next_state, visited, q, FILL_A);
				if (IsSuccess(next_state, goal))
					break;
			}
			// Fill B
			if (current_state->B < B)
			{
				next_state = new State();
				next_state->A = current_state->A;
				next_state->B = B;
				StoreState(current_state, next_state, visited, q, FILL_B);
				if (IsSuccess(next_state, goal))
					break;
			}
			// Empty A
			if (current_state->A != 0)
			{
				next_state = new State();
				next_state->A = 0;
				next_state->B = current_state->B;
				StoreState(current_state, next_state, visited, q, EMPTY_A);
				if (IsSuccess(next_state, goal))
					break;
			}
			// Empty B
			if (current_state->B != 0)
			{
				next_state = new State();
				next_state->A = current_state->A;
				next_state->B = 0;
				StoreState(current_state, next_state, visited, q, EMPTY_B);
				if (IsSuccess(next_state, goal))
					break;
			}
			// Pour A B
			if (current_state->A != 0 && current_state->B != B)
			{
				next_state = new State();
				int diff = B - current_state->B;
				int poured = min(current_state->A, diff);
				next_state->B = current_state->B + poured;
				next_state->A = current_state->A - poured;
				StoreState(current_state, next_state, visited, q, POUR_A_B);
				if (IsSuccess(next_state, goal))
					break;
			}
			// Pour B A
			if (current_state->B != 0 && current_state->A != A)
			{
				next_state = new State();
				int diff = A - current_state->A;
				int poured = min(current_state->B, diff);
				next_state->A = current_state->A + poured;
				next_state->B = current_state->B - poured;
				StoreState(current_state, next_state, visited, q, POUR_B_A);
				if (IsSuccess(next_state, goal))
					break;
			}
		}
		vector <Action > action_list;
		State * temp_state = next_state;
		while (temp_state->LastAction != NONE)
		{
			action_list.push_back(temp_state->LastAction);
			temp_state = temp_state->LastState;
		}
		vector <Action >::reverse_iterator r_ite = action_list.rbegin();
		vector <Action >::reverse_iterator r_end = action_list.rend();
		while (r_ite != r_end)
		{
			cout << description[(int)(*r_ite)] << endl;
			++r_ite;
		}
		cout << "success" << endl;
		delete empty_state, next_state;
		visited.clear();
		while (!q.empty())
			q.pop();
	}
	return 0;
}
