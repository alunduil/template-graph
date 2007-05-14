//
// C++ Interface: vertex
//
// Description:
//
//
// Author: Alex Brandt <alunduil@alunduil.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

#include <list>
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>

namespace Graphs
{
	template<typename T> class Vertex;
	template<typename T> std::ostream &operator<< (std::ostream &, const Vertex<T> &);

	/**
	@class Vertex vertex.h
	@brief Node in the graph.
	@author Alex Brandt <alunduil@alunduil.com>

	Vertex of a graph. Basically a node in the network. It's a wonderful day in the neighborhood...
	*/
	template<typename T>
	class Vertex
	{
		public:
			/**
			@param mrRogers The data the vertex should hold.

			Constructor
			*/
			Vertex(T mrRogers);

			/**
			@param otherVertex The other vertex to copy.

			Copy Constructor
			*/
			Vertex(const Vertex<T> &otherVertex);

			/**
			Destructor
			*/
			~Vertex(void);

			/**
			@param neighbor The neighbor to say goodbye to.

			Delete neighbor
			*/
			void DeleteNeighbor(const Vertex<T> &neighbor);

			/**
			@param neighbor Please won't you be my neighbor?
			@param weight Not that they are fat, just more expensive.

			Create neighbor
			*/
			void CreateNeighbor(const Vertex<T> &neighbor, const int weight = 1);

			/**
			@return The data Mr. Rogers holds for us.

			Get Mr. Rogers
			*/
			T Get(void) const;

			/**
			@param data The new data we want Mr. Rogers to hold.

			Set Mr. Rogers
			*/
			void Set(T data);

			/**
			@return The neighborhood.

			Getting the neighborhood to play with.
			*/
			std::list<boost::tuple<Vertex<T>*, int> > Neighborhood(void);

			/**
			@return The neighbors.

			Collects the neighbors to play with.
			*/
			std::list<Vertex<T>*> Neighbors(void);

			/**
			@param that That vertex to compare.
			@return True if the vertices are equivalent.

			Equivalency Operator
			*/
			bool operator==(const Vertex<T> &that) const;

			/**
			@param that That vertex to compare.
			@return True if the vertices are not equal.

			Inequality Operator
			*/
			bool operator!=(const Vertex<T> &that) const;

			/**
			@param that That vertex to compare.
			@return True if this is greater than that.

			Greater than operator
			*/
			bool operator>(const Vertex<T> &that) const;

			/**
			@param that That vertex to compare.
			@return True if this is greater than or equal to that.

			Greater than or equal operator.
			*/
			bool operator>=(const Vertex<T> &that) const;

			/**
			@param that That vertex to compare.
			@return True if this is less than that.

			Less than operator.		outStream << otherVertex.mrRogers;
			*/
			bool operator<(const Vertex<T> &that) const;

			/**
			@param that That vertex to compare.
			@return True if this is less than or equal to that.

			Less than or equal operator.
			*/
			bool operator<=(const Vertex<T> &that) const;

			/**
			@param other The vertex to assign to this one.
			@return A reference to the new vertex.

			Assignment Operator.
			*/
			Vertex<T> &operator=(const Vertex<T> &other);

			/**
			@param otherVertex That vertex to output to the stream.
			@param outStream The stream to output on to.
			@return The stream state.

			Dump the neighbor in the river.
			*/
			std::ostream &Dump(std::ostream &out) const;

			/**
			@param otherVertex The vertex to find the weight to.
			@return The weight from this vertex to that vertex.

			Grab the weight of the path.
			*/
			int GetWeight(const Vertex<T> &otherVertex) const;

		private:
			std::list<boost::tuple<Vertex<T>*, int> >	neighborhood;	//!< Neighboring nodes in the graph. The list contains tuples that correspond the end of the edge to the weight of the edge.
			T											mrRogers;		//!< The man himself to hold our dear data.

			/**
			@param myTuple This static methods very own tuple.
			@return The weight of this neighbor.

			Get the weight of the neighbor.
			*/
			static int GetWeightFromTuple(boost::tuple<Vertex<T>*, int> myTuple);

			/**
			@param myTuple The tuple[trunk] to extract our neighbor from.
			@return The neighbor to dispense with.

			Get the neighbor.
			*/
			static Vertex<T>* GetVertexFromTuple(boost::tuple<Vertex<T>*, int> myTuple);

	};

	template<typename T>
	Vertex<T>::Vertex(T mrRogers)
	:neighborhood(std::list<boost::tuple<Vertex<T>*, int> >()), mrRogers(mrRogers)
	{
	}

	template<typename T>
	Vertex<T>::Vertex(const Vertex<T> &otherVertex)
	:neighborhood(otherVertex.neighborhood), mrRogers(otherVertex.mrRogers)
	{
	}

	template<typename T>
	Vertex<T> &Vertex<T>::operator=(const Vertex<T> &other)
	{
		if (this != &other)
		{
			this->neighborhood = other.neighborhood;
			this->mrRogers = other.mrRogers;
		}
		return *this;
	}

	template<typename T>
	Vertex<T>::~Vertex(void)
	{
	}

	template<typename T>
	void Vertex<T>::CreateNeighbor(const Vertex<T> &neighbor, const int weight)
	{
		neighborhood.insert(neighborhood.end(), boost::tuple<Vertex<T>*, int>(const_cast<Vertex<T>*>(&neighbor), weight));
		return;
	}

	template<typename T>
	void Vertex<T>::DeleteNeighbor(const Vertex<T> &neighbor)
	{
		for (class std::list<boost::tuple<Vertex<T>*, int> >::iterator i = neighborhood.begin(); i != neighborhood.end(); i++)
			if (boost::get<0>(*i) == boost::get<0>(neighbor))
				neighborhood.erase(i);
		return;
	}

	template<typename T>
	T Vertex<T>::Get(void) const
	{
		return mrRogers;
	}

	template<typename T>
	void Vertex<T>::Set(T data)
	{
		mrRogers = data;
		return;
	}

	template<typename T>
	bool Vertex<T>::operator<=(const Vertex<T> &that) const
	{
		return static_cast<const void*>(this) <= static_cast<const void*>(&that);
	}

	template<typename T>
	bool Vertex<T>::operator<(const Vertex<T> &that) const
	{
		return static_cast<const void*>(this) < static_cast<const void*>(&that);
	}

	template<typename T>
	bool Vertex<T>::operator==(const Vertex<T> &that) const
	{
		return static_cast<const void*>(this) == static_cast<const void*>(&that);
	}

	template<typename T>
	bool Vertex<T>::operator>=(const Vertex<T> &that) const
	{
		return static_cast<const void*>(this) >= static_cast<const void*>(&that);
	}

	template<typename T>
	bool Vertex<T>::operator>(const Vertex<T> &that) const
	{
		return static_cast<const void*>(this) > static_cast<const void*>(&that);
	}

	template<typename T>
	bool Vertex<T>::operator!=(const Vertex<T> &that) const
	{
		return static_cast<const void*>(this) != static_cast<const void*>(&that);
	}

	template<typename T>
	std::list<boost::tuple<Vertex<T>*, int> > Vertex<T>::Neighborhood(void)
	{
		return neighborhood;
	}

	template<typename T>
	std::list<Vertex<T>*> Vertex<T>::Neighbors(void)
	{
		std::list<Vertex<T>*> neighbors;	// The neigbors.

// 		std::transform(neighborhood.begin(), neighborhood.end(), neighbors.begin(), boost::lambda::bind(&GetVertexFromTuple, boost::lambda::_1));
		std::for_each(neighborhood.begin(), neighborhood.end(), boost::lambda::bind(&std::list<Vertex<T>*>::push_back, var(neighbors), boost::lambda::bind(&GetVertexFromTuple, boost::lambda::_1)));
		return neighbors;
	}

	template<typename T>
	std::ostream &Vertex<T>::Dump(std::ostream &outStream) const
	{
 		outStream << mrRogers;
		for_each(neighborhood.begin(), neighborhood.end(), boost::lambda::var(outStream) << boost::lambda::constant(" -> ") << boost::lambda::bind(&Vertex<T>::Get, *boost::lambda::bind<Vertex<T>*>(&Vertex<T>::GetVertexFromTuple, boost::lambda::_1)) << boost::lambda::constant(":") << boost::lambda::bind<int>(&Vertex<T>::GetWeightFromTuple, boost::lambda::_1));
		return outStream;
	}

	template<typename T>
	std::ostream &operator<< (std::ostream &out, const Vertex<T> &vertex)
	{
		return vertex.Dump(out);
	}

	template<typename T>
	int Vertex<T>::GetWeightFromTuple(boost::tuple<Vertex<T>*, int> myTuple)
	{
		return boost::get<1>(myTuple);
	}

	template<typename T>
	Vertex<T>* Vertex<T>::GetVertexFromTuple(boost::tuple<Vertex<T>*, int> myTuple)
	{
		return boost::get<0>(myTuple);
	}

	template<typename T>
	int Vertex<T>::GetWeight(const Vertex<T> &otherVertex) const
	{
		return GetWeightFromTuple(*find_if(neighborhood.begin(), neighborhood.end(), boost::lambda::bind(&GetVertexFromTuple, boost::lambda::_1) == boost::lambda::constant(&otherVertex)));
	}
}

#endif
