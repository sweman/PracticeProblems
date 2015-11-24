// TaskOrder.cpp 
//
// This program finds an order for running given set of tasks according
// to the rules provided. 
// Task rules are represented in a NxN matrix for the N tasks.
// Each row represents a target task (T0) with the columns of that row 
// indicating tasks that T0 may be dependent on. If a column j is set in 
// row i then that means task i is blocked on task j (i.e., task j must 
// run before task i can run).

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// to save some key strokes
typedef vector< vector<unsigned int> > matrix;

// Prints tasks in an order that satisfies the given rules.
// Iterates over the list of tasks and prints the task that is not
// blocked by any other task. Once a task is printed, it removes the 
// dependency of all other blocks on the just completed/printed task.

void printTaskOrder(matrix& m)
{
	unsigned int i = 0;
	unsigned int numPrinted = 0;
	// iterate over all target tasks
	while (numPrinted < m.size()) {
		// check if the current task is depenedent on any tasks
		unsigned int j = 0;
		for (; j < m.size(); j++){
			if (m[i][j] != 0) {
				// this task is dependent on another still-unrun task, so skip it
				break;
			}
		}
		if (j == m.size()) {
			// this task (row) is not blocked by any other task
			// so print this task and also remove the dependency of all 
			// the other tasks on this task (clear the column)
			cout << i + 1 << " "; // make output 1-based
            numPrinted++;
			// remove dependencies of other tasks on this task (clear the 
			// column corresponding to this task)
			for (unsigned int k = 0; k < m.size(); k++) {
				m[k][i] = 0;
			}
			// We just completed this task. So make this task dependent on itself to prevent 
			// this task from being considered again (otherwise we have an infinite loop)
			m[i][i] = 1; 
//			i = 0;       // start looking at tasks from the beginning as earlier tasks may have now become unblocked
//			continue;    // start next iteration of while loop (with i = 0)
		}
		if(++i == m.size()) i = 0;  // check next target task (row)
	}
	cout << endl;
}
// Reads task dependencies from stdin and populates the passed-in 
// task dependency matrix
// Each input line is of the form ...
// T0 k T1 T2 ... Tk
// ... indicating Task T0 depends on k tasks: T0 - Tk
void getRules(unsigned int numRules, matrix& taskDependMatrix)
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
			taskDependMatrix[T0-1][Tk-1] = 1;  // make indices 0-based
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
	
	// create an NxN matrix. Each row represents a task T0. The columns of the row represent
	// the tasks that T0 is dependent upon
	matrix taskDependencyMatrix (N, vector<unsigned int> (N) );

	getRules(M, taskDependencyMatrix);

	printTaskOrder(taskDependencyMatrix);

	return 0;
}

