//
// C++ Interface: graph
//
// Description:
//
//
// Author: Alex Brandt <alunduil@alunduil.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <iostream>
#include <list>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <algorithm>
#include <boost/lambda/bind.hpp>
#include <queue>
#include <map>
#include <cmath>
#include <vector>

#include "vertex.h"

/**
@brief The Graphs namespace for all of our graphing tools.

This namespace is where all corrollary objects to a Graph should
be placed. It will keep our programming cleaner, and tighter.
*/
namespace Graphs
{
	/**
	@brief Weighting enum for keywording the Graph.

	This enum allows us to pass the keyword to the graph upon instantiation.
	This sets up the graph in the desired way so that we have more control in
	whether it is weighted.
	*/
	enum Weighting
	{
		Weighted,						//!< Weighted Graph will be created.
		Unweighted						//!< Unweighted Graph will be created.
	};

	/**
	@brief Direction enum for keywording the Graph.

	This enum allows us to pass the keyword to the graph upon instantiation.
	This sets up the graph in the desired way so that we have more control in
	whether it is weighted.
	*/
	enum Direction
	{
		Directed,						//!< Directed Graph will be created.
		Undirected						//!< Undirected Graph will be created.
	};

	/**
	Fun Things...
	*/
	template<class T> class Graph;
	template<class T>
	std::ostream &operator <<(std::ostream &, const Graph<T> &);
	const int Infinity = static_cast<int>(pow(2,32));

	/**
	@class Graph graph.h
	@brief Graph class to store networks in memory.
	@author Alex Brandt <alunduil@alunduil.com>

	This Graph can be Weighted, Unweighted, Directed, or Undirected.
	*/
	template<class T>
	class Graph
	{
		public:
			/**
			Constructor
			*/
			Graph(Weighting weighting = Unweighted, Direction direction = Undirected);

			/**
			Constructor
			*/
			Graph(Direction direction = Undirected, Weighting weighting = Unweighted);

			/**
			Constructor
			*/
			explicit Graph();

			/**
			Destructor
			*/
			~Graph();

			/**
			Copy Constructor
			*/
			Graph(const Graph<T> &otherGraph);

			/**
			Assignment Operator
			*/
			Graph &operator=(const Graph<T> &otherGraph);

			/**
			Delete all edges and vertices.
			*/
			void Destroy(void);

			/**
			@return True if the Graph is empty; otherwise false.

			Determine if the Graph is empty.
			*/
			bool IsEmpty(void) const;

			/**
			@return The number of edges.
			@sa VertexCount()

			Count of the number of edges in the graph.
			*/
			int EdgeCount(void) const;

			/**
			@return The number of vertices.
			@sa EdgeCount()

			Count of the number of vertices in the Graph.
			*/
			int VertexCount(void) const;

			/**
			@param otherVertex Vertex to insert into the Graph.
			@sa InsertEdge()

			Insert a vertex into the graph. NOTE: This allocates a new vertex to ensure the reference doesn't go out of scope.
			*/
			Vertex<T> & InsertVertex(const Vertex<T> &otherVertex);

			/**
			@param data The data to insert in the new vertex.
			@sa InsertVertex()

			Pass the data to the Insert method allowing the vertex to be created as it's inserted.
			*/
			Vertex<T> & InsertNewVertex(const T &data);

			/**
			@param vertexA Starting vertex for the edge.
			@param vertexB Finishing vertex for the edge.
			@param weight The weight of the new edge.
			@sa InsertVertex()

			Insert an edge into the Graph.
			*/
			void InsertEdge(Vertex<T> &vertexA, Vertex<T> &vertexB, const int weight = 1);

			/**
			@param vertexA Starting vertex for the edge.
			@param vertexB Finishing vertex for the edge.
			@param weight The weight of the new edge.
			@sa InsertVertex()
			@sa InsertEdge()

			Insert a bidirectional edge into the graph.
			*/
			void InsertBidirectionalEdge(Vertex<T> &vertexA, Vertex<T> &vertexB, const int weight = 1);

			/**
			@param vertexA Starting vertex for the edge.
			@param vertexB Finishing vertex for the edge.
			@sa DeleteVertex()

			Delete a specific edge from the graph.
			*/
			void DeleteEdge(Vertex<T> &vertexA, Vertex<T> &vertexB);

			/**
			@param otherVertex Vertex to remove from the graph.
			@sa DeleteEdge

			Delete a specified vertex, and it's associated edges.
			*/
			void DeleteVertex(const Vertex<T> &otherVertex);

			/**
			Simply dumps out the graph's contents.
			*/
			std::ostream &Dump(std::ostream &) const;

			/**
			@param predicate Predicate function to determine when we've found an item in question.
			@return Set of references to the matched items.

			Finds all the instances matched by the predicate used, and places references in a set to be returned.
			*/
			std::list<Vertex<T> &> FindAll(boost::function<bool (const Vertex<T> &)> predicate);

			/**
			@param predicate Predicate function to determine when we've found an item in question.
			@return A reference to the first instance that matches.

			Finds the first instance matched by the predicate used, and returns a reference.
			*/
			Vertex<T> & FindVertex(boost::function<bool (const Vertex<T> &)> predicate);

			/**
			@param predicate Predicate function to determine when we've found an item in question.
			@return A reference to the first instance that matches.

			Finds the first instance matched by the predicate used, and returns a reference.
			*/
			Vertex<T> & FindVertex(boost::function<bool (const Vertex<T> *)> predicate);

			/**
			@param predicate Predicate function to determine when we'be found an item in question.
			@return A reference to the first instance that matches.

			Finds the first instance matched by the predicate used, and returns a reference.
			*/
			Vertex<T> & Find(boost::function<bool (const T &)> predicate);

			/**
			@param vertexA The source vertex.
			@param vertexB The destination vertex.
			@return A queue that is the path to follow.

			Dijkstra's shortest path from one node to another.
			*/
			std::queue<Vertex<T>*> ShortestPath(const Vertex<T> &vertexA, const Vertex<T> &vertexB);
		private:
			std::set<Vertex<T>*>		vertices;		//!< The vertices of the graph.
			Weighting					weighting;		//!< Weighted graph?
			Direction					direction;		//!< Directed graph?
			int							edgeCount;		//!< Number of edges.
	};

	template<class T>
	Graph<T>::Graph(Weighting weighting, Direction direction)
	:vertices(std::set<Vertex<T>*>()), weighting(weighting), direction(direction), edgeCount(0)
	{
	}

	template<class T>
	Graph<T>::Graph(Direction direction, Weighting weighting)
	:vertices(std::set<Vertex<T>*>()), weighting(weighting), direction(direction), edgeCount(0)
	{
	}

	template<class T>
	Graph<T>::Graph()
	:vertices(std::set<Vertex<T>*>()), weighting(Unweighted), direction(Undirected), edgeCount(0)
	{
	}

	template<class T>
	Graph<T>::~Graph()
	{
	}

	template<class T>
	Graph<T>::Graph(const Graph<T> &otherGraph)
	:vertices(otherGraph.vertices), weighting(otherGraph.weighting), direction(otherGraph.direction), edgeCount(otherGraph.edgeCount)
	{
		transform(otherGraph.vertices.begin(), otherGraph.vertices.end(), vertices.begin(), boost::lambda::bind(&(new Vertex<T>), otherGraph.vertices, boost::lambda::_1));
	}

	template<class T>
	void Graph<T>::DeleteEdge(Vertex<T> &vertexA, Vertex<T> &vertexB)
	{
		vertexA.DeleteNeighbor(vertexB);
		if (direction == Undirected)
			vertexB.DeleteNeighbor(vertexA);
		edgeCount--;
		return;
	}

	template<class T>
	void Graph<T>::DeleteVertex(const Vertex<T> &otherVertex)
	{
		vertices.erase(const_cast<Vertex<T>*>(&otherVertex));
		return;
	}

	template<class T>
	void Graph<T>::Destroy(void)
	{
		vertices.clear();
		return;
	}

	template<class T>
	std::ostream &Graph<T>::Dump(std::ostream &out) const
	{
		out << "Dumping graph:" << std::endl;
		out << "\tNumber of Vertices: " << VertexCount() << "\tNumber of Edges: " << EdgeCount() << "\n";

		for_each(vertices.begin(), vertices.end(), boost::lambda::var(out) << *boost::lambda::_1 << boost::lambda::constant("\n"));

		return out;
	}

	template<class T>
	int Graph<T>::EdgeCount(void) const
	{
		return edgeCount;
	}

	template<class T>
	void Graph<T>::InsertEdge(Vertex<T> &vertexA, Vertex<T> &vertexB, const int weight)
	{
		vertexA.CreateNeighbor(vertexB, weight);
		if (direction == Undirected)
			vertexB.CreateNeighbor(vertexA, weight);
		edgeCount++;
		return;
	}

	template<class T>
	void Graph<T>::InsertBidirectionalEdge(Vertex<T> &vertexA, Vertex<T> &vertexB, const int weight)
	{
		vertexA.CreateNeighbor(vertexB, weight);
		vertexB.CreateNeighbor(vertexA, weight);
		edgeCount++;
		edgeCount++;
		return;
	}

	template<class T>
	Vertex<T> & Graph<T>::InsertVertex(const Vertex<T> &otherVertex)
	{
		return **vertices.insert(new Vertex<T>(otherVertex)).first;
	}

	template<class T>
	Vertex<T> & Graph<T>::InsertNewVertex(const T &data)
	{
		return InsertVertex(Vertex<T>(data));
	}

	template<class T>
	bool Graph<T>::IsEmpty(void) const
	{
		return vertices.empty();
	}

	template<class T>
	Graph<T> &Graph<T>::operator=(const Graph<T> &otherGraph)
	{
		if (this != &otherGraph)
		{
			this->direction = otherGraph.direction;
			this->edgeCount = otherGraph.edgeCount;
			this->vertexCount = otherGraph.vertexCount;
			this->vertices = transform(otherGraph.vertices.begin(), otherGraph.vertices.end(), vertices.begin(), boost::lambda::bind(&(new Vertex<T>, boost::lambda::_1)));
			this->weighting = otherGraph.weighting;
		}
		return *this;
	}

	template<class T>
	int Graph<T>::VertexCount(void) const
	{
		return vertices.size();
	}

	template<class T>
	std::list<Vertex<T> &> Graph<T>::FindAll(boost::function<bool (const Vertex<T> &)> predicate)
	{
		std::list<Vertex<T> &>	foundItems;	// The items we have found using the predicate provided.

		for_each(vertices.begin(), vertices.end(), if_(predicate(boost::lambda::_1))[boost::lambda::bind(&std::list<Vertex<T> &>::push_back, foundItems, boost::lambda::_1)]);

		return foundItems;
	}

	template<class T>
	Vertex<T> & Graph<T>::FindVertex(boost::function<bool (const Vertex<T> &)> predicate)
	{
		return FindVertex(static_cast<boost::function<bool (const Vertex<T>*)> >(boost::lambda::bind(predicate, *boost::lambda::_1)));
	}

	template<class T>
	Vertex<T> & Graph<T>::FindVertex(boost::function<bool (const Vertex<T> *)> predicate)
	{
		return **find_if(vertices.begin(), vertices.end(), predicate);
	}

	template<class T>
	Vertex<T> & Graph<T>::Find(boost::function<bool (const T &)> predicate)
	{
		return FindVertex(static_cast<boost::function<bool (const Vertex<T>*)> >(boost::lambda::bind(predicate, boost::lambda::bind(&Vertex<T>::Get, *boost::lambda::_1))));
	}

	template<class T>
	std::ostream &operator <<(std::ostream &out, const Graph<T> &graph)
	{
		return graph.Dump(out);
	}

	template<class T>
	std::queue<Vertex<T>*> Graph<T>::ShortestPath(const Vertex<T> &vertexA, const Vertex<T> &vertexB)
	{
		using namespace boost::lambda;
		using boost::function;
		using namespace std;

		list<Vertex<T>*>					shortestPathList,	// The found shortest path.
											unvisitedNodes;		// The nodes we need to visit.
		map<const Vertex<T>*, int>			distance;			// The distance map.
		map<const Vertex<T>*, Vertex<T>*>	parents;			// The parent lookup list.
		queue<Vertex<T>*>					shortestPath;		// The found shortest path (clean).

		/*
		Initialize the sources.
		*/
		for_each
		(
			vertices.begin(), vertices.end(),
			(
				var(distance)[_1] = constant(Infinity),
				var(parents)[_1] = constant(static_cast<Vertex<T>*>(NULL))
			)
		);
		distance[&vertexA] = 0;

		/*
		Make the priority queue with all of our vertices in it.
		*/
		for_each
		(
			vertices.begin(), vertices.end(),
			bind(&list<Vertex<T>*>::push_back, var(unvisitedNodes), _1)
		);

		/*
		Dijkstra's Algorithm (modified to end when we hit the target:
		*/
		while (!unvisitedNodes.empty() && *min_element(unvisitedNodes.begin(), unvisitedNodes.end(), var(distance)[_1] < var(distance)[_2]) != &vertexB)
		{
			Vertex<T> *current = *min_element(unvisitedNodes.begin(), unvisitedNodes.end(), var(distance)[_1] < var(distance)[_2]);
			unvisitedNodes.remove(current);
			shortestPathList.push_back(current);
			list<Vertex<T>*>	neighbors = current->Neighbors();
			for_each
			(
				neighbors.begin(),
				neighbors.end(),
				if_(
					var(distance)[_1]
						> (var(distance[current]) + bind(&Vertex<T>::GetWeight, var(current), *_1))
				)
				[
					var(distance)[_1] = var(distance[current])
						+ bind(&Vertex<T>::GetWeight, var(parents)[_1] = var(current), *_1)
				]
			);
		}
		shortestPathList.push_back(*min_element(unvisitedNodes.begin(), unvisitedNodes.end(), var(distance)[_1] < var(distance)[_2]));

		/*
		Remove extra crappy nodes.
		*/
		reverse(shortestPathList.begin(), shortestPathList.end());
		for (typename list<Vertex<T>*>::iterator i = shortestPathList.begin(); *i != &vertexA;)
		{
			if (parents[*i] != *(++i))
			{
				shortestPathList.remove(*i);
				i = shortestPathList.begin();
			}
		}
		reverse(shortestPathList.begin(), shortestPathList.end());
		for_each
		(
			shortestPathList.begin(), shortestPathList.end(),
			bind(&queue<Vertex<T>*>::push, var(shortestPath), _1)
		);
		return shortestPath;
	}
}

#endif
