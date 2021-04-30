/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
#include "foreach.h"
using namespace std;

Grid<node*> createGraph(Grid<double>& world) {
	Grid<node*> graph(world.numRows(), world.numCols());
	for (int i = 0; i < world.numRows(); i++) {
		for (int j = 0; j < world.numCols(); j++) {
			node* n = new node;
			n->color = GRAY;
			Loc l; l.row = i; l.col = j;
			n->loc = l;
			n->parent = NULL;
			graph[i][j] = n;
		}
	}
	return graph;
}

Vector<Loc> getPath(node* &curr, Loc start) {
	Vector<Loc> reversedPath;

	while (curr != NULL) {
		reversedPath.add(curr->loc);
		curr = curr->parent;
	}
	reversedPath.add(start);

	Vector<Loc> path;
	
	for(int i = reversedPath.size() - 1; i >= 0; i--) {
		path.add(reversedPath[i]);
	} 
	return path;
}

void getClusters(int numRows, int numCols, Map<Loc, Set<Loc>* >& res) {
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			Loc loc = makeLoc(i, j);
			Set<Loc>* set = new Set<Loc>;
			set->add(loc);
			res[loc] = set;
		}
	}
}

Set<Edge> getAllEdges(int numRows, int numCols) {
	Set<Edge> res;
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			Loc start = makeLoc(i, j);
			if (i + 1 < numRows) {
				Loc end = makeLoc(i + 1, j);
				Edge e = makeEdge(start, end);
				res.add(e);
			}
			if (j + 1 < numCols) {
				Loc end = makeLoc(i, j + 1);
				Edge e = makeEdge(start, end);
				res.add(e);
			}
		}
	}
	return res;
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {

	TrailblazerPQueue<node*> pq;
	
	Grid<node*> graph = createGraph(world);

	node* startNode = graph[start.row][start.col];
	startNode->color = YELLOW;
	startNode->value = 0;
	pq.enqueue(startNode, heuristic(start, end, world));
	
	while(!pq.isEmpty()) {
		node* curr = pq.dequeueMin();
		curr->color = GREEN;
		colorCell(world, curr->loc, GREEN);
		if(curr->loc == end) {
			break;
		}
		for (int i = curr->loc.row - 1; i <= curr->loc.row + 1; i++) {
			for (int j = curr->loc.col - 1; j <= curr->loc.col + 1; j++) {
				if (graph.inBounds(i, j)) {
					if (graph[i][j]->color == GRAY) {
						graph[i][j]->color = YELLOW;
						colorCell(world, graph[i][j]->loc, YELLOW);
						graph[i][j]->value = costFn(curr->loc, graph[i][j]->loc, world) + curr->value;

						graph[i][j]->parent = curr;
						pq.enqueue(graph[i][j], costFn(curr->loc, graph[i][j]->loc, world) + curr->value + 
							heuristic(graph[i][j]->loc, end, world));
					} else if (graph[i][j]->color == YELLOW &&
							costFn(curr->loc, graph[i][j]->loc, world) + curr->value < graph[i][j]->value) {
						graph[i][j]->value = costFn(curr->loc, graph[i][j]->loc, world) + curr->value;

						graph[i][j]->parent = curr;
						pq.decreaseKey(graph[i][j], costFn(curr->loc, graph[i][j]->loc, world) + curr->value + 
							heuristic(graph[i][j]->loc, end, world));
					}
				}
			}
		}
	}
	node* curr = graph[end.row][end.col];
	Vector<Loc> path = getPath(curr, start);
	foreach(node* tmp in graph) {
		delete tmp;
	}
    return path;
}

Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> result;
	TrailblazerPQueue<Edge> pq;
	Map<Loc, Set<Loc>* > clusters;
	getClusters(numRows, numCols, clusters);
	Set<Edge> allEdges = getAllEdges(numRows, numCols);
	foreach(Edge e in allEdges) {
		pq.enqueue(e, randomReal(0, 1)); 
	}

	int numClusters = numCols * numRows;
	while(numClusters >= 2) {
		Edge e = pq.dequeueMin();
		if (!clusters[e.start]->contains(e.end)) {
			*clusters[e.start] += *clusters[e.end];
			delete clusters[e.end];
			foreach (Loc loc in *clusters[e.start]) {
				clusters[loc] = clusters[e.start];
			}
			numClusters--;
			result += e;
		} 
	}
    return result;
}

