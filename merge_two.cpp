#include<vector>
#include"merge_two.h"
#include<algorithm>
#include<ctime>
#include<cstdlib>
using namespace std;
void Map_Graph_To_TCAM_Empty_Random(Graph& dag,TCAM& tcam){
	srand((unsigned int)clock());
	//tcam.Empty_List.clear();
	printf("%d",TCAM::Capability);
	for(unsigned int i =1;i<= TCAM::Capability;i++){
		tcam.Empty_List.push_back(i);
	}
	random_shuffle(tcam.Empty_List.begin(),tcam.Empty_List.end());
	unsigned int n = Graph::Capability - Graph::N_current; 
	sort(tcam.Empty_List.begin()+n,tcam.Empty_List.end());
	TCAM::N_current = 0;
	for(int i = 1;i <=Graph::N_current;i++){
		dag.array[i].position = tcam.Empty_List[n+i-1];
		tcam.entry[tcam.Empty_List[n+i-1]].index = i;
		tcam.entry[tcam.Empty_List[n+i-1]].occupy = true;
		TCAM::N_current++;
	}
	tcam.Empty_List.resize(n);
	sort(tcam.Empty_List.begin(), tcam.Empty_List.end());
}


void Map_Graph_To_TCAM_Empty_Uniform(Graph& dag,TCAM& tcam){
	TCAM::N_current = 0;
	tcam.Empty_List.clear();
	unsigned int k = TCAM::Capability/(TCAM::Capability - Graph::N_current);
	for(unsigned int i = 1;i <= TCAM::Capability;i++){
		if(TCAM::N_current == Graph::N_current){
			tcam.Empty_List.push_back(i);
		}
		else if(i%k == 0){
			tcam.Empty_List.push_back(i);
		}
		else{
			TCAM::N_current++;
			dag.array[TCAM::N_current].position = i;
			tcam.entry[i].index = TCAM::N_current;
			tcam.entry[i].occupy = true;
		}
	}
}







void Map_Graph_To_TCAM_3(Graph& dag, TCAM& tcam) {
	//srand((unsigned int)clock());
	//tcam.Empty_List.clear();
	unsigned int n = Graph::Capability - Graph::N_current;
	//printf("%d", TCAM::Capability);
	for (unsigned int i = 1; i <= n; i++) {
		tcam.Empty_List.push_back(i+ Graph::N_current);
	}
	//random_shuffle(tcam.Empty_List.begin(), tcam.Empty_List.end());

	//sort(tcam.Empty_List.begin() + n, tcam.Empty_List.end());
	TCAM::N_current = 0;
	for (int i = 1; i <= Graph::N_current; i++) {
		dag.array[i].position = i;
		tcam.entry[i].index = i;
		tcam.entry[i].occupy = true;
		TCAM::N_current++;
	}
	//tcam.Empty_List.resize(n);
	//sort(tcam.Empty_List.begin(), tcam.Empty_List.end());
}
void Map_Graph_To_TCAM(Graph& dag,TCAM& tcam){
	TCAM::N_current = 0;
	for(int i = 1;i <=Graph::N_current;i++){
		dag.array[i].position = i;
		tcam.entry[i].index = i;
		tcam.entry[i].occupy = true;
		TCAM::N_current++;
		
	}
}
int remove_redundancy(vector<Node>& rule,int rule_num){

	int cover;
	int tmp, tmp2;
	int num_rst = 0;

	if (rule_num == 1) return rule_num;

	tmp = rule_num - 1;
	tmp2 = rule_num - 2;
	while (tmp >= 1) {
		for (int i = tmp2; i >= 0; i--) {
			int k = 0;
			cover = 1;
			while (k < 4)
			{				
				if (max(rule[i].src_ip.low, rule[tmp].src_ip.low) > max(rule[tmp].src_ip.low, rule[tmp].src_ip.low) ||
					min(rule[i].src_ip.high, rule[tmp].src_ip.high) < min(rule[tmp].src_ip.high, rule[tmp].src_ip.high))
				{
					cover = 0;
					break;
				}
				else k++;

				if (max(rule[i].dst_ip.low, rule[tmp].dst_ip.low) > max(rule[tmp].dst_ip.low, rule[tmp].dst_ip.low) ||
					min(rule[i].dst_ip.high, rule[tmp].dst_ip.high) < min(rule[tmp].dst_ip.high, rule[tmp].dst_ip.high))
				{
					cover = 0;
					break;
				}
				else k++;

				if (max(rule[i].src_port.low, rule[tmp].src_port.low) > max(rule[tmp].src_port.low, rule[tmp].src_port.low) ||
					min(rule[i].src_port.high, rule[tmp].src_port.high) < min(rule[tmp].src_port.high, rule[tmp].src_port.high))
				{
					cover = 0;
					break;
				}
				else k++;

				if (max(rule[i].dst_port.low, rule[tmp].dst_port.low) > max(rule[tmp].dst_port.low, rule[tmp].dst_port.low) ||
					min(rule[i].dst_port.high, rule[tmp].dst_port.high) < min(rule[tmp].dst_port.high, rule[tmp].dst_port.high))
				{
					cover = 0;
					break;
				}
				else k++;

			}
		
			if (cover == 1) {

				for (int j = tmp; j < rule_num - 1; j++) {
					rule[j] = rule[j+1];
				}

				rule_num --;

				break;
			}
		}
		tmp--;
		tmp2--;
	}
	return rule_num;
}
int loadrule(FILE *fp, vector<Node>& rule_set) {

	int tmp;
	unsigned sip1, sip2, sip3, sip4, siplen;
	unsigned dip1, dip2, dip3, dip4, diplen;
	unsigned proto, protomask;
	unsigned s1, s2;
	const unsigned int i = 0;
	unsigned int cnt = 0;
	vector<Node> rule(1);
	while (1) {

		if (fscanf_s(fp, "@%d.%d.%d.%d/%d\t%d.%d.%d.%d/%d\t%d : %d\t%d : %d\t%x/%x\t%x/%x\n",
			&sip1, &sip2, &sip3, &sip4, &siplen, &dip1, &dip2, &dip3, &dip4, &diplen,
			&rule[i].src_port.low, &rule[i].src_port.high, &rule[i].dst_port.low, &rule[i].dst_port.high,
			&proto, &protomask,&s1,&s2) != 18) break;
		if (siplen == 0) {
			rule[i].src_ip.low = 0;
			rule[i].src_ip.high = 0xFFFFFFFF;
		}
		else if (siplen > 0 && siplen <= 8) {
			tmp = sip1 << 24;
			rule[i].src_ip.low = tmp;
			rule[i].src_ip.high = rule[i].src_ip.low + (1 << (32 - siplen)) - 1;
		}
		else if (siplen > 8 && siplen <= 16) {
			tmp = sip1 << 24; tmp += sip2 << 16;
			rule[i].src_ip.low = tmp;
			rule[i].src_ip.high = rule[i].src_ip.low + (1 << (32 - siplen)) - 1;
		}
		else if (siplen > 16 && siplen <= 24) {
			tmp = sip1 << 24; tmp += sip2 << 16; tmp += sip3 << 8;
			rule[i].src_ip.low = tmp;
			rule[i].src_ip.high = rule[i].src_ip.low + (1 << (32 - siplen)) - 1;
		}
		else if (siplen > 24 && siplen <= 32) {
			tmp = sip1 << 24; tmp += sip2 << 16; tmp += sip3 << 8; tmp += sip4;
			rule[i].src_ip.low = tmp;
			rule[i].src_ip.high = rule[i].src_ip.low + (1 << (32 - siplen)) - 1;
		}
		else {
			printf("Src IP length exceeds 32\n");
			return 0;
		}
		if (diplen == 0) {
			rule[i].dst_ip.low = 0;
			rule[i].dst_ip.high = 0xFFFFFFFF;
		}
		else if (diplen > 0 && diplen <= 8) {
			tmp = dip1 << 24;
			rule[i].dst_ip.low = tmp;
			rule[i].dst_ip.high = rule[i].dst_ip.low + (1 << (32 - diplen)) - 1;
		}
		else if (diplen > 8 && diplen <= 16) {
			tmp = dip1 << 24; tmp += dip2 << 16;
			rule[i].dst_ip.low = tmp;
			rule[i].dst_ip.high = rule[i].dst_ip.low + (1 << (32 - diplen)) - 1;
		}
		else if (diplen > 16 && diplen <= 24) {
			tmp = dip1 << 24; tmp += dip2 << 16; tmp += dip3 << 8;
			rule[i].dst_ip.low = tmp;
			rule[i].dst_ip.high = rule[i].dst_ip.low + (1 << (32 - diplen)) - 1;
		}
		else if (diplen > 24 && diplen <= 32) {
			tmp = dip1 << 24; tmp += dip2 << 16; tmp += dip3 << 8; tmp += dip4;
			rule[i].dst_ip.low = tmp;
			rule[i].dst_ip.high = rule[i].dst_ip.low + (1 << (32 - diplen)) - 1;
		}
		else {
			printf("Dest IP length exceeds 32\n");
			return 0;
		}
		rule[i].protocol.mask = protomask;
		rule[i].protocol.value = proto;

		rule[i].priority = cnt + 1;
		rule_set.push_back(rule[i]);
		cnt++;
	}
	return cnt;
}
unsigned int Find_Low_Boundary(const Graph& dag,const Node& update){
	unsigned int position = TCAM::N_current + 1;
	unsigned int k = 0;
	for(int i = 0;i < update.p_out.size();i++){
		k = update.p_out[i];
		position = min(position,dag.array[k].position);
	}
	return position;
}
unsigned int Find_Low_Boundary_2(const Graph& dag,const Node& update){
	unsigned int position = TCAM::Capability+1;
	unsigned int k = 0;
	for(int i = 0;i < update.p_out.size();i++){
		k = update.p_out[i];
		position = min(position,dag.array[k].position);
	}
	return position;
}
unsigned int Find_High_Boundary(const Graph& dag,const Node& update){
	unsigned int position = 0;
	unsigned int k = 0;
	for(int i = 0;i < update.p_in.size();i++){
		k = update.p_in[i];
		position = max(position,dag.array[k].position);
	}
	return position;
}
unsigned int Find_High_Boundary_2(const Graph& dag,const Node& update){
	unsigned int position = 0;
	unsigned int k = 0;
	for(int i = 0;i < update.p_in.size();i++){
		k = update.p_in[i];
		position = max(position,dag.array[k].position);
	}
	return position;
}
void Algorithm_1(const Graph& dag,Node& update,vector<int>& r){
	unsigned int k = Find_Low_Boundary(dag,update);
	for(;k<=TCAM::N_current+1;k++){
		r.push_back(k);
		// break;
	}
}
void Graph_Update(Graph& dag,TCAM& tcam,Node& update,vector<int>& r){
	// 1,2,3,8,9
	Graph::N_current++;
	dag.array[Graph::N_current] = update;
	dag.array[Graph::N_current].flag = true;
	
	for(unsigned int i = 0;i < update.p_in.size();i++){
		unsigned int index = update.p_in[i];
		dag.array[index].p_out.push_back(Graph::N_current);
	}
	for(unsigned int i = 0;i < update.p_out.size();i++){
		unsigned int index = update.p_out[i];
		dag.array[index].p_in.push_back(Graph::N_current);
	}
	for(unsigned int i =r.size()-1;i >=1;i--){
		dag.array[tcam.entry[r[i-1]].index].position = r[i];
	}
	dag.array[Graph::N_current].position = r[0];
}
void Graph_And_TCAM_Update_With_Collision(Graph& dag,TCAM& tcam,vector<int>& r){
	// 1,2,3,8,9 position
	
	for(unsigned int i = r.size()-1;i >= 1;i--){
		dag.array[tcam.entry[r[i-1]].index].position = r[i];
	}
	for (unsigned int i = r.size()-1; i >= 1; i--) {
		tcam.entry[r[i]] = tcam.entry[r[i - 1]];
	}
	tcam.entry[r[0]].occupy = false;
	tcam.entry[r[0]].index = 0;
	tcam.Empty_List.erase(find(tcam.Empty_List.begin(),tcam.Empty_List.end(),r.back()));
	tcam.Empty_List.push_back(r[0]);
	sort(tcam.Empty_List.begin(),tcam.Empty_List.end());

}
void TCAM_Update(Graph& dag,TCAM& tcam,Node& update,vector<int>& r){
	TCAM::N_current++;
	for(unsigned int i = r.size()-1;i>=1;i--){
		tcam.entry[r[i]] = tcam.entry[r[i-1]];
	}
	tcam.entry[r[0]].occupy = true;
	tcam.entry[r[0]].index = Graph::N_current;
}
void TCAM_Update_2(Graph& dag, TCAM& tcam, Node& update, vector<int>& r) {
	TCAM::N_current++;
	for (unsigned int i = r.size() - 1; i >= 1; i--) {
		tcam.entry[r[i]] = tcam.entry[r[i - 1]];
	}
	tcam.entry[r[0]].occupy = true;
	tcam.entry[r[0]].index = Graph::N_current;
	tcam.Empty_List.erase(find(tcam.Empty_List.begin(),tcam.Empty_List.end(),r.back()));
}
void Rule_Set_Into_Graph(Graph& graph,vector<Node>& rule_set,const unsigned int n){
	for(unsigned int c = 1;c<=n;c++){
		graph.array[c].src_ip = rule_set[c-1].src_ip;
		graph.array[c].dst_ip = rule_set[c-1].dst_ip;
		graph.array[c].src_port = rule_set[c-1].src_port;
		graph.array[c].dst_port = rule_set[c-1].dst_port;
		graph.array[c].priority = rule_set[c-1].priority;
		graph.array[c].flag = true;
		graph.array[c].position = c;
		Graph::N_current++;
	}
}
void Rule_Set_Split(vector<Node>& rule_set,vector<Node>& rule_in_TCAM,vector<Node>& rule_to_Update,const unsigned int interval){
	rule_in_TCAM.clear();
	rule_to_Update.clear();
	const unsigned int s  = rule_set.size();
	for(unsigned int i = 0; i < s;i++){
		//if (((i + 1) % interval == 0) || ((i + 1) == 1)) {
		if((i+1)%interval == 0){
			rule_to_Update.push_back(rule_set[i]);
		}
		else{
			rule_in_TCAM.push_back(rule_set[i]);
		}
		
	}
	
}
void Algorithm_2(const Graph& dag,const TCAM& tcam,Node& update,vector<int>& r){
	unsigned int k = Find_Low_Boundary(dag,update);
	if(tcam.entry[k].occupy == false){
		r.push_back(k);
	}
	else{
		do{
			r.push_back(k);
			k = Find_Low_Boundary(dag,dag.array[tcam.entry[k].index]);
		}
		while(tcam.entry[k].occupy == true);
		r.push_back(k);
	}
}
void Graph_Cost_Down_Computing(Graph& dag,TCAM& tcam){
	for(unsigned int i = TCAM::N_current;i >= 1;i--){
		unsigned int p_tmp,cost_tmp;
		unsigned int p = Find_Low_Boundary(dag,dag.array[tcam.entry[i].index]);
		p_tmp = p;
		cost_tmp = dag.array[tcam.entry[p_tmp].index].low_cost;
		for(unsigned int j = i+1; j < p; j++){
			if(cost_tmp > dag.array[tcam.entry[j].index].low_cost){
				p_tmp = j;
				cost_tmp = dag.array[tcam.entry[p_tmp].index].low_cost;
			}
		}
		dag.array[tcam.entry[i].index].low_cost = cost_tmp + 1;
		dag.array[tcam.entry[i].index].low_cost_index = p_tmp;
	}
}
void Algorithm_3(Graph& dag,TCAM& tcam,Node& update,double& t,vector<int>& r){
	Graph_Cost_Down_Computing(dag,tcam);
	double t_start,t_end;
	// Find_Relevant_Rule(dag,update);
	t_start = clock();
	unsigned int pos_low = Find_Low_Boundary(dag,update);
	unsigned int pos_high = Find_High_Boundary(dag,update);
	unsigned int pos_tmp = 0;
	unsigned int cost_tmp = 0xffff;
	for(unsigned int i = pos_high+1; i <= pos_low;i++){
		if(cost_tmp > dag.array[tcam.entry[i].index].low_cost){
			pos_tmp = i;
			cost_tmp = dag.array[tcam.entry[pos_tmp].index].low_cost;
		}
	}
	while(1){
		r.push_back(pos_tmp);
		if(tcam.entry[pos_tmp].occupy == false)
			break;
		pos_tmp = dag.array[tcam.entry[pos_tmp].index].low_cost_index;
		
	}
	t_end = clock();
	t = ((double)(t_end - t_start))/ CLOCKS_PER_SEC;
}
void TCAM_Print_Intact(const Graph& dag,const TCAM& tcam){
	printf("The TCAM's Capability is %d,and there exists %d Rules in TCAM\n",TCAM::Capability,TCAM::N_current);
	printf("Position\t Priority\t Low_Cost_Positon\tLow_Cost\n");
	for(unsigned int i = 1;i <= TCAM::N_current ;i++){
		if(tcam.entry[i].occupy == true)
		printf("%d\t\t    %d\t\t%d\t\t%d\n",i,dag.array[tcam.entry[i].index].priority,dag.array[tcam.entry[i].index].low_cost_index,dag.array[tcam.entry[i].index].low_cost);
	else{
		printf("%d\n",i);
	}
	}
}
bool Correctness_Judge(const Graph& dag){
	unsigned int s,from,to;
	bool r = true;
	for(unsigned int i = 1;i <= Graph::N_current;i++){
		s = dag.array[i].p_out.size();
		for(unsigned int j = 0;j<s;j++){
			if(dag.array[i].position >= dag.array[dag.array[i].p_out[j]].position){
				printf("Collision Happens Between Priority %d and Priority %d \n",dag.array[i].priority, dag.array[dag.array[i].p_out[j]].priority);
				r = false;
			}
		}
		
	}
	if(r)
		printf("Perfect! No collision Happens\n");
	else{
		printf("Shit!!! Collision Happens\n");
	}
	return r;
}
bool Collision_Judge(const Graph& dag,const Node& update){
	unsigned int k_low = Find_Low_Boundary(dag,update);
	unsigned int k_high = Find_High_Boundary(dag,update);
	if(k_low < k_high){
		// printf("Confliction happens and do not insert the update with the Priority %d\n",update.priority);
		return false;
	}
    else{
		return true;
	}
}
unsigned int Collision_Judge_With_Solved(Graph& dag,TCAM& tcam,Node& update){
	unsigned int k_low = Find_Low_Boundary_2(dag,update);
	unsigned int k_high = Find_High_Boundary_2(dag,update);
	unsigned int c  = 0;
	while(k_low < k_high){
			unsigned int empty_low = Find_First_Empty_Location_Down(tcam.Empty_List,k_low);
			unsigned int empty_high = Find_First_Empty_Location_Up(tcam.Empty_List,k_high);
			if(empty_high == 0 && empty_low == 0){
				cout<<"No Solution£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡"<<endl;
				return 0;
			}
			else if(empty_low != 0){
				vector<int> r;
				r.clear();
				Find_One_Solution_Down(dag,tcam,dag.array[tcam.entry[k_low].index],empty_low,r);
				r.push_back(empty_low);
				Graph_And_TCAM_Update_With_Collision(dag,tcam,r);
				c = c + r.size();
			}
			else{
				vector<int> r;
				r.clear();
				Find_One_Solution_Up(dag,tcam,dag.array[tcam.entry[k_high].index],empty_high,r);
				r.push_back(empty_high);
				Graph_And_TCAM_Update_With_Collision(dag,tcam,r);
				c = c + r.size();
			}
	k_low = Find_Low_Boundary_2(dag,update);
	k_high = Find_High_Boundary_2(dag,update);
			
	}
	return c;
}
void Algorithm_4(const Graph& dag,const TCAM& tcam,Node& update,vector<int>& r){
	vector<int>  tmp_r;
	r.clear();
	unsigned int k_low = Find_Low_Boundary_2(dag,update);
	unsigned int k_high = Find_High_Boundary_2(dag,update);
	unsigned int empty_low = Find_First_Empty_Location_Down(tcam.Empty_List,k_high);
	unsigned int empty_high = Find_First_Empty_Location_Up(tcam.Empty_List,k_low);
	if((empty_low != 0)&&(empty_low <= k_low) && (empty_low >= k_high)){
		r.push_back(empty_low);
		return ;
	}
	else if(empty_low != 0){
		unsigned int tmp_cost = 9999;
		vector<int> tmp_r;
		tmp_r.clear();
		for(unsigned int i = k_high+1;i <=k_low;i++){
			tmp_r.clear();
			Find_One_Solution_Down(dag,tcam,dag.array[tcam.entry[i].index],empty_low,tmp_r);
			if(tmp_r.size() < tmp_cost){
				tmp_cost = tmp_r.size();
				r = tmp_r;
			}
		}
		r.push_back(empty_low);
		return ;
	}
	else if(empty_high != 0){
		unsigned int tmp_cost = 9999;
		vector<int> tmp_r;
		tmp_r.clear();
		for(unsigned int i = k_high;i <=k_low-1;i++){
			tmp_r.clear();
			Find_One_Solution_Up(dag,tcam,dag.array[tcam.entry[i].index],empty_high,tmp_r);
			if(tmp_r.size() < tmp_cost){
				tmp_cost = tmp_r.size();
				r = tmp_r;
			}
		}
		r.push_back(empty_high);
		return ;
	}
	else
		printf("No solution!!!!!!!!!!!!\n");

}

//void Algorithm_4(const Graph dag, const TCAM tcam, Node update, vector<int>& r) {
//	vector<int>  tmp_r;
//	r.clear();
//	unsigned int k_low = Find_Low_Boundary_2(dag, update);
//	unsigned int k_high = Find_High_Boundary_2(dag, update);
//	unsigned int empty_low = Find_First_Empty_Location_Down(tcam.Empty_List, k_high);
//	unsigned int empty_high = Find_First_Empty_Location_Up(tcam.Empty_List, k_low);
//	if ((empty_low != 0) && (empty_low <= k_low) && (empty_low >= k_high)) {
//		r.push_back(empty_low);
//		return;
//	}
//	else if ((empty_high != 0) && (empty_high <= k_low) && (empty_high >= k_high)) {
//		r.push_back(empty_low);
//		return;
//	}
//	else if (empty_low != 0) {
//		unsigned int tmp_cost = 9999;
//		vector<int> tmp_r;
//		tmp_r.clear();
//		for (unsigned int i = k_high + 1;i <= k_low;i++) {
//			tmp_r.clear();
//			Find_One_Solution_Down(dag, tcam, dag.array[tcam.entry[i].index], empty_low, tmp_r);
//			if (tmp_r.size() == 1)
//			{
//				r = tmp_r;
//				r.push_back(empty_low);
//				return;
//			}
//			if (tmp_r.size() < tmp_cost) {
//				tmp_cost = tmp_r.size();
//				r = tmp_r;
//			}
//		}
//		r.push_back(empty_low);
//		return;
//	}
//	else if (empty_high != 0) {
//		unsigned int tmp_cost = 9999;
//		vector<int> tmp_r;
//		tmp_r.clear();
//		for (unsigned int i = k_high;i <= k_low - 1;i++) {
//			tmp_r.clear();
//			Find_One_Solution_Up(dag, tcam, dag.array[tcam.entry[i].index], empty_high, tmp_r);
//			if (tmp_r.size() == 1)
//			{
//				r = tmp_r;
//				r.push_back(empty_high);
//				return;
//			}
//			if (tmp_r.size() < tmp_cost) {
//				tmp_cost = tmp_r.size();
//				r = tmp_r;
//			}
//		}
//		r.push_back(empty_high);
//		return;
//	}
//	else
//		printf("No solution!!!!!!!!!!!!\n");
//
//
//}
void Find_One_Solution_Down(const Graph& dag,const TCAM& tcam,const Node& rule,const unsigned int pos,vector<int>& r){
	unsigned int tmp_pos = 9999;
	for(unsigned int i = 0;i < rule.p_out.size();i++){
		tmp_pos = min(tmp_pos,dag.array[rule.p_out[i]].position);
	}
	if(tmp_pos > pos){
		r.push_back(rule.position);
		return ;
	}
	else{
		r.push_back(rule.position);
		Find_One_Solution_Down(dag,tcam,dag.array[tcam.entry[tmp_pos].index],pos,r);
	}
}
void Find_One_Solution_Up(const Graph& dag,const TCAM& tcam,const Node& rule,const unsigned int pos,vector<int>& r){
	unsigned int tmp_pos = 0;
	for(unsigned int i = 0;i < rule.p_in.size();i++){
		tmp_pos = max(tmp_pos,dag.array[rule.p_in[i]].position);
	}
	if(tmp_pos < pos){
		r.push_back(rule.position);
		return ;
	}
	else{
		r.push_back(rule.position);
		Find_One_Solution_Up(dag,tcam,dag.array[tcam.entry[tmp_pos].index],pos,r);
	}
}
unsigned int Find_First_Empty_Location_Up(const vector<int>& Empty_List,const unsigned value){
	unsigned int r = 0;
	unsigned int end = Empty_List.size()-1;
	for( int i = 0;i <= end;i++){
		if(Empty_List[i]<value){
			r = Empty_List[i];
		}
		else{
			break;
		}
	}
	return r;
}
unsigned int Find_First_Empty_Location_Down(const vector<int>& Empty_List,const unsigned value){
	unsigned int r = 0;
	unsigned int end = Empty_List.size()-1;
	for(int i = end;i >=0;i--){
		if(Empty_List[i]>value){
			r = Empty_List[i];
		}
		else
			break;
	}
	return r;
}






















