#include "Graph.h"
#include "TCAM.h"
#include <vector>
#include<algorithm>
using namespace std;
void Map_Graph_To_TCAM(Graph& dag,TCAM& tcam);
void Map_Graph_To_TCAM_Empty_Random(Graph& dag,TCAM& tcam);
void Map_Graph_To_TCAM_3(Graph& dag, TCAM& tcam);
void Map_Graph_To_TCAM_Empty_Uniform(Graph& dag,TCAM& tcam);
int loadrule(FILE *fp, vector<Node>& rule);
int remove_redundancy(vector<Node>& rule, int rule_num);
unsigned int Find_Low_Boundary(const Graph& dag,const Node& update);
unsigned int Find_High_Boundary(const Graph& dag,const Node& update);
unsigned int Find_Low_Boundary_2(const Graph& dag,const Node& update);
unsigned int Find_High_Boundary_2(const Graph& dag,const Node& update);
void Algorithm_1(const Graph& dag,Node& update,vector<int>& r);
void Rule_Set_Into_Graph(Graph& dag,vector<Node>& rule_set,const unsigned int n);
void Rule_Set_Split(vector<Node>& rule_set,vector<Node>& rule_in_TCAM,vector<Node>& rule_to_Update,const unsigned int interval);
void Graph_Update(Graph& dag,TCAM& tcam,Node& update,vector<int>& r);
void TCAM_Update_2(Graph& dag, TCAM& tcam, Node& update, vector<int>& r);
void TCAM_Update(Graph& dag,TCAM& tcam,Node& update,vector<int>& r);
void Algorithm_2(const Graph& dag,const TCAM& tcam, Node& update,vector<int>& r);
void Algorithm_3(Graph& dag,TCAM& tcam, Node& update,double& t,vector<int>& r);
void TCAM_Print_Intact(const Graph& dag,const TCAM& tcam);
bool Correctness_Judge(const Graph& dag);
bool Collision_Judge(const Graph& dag,const Node& update);
void Algorithm_4(const Graph& dag, const TCAM& tcam, Node& update, vector<int>& r);
unsigned int Find_First_Empty_Location_Up(const vector<int>& Empty_List,const unsigned value);
unsigned int Find_First_Empty_Location_Down(const vector<int>& Empty_List,const unsigned value);
void Find_One_Solution_Up(const Graph& dag,const TCAM& tcam,const Node& rule,const unsigned int pos,vector<int>& r);
void Find_One_Solution_Down(const Graph& dag,const TCAM& tcam,const Node& rule,const unsigned int pos,vector<int>& r);
unsigned int Collision_Judge_With_Solved(Graph& dag,TCAM& tcam,Node& update);
void Graph_And_TCAM_Update_With_Collision(Graph& dag,TCAM& tcam,vector<int>& r);