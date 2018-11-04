#include <vector>
// #include"Graph.h"
using namespace std;
class Entry {
public:
	Entry();
	void Entry_Print();
	bool occupy;
	unsigned int index;
};
class TCAM {
public:
	TCAM();
	void TCAM_Print();
	void TCAM_Init();
	static unsigned int Capability;
	static unsigned int N_current;
	vector<Entry> entry;
	vector<int> Empty_List;
};
// void TCAM_Update(TCAM& tcam,const vector<int>& r)
