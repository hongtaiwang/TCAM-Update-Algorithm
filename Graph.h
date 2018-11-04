#include<vector>
#include<iostream>
using namespace std;
#define rule_set_Size 50
class Src_IP {
public:
	Src_IP();
	Src_IP(const unsigned int low, const unsigned int high);
	unsigned int low;
	unsigned int high;
};
class Dst_IP {
public:
	Dst_IP();
	Dst_IP(const unsigned int low, const unsigned int high);
	unsigned int low;
	unsigned int high;
};
class Src_PORT {
public:
	Src_PORT();
	Src_PORT(const unsigned int low, const unsigned int high);
	unsigned int low;
	unsigned int high;
};
class Dst_PORT {
public:
	Dst_PORT();
	Dst_PORT(const unsigned int low, const unsigned int high);
	unsigned int low;
	unsigned int high;
};
class Protocol {
public:
	Protocol();
	Protocol(const unsigned int value, const unsigned int mask);
	unsigned int value;
	unsigned int mask;
};
class Node {
public:
	Node();
	// void Node_Print();
	bool flag;
	unsigned int priority;
	unsigned int position;
	unsigned int low_cost;
	unsigned int low_cost_index;
	unsigned int high_cost;
	unsigned int high_cost_index;
	Src_IP src_ip;
	Dst_IP dst_ip;
	Src_PORT src_port;
	Dst_PORT dst_port;
	Protocol protocol;
	vector<int>p_out;
	vector<int>p_in;
};
class Graph {
public:
	static unsigned int Capability;
	static unsigned int N_current;
	vector<Node>array;
	Graph();
	void Graph_Init();
	void Graph_Print();
	void Graph_Isolated_Node_Find(vector<int>& r);
};
void Graph_Build(Graph& DAG);
bool Node_Overlap(const Node& x,const Node& y);
template <typename T>
bool Range_Overlap(T& x,T& y);
void Find_Relevant_Rule(const Graph& dag,Node& update);

