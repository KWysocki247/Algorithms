import java.io.FileWriter;
import java.io.IOException;

public class KruskalMST {

    int numNodes;
    int[] inWhichSet;
    int numSets;
    int totalMSTCost;
    edgeNode listHeadEdge;
    edgeNode listHeadMST;

    public KruskalMST(int numNodes){
        this.numNodes = numNodes;
        this.numSets = numNodes;
        this.totalMSTCost = 0;
        this.inWhichSet = new int[this.numNodes+1];
        for(int i = 1; i < this.numNodes+1; i++){
            this.inWhichSet[i] = i;
        }
        listHeadEdge = new edgeNode(0,0,0);
        listHeadMST = new edgeNode(0,0,0);
    }

    void insert(edgeNode node, edgeNode listHead){
         edgeNode traverser = listHead;
         while(traverser.getNext() != null && traverser.getNext().getCost() <= node.getCost()) {
             traverser = traverser.getNext();
         }
         node.setNext(traverser.getNext());
         traverser.setNext(node);
    }

    edgeNode removedEdge(edgeNode listHead){
        if(listHead.getNext() != null){
            edgeNode temp = listHead.getNext();
            listHead.setNext(listHead.getNext().getNext());
            return temp;
        }
        return null;
    }

    void merge2Sets(int node1, int node2){
        if(inWhichSet[node1] < inWhichSet[node2]){
            int Android18 = inWhichSet[node2];
            for(int i = 1; i < inWhichSet.length; i++){
                if(inWhichSet[i] == Android18)
                    inWhichSet[i] = inWhichSet[node1];
            }
        }
        else{
            int Yamcha = inWhichSet[node1];
            for(int i = 1; i < inWhichSet.length; i++){
                if(inWhichSet[i] == Yamcha){
                    inWhichSet[i] = inWhichSet[node2];
                }
            }
        }
    }

    void printAry(FileWriter outFile) throws IOException {
        for(int i = 1; i < inWhichSet.length; i++){
            outFile.write("Set[" + i + "]" + inWhichSet[i] +"\n");
        }
        outFile.write("\n");
    }

    void printList(edgeNode listHead, FileWriter outFile) throws IOException {
        listHead.printNode(listHead, outFile);
        if(listHead.getNext() == null){
            outFile.write("\n");
            return;
        }
        printList(listHead.getNext(), outFile);
    }
}
