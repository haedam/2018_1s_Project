#include "DepartmentList.h"
using namespace std;

bool DepartmentList::insert(char department[]) {
	DepartmentNode* newDep = new DepartmentNode;

	strcpy_s(newDep->de_name, department);
	newDep->Pnext = Phead;

	if (Phead == NULL) {
		Phead = newDep;
	}
	else {
		Node* cur = Phead;
		while (cur->Pnext != Phead) {
			cur = cur->Pnext;
		}
		cur->Pnext = newDep;
	}

	return 0;
}

bool DepartmentList::pop(char department[]) {
	if (Phead == NULL) {
		return 0;
	}
	Node* cur = Phead;
	DepartmentNode* pop;

	do {
		pop = (DepartmentNode*)cur;

		if (!strcmp(pop->de_name, department)) {
			pop->Pnext = cur->Pnext;
			delete pop;
			return 0;
		} // pop works

		cur = cur->Pnext;
	} while (cur != Phead);
	return 1; // pop does not work
}

bool DepartmentList::modify_department(char before[], char after[]) {
	Node* cur = Phead;
	DepartmentNode* depCur = NULL;
	DepartmentNode* beforeDep = NULL;
	DepartmentNode* afterDep = NULL;

	do { // find a node that has same de_name as before and after
		depCur = (DepartmentNode*)cur;
		if (!strcmp(depCur->de_name, before)) {
			beforeDep = depCur;
		}
		if (!strcmp(depCur->de_name, after)) {
			afterDep = depCur;
		}
		cur = cur->Pnext;
	} while (cur != Phead);

	if (beforeDep == NULL) {
		return 1;
	} // if before department is not exist
	else if (afterDep == NULL) {
		strcpy_s(beforeDep->de_name, after);
	} // if after department is not exist
	else {
		cur = Phead;
		while (cur->Pnext != beforeDep) {
			cur = cur->Pnext;
		} // find pre_beforeDep
		cur->Pnext = beforeDep->Pnext;

		Node* afterName = afterDep->Pdown;
		while (afterName->Pdown != NULL) {
			afterName = afterName->Pdown;
		} // find the afterName's tail
		afterName->Pdown = beforeDep->Pdown;
		beforeDep->Pdown = NULL;
		delete beforeDep;
	} // if after department is already exist

	return 0;
}

bool DepartmentList::sort() {
	Node* cur = Phead->Pnext;
	Node* pre = Phead;
	if (cur == NULL) {
		return 1;
	} // Only one department is exist, do not sorting
	Node* cmp = NULL;
	Node* preCmp = NULL;
	DepartmentNode* insert;

	do {
		insert = (DepartmentNode*)cur;
		cmp = Phead;
		cur = cur->Pnext; // move cur to next
		while (cmp != insert) {
			// insert's de_name is greater than cmp's de_name
			if (strcmp(((DepartmentNode*)cmp)->de_name, insert->de_name) > 0) {
				if (cmp == Phead) {
					Phead = insert;
					insert->Pnext = cmp;
				} // if cmp is head, replace it to insert
				else {
					insert->Pnext = cmp;
					preCmp->Pnext = insert;
				}
				break;
			}
			preCmp = cmp;
			cmp = cmp->Pnext;
		}
		// if insert was not relocated, move pre
		if (pre->Pnext != cur)
			pre = pre->Pnext;
	} while (cur != Phead);

	return 0;
}

bool DepartmentList::insertStudent(NameNode* insert, char department[]) {
	Node* cur = Phead;
	Node* nameCur;
	DepartmentNode* depCur;

	do {
		depCur = (DepartmentNode*)cur;

		if (!strcmp(depCur->de_name, department)) {
			nameCur = cur;
			while (nameCur->Pdown) {
				nameCur = nameCur->Pdown;
			}
			nameCur->Pdown = insert;
			return 0;
		} // name insertion

		cur = cur->Pnext;
	} while (cur != Phead);

	return 1; // name insertion does not work
}

bool DepartmentList::nameSort_Ascend() {
	Node* pre = Phead->Pdown;
	Node* cur = pre->Pdown;
	if (cur == NULL) {
		return 1;
	} // Only one name is exist, do not sorting
	Node* cmp;
	Node* preCmp;
	NameNode* insert;

	do {
		insert = (NameNode*)cur;
		preCmp = Phead;
		cmp = Phead->Pdown;
		cur = cur->Pdown; // move cur to next
		while (cmp != insert) {
			// insert's name is greater than cmp's name
			if (strcmp(((NameNode*)cmp)->name, insert->name) > 0) {
				insert->Pdown = cmp;
				preCmp->Pdown = insert;
				break;
			}
			preCmp = cmp;
			cmp = cmp->Pnext;
		}
		// if insert was not relocated, move pre
		if (pre->Pnext != cur)
			pre = pre->Pnext;
	} while (cur);

	return 0;
}

bool DepartmentList::nameSort_Descend() {
	Node* pre = Phead->Pdown;
	Node* cur = pre->Pdown;
	if (cur == NULL) {
		return 1;
	} // Only one name is exist, do not sorting
	Node* cmp;
	Node* preCmp;
	NameNode* insert;

	do {
		insert = (NameNode*)cur;
		preCmp = Phead;
		cmp = Phead->Pdown;
		cur = cur->Pdown; // move cur to next
		while (cmp != insert) {
			// insert's name is greater than cmp's name
			if (strcmp(((NameNode*)cmp)->name, insert->name) < 0) {
				insert->Pdown = cmp;
				preCmp->Pdown = insert;
				break;
			}
			preCmp = cmp;
			cmp = cmp->Pnext;
		}
		// if insert was not relocated, move pre
		if (pre->Pnext != cur)
			pre = pre->Pnext;
	} while (cur);

	return 0;
}

bool DepartmentList::print() {
	DepartmentNode* dep = (DepartmentNode*)Phead;
	NameNode* name;
	GradeNode* gradeNode;
	StudentIDNode* ID;
	ContactNode* contct;
	string print("");
	char grade[2];
	grade[1] = '\0';

	while (dep != Phead) {
		dep = (DepartmentNode*)dep->Pnext;
		name = (NameNode*)dep->Pdown;
		while (name) {
			gradeNode = name->Pleft;
			ID = name->Pfront;
			contct = name->Pright;

			print.append(dep->de_name);
			print.append("/");
			print.append(name->name);
			print.append("/");
			grade[0] = gradeNode->grade + '0';
			print.append(grade);
			print.append("/");
			print.append(ID->studentid);
			print.append("/");
			print.append(contct->contact);
			print.append("\n");

			name = (NameNode*)name->Pdown;
		}
	}
	cout << print << endl;
	return 0;
}

bool DepartmentList::print(char department[]) {
	DepartmentNode* dep = (DepartmentNode*)Phead;
	NameNode* name;
	GradeNode* gradeNode;
	StudentIDNode* ID;
	ContactNode* contct;

	while (!strcmp(department, dep->de_name)) {
		dep = (DepartmentNode*)dep->Pnext;
	}
	
	string print("");
	name = (NameNode*)dep->Pdown;
	char grade[2];
	grade[1] = '\0';

	while (name) {
		gradeNode = name->Pleft;
		ID = name->Pfront;
		contct = name->Pright;

		print.append(dep->de_name);
		print.append("/");
		print.append(name->name);
		print.append("/");
		grade[0] = gradeNode->grade + '0';
		print.append(grade);
		print.append("/");
		print.append(ID->studentid);
		print.append("/");
		print.append(contct->contact);
		print.append("\n");

		name = (NameNode*)name->Pdown;
	}
	cout << print << endl;
	return 0;
}

bool DepartmentList::save(char fileName[]) {
	ofstream saveFile(fileName); // 과순으로 오름차순, 학과기준->이름
	if (!saveFile) {
		cerr << "Error opening save file \n";
		return 1;
	}
	DepartmentNode* dep = (DepartmentNode*)Phead->Pnext;
	NameNode* name;
	GradeNode* gradeNode;
	StudentIDNode* ID;
	ContactNode* contct;
	string print("");
	char grade[2];
	grade[1] = '\0';

	while (dep != Phead) {
		name = (NameNode*)dep->Pdown;
		while (name) {
			gradeNode = name->Pleft;
			ID = name->Pfront;
			contct = name->Pright;

			print.append(dep->de_name);
			print.append("/");
			print.append(name->name);
			print.append("/");
			grade[0] = gradeNode->grade + '0';
			print.append(grade);
			print.append("/");
			print.append(ID->studentid);
			print.append("/");
			print.append(contct->contact);
			print.append("\n");

			name = (NameNode*)name->Pdown;
		}
		dep = (DepartmentNode*)dep->Pnext;
	}
	saveFile << print << endl;
	saveFile.close();
	return 0;
}

bool DepartmentList::changeDep(char name[], char before[], char after[]) {
	Node* nameNode = Phead->Pnext;
	Node* cur = Phead->Pnext;

	// finde nameNode that has same name
	while (nameNode) {
		if (strcmp(((DepartmentNode*)nameNode)->de_name, before)) {
			nameNode = nameNode->Pdown;
			while (strcmp(((NameNode*)nameNode)->name, name)) {
				nameNode = nameNode->Pdown;
				if (!nameNode) {
					//error: cannot find name in before
					return 1;
				}
			} // findout

			// delete link
			nameNode->Pup->Pdown = nameNode->Pdown;
			nameNode->Pdown->Pup = nameNode->Pup;
			break;
		}
		nameNode = nameNode->Pnext;
	}
	
	// insert nameNode in new department
	while (cur) {
		if (strcmp(((DepartmentNode*)cur)->de_name, after)) {
			nameNode->Pdown = cur->Pdown;
			cur->Pdown = nameNode;
			return 0;
		}
		cur = cur->Pnext;
	}

	return 1; // insertion error
}

char* DepartmentList::getDep(char name[]) {
	Node* dep = Phead->Pnext;
	NameNode* cur = NULL;
	while (dep) {
		cur = (NameNode*)dep->Pdown;
		while (cur) {
			if (!strcmp(cur->name, name)) {
				return ((DepartmentNode*)dep)->de_name;
			}
			cur = (NameNode*)cur->Pdown;
		}
		dep = dep->Pnext;
	}

	return NULL;
}