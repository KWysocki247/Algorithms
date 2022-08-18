import java.io.FileWriter;
import java.io.IOException;

public class edgeNode {

    private int Ni;
    private int Nj;
    private int cost;
    private edgeNode next;

    public edgeNode(int n1, int n2, int cost){
        this.Ni = n1;
        this.Nj = n2;
        this.cost = cost;
        this.next = null;
    }

    void printNode(edgeNode node, FileWriter outFile) throws IOException {
        outFile.write( "--> <" + node.getNi() + "," + node.getNj() + "," + node.getCost() + ">");
    }

    void setNext(edgeNode next){
        this.next = next;
    }

    edgeNode getNext(){
        return this.next;
    }

    int getNi(){
        return this.Ni;
    }

    int getNj(){
        return this.Nj;
    }

    int getCost(){
        return this.cost;
    }



}
