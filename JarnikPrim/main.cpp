//
//  main.cpp
//  JarnikPrim
//
//  Created by Dominik Plíšek on 5/20/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>

using namespace std;


#ifndef __PROGTEST__
#include "CGraph.h"
#include "t_edge.h"
#include "t_node.h"
#endif

struct t_heapElem {
    int nodeIndex;
    int parent;
    int distance;
};

vector<t_edge>* removeEdgesFromGraph(CGraph& g) {
	vector<t_edge>* edges = new vector<t_edge>();
	while (g.getEdgeCounter() != 0) {
		t_edge edge = g.getEdge(1);
		edges->push_back(edge);
		g.deleteEdge(1);
	}
	return edges;
}

vector<t_heapElem>* buildHeap(CGraph& g, const int startIndex) {
	vector<t_heapElem>* heap = new vector<t_heapElem>;
	for (int i = 1; i <= g.getNodeCounter(); ++i) {
		t_heapElem elem;
		elem.nodeIndex = i;
		elem.parent = -1;
		if (i == startIndex) {
			elem.distance = 0;
		} else {
			elem.distance = INT_MAX;
		}
		heap->push_back(elem);
	}
	return heap;
}

t_heapElem extractMin(vector<t_heapElem>* heap) {
	t_heapElem min = *heap->begin();
	int minIndex = 0;
	int i = 1;
	for (vector<t_heapElem>::iterator it = heap->begin() + 1; it != heap->end(); ++it, ++i) {
		if ((*it).distance < min.distance) {
			min = *it;
			minIndex = i;
		}
	}
	heap->erase(heap->begin() + minIndex);
	return min;
}

t_edge getEdge(vector<t_edge>* edges, int a, int b) {
	for (vector<t_edge>::iterator it = edges->begin(); it != edges->end(); ++it) {
		if (((*it).sourceIndex == a && (*it).destinationIndex == b)
            || ((*it).sourceIndex == b && (*it).destinationIndex == a)) {
			return *it;
		}
	}
	cout << "Could't find edge from " << a << " to " << b << "!" << endl;
    exit(EXIT_FAILURE);
}

list<int>* getAdj(vector<t_edge>* edges, int nodeIndex) {
	list<int>* adj = new list<int>();
	for (vector<t_edge>::iterator it = edges->begin(); it != edges->end(); ++it) {
		int destinationIndex;
		if ((*it).sourceIndex == nodeIndex) {
			destinationIndex = (*it).destinationIndex;
		} else if ((*it).destinationIndex == nodeIndex) {
			destinationIndex = (*it).sourceIndex;
		} else {
			continue;
		}
		adj->push_back(destinationIndex);
	}
	return adj;
}

int getHeapElemIndex(vector<t_heapElem>* heap, int nodeIndex) {
	int i = 0;
	for (vector<t_heapElem>::iterator it = heap->begin(); it != heap->end(); ++it, ++i) {
		if ((*it).nodeIndex == nodeIndex) {
			return i;
		}
	}
	return -1;
}

void JP_MST(CGraph& g, const int startIndex) {
	vector<t_edge>* edges = removeEdgesFromGraph(g);
	vector<t_heapElem>* heap = buildHeap(g, startIndex);
	while (!heap->empty()) {
		t_heapElem nearestElem = extractMin(heap);
		if (nearestElem.nodeIndex != startIndex) {
			g.addEdge(getEdge(edges, nearestElem.parent, nearestElem.nodeIndex));
		}
		list<int>* adj = getAdj(edges, nearestElem.nodeIndex);
		for (list<int>::iterator it = adj->begin(); it != adj->end(); ++it) {
			int adjElemIndex = getHeapElemIndex(heap, *it);
			if (adjElemIndex == -1)
				continue;
			t_heapElem adjElem = (*heap)[adjElemIndex];
			int edgeValue = getEdge(edges, nearestElem.nodeIndex, *it).value;
			if (edgeValue >= adjElem.distance)
				continue;
			adjElem.parent = nearestElem.nodeIndex;
			adjElem.distance = edgeValue;
			heap->erase(heap->begin() + adjElemIndex);
			heap->push_back(adjElem);
		}
		delete adj;
	}
	delete edges;
	delete heap;
}

#ifndef __PROGTEST__

int main(int argc, const char * argv[])
{
    CGraph g;
    t_node node1;
    t_node node2;
    t_node node3;
    t_node node4;
    t_node node5;
    t_node node6;
    t_node node7;
    t_node node8;
    t_node node9;
    t_node node10;
    t_node node11;
    g.addNode(node1);
    g.addNode(node2);
    g.addNode(node3);
    g.addNode(node4);
    g.addNode(node5);
    g.addNode(node6);
    g.addNode(node7);
    g.addNode(node8);
    g.addNode(node9);
    g.addNode(node10);
    g.addNode(node11);
    t_edge edge1(1, 2, 59);
    t_edge edge2(1, 3, 81);
    t_edge edge3(1, 4, 6);
    t_edge edge4(1, 5, 21);
    t_edge edge5(1, 7, 56);
    t_edge edge6(1, 8, 15);
    t_edge edge7(1, 11, 89);
    t_edge edge8(2, 3, 19);
    t_edge edge9(2, 5, 61);
    t_edge edge10(2, 6, 76);
    t_edge edge11(2, 7, 99);
    t_edge edge12(2, 9, 55);
    t_edge edge13(2, 10, 54);
    t_edge edge14(2, 11, 96);
    t_edge edge15(3, 4, 32);
    t_edge edge16(3, 6, 94);
    t_edge edge17(3, 7, 80);
    t_edge edge18(3, 8, 67);
    t_edge edge19(3, 9, 59);
    t_edge edge20(3, 10, 39);
    t_edge edge21(3, 11, 93);
    t_edge edge22(4, 5, 63);
    t_edge edge23(4, 7, 61);
    t_edge edge24(4, 8, 52);
    t_edge edge25(4, 9, 49);
    t_edge edge26(4, 10, 67);
    t_edge edge27(5, 7, 43);
    t_edge edge28(5, 8, 80);
    t_edge edge29(5, 9, 17);
    t_edge edge30(5, 10, 6);
    t_edge edge31(5, 11, 77);
    t_edge edge32(6, 7, 76);
    t_edge edge33(6, 8, 38);
    t_edge edge34(6, 9, 34);
    t_edge edge35(6, 10, 48);
    t_edge edge36(6, 11, 93);
    t_edge edge37(7, 8, 48);
    t_edge edge38(7, 10, 36);
    t_edge edge39(7, 11, 11);
    t_edge edge40(8, 9, 61);
    t_edge edge41(8, 10, 11);
    t_edge edge42(9, 10, 61);
    t_edge edge43(9, 11, 15);
    t_edge edge44(10, 11, 17);
    g.addEdge(edge1);
    g.addEdge(edge2);
    g.addEdge(edge3);
    g.addEdge(edge4);
    g.addEdge(edge5);
    g.addEdge(edge6);
    g.addEdge(edge7);
    g.addEdge(edge8);
    g.addEdge(edge9);
    g.addEdge(edge10);
    g.addEdge(edge11);
    g.addEdge(edge12);
    g.addEdge(edge13);
    g.addEdge(edge14);
    g.addEdge(edge15);
    g.addEdge(edge16);
    g.addEdge(edge17);
    g.addEdge(edge18);
    g.addEdge(edge19);
    g.addEdge(edge20);
    g.addEdge(edge21);
    g.addEdge(edge22);
    g.addEdge(edge23);
    g.addEdge(edge24);
    g.addEdge(edge25);
    g.addEdge(edge26);
    g.addEdge(edge27);
    g.addEdge(edge28);
    g.addEdge(edge29);
    g.addEdge(edge30);
    g.addEdge(edge31);
    g.addEdge(edge32);
    g.addEdge(edge33);
    g.addEdge(edge34);
    g.addEdge(edge35);
    g.addEdge(edge36);
    g.addEdge(edge37);
    g.addEdge(edge38);
    g.addEdge(edge39);
    g.addEdge(edge40);
    g.addEdge(edge41);
    g.addEdge(edge42);
    g.addEdge(edge43);
    g.addEdge(edge44);

    JP_MST(g, 1);
    
    cout << g << endl;
    
    return 0;
}

#endif