// TaskOrder3.cpp (uses DFS) 
//
// This program finds an order for running given set of tasks according
// to the rules provided. 
// Task rules are represented in a vector of dependency lists for the N tasks.
// Each entry represents a target task (T0) with the list of the tasks that T0 
// is dependent on, i.e., he list at index i of the dependencyList vector will 
// contain entries representing the tasks that task i is dependent on.
/*
Problem Title: Project File Dependencies
Project managers, such as the UNIX utility make, are used to maintain large software projects made up
from many components. Users write a project file specifying which components (called tasks) depend on
others and the project manager can automatically update the components in the correct order.
Write a program that reads a project file from stdin and writes to stdout the order in which the tasks
should be performed.
Input
For simplicity we represent each task by an integer number from where is the total number
of tasks. The first line of input specifies the number of tasks and the number of rules, such that
and .
The rest of the input consists of rules, one in each line, specifying dependencies using the following
syntax:
This rule means that task number depends on tasks (we say that task is the target
and are dependents).
Note that tasks numbers are separated by single spaces and that rules end with a newline. Rules can
appear in any order, but each task can appear as target only once.
Your program can assume that there are no circular dependencies in the rules, i.e. no task depends
directly or indirectly on itself.
Output
The output should be a single line with the permutation of the tasks to be performed, ordered by
dependencies (i.e. no task should appear before others that it depends on).
To avoid ambiguity in the output, tasks that do not depend on each other should be ordered by their
number (lower numbers first).
Example
Input:
5 4
3 2 1 5
2 2 5 3
4 1 3
5 1 1
Output:
1 5 3 2 4
*/
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

// to arrange elements in decrementing order in the set below
class myComp
{
public:
	bool operator() (const unsigned int lhs, const unsigned int rhs) { return lhs > rhs; }
};
// Using set (instead of list, e.g.) for the adjcacency list. This is to fulfill 
// the requirement that if two or more tasks are unblocked then we run the task 
// with the lower ID first. The set arranges task IDs in decrementing order. That 
// combined with recursion and a stack will give us that order.
using adjList = vector < set<unsigned int, myComp > > ;


class Graph
{
public:
	Graph(unsigned int n) : numV(n) { 
		adj.resize(n + 1);
	}
	void addEdge(unsigned int from, unsigned int to);
	unsigned int getNumV() { return numV; }
	void printGraph();

	adjList adj;

private:	
	unsigned int numV;
};

void Graph::addEdge(unsigned int from, unsigned int to)
{
	if (from <= numV && to <= numV) {
		adj[from].insert(to);
	}
}
void Graph::printGraph()
{
	//for (auto al : adj) {
	for (auto i = 1; i <= getNumV(); i ++) {
		auto al = adj[i];
		cout << i << ": ";
		for (auto v : al) {
			cout << v << " ";
		}
		cout << endl;
	}
}
// Graph Topological Sort (GraphTS) 
//   Performs the topological sorting of the graph
class GraphTS
{
public:
	GraphTS(Graph& aG) : G(aG) { visited.resize(aG.getNumV()+1); }
	void printOrderedTasks();
private:
	Graph& G;
	void dfs(unsigned int s);
	vector<bool> visited;
	stack<unsigned int> stk;
};
void GraphTS::printOrderedTasks()
{
	for (unsigned int i = 1; i <= G.getNumV(); i++) {
		visited[i] = false;
	}
	for (unsigned int i = 1; i <= G.getNumV(); i++) {
		if (!visited[i]) {
			dfs(i);
			visited[i] = true;
		}
	}
	// print tasks from the stack
	cout << "The task order is " << endl;
	while (!stk.empty()) {
		unsigned int v = stk.top();
		stk.pop();
		cout << v << " ";
	}
	cout << endl;
}
void GraphTS::dfs(unsigned int s)
{
	for (auto ss : G.adj[s]) {
		if (!visited[ss]) {
			dfs(ss);
			visited[ss] = true;
		}
	}
	stk.push(s);
}


// Reads task dependencies from stdin and populates the passed-in 
// task dependency list and blocked flags
// Each input line is of the form ...
// T0 k T1 T2 ... Tk
// ... indicating Task T0 depends on k tasks: T0 - Tk
void getRules(unsigned int numRules, Graph& G)
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
			// edges represent dependencies. An edge u->v means v is dependent on u
			G.addEdge(Tk/*from*/, T0/*to*/);
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

	// create a Graph object of N vertices (N+1, actually, so we can use 1-based indices for convenience)
	Graph G(N);
	
	
	// Read rules from stdin
	getRules(M, G);

	cout << "Graph: " << endl;
	G.printGraph();

	// create a Graph Topological sort object
	GraphTS GTS(G);

	// print the tasks in an order that follows the given rules 
	GTS.printOrderedTasks();

	return 0;
}


