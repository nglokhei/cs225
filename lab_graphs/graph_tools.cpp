/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */

    vector<Edge> e = graph.getEdges();
    if (e.size() == 0)
	return 0;

    Edge ed = e[0];
    int ret = ed.weight;
    for (size_t i = 1; i < e.size(); i++){
	Edge tmpEd = e[i];
	int tmpEdWeight = tmpEd.weight;
	if (tmpEdWeight < ret){
	    ret = tmpEdWeight;
	    ed = tmpEd;
	}
    }

    graph.setEdgeLabel(ed.source, ed.dest, "MIN");
    return ret;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    if (start == end)
	return 0;
    std::unordered_map<Vertex, Vertex> parent;
    std::queue<Vertex> q;
    q.push(start);

    Vertex v;
    bool stop = false;
    while (q.size() > 0 && !stop){
	Vertex v = q.front();
	q.pop();

	vector<Vertex> adj = graph.getAdjacent(v);
	for (size_t i = 0; i < adj.size();i++){
	    if (adj[i] == end){
		parent[adj[i]] = v;
		stop = true;
		break;
	    }
	    
	    auto got = parent.find(adj[i]);
	    if (got == parent.end()){
		parent[adj[i]] = v;
		q.push(adj[i]);
	    }
	}
    }

    v = end;
    int count = 0;
    while (v != start){
	graph.setEdgeLabel(v,parent[v],"MINPATH");
	v = parent[v];
	count++;
    }
    return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */

    std::vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end());

    std::vector<Vertex> vertices = graph.getVertices();
    int n = vertices.size();
    std::unordered_map<Vertex,int> index;
    for (int i = 0; i < n; i++)
	index[vertices[i]] = i;

    DisjointSets s;
    s.addelements(n);

    int count = 0;
    for (size_t i = 0; i < edges.size(); i++){
	Vertex v1 = edges[i].source;
	Vertex v2 = edges[i].dest;
	int index1 = index[v1];
	int index2 = index[v2];
	if (s.find(index1) != s.find(index2)){
	    s.setunion(s.find(index1), s.find(index2));
	    graph.setEdgeLabel(v1, v2, "MST");
	    count++;
	}
	if (count == n - 1)
	    break;
    }		    
}

