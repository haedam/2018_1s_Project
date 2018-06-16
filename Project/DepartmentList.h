#pragma once
#include "Department.h"
#include "Name.h"
#include <string>
#include <fstream>

// Department node의 Linked list를 가지는 Class
class DepartmentList {
private:
	DepartmentNode *Phead;

public:
	DepartmentList() :Phead(NULL) {}
	~DepartmentList() {
		delete Phead;
	}

	bool insert(char department[]);
	bool pop(char department[]);
	bool modify_department(char before[], char after[]);
	bool sort();
	bool insertStudent(NameNode* insert, char department[]);
	bool nameSort_Ascend();
	bool nameSort_Descend();
	bool print();
	bool print(char deoartment[]);
	bool save(char fileName[]);
	bool changeDep(char name[], char before[], char after[]);
	char* getDep(char name[]);
};