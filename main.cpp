/***************************************************************************
 *   Copyright (C) 2006 by Alex Brandt                                     *
 *   alunduil@alunduil.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful.       *
 *   but WITHOUT ANY WARRANTY: without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc..                                       *
 *   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.              *
 ***************************************************************************/

/**
@mainpage
@brief Assignment 7 Graphs
@author Alex Brandt <alunduil@alunduil.com>
@date 2007
@version 0.1

@section intro_sec Introduction

This is assignment 7 for CSIS 352 at MSUM.
Write a C++ ADT for a graph.
Allow for the Graph to be Wieghted or Unweighted and either Directed or Undirected, declared in either order.
The default is Unweighted and Undirected.
These should be an enum (Keyword) type so the following declarations are valid syntax:
	- Graph&lt;City&gt;        map(Directed, Weighted);\n
	- Graph&lt;City&gt;        map(Weighted, Directed);\n
	- Graph&lt;Something&gt;   graph(Directed);\n
	- Graph&lt;Something&gt;   graph(Weighted);\n
	- Graph&lt;AnotherType&gt; graph;\n
	- etc.
	.

@section install_sec Install

This program was created using Ubuntu Linux with a 2.6.17 kernel revision 11 on an x86 architecture.
The compiler used for building and testing is gcc version 4.1.2 prerelease provided by the ubuntu repositories (www.ubuntu.com).

To build this program, simply type 'make' which creates the default executable, prog7.

If the boost libraries are not installed on your system they will automatically be downloaded and installed.

@section desc_sec Description

This program utilizes the following:
	-# STL's set
	-# STL's list
	-# Boost's tuple
	.

@section IO_sec Input and Output

@subsection input_sec Input

No input necessary for this application.

@subsection output_sec Output

The output of this program is a dump of the graph created in the main function.

@section test_sec Program Testing

@section bug_sec Bugs

There are no known bugs in this program.

If bugs are found please email Alex Brandt <alunduil@alunduil.com> with a bugreport.

*/

#include <iostream>

#include "graph.h"

using namespace Graphs;
using namespace std;
using namespace boost::lambda;

int main(void)
{
	Graph<string>			map(Directed, Weighted);	//!< Map of the cities we want.
	string					sourceCity,					//!< Source City.
							destinationCity;			//!< Destination City.
	queue<Vertex<string>*>	shortestPath;				//!< Shortest Path.

	/*
	Insert the cities into our map.
	*/

	Vertex<string>	&fargo			= map.InsertNewVertex("Fargo"),
					&minneapolis	= map.InsertNewVertex("Minneapolis"),
					&chicago		= map.InsertNewVertex("Chicago"),
					&detroit		= map.InsertNewVertex("Detroit"),
					&newYork		= map.InsertNewVertex("New York"),
					&miami			= map.InsertNewVertex("Miami"),
					&houston		= map.InsertNewVertex("Houston"),
					&stLouis		= map.InsertNewVertex("St. Louis"),
					&denver			= map.InsertNewVertex("Denver"),
					&seattle		= map.InsertNewVertex("Seattle"),
					&losAngeles		= map.InsertNewVertex("Los Angeles"),
					&phoenix		= map.InsertNewVertex("Phoenix");

	/*
	Attach the edges to the nodes.
	*/

	map.InsertEdge(seattle, chicago, 2072);
	map.InsertEdge(losAngeles, seattle, 1151);
	map.InsertBidirectionalEdge(losAngeles, denver, 1023);
	map.InsertBidirectionalEdge(losAngeles, phoenix, 381);
	map.InsertBidirectionalEdge(losAngeles, newYork, 2824);
	map.InsertBidirectionalEdge(phoenix, houston, 1186);
	map.InsertBidirectionalEdge(denver, minneapolis, 920);
	map.InsertBidirectionalEdge(fargo, minneapolis, 240);
	map.InsertBidirectionalEdge(minneapolis, chicago, 409);
	map.InsertEdge(houston, stLouis, 780);
	map.InsertBidirectionalEdge(houston, miami, 1190);
	map.InsertEdge(stLouis, denver, 861);
	map.InsertBidirectionalEdge(stLouis, detroit, 547);
	map.InsertBidirectionalEdge(chicago, detroit, 286);
	map.InsertBidirectionalEdge(chicago, newYork, 821);
	map.InsertEdge(detroit, newYork, 640);
	map.InsertBidirectionalEdge(miami, newYork, 1281);

	/*
	Output the graph.
	*/

	cout << map << endl;

	cout << "Shortest Pathing Program 1.0" << endl;
	cout << "Copyright (C) 2007 Alex Brandt" << endl;
	cout << "ShortestPath is a small utility that allows simple lookups to be performed on a" << endl;
	cout << "graph. When typing the city name type it exactly as it appears in the dump of" << endl;
	cout << "the map. The city names _are_ case sensitive! When you are finished simply type" << endl;
	cout << "'exit', 'quit', or '^D' to end the program." << endl;

	do
	{
		cout << endl;
		/*
		Get the source and destination of our little escapade.
		*/
		cout << "Source City:\t\t";
		getline(cin, sourceCity);
		if (toupper(sourceCity[0]) == 'E' || toupper(sourceCity[0]) == 'Q' || cin.eof())
			return 0;

		cout << "Destination City\t";
		getline(cin, destinationCity);
		if (toupper(destinationCity[0]) == 'E' || toupper(destinationCity[0]) == 'Q' || cin.eof())
			return 0;

		/*
		Get the shortest path.
		*/
		shortestPath = map.ShortestPath(map.Find(_1 == var(sourceCity)), map.Find(_1 == var(destinationCity)));

		/*
		Output the shortest path.
		*/
		while (shortestPath.size() > 1)
		{
			cout << shortestPath.front()->Get() << " -> ";
			shortestPath.pop();
		}
		cout << shortestPath.front()->Get() << endl;
		shortestPath.pop();
	} while (true);
}
