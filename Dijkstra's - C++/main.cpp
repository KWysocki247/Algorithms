#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

class DijktraSSS {

public:

	int numNodes;
	int sourceNode;
	int minNode;
	int currentNode;
	int newCost;
	int** costMatrix;
	int* fatherAry;
	int* markedAry;
	int* bestCostAry;


	DijktraSSS(int x) {

		this->numNodes = x;
		costMatrix = new int* [numNodes + 1];
		for (int i = 0; i < numNodes + 1; i++) {
			costMatrix[i] = new int[numNodes + 1];
			for (int j = 0; j < numNodes + 1; j++) {
				if (i == j)
					costMatrix[i][j] = 0;
				else
					costMatrix[i][j] = 99999;
			}
		}
		fatherAry = new int[numNodes + 1];
		for (int i = 0; i < numNodes + 1; i++) {
			fatherAry[i] = i;
		}
		markedAry = new int[numNodes + 1];
		for (int i = 0; i < numNodes + 1; i++) {
			markedAry[i] = 0;
		}
		bestCostAry = new int[numNodes + 1];
		for (int i = 0; i < numNodes + 1; i++) {
			bestCostAry[i] = 99999;
		}
	}

	void loadCostMatrix(ifstream& inFile) {
		int row;
		int column;
		int cost;
		while (!inFile.eof()) {
			inFile >> row;
			inFile >> column;
			inFile >> cost;
			this->costMatrix[row][column] = cost;
		}
	}

	void setBestCostAry(int sourceNode) {
		for (int i = 0; i < numNodes + 1; i++)
			bestCostAry[i] = costMatrix[sourceNode][i];
	}

	void setFatherAry(int sourceNode) {
		for (int i = 0; i < numNodes + 1; i++)
			fatherAry[i] = sourceNode;
	}

	void setMarkedAry(int sourceNode) {
		for (int i = 0; i < numNodes + 1; i++) {
			if (i == sourceNode)
				markedAry[i] = 1;
			else
				markedAry[i] = 0;
		}
	}

	void findMinNode() {
		int minCost = 99999;
		minNode = 0;
		int index = 1;
		while (index <= numNodes) {
			if (markedAry[index] == 0) {
				if (bestCostAry[index] < minCost) {
					minCost = bestCostAry[index];
					minNode = index; 
				}
			}
			index++;
		}
	}

	int computeCost(int minNode, int currentNode) {
		return bestCostAry[minNode] + costMatrix[minNode][currentNode];
	}

	void deBugPrint(ofstream& outFile) {
		outFile << endl << "The sourceNode is: " << sourceNode << endl;
		outFile << "The fatherAry is: ";
		for (int i = 1; i < numNodes + 1; i++) {
			outFile << fatherAry[i] << " ";
		}
		outFile << endl << "The bestCostAry is: ";
		for (int i = 1; i < numNodes + 1; i++) {
			outFile << bestCostAry[i] << " ";
		}
		outFile << endl << "The markedAry is: ";
		for (int i = 1; i < numNodes + 1; i++) {
			outFile << markedAry[i] << " ";
		}
		outFile << endl;
	}

	void printShortestPath(int currentNode, int sourceNode, ofstream& SSSfile) {
		SSSfile << "The path from " << sourceNode << " to " << currentNode << " : " << currentNode;
		int father = fatherAry[currentNode];
		while (father != sourceNode) {
			SSSfile << " <-- " << father;
			father = fatherAry[father];
		}
		SSSfile << " <-- " << father << " : cost = " << bestCostAry[currentNode] << endl;
	}
};


int main(int argx, char** argv) {
	ifstream inFile;
	ofstream DebugFile;
	ofstream SSSFile;
	int num;
	inFile.open(argv[1]);
	DebugFile.open(argv[3]);
	SSSFile.open(argv[2]);
	inFile >> num;
	DijktraSSS* dk = new DijktraSSS(num);
	dk->loadCostMatrix(inFile);
	dk->sourceNode = 1;
	SSSFile << "============================== \n" <<
		"There are 7 nodes in the input graph.Below are the all pairs of shortest paths :\n" 
		<< "============================== \n";
	while (dk->sourceNode <= dk->numNodes) {
		dk->setBestCostAry(dk->sourceNode);
		dk->setFatherAry(dk->sourceNode);
		dk->setMarkedAry(dk->sourceNode);
		for (int i = 1; i < dk->numNodes; i++) {
			dk->findMinNode();
			dk->markedAry[dk->minNode] = 1;
			dk->deBugPrint(DebugFile);
			dk->currentNode = 1;
			while (dk->currentNode <= dk->numNodes) {
				if (dk->markedAry[dk->currentNode] == 0) {
					dk->newCost = dk->computeCost(dk->minNode, dk->currentNode);
					if (dk->newCost < dk->bestCostAry[dk->currentNode]) {
						dk->bestCostAry[dk->currentNode] = dk->newCost;
						dk->fatherAry[dk->currentNode] = dk->minNode;
						dk->deBugPrint(DebugFile);
					}
				}
				dk->currentNode++;
			}
		}
		dk->currentNode = 1;
		SSSFile << "The Source Node = " << dk->sourceNode << endl;
		while (dk->currentNode <= dk->numNodes) {
			dk->printShortestPath(dk->currentNode, dk->sourceNode, SSSFile);
			dk->currentNode++;
		}
		SSSFile << "============================== \n";
		dk->sourceNode++;
	}
	DebugFile.close();
	SSSFile.close();
	inFile.close();
}

