#pragma once
#include "Contctlist.h"
#include "DepartmentList.h"
#include "Gradelist.h"
#include "Namelist.h"
#include "StudentIDlist.h"

#include <fstream>

// Command.txt로부터 명령어를 읽고 다른 class들을
// 이용하여 명령어의 전체적인 동작을 수행하는 Class
class Manager {
private:
	ContctList contctlist;
	DepartmentList departmentlist;
	GradeList gradelist;
	NameList namelist;
	StudentIDList IDlist;
public:
	void LEAD_COMMAND();
	bool LOAD();
	bool ADD();
	bool UPDATE();
	bool MODIFY_DEPARTMENT(char before[], char after[]);
	bool DELETE_DEPARTMENT(char department[]);
	bool PRINT();
	bool PRINT(char department[]);
	bool PRINT_STUDENT_ID();
	bool PRINT_CONTACT();
	bool FIND_NAME(char name[]);
	bool SAVE(char fileName[]);
};