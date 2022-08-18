#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

class HuffmanCoding {

    class treeNode {

    private:
        string chStr;
        int frequency;
        string code;
        treeNode* left;
        treeNode* right;
        treeNode* next;

    public:
        
        treeNode(string chStr, int frequency, string code, treeNode* left, treeNode* right, treeNode* next) {
            this->chStr = chStr;
            this->frequency = frequency;
            this->code = code;
            this->left = left;
            this->right = right;
            this->next = next;
        }

        void setNext(treeNode* next) {
            this->next = next;
        }

        string getChStr() {
            return this->chStr;
        }

        int getFreq() {
            return this->frequency;
        }

        string getCode() {
            return this->code;
        }

        treeNode* getLeft() {
            return this->left;
        }

        treeNode* getRight() {
            return this->right;
        }

        treeNode* getNext() {
            return this->next;
        }

        void setCode(string code) {
            this->code = code;
        }

        void setChrStr(string chr) {
            this->chStr = chr;
        }

        void printNode(treeNode* T, ofstream& file) {
            file << "(" << T->chStr << ", " << T->frequency << ", " << T->code << ", ";
            if (T->getNext() != NULL){
                file << T->next->chStr << ", ";
            }
            else {
                file << "NULL, ";
            }
            if (T->left != NULL) {
                file << T->left->chStr << ", ";
            }
            else {
                file << "NULL, ";
            }
            if (T->right != NULL) {
                file << T->right->chStr << ") -->";
            }
            else {
                file << "NULL) --> ";
            }
        }

    };

    class linkedList {
    private:
        treeNode* listHead;

    public:
        linkedList() {
            treeNode* dummyNode = new treeNode("dummyNode", 0, "", NULL, NULL, NULL);
            listHead = dummyNode;
        }

        treeNode* getHead() {
            return this->listHead;
        }

        treeNode* findSpot(treeNode* newNode, treeNode* listHead) {
            treeNode* spot = listHead;
            while (spot->getNext() != NULL && newNode->getFreq() >= spot->getNext()->getFreq()) {
                spot = spot->getNext();
            }
            return spot;
        }

        void insertOneNode(treeNode* spot, treeNode* newNode) {
            newNode->setNext(spot->getNext());
            spot->setNext(newNode);
        }

        void printList(treeNode* listhead, ofstream& file) {
            treeNode* iterator = new treeNode(listhead->getChStr(),listHead->getFreq() ,listHead->getCode(), listHead->getLeft(), listHead->getRight() ,listHead->getNext());
            while (iterator->getNext() != NULL) {
                iterator->printNode(iterator, file);
                iterator = iterator->getNext();
            }
            file << endl;
        }
    };

    class BinaryTree {
    private:
        treeNode* root;

    public:
        BinaryTree(treeNode* root) {
            this->root = root;
        }

        BinaryTree() {

        }

        void setRoot(treeNode* root) {
            this->root = root;
        }

        treeNode* getRoot() {
            return this->root;
        }

        void preOrderTraversal(treeNode* Root, ofstream& file) {
            if (Root == NULL)
                return;
            if (isLeaf(Root)) {
                Root->printNode(Root, file);
                file << endl;
            }
            else {
                Root->printNode(Root, file);
                file << endl;
                preOrderTraversal(Root->getLeft(), file);
                preOrderTraversal(Root->getRight(), file);
            }
        }

        void inOrderTraversal(treeNode* Root, ofstream& file) {
            if (Root == NULL)
                return;
            if (isLeaf(Root)) {
                Root->printNode(Root, file);
                file << endl;
            }
            else {
                inOrderTraversal(Root->getLeft(), file);
                Root->printNode(Root, file);
                file << endl;
                inOrderTraversal(Root->getRight(), file);
            }
        }

        void postOrderTraversal(treeNode* Root, ofstream& file) {
            if (Root == NULL)
                return;
            if (isLeaf(Root)) {
                Root->printNode(Root, file);
                file << endl;
            }
            else {
                postOrderTraversal(Root->getLeft(), file);
                postOrderTraversal(Root->getRight(), file);
                Root->printNode(Root, file);
                file << endl;
            }
        }

        bool isLeaf(treeNode* node) {
            if (node->getLeft() == NULL && node->getRight() == NULL)
                return true;
            return false;
        }
    };


    private:
        int charCountAry[256] = { 0 };
        string charCode[256];
        BinaryTree bt;
        linkedList* listHead = new linkedList();

public:
    HuffmanCoding() {
        
    }

    string* getCharCode() {
        return charCode;
    }

    linkedList* getList() {
        return this->listHead;
    }

    BinaryTree getBT() {
        return this->bt;
    }

    void computeCharCounts(ifstream& file) {
        char ch;
        int asciiIndex;
        while (true) {
            if (file.eof()){
                break;
            }
            else {
                file.get(ch);
                asciiIndex = (int)ch;
                charCountAry[asciiIndex]++;
            }
        }
    }

    void printCountAry(ofstream& file) {
        for (int i = 0; i < 256; i++) {
            if (charCountAry[i] == 0) {
                continue;
            }
            else {
                if(i == 10)
                    file << "\\n" << " " << charCountAry[i] << endl;
                else
                    file << (char)i << " " << charCountAry[i] << endl;
            }
        }
    }

    void constructHuffmanLList(ofstream& file) {
        int index = 0;
        while (index < 256) {
            if ((int)charCountAry[index] > 0) {
                char chr = (char) index;
                int prob = charCountAry[index];
                string character = string(1, chr);
                if (character == "\n") {
                    character = "\\n";
                }
                treeNode* newNode = new treeNode(character, prob, "" , NULL, NULL, NULL);
                listHead->insertOneNode(listHead->findSpot(newNode ,listHead->getHead()), newNode);
                listHead->printList(listHead->getHead(), file);
            }
            index++;
        }
        file << endl;
    }

    void constructHuffmanBinTree(ofstream& file) {
        while (listHead->getHead()->getNext()->getNext() != NULL) {
            treeNode* newNode = new treeNode(listHead->getHead()->getNext()->getChStr() + listHead->getHead()->getNext()->getNext()->getChStr(), 
                listHead->getHead()->getNext()->getFreq() + listHead->getHead()->getNext()->getNext()->getFreq(), 
                " ", listHead->getHead()->getNext(), listHead->getHead()->getNext()->getNext(), NULL);
            listHead->insertOneNode(listHead->findSpot(newNode ,listHead->getHead()), newNode);
            listHead->getHead()->setNext(listHead->getHead()->getNext()->getNext()->getNext());
            listHead->printList(listHead->getHead(), file);
        }
        BinaryTree root = listHead->getHead()->getNext();
        file << endl;
        bt = root;
    }

    void constructCharCode(BinaryTree binaryTree, string code) {
        if (binaryTree.isLeaf(binaryTree.getRoot())) {
            binaryTree.getRoot()->setCode(code);
            string checkForNewLine = binaryTree.getRoot()->getChStr();
            if (checkForNewLine == "\\n") {
                checkForNewLine = "\n";
            }
            int index = (int)checkForNewLine[0];
            charCode[index] = code;
        }
        else {
            constructCharCode(binaryTree.getRoot()->getLeft(), code + "0");
            constructCharCode(binaryTree.getRoot()->getRight(), code + "1");
        }
    }

    void Encode(ifstream& orgFile, ofstream& compFile) {
        char charIn;
        int index;
        string code;
        while (!orgFile.eof()) {
            orgFile.get(charIn);
            index = (int)charIn;
            code = charCode[index];
            compFile << code;
        }
    }

    void Decode(ifstream& orgFile, ofstream& deCompFile) {
        treeNode* spot = new treeNode(bt.getRoot()->getChStr(), bt.getRoot()->getFreq(), 
            bt.getRoot()->getCode(), bt.getRoot()->getLeft(), bt.getRoot()->getRight(), 
            bt.getRoot()->getNext());
        while (!orgFile.eof()) {
            if (bt.isLeaf(spot)) {
                if (spot->getChStr() == "\\n") {
                    deCompFile << "\n";
                }
                else {
                    deCompFile << spot->getChStr();
                }              
                spot = bt.getRoot();
            }
            char oneBit;
            orgFile.get(oneBit);
            if (oneBit == '0') {
                spot = spot->getLeft();
            }
            else if (oneBit == '1') {
                spot = spot->getRight();
            }
            else {
                deCompFile << "Error!The compress file contains invalid character!";
                exit(0); 
            }
        }
        if (bt.isLeaf(spot) && orgFile.eof()) {
            deCompFile << "Error: The compress file is corrupted!";
        }
    }

    void userInterface() {
        string nameOrg;
        string nameCompress;
        string nameDeCompress;
        char yesNo;
        while (true) {
            cout << "Would you like to encode a file? Please type Y for Yes or N for No: " ;
            cin >> yesNo;
            if (yesNo == 'N') {
                exit(0);
            }
            else {
                cout << "Please enter the name of the file to be compressed: ";
                cin >> nameOrg;
            }
            size_t positionOfDot = nameOrg.find(".");
            nameCompress = nameOrg.substr(0, positionOfDot) + "_Compressed.txt";
            nameDeCompress = nameOrg.substr(0, positionOfDot) + "_DeCompress.txt";
            ifstream orgFile;
            ofstream compFile;
            ofstream deCompFile;
            orgFile.open(nameOrg);
            compFile.open(nameCompress);
            deCompFile.open(nameDeCompress);
            Encode(orgFile, compFile);
            orgFile.close();
            compFile.close();
            orgFile.open(nameCompress);
            Decode(orgFile, deCompFile);
            orgFile.close();
            deCompFile.close();
        }
    }

};

int main(int argx, char** argv){
    string nameInFile = argv[1];
    ifstream inFile;
    ofstream DebugFile;
    inFile.open(nameInFile);
    size_t positionOfDot = nameInFile.find(".");
    string nameDebugFile = nameInFile.substr(0, positionOfDot) + "_DeBug.txt";
    DebugFile.open(nameDebugFile);
    HuffmanCoding hmc = *new HuffmanCoding();
    hmc.computeCharCounts(inFile);
    hmc.printCountAry(DebugFile);
    DebugFile << endl << "LinkedList Printing:" << endl;
    hmc.constructHuffmanLList(DebugFile);
    DebugFile << endl << "BinaryTree Printing:" << endl;
    hmc.constructHuffmanBinTree(DebugFile);
    hmc.constructCharCode(hmc.getBT() ,"");
    DebugFile << endl << "Now printing Sorted LinkedList:" << endl;
    hmc.getList()->printList(hmc.getList()->getHead(), DebugFile);
    DebugFile << endl << "PreOrder Traversal:" << endl;
    hmc.getBT().preOrderTraversal(hmc.getBT().getRoot(), DebugFile);
    DebugFile << endl << endl << "InOrder Traversal:" << endl;
    hmc.getBT().inOrderTraversal(hmc.getBT().getRoot(), DebugFile);
    DebugFile << endl << endl << "PostOrder Traversal:" << endl;
    hmc.getBT().postOrderTraversal(hmc.getBT().getRoot(), DebugFile);
    hmc.userInterface();
    DebugFile.close();
    inFile.close();
}

