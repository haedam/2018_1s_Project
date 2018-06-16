#include "Namelist.h"
#include <string>
using namespace std;

/*
///////////////////////
// copy constructor
///////////////////////
NameList::NameList(const NameList& cpyList) {
	NameNode* cpyNode = cpyList.Phead;
	Phead = new NameNode;
	NameNode* cur = Phead;
	Node* dep;
	while (!cpyNode) {
		insert(cpyNode->name, cpyNode->Pleft->grade, cpyNode->Pfront->studentid, cpyNode->Pright->contact); // To copy Node
		cur = (NameNode*)cur->Pnext;
		dep = cpyNode->Pup;
		while (dep->Pup) {
			dep = dep->Pup;
		}
		cur->Pup = dep; // To copy departent
		cpyNode = (NameNode*)cpyNode->Pnext;
	}
}
*/

void NameList::setHead(GradeNode* gradeHead, StudentIDNode* IDHead, ContactNode* contctHead) {
	Phead->Pleft = gradeHead;
	Phead->Pfront = IDHead;
	Phead->Pright = contctHead;
}

NameNode* NameList::insert(char name[], int grade, char studentid[], char contact[]) {
	NameNode* newName = new NameNode;
	strcpy_s(newName->name, name);
	GradeNode* newGrade = new GradeNode;
	newGrade->grade = grade;
	StudentIDNode* newID = new StudentIDNode;
	strcpy_s(newID->studentid, studentid);
	ContactNode* newContact = new ContactNode;
	strcpy_s(newContact->contact, contact);

	newName->Pleft = newGrade;
	newName->Pfront = newID;
	newName->Pright = newContact;

	if (Phead == NULL) {
		Phead = new NameNode;
		Phead->Pnext = newName;
		newName->Pprev = Phead;
		Phead->Pleft = new GradeNode;
		Phead->Pfront = new StudentIDNode;
		Phead->Pright = new ContactNode;
		Phead->Pleft->Pleft = newName->Pleft;
		Phead->Pfront->Pfront = newName->Pfront;
		Phead->Pright->Pright = newName->Pright;
	}
	else {
		Node* cur = Phead;
		while (cur->Pnext) {
			cur = cur->Pnext;
		}
		cur->Pnext = newName;
		newName->Pprev = cur;
		NameNode* curName = (NameNode*)cur;
		curName->Pleft->Pleft = newName->Pleft;
		curName->Pfront->Pfront = newName->Pfront;
		curName->Pright->Pright = newName->Pright;
	}
	return newName;
}

bool NameList::pop(char name[]) {
	if (Phead == NULL) {
		return 1;
	}
	Node* cur = Phead;
	NameNode* pop;

	while (cur != NULL) {
		pop = (NameNode*)cur;

		if (!strcmp(pop->name, name)) {
			NameNode* pre = (NameNode*)pop->Pprev;
			pre->Pnext = pop->Pnext;
			pre->Pleft->Pleft = pop->Pleft->Pleft;
			pre->Pfront->Pfront = pop->Pfront->Pfront;
			pre->Pright->Pright = pop->Pright->Pright;
			pop->Pnext->Pprev = pre;
			delete pop;
			return 0;
		} // pop works

		cur = cur->Pnext;
	}

	return 1; // pop didn't work
}

// bubble sort
bool NameList::sort() {
	Node* cur = Phead->Pnext;
	if (cur == NULL) {
		return 1;
	} // Only one department is exist, do not sorting
	Node* bubble = NULL;
	Node* nBubble = NULL;
	char name[32] = "";

	while (cur->Pnext) {
		cur = cur->Pnext;
	}

	while (cur != Phead) {
		bubble = Phead;
		while (bubble != cur) {
			if (strcmp(((NameNode*)bubble)->name, ((NameNode*)bubble->Pnext)->name) > 0) {
				nBubble = bubble->Pnext;
				bubble->Pnext = nBubble->Pnext;
				nBubble->Pnext = bubble;
				nBubble->Pprev = bubble->Pprev;
				bubble->Pprev = nBubble;
			} // interchanging bubble with nBubble
			else
				bubble = bubble->Pnext;
		}
		cur = cur->Pprev;
	}
	return 0;
}

// find command
bool NameList::get(char name[]) {
	Node* dep;
	NameNode* cur = Phead;
	string print("");
	char grade[2];
	grade[1] = '\0';
	if (sizeof(name) <= 3 * sizeof(char)) {
		int end_of_fname = 0;
		while (cur) {
			if (!strncmp(name, cur->name, 2)) {
				dep = cur->Pup;
				while (dep->Pup) {
					dep = dep->Pup;
				} // get department
				print.append(((DepartmentNode*)dep)->de_name);
				print.append("/");
				print.append(name);
				print.append("/");
				grade[0] = cur->Pleft->grade + '0';
				print.append(grade);
				print.append("/");
				print.append(cur->Pfront->studentid);
				print.append("/");
				print.append(cur->Pright->contact);
				print.append("\0");
				end_of_fname = 1;
			}
			else if (end_of_fname)
				return 0;  // if family_name loop is end, end get func.
			
			cur = (NameNode*)cur->Pnext;
		}
	}
	else {
		while (cur) {
			if (!strcmp(name, cur->name)) {
				dep = cur->Pup;
				while (dep->Pup) {
					dep = dep->Pup;
				} // get department
				print.append(((DepartmentNode*)dep)->de_name);
				print.append("/");
				print.append(name);
				print.append("/");
				grade[0] = cur->Pleft->grade + '0';
				print.append(grade);
				print.append("/");
				print.append(cur->Pfront->studentid);
				print.append("/");
				print.append(cur->Pright->contact);
				print.append("\0");
				return 0;
			}
			cur = (NameNode*)cur->Pnext;
		}
	}
	return 0;
}

bool NameList::printID(StudentIDNode* IDhead) {
	StudentIDNode* IDNode = IDhead->Pfront;
	NameNode* cur;
	Node* dep;
	char ID[32] = "";
	char grade[2];
	grade[1] = '\0';
	string print("");

	while (IDNode) {
		strcpy_s(ID, IDNode->studentid);
		cur = (NameNode*)Phead->Pnext;
		while (cur) {
			if (!strcmp(ID, cur->Pfront->studentid)) {
				dep = (DepartmentNode*)cur->Pup;
				while (dep->Pup) {
					dep = dep->Pup;
				}
				print.append(((DepartmentNode*)dep)->de_name);
				print.append("/");
				print.append(cur->name);
				print.append("/");
				grade[0] = cur->Pleft->grade + '0';
				print.append(grade);
				print.append("/");
				print.append(cur->Pfront->studentid);
				print.append("/");
				print.append(cur->Pright->contact);
				print.append("\0");
				break;
			}
			cur = (NameNode*)cur->Pnext;
		}
		IDNode = IDNode->Pfront;
	}
	cout << print << endl;
	return 0;							// return print;
}

bool NameList::printContct(ContactNode* contactHead) {
	ContactNode* contactNode = contactHead;
	NameNode* cur;
	Node* dep;
	char contact[32] = "";
	char grade[2];
	grade[1] = '\0';
	string print("");

	while (contactNode) {
		strcpy_s(contact, contactNode->contact);
		cur = (NameNode*)Phead->Pnext;
		while (cur) {
			if (!strcmp(contact, cur->Pright->contact)) {
				dep = (DepartmentNode*)cur->Pup;
				while (dep->Pup) {
					dep = dep->Pup;
				}
				print.append(((DepartmentNode*)dep)->de_name);
				print.append("/");
				print.append(cur->name);
				print.append("/");
				grade[0] = cur->Pleft->grade + '0';
				print.append(grade);
				print.append("/");
				print.append(cur->Pfront->studentid);
				print.append("/");
				print.append(cur->Pright->contact);
				print.append("\0");
				break;
			}
			cur = (NameNode*)cur->Pnext;
		}
		contactNode = contactNode->Pright;
	}
	cout << print << endl;
	return 0;						// return print;
}