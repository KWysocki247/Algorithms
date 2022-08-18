import java.io.*; 
import java.util.*;

public class main {

    public static void main(String[] args) {
        String inFile = args[0];
        String deBugFile = args[1];
        String treeFile = args[2];
        twoThreeTree twoThree = new twoThreeTree();
        try {
            FileReader fReader = new FileReader(inFile);
            FileWriter fWriter = new FileWriter(deBugFile);
            FileWriter treeWriter = new FileWriter(treeFile);
            Scanner input = new Scanner(fReader);
            twoThree.initialTree(fReader, fWriter, input);
            while(input.hasNext()) {
                int data = input.nextInt();
                treeNode Spot = twoThree.findSpot(twoThree.getRoot(), data, fWriter);
                while(Spot == null && input.hasNext()) {
                    treeWriter.write("Data is in the database, no need to insert\n");
                    data = input.nextInt();
                    Spot = twoThree.findSpot(twoThree.getRoot(), data, fWriter);
                }
                fWriter.write("This is Spot: \n");
                Spot.printNode(twoThree.getRoot(), fWriter);
                fWriter.write("\n");
                treeNode newNode = new treeNode(data, -1, null, null, null, null);
                twoThree.treeInsert(Spot, newNode);
                fWriter.write("This is PreOrder: \n");
                twoThree.preOrder(twoThree.getRoot(), fWriter);
                fWriter.write("\n");
            }
            treeWriter.write("THIS IS PRE-ORDER: \n");
            twoThree.preOrder(twoThree.getRoot(),treeWriter);
            fReader.close();
            fWriter.close();
            treeWriter.close();
            input.close();
        }
        catch(IOException ie) {
            System.out.println(ie);
        }
    }
}
