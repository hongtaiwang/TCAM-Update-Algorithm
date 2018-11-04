#include"Graph.h"
#include <stdio.h>
using namespace std;
unsigned int  Graph::Capability = rule_set_Size;
unsigned int Graph::N_current = 0;
Src_IP::Src_IP() {}
Dst_IP::Dst_IP() {}
Src_PORT::Src_PORT() {}
Dst_PORT::Dst_PORT() {}
Protocol::Protocol() {}
Src_IP::Src_IP(const unsigned int low, const unsigned int high) {
	this->low = low;
	this->high = high;
}
Dst_IP::Dst_IP(const unsigned int low, const unsigned int high) {
	this->low = low;
	this->high = high;
}
Src_PORT::Src_PORT(const unsigned int low, const unsigned int high) {
	this->low = low;
	this->high = high;
}
Dst_PORT::Dst_PORT(const unsigned int low, const unsigned int high) {
	this->low = low;
	this->high = high;
}
Protocol::Protocol(const unsigned int value, const unsigned int mask) {
	this->value = value;
	this->mask = mask;
}
Graph::Graph() {
	this->array.clear();
	this->array.resize(Graph::Capability + 1);
}
void Graph::Graph_Print() {
	printf("(Pri\tPos)\t the output edge\n");
	for (int c = 0; c <= Graph::Capability; c++) {
		if(this->array[c].flag){
			printf("(%d\t%d): ",this->array[c].priority,this->array[c].position);
			for (int i = 0; i<this->array[c].p_out.size(); i++) {
				printf("(%d\t%d)",this->array[this->array[c].p_out[i]].priority,this->array[this->array[c].p_out[i]].position);
			}
			printf("\n");
		}
	}
}
Node::Node() {
	this->flag = false;
	this->priority = 0;
	this->position = 0;
	this->low_cost = 0;
	this->low_cost_index = 0;
	this->high_cost = 0;
	this->high_cost_index = 0;
	this->src_ip.low = 0;
	this->src_ip.high = 0;
	this->dst_ip.low = 0;
	this->dst_ip.high = 0;
	this->src_port.low = 0;
	this->src_port.high = 0;
	this->dst_port.low = 0;
	this->dst_port.high = 0;
	this->protocol.value = 0;
	this->protocol.mask = 0;
	this->p_in.clear();
	this->p_out.clear();
}

// void Node::Node_Print() {
	// printf("%d\t%d\n", this->priority, this->position);
	// for (int i = 0; i<this->p_out.size(); i++) {
		// printf(",%d",this->p_out[i]);
	// }
	// printf("\n");
// }

template <typename T>
bool Range_Overlap(T& x,T& y){
	if((x.low<=y.low && x.high>=y.low)||(x.low>y.low && x.low<=y.high))
		return true;
	else
		return false;
}
bool Node_Overlap(const Node& x,const Node& y){
	if(Range_Overlap(x.src_ip,y.src_ip)&&Range_Overlap(x.dst_ip,y.dst_ip)&&Range_Overlap(x.src_port,y.src_port)&&Range_Overlap(x.dst_port,y.dst_port))
		return true;
	else
		return false;
}
void Graph_Build(Graph& DAG){
	for(int c =1; c<=Graph::N_current;c++){
		for(int c_next = c+1;c_next <=Graph::N_current;c_next++){
			if(Node_Overlap(DAG.array[c],DAG.array[c_next])){
				if(DAG.array[c].priority<DAG.array[c_next].priority){
					DAG.array[c].p_out.push_back(c_next);
					DAG.array[c_next].p_in.push_back(c);
				}
				else{
					DAG.array[c].p_in.push_back(c_next);
					DAG.array[c_next].p_out.push_back(c);
				}
			}
		}
	}
	
}

void Find_Relevant_Rule(const Graph& dag,Node& update){
	
	for(unsigned int i = 1;i < Graph::N_current;i++){
		if(Node_Overlap(dag.array[i],update)){
			if(dag.array[i].priority<update.priority){
				update.p_in.push_back(i);
			}
			else{
				update.p_out.push_back(i);
			}
		}
	}
	
}

void Graph::Graph_Isolated_Node_Find(vector<int>& r){
	r.clear();
	int isolate_num = 0;
	
	for (unsigned int x = 1;x <= Graph::N_current;x++)
	{
		if ((this->array[x].p_in.size() == 0) && (this->array[x].p_out.size() == 0))
			r.push_back(this->array[x].priority);
	}
	cout << "There are " << r.size() << "isolate nodes." << endl;
}
void Graph::Graph_Init(){
	Graph::N_current = 0;
	this->array.clear();
	this->array.resize(Graph::Capability+1);
}

		