#include"TCAM.h"
#include <stdio.h>
#define rule_set_Size 1000
using namespace std;

unsigned int TCAM::Capability = rule_set_Size;
unsigned int TCAM::N_current = 0;
TCAM::TCAM() {
	this->entry.clear();
	this->Empty_List.clear();
	this->entry.resize(TCAM::Capability+1);
	// = new Entry[TCAM::Capability + 1];
}
void TCAM::TCAM_Print() {
	printf("Position:\tAvailable:\tthe related Node Index\n");
	for (int c = 1; c <= TCAM::Capability; c++) {
		if(this->entry[c].occupy == false){
			printf("%d\t",c);
			continue;
		}
		this->entry[c].Entry_Print();
	}
}
Entry::Entry() {
	this->occupy = false;
	this->index = 0;
}
void Entry::Entry_Print() {
	printf("%d\t%d\n", ~(this->occupy),this->index);
}
void TCAM::TCAM_Init(){
	TCAM::N_current = 0;
	this->entry.clear();
	this->entry.resize(TCAM::Capability+1);
	this->Empty_List.clear();
	}

