import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class main {

    public static void main(String[] args) {
        String inFile = args[0];
        String MSTFile = args[1];
        String deBugFile = args[2];
        try {
            FileReader fReader = new FileReader(inFile);
            FileWriter mstWriter = new FileWriter(MSTFile);
            FileWriter deBugWriter = new FileWriter(deBugFile);
            Scanner input = new Scanner(fReader);
            KruskalMST Krillin = new KruskalMST(input.nextInt());
            Krillin.printAry(deBugWriter);
            while(input.hasNextInt()){
                edgeNode newEdge = new edgeNode(input.nextInt(), input.nextInt(), input.nextInt());
                Krillin.insert(newEdge, Krillin.listHeadEdge);
                deBugWriter.write("listhead");
                Krillin.printList(Krillin.listHeadEdge, deBugWriter);
            }
            while(Krillin.numSets > 1) {
                edgeNode nextEdge = Krillin.removedEdge(Krillin.listHeadEdge);
                while(Krillin.inWhichSet[nextEdge.getNi()] == Krillin.inWhichSet[nextEdge.getNj()]) {
                    nextEdge = Krillin.removedEdge(Krillin.listHeadEdge);
                }
                Krillin.insert(nextEdge, Krillin.listHeadMST);
                Krillin.totalMSTCost += nextEdge.getCost();
                Krillin.merge2Sets(nextEdge.getNi(), nextEdge.getNj());
                Krillin.numSets--;
                Krillin.printAry(deBugWriter);
                deBugWriter.write("Printing listHeadMST NOW: \n");
                Krillin.printList(Krillin.listHeadMST, deBugWriter);
                deBugWriter.write("Printing listHeadEdge NOW: \n");
                Krillin.printList(Krillin.listHeadEdge, deBugWriter);
            }
            mstWriter.write("*** A Kruskal's MST of the input graph is given below: ***\n");
            mstWriter.write("\t" + Krillin.numNodes + "\n");
            edgeNode Trunks = Krillin.listHeadMST.getNext();
            while(Trunks != null) {
                mstWriter.write("\t" + Trunks.getNi() + " " + Trunks.getNj() + " " + Trunks.getCost() + "\n");
                Trunks = Trunks.getNext();
            }
            mstWriter.write("*** The total cost of a Kruskal's MST is: " + Krillin.totalMSTCost + "\n");
            mstWriter.write("listHead");
            Krillin.printList(Krillin.listHeadMST, mstWriter);
            fReader.close();
            mstWriter.close();
            deBugWriter.close();
            input.close();
        }
        catch(IOException ie){
            System.out.println(ie);
        }
    }
}
