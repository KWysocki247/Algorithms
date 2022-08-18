#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

class AstarNode {

public:

	int configuration[9] = { 0 };
	int gStar = 0;
	int hStar = 0;
	int fStar = 0;
	AstarNode* parent = NULL;
	AstarNode* next = NULL;

	AstarNode() {
		AstarNode* parent = NULL;
		AstarNode* next = NULL;
	}

	AstarNode(ifstream& inFile) {
		for (int i = 0; i < 9; i++) {
			inFile >> configuration[i];
		}
	}

	string printNode(AstarNode* node) {
		string ans = "<";
		for (int i = 0; i < 9; i++) {
			ans += to_string(node->configuration[i]) + " ";
		}
		ans += "; " + to_string(node->fStar) + "; ";
		if (node->parent == NULL) {
			ans += "There is no parent, 'tis orphan :,(";
		}
		else {
			for (int i = 0; i < 9; i++) {
				ans += to_string(node->parent->configuration[i]) + " ";
			}
		}
		return ans + ">\n";
	}
};

class AStarSearch {

public:
	AstarNode* startNode;
	AstarNode* goalNode;
	AstarNode* OpenList;
	AstarNode* CloseList;
	AstarNode* childList;

	AStarSearch(ifstream& inFile1, ifstream& inFile2) {
		startNode = new AstarNode(inFile1);
		goalNode = new AstarNode(inFile2);
		OpenList = new AstarNode();
		CloseList = new AstarNode();
		childList = new AstarNode();
	}

	void computeGstar(AstarNode* node) {
		node->gStar = node->parent->gStar + 1;
	}

	void computerHstar(AstarNode* node) {
		for (int i = 0; i < 9; i++) {
			if (node->configuration[i] != goalNode->configuration[i])
				node->hStar++;
		}
	}

	void computeFstar(AstarNode* node) {
		node->fStar = node->gStar + node->hStar;
	}

	bool match(int configuration1[], int configuration2[]) {
		for (int i = 0; i < 9; i++) {

			if (configuration1[i] == configuration2[i]) {
				continue;
			}
			else
				return false;
		}
		return true;
	}

	bool isGoalNode(AstarNode* node) {
		return match(node->configuration, goalNode->configuration);
	}

	void listInsert(AstarNode* node, AstarNode* OpenOrCloseWhichEverWeAreFeelingToday) {
		AstarNode* traverser = OpenOrCloseWhichEverWeAreFeelingToday;
		while (traverser->next != NULL && node->fStar > traverser->next->fStar) {
			traverser = traverser->next;
		}
		node->next = traverser->next;
		traverser->next = node;
	}

	AstarNode* remove(AstarNode* OpenOrCloseWhichEverWeAreFeelingToday) {
		AstarNode* temporary = OpenOrCloseWhichEverWeAreFeelingToday->next;
		OpenOrCloseWhichEverWeAreFeelingToday->next = OpenOrCloseWhichEverWeAreFeelingToday->next->next;
		return temporary;
	}

	bool checkAncestors(AstarNode* currentNode, AstarNode* parentalUnit) {
		if (currentNode->parent == NULL) {
			return false;
		}
		else if (match(currentNode->configuration, parentalUnit->configuration))
			return true;
		else if (parentalUnit->parent == NULL)
			return false;
		else
			return checkAncestors(currentNode, parentalUnit->parent);
	}

	void constructChildList(AstarNode* currentNode) {
		int zeroSpot = 0;
		int parentConfig[9] = { 0 };
		childList = new AstarNode();

		for (int i = 0; i < 9; i++) {
			if (currentNode->configuration[i] == 0) {
				zeroSpot = i;
			}
			parentConfig[i] = currentNode->configuration[i];
		}

		if (zeroSpot == 4) {
			AstarNode* child1 = new AstarNode();
			child1->parent = currentNode;
			AstarNode* child2 = new AstarNode();
			child2->parent = currentNode;
			AstarNode* child3 = new AstarNode();
			child3->parent = currentNode;
			AstarNode* child4 = new AstarNode();
			child4->parent = currentNode;
			for (int i = 0; i < 9; i++) {
				child1->configuration[i] = parentConfig[i];
				child2->configuration[i] = parentConfig[i];
				child3->configuration[i] = parentConfig[i];
				child4->configuration[i] = parentConfig[i];
			}
			child1->configuration[4] = child1->configuration[1];
			child1->configuration[1] = 0;

			child2->configuration[4] = child2->configuration[3];
			child2->configuration[3] = 0;

			child3->configuration[4] = child3->configuration[5];
			child3->configuration[5] = 0;

			child4->configuration[4] = child4->configuration[7];
			child4->configuration[7] = 0;

			if (!checkAncestors(child1, currentNode)) {
				push(child1);
			}
			if (!checkAncestors(child2, currentNode)) {
				push(child2);
			}
			if (!checkAncestors(child3, currentNode)) {
				push(child3);
			}
			if (!checkAncestors(child4, currentNode)) {
				push(child4);
			}
		}
		else if (zeroSpot % 2 == 0) {
			AstarNode* child1 = new AstarNode();
			child1->parent = currentNode;
			AstarNode* child2 = new AstarNode();
			child2->parent = currentNode;
			for (int i = 0; i < 9; i++) {
				child1->configuration[i] = parentConfig[i];
				child2->configuration[i] = parentConfig[i];
			}
			if (zeroSpot == 0) {
				child1->configuration[0] = child1->configuration[1];
				child1->configuration[1] = 0;

				child2->configuration[0] = child2->configuration[3];
				child2->configuration[3] = 0;
			}

			if (zeroSpot == 2) {
				child1->configuration[2] = child1->configuration[1];
				child1->configuration[1] = 0;

				child2->configuration[2] = child2->configuration[5];
				child2->configuration[5] = 0;
			}

			if (zeroSpot == 6) {
				child1->configuration[6] = child1->configuration[3];
				child1->configuration[3] = 0;

				child2->configuration[6] = child2->configuration[7];
				child2->configuration[7] = 0;
			}

			if (zeroSpot == 8) {
				child1->configuration[8] = child1->configuration[5];
				child1->configuration[5] = 0;

				child2->configuration[8] = child2->configuration[7];
				child2->configuration[7] = 0;
			}
			if (!checkAncestors(child1, currentNode)) {
				push(child1);
			}
			if (!checkAncestors(child2, currentNode)) {
				push(child2);
			}
		}
		else {
			AstarNode* child1 = new AstarNode();
			child1->parent = currentNode;
			AstarNode* child2 = new AstarNode();
			child2->parent = currentNode;
			AstarNode* child3 = new AstarNode();
			child3->parent = currentNode;
			for (int i = 0; i < 9; i++) {
				child1->configuration[i] = parentConfig[i];
				child2->configuration[i] = parentConfig[i];
				child3->configuration[i] = parentConfig[i];
			}

			if (zeroSpot == 1) {
				child1->configuration[1] = child1->configuration[0];
				child1->configuration[0] = 0;

				child2->configuration[1] = child2->configuration[2];
				child2->configuration[2] = 0;

				child3->configuration[1] = child3->configuration[4];
				child3->configuration[4] = 0;
			}

			if (zeroSpot == 3) {
				child1->configuration[3] = child1->configuration[0];
				child1->configuration[0] = 0;

				child2->configuration[3] = child2->configuration[4];
				child2->configuration[4] = 0;

				child3->configuration[3] = child3->configuration[6];
				child3->configuration[6] = 0;
			}

			if (zeroSpot == 5) {
				child1->configuration[5] = child1->configuration[2];
				child1->configuration[2] = 0;

				child2->configuration[5] = child2->configuration[8];
				child2->configuration[8] = 0;

				child3->configuration[5] = child3->configuration[4];
				child3->configuration[4] = 0;
			}

			if (zeroSpot == 7) {
				child1->configuration[7] = child1->configuration[6];
				child1->configuration[6] = 0;

				child2->configuration[7] = child2->configuration[8];
				child2->configuration[8] = 0;

				child3->configuration[7] = child3->configuration[4];
				child3->configuration[4] = 0;
			}

			if (!checkAncestors(child1, currentNode)) {
				push(child1);
			}
			if (!checkAncestors(child2, currentNode)) {
				push(child2);
			}
			if (!checkAncestors(child3, currentNode)) {
				push(child3);
			}
		}
	}

	void printList(AstarNode* listHead, ofstream& outFile1) {
		int count = 1;
		while (listHead->next != NULL) {
			outFile1 << listHead->printNode(listHead);
			listHead = listHead->next;
			count++;
		}
	}

	void printSolution(AstarNode* currentNode, ofstream& outFile2) {
		if (currentNode->parent != NULL) {
			printSolution(currentNode->parent, outFile2);
		}
		if (isGoalNode(currentNode)) {
			outFile2 << "\nPRINTING SOLUTION: \n";
		}
		else if (currentNode == startNode) {
			outFile2 << "PRINTING START NODE \n";
		}
		else {
			outFile2 << "\nPRINTING INTERMEDIATE ITERATION \n";
		}
		for (int i = 0; i < 9; i++) {
			if (currentNode->configuration[i] == 0) {
				outFile2 << "  ";
			}
			else {
				outFile2 << currentNode->configuration[i] << " ";
			}
			if ((i + 1) % 3 == 0) {
				outFile2 << endl;
			}
			else {
				outFile2 << " ";
			}
		}
	}

	AstarNode* pop() {
		AstarNode* temporary = childList->next;
		childList->next = childList->next->next;
		return temporary;
	}

	void push(AstarNode* node) {
		node->next = childList->next;
		childList->next = node;
	}

};

int main(int argx, char** argv) {
	ifstream inFile1;
	ifstream inFile2;
	ofstream outFile1;
	ofstream outFile2;
	inFile1.open(argv[1]);
	inFile2.open(argv[2]);
	outFile1.open(argv[3]);
	outFile2.open(argv[4]);

	int counter = 0;
	int loop1 = 0;
	int loop2 = 0;
	int loop3 = 0;
	int loop4 = 0;
	int loop5 = 0;
	AStarSearch* ASS = new AStarSearch(inFile1, inFile2);
	ASS->computerHstar(ASS->startNode);
	ASS->computeFstar(ASS->startNode);
	ASS->listInsert(ASS->startNode, ASS->OpenList);
	AstarNode* currentNode = new AstarNode();

	while (ASS->OpenList->next != NULL) {
		loop1++;
		loop2 = 0;
		currentNode = ASS->remove(ASS->OpenList);
		ASS->listInsert(currentNode, ASS->CloseList);
		if (ASS->isGoalNode(currentNode)) {
			ASS->printSolution(currentNode, outFile2);
			inFile1.close();
			inFile2.close();
			outFile1.close();
			outFile2.close();
			return 0;
		}
		ASS->constructChildList(currentNode);
		while (ASS->childList->next != NULL) {
			loop2++;
			AstarNode* child = ASS->pop();
			ASS->computeGstar(child);
			ASS->computerHstar(child);
			ASS->computeFstar(child);

			AstarNode* OpenIterator = ASS->OpenList;
			AstarNode* ClosedIterator = ASS->CloseList;
			bool flag = false;

			while (OpenIterator->next != NULL) {
				loop3++;
				if (ASS->match(child->configuration, OpenIterator->next->configuration)) {
					flag = true;
					if (child->fStar < OpenIterator->fStar) {
						ASS->remove(OpenIterator);
						ASS->listInsert(child, ASS->OpenList);
						child->parent = currentNode;
						break;
					}
				}
				OpenIterator = OpenIterator->next;
			}
			if (flag == false) {
				while (ClosedIterator->next != NULL) {
					loop4++;
					if (child->fStar < ClosedIterator->fStar) {
						flag = true;
						ASS->remove(ClosedIterator);
						ASS->listInsert(child, ASS->OpenList);
						child->parent = currentNode;
						break;
					}
					ClosedIterator = ClosedIterator->next;
				}
			}
			if (flag == false) {
				ASS->listInsert(child, ASS->OpenList);
				child->parent = currentNode;
			}

		}
		if (counter < 20) {
			loop5++;
			outFile1 << "This is Open list:";
			outFile1 << endl;
			ASS->printList(ASS->OpenList, outFile1);
			outFile1 << endl;
			outFile1 << "This is CLOSE list:";
			outFile1 << endl;
			ASS->printList(ASS->CloseList, outFile1);
			outFile1 << endl;
			counter++;
		}
	}

	outFile1 << "no solution can be found in the search!";
	inFile1.close();
	inFile2.close();
	outFile1.close();
	outFile2.close();
	return 0;
}