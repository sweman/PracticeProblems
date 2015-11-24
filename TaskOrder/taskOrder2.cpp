// TaskOrder.cpp 
//
// This program finds an order for running given set of tasks according
// to the rules provided. 
// Task rules are represented in a vector of dependency lists for the N tasks.
// Each entry represents a target task (T0) with the list of the tasks that T0 
// is dependent on, i.e., the list at index i of the dependencyList vector will 
// contain entries representing the tasks that task i is dependent on.

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>

using namespace std;

// to save some key strokes
typedef vector< list<unsigned int> > dependencyList;

// Prints tasks in an order that satisfies the given rules.
// Iterates over the list of tasks and prints the task that is not
// blocked by any other task. When a task is unblocked/printed,
// it updates the dependency lists of other tasks.
void printTaskOrder(dependencyList& dependList, vector<bool>& blocked)
{
	unsigned int numPrinted = 0;
	vector<bool> printed(dependList.size());

	// iterate over all target tasks
	unsigned int i = 1; // using 1-based indices for convenience
	while (numPrinted < dependList.size()-1) {

		if (blocked[i]) {
			// This task (T0) is blocked, let's see if any of the tasks it depends on 
			// is unblocked. If we find an unblocked task then we remove it from
			// this task's dependency list. If no blocked tasks remains in this 
			// list then we will unblock/print the current task as well.
			while (!dependList[i].empty()) {
				unsigned int task = dependList[i].front();
				if (!printed[task]) {
					// dependent on a task that is not yet printed, so can't print this one yet. Go check the next task
					break;
				}
				else {
					// the task on which this task (T0) depends is not blocked, so remove it from T0's dependency list
					dependList[i].pop_front();
				}
			}
			if (dependList[i].empty()) {
				blocked[i] = false;
				cout << i << " ";
				printed[i] = true;
				numPrinted++;
				// we just unblocked the current task so now go start checking
				// from the beginning of the dependency list to see
				// what tasks got unblocked by the current task getting 
				// unblocked. This is to fulfill the requirement that if
				// tasks are not dependent on each other then the 
				// lower-numbered task should be printed first.
				i = 1;
				continue;
			}
		}
		else {
			// not blocked, print it of not already printed
			if (!printed[i]) {
				cout << i << " ";
				printed[i] = true;
				numPrinted++;
			}

		}
        if (++i > dependList.size() - 1) i = 1;  // check next target task (T0)
	}
	cout << endl;
}

// Reads task dependencies from stdin and populates the passed-in 
// task dependency list and blocked flags
// Each input line is of the form ...
// T0 k T1 T2 ... Tk
// ... indicating Task T0 depends on k tasks: T0 - Tk
void getRules(unsigned int numRules, dependencyList& dependList, vector<bool>& blocked)
{
	while (numRules > 0) {
		string line;
		unsigned int T0;   // target task
		unsigned int k;    // number of tasks the current task depends on

		getline(cin, line);
		istringstream input(line);

		input >> T0 >> k;
		// read the k tasks that T0 depends on
		for (unsigned int i = 0; i < k; i++) {
			unsigned int Tk; // task on which T0 depends
			input >> Tk;
			dependList[T0].push_front(Tk);
		}
		if (dependList[T0].size() > 0) {
			blocked[T0] = true;
		}
		numRules--;
	}
}

int main(int argc, char* argv[])
{
	unsigned int N; // number of tasks
	unsigned int M; // number of rules

	cin >> N >> M;

	// consume the previous new line character so that it does not interfere with subsequent input
	cin.ignore(256, '\n');

	// create a vector of N lists (N+1, actually, so we can use 1-based indices for convenience)
	// Each list in the vector at index i represents task i's dependency list.
	dependencyList taskDependencyList(N + 1);
	// flag at index i indicates whether task i is currently blocked
	vector<bool> blocked(N + 1);

	// Read rules from stdin
	getRules(M, taskDependencyList, blocked);
	
	// print the tasks in an order that follows the given rules 
	printTaskOrder(taskDependencyList, blocked);

	return 0;
}


