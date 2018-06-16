#include "Manager.h"
using namespace std;

void Manager::LEAD_COMMAND(){
	ifstream cmdFile("Command.txt");
	ofstream log("LOG.txt"); // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if (!cmdFile || !log) {
		cerr << "Error opening save file \n";
		return;
	}

	string cmdline;
	char cmd[32], parameter[32], parameter2[32];
	int i, split, strinit;

	while (cmdFile.peek() != EOF) {
		getline(cmdFile, cmdline);

		i = -1;
		split = 0;
		strinit = 0;
		cmd[0] = NULL;
		parameter[0] = NULL;
		parameter2[0] = NULL;

		do {
			i++;
			if (cmdline[i] == ' ') {
				if (!split) {
					cmd[i] = '\0';
				}
				else {
					parameter[i - strinit] = '\0';
				}
				split++;
				strinit = i + 1;
			} // split setting
			else if (!split) {
				cmd[i] = cmdline[i];
			} // get cmd
			else if(split == 1){
				parameter[i - strinit] = cmdline[i];
			} // get parameter
			else {
				parameter2[i - strinit] = cmdline[i];
			} // get parameter2
		} while (cmdline[i] != '\0');

		//parameter2[i - strinit] = '\0';

		if (!strcmp(cmd, "LOAD")) {
			LOAD();
		}
		else if (!strcmp(cmd, "ADD")) {
			ADD();
		}
		else if (!strcmp(cmd, "UPDATE")) {
			UPDATE();
		}
		else if (!strcmp(cmd,"MODIFY_DEPARTMENT")) {
			if (!parameter || !parameter2) {
				// error occurs
			}
			MODIFY_DEPARTMENT(parameter, parameter2);
		}
		else if (!strcmp(cmd, "DELETE_DEPARTMENT")) {
			DELETE_DEPARTMENT(parameter);
		}
		else if (!strcmp(cmd, "PRINT")) {
			if (!parameter) {
				PRINT();
			}
			else {
				PRINT(parameter);
			}
		}
		else if (!strcmp(cmd, "PRINT_STUDENT_ID")) {
			PRINT_STUDENT_ID();
		}
		else if (!strcmp(cmd, "PRINT_CONTACT")) {
			PRINT_CONTACT();
		}
		else if (!strcmp(cmd, "FIND_NAME")) {
			if (!parameter) {
				// error
			}
			FIND_NAME(parameter);
		}
		else if (!strcmp(cmd, "SAVE")) {
			SAVE(parameter);
		}
		else if (!strcmp(cmd, "EXIT")) {
			cmdFile.close();
			log.close();
			return;
		}
		else; // ******************************
	}
}

bool Manager::LOAD() {
	ifstream infoFile("Information.txt");
	if (!infoFile) {
		cerr << "Error opening save file \n";
		return 1;
	}
	string infoline;
	char dep[32], name[32], studentID[32], contact[32];
	int grade, i, j, split, strinit;

	while (infoFile.peek() != EOF) {
		getline(infoFile, infoline);
		
		i = -1;
		j = 0;
		split = 0;
		strinit = 0;
		dep[0] = NULL;
		name[0] = NULL;
		studentID[0] = NULL;
		contact[0] = NULL;

		do {
			i++;
			if (infoline[i] == '\t') {
				switch (split) {
				case 0:
					dep[j] = '\0';
					break;
				case 1:
					name[j] = '\0';
					break;
				case 3:
					studentID[j] = '\0';
					break;
				}
				split++;
				j = 0;
			} // split setting
			else if (!split) {
				dep[j] = infoline[i];
			} // get department
			else if (split == 1) {
				name[j] = infoline[i];
			} // get name
			else if (split == 2) {
				grade = (int)(infoline[i]-'0');
			} // get grade
			else if (split == 3) {
				studentID[j] = infoline[i];
			}
			else {
				contact[j] = infoline[i];
			}
			j++;
		} while (infoline[i] != '\0');

		departmentlist.insert(dep);
		// namelist.insert returns namenode
		departmentlist.insertStudent(namelist.insert(name, grade, studentID, contact), dep);
	}

	// set IDlist, contctlist, gradelist
	IDlist.setHead();
	contctlist.setHead();
	gradelist.setHead();
	namelist.setHead(gradelist.getHead(), IDlist.getHead(), contctlist.getHead());

	infoFile.close();
	return 0;
}

bool Manager::ADD() {
	ifstream infoFile("Add_Information.txt");
	if (!infoFile) {
		cerr << "Error opening save file \n";
		return 1;
	}
	string infoline;
	char dep[32], name[32], studentID[32], contact[32];
	int grade, i, j, split, strinit;

	while (infoFile.peek() != EOF) {
		getline(infoFile, infoline);

		i = -1;
		j = 0;
		split = 0;
		strinit = 0;
		dep[0] = NULL;
		name[0] = NULL;
		studentID[0] = NULL;
		contact[0] = NULL;

		do {
			i++;
			if (infoline[i] == '\t') {
				switch (split) {
				case 0:
					dep[j] = '\0';
					break;
				case 1:
					name[j] = '\0';
					break;
				case 3:
					studentID[j] = '\0';
					break;
				}
				split++;
				j = 0;
			} // split setting
			else if (!split) {
				dep[j] = infoline[i];
			} // get department
			else if (split == 1) {
				name[j] = infoline[i];
			} // get name
			else if (split == 2) {
				grade = (int)(infoline[i] - '0');
			} // get grade
			else if (split == 3) {
				studentID[j] = infoline[i];
			}
			else {
				contact[j] = infoline[i];
			}
			j++;
		} while (infoline[i] != '\0');

		departmentlist.insert(dep);
		// namelist.insert returns namenode
		departmentlist.insertStudent(namelist.insert(name, grade, studentID, contact), dep);
	}

	infoFile.close();
	return 0;
}

bool Manager::UPDATE() {
	ifstream update("Update_information.txt");
	if (!update) {
		cerr << "Error opening save file \n";
		return 1;
	}
	string updateline;

	char dep[32], name[32], studentID[32], contact[32];
	int grade, i, j, split, strinit;

	while (update.peek() != EOF) {
		getline(update, updateline);

		i = -1;
		j = 0;
		split = 0;
		strinit = 0;
		dep[0] = NULL;
		name[0] = NULL;
		studentID[0] = NULL;
		contact[0] = NULL;

		do {
			i++;
			if (updateline[i] == '\t') {
				switch (split) {
				case 0:
					dep[j] = '\0';
					break;
				case 1:
					name[j] = '\0';
					break;
				case 3:
					studentID[j] = '\0';
					break;
				}
				split++;
				j = 0;
			} // split setting
			else if (!split) {
				dep[j] = updateline[i];
			} // get department
			else if (split == 1) {
				name[j] = updateline[i];
			} // get name
			else if (split == 2) {
				grade = (int)(updateline[i] - '0');
			} // get grade
			else if (split == 3) {
				studentID[j] = updateline[i];
			}
			else {
				contact[j] = updateline[i];
			}
			j++;
		} while (updateline[i] != '\0');

		//update
		departmentlist.changeDep(name, departmentlist.getDep(name), dep);
	}

	update.close();
	return 0;
}

bool Manager::MODIFY_DEPARTMENT(char before[], char after[]) {
	departmentlist.modify_department(before, after);
	return 0;
}

bool Manager::DELETE_DEPARTMENT(char department[]) {
	departmentlist.pop(department);
	return 0;
}

bool Manager::PRINT() {
	departmentlist.nameSort_Descend();
	departmentlist.print(); // 내림차순
	return 0;
}

bool Manager::PRINT(char department[]) {
	departmentlist.nameSort_Descend();
	departmentlist.print(department); // 내림차순
	return 0;
}

bool Manager::PRINT_STUDENT_ID() {
	IDlist.sort();
	namelist.printID(IDlist.getHead()); // 삽입정렬, 오름차순
	return 0;
}

bool Manager::PRINT_CONTACT() {
	contctlist.sort();
	namelist.printContct(contctlist.getHead()); // 선택정렬, 내림차순
	return 0;
}

bool Manager::FIND_NAME(char name[]) {
	namelist.sort();
	namelist.get(name); // 거품정렬, 오름차순
	return 0;
}

bool Manager::SAVE(char fileName[]) {
	departmentlist.sort();
	departmentlist.nameSort_Ascend(); // sorting
	departmentlist.save(fileName);
	return 0;
}