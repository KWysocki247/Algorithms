import java.io.*; 
import java.util.*;

public class twoThreeTree {

    private treeNode Root;

    public twoThreeTree() {

    }

    treeNode getRoot() {
        return this.Root;
    }



    void initialTree(FileReader inFile, FileWriter deBugFile, Scanner input) throws IOException{
        Root = new treeNode(-1, -1, null, null, null, null);
        int data1 = input.nextInt();
        int data2 = input.nextInt();
        if(data2 < data1) {
            int temp = data1;
            data1 = data2;
            data2 = temp;
        }
        treeNode newNode1 = new treeNode(data1, -1, null, null, null, Root);
        treeNode newNode2 = new treeNode(data2, -1, null, null ,null, Root);
        Root.setChild1(newNode1);
        Root.setChild2(newNode2);
        Root.setKey1(data2);
        deBugFile.write("This is Root Node:\n");
        Root.printNode(Root, deBugFile);
        deBugFile.write("\n");
    }

    void preOrder(treeNode node, FileWriter outFile) throws IOException {
        if (isLeaf(node)) {
            node.printNode(node, outFile);
            outFile.write("\n");
        }
        else {
            node.printNode(node, outFile);
            outFile.write("\n");
            preOrder(node.getChild1(), outFile);
            preOrder(node.getChild2(), outFile);
            if(node.getChild3() != null){
                preOrder(node.getChild3(), outFile);
            }
        }
    }

    public static boolean isLeaf(treeNode node) {
        if(node.getChild1() == null && node.getChild2() == null && node.getChild3() == null)
            return true;
        return false;
    }

    public static boolean isRoot(treeNode node) {
        if(node.getFather() == null)
            return true;
        return false;
    }

    treeNode findSpot(treeNode spot, int data, FileWriter deBugFile) throws IOException{
        if(isLeaf(spot)) {
            deBugFile.write("You are at leaf level, you are too far down the tree");
            return null;
        }
        else if(data == spot.getKey1() || data == spot.getKey2()) {
            return null;
        }
        else if(isLeaf(spot.getChild1())) {
            return spot;
        }
        else{

            if(data < spot.getKey1()) {
                return findSpot(spot.getChild1(), data, deBugFile);
            }
            if(spot.getKey2() == -1 || data < spot.getKey2()) {
                return findSpot(spot.getChild2(), data, deBugFile);
            }
            if(spot.getKey2() != -1 && data >= spot.getKey2()) {
                return findSpot(spot.getChild3(), data, deBugFile);
            }
        }
        return null;
    }

    void treeInsert(treeNode spot, treeNode newNode) {
        newNode.setFather(spot);
        if(spot.getChild3() == null) {
            treeNode one = spot.getChild1();
            treeNode two = spot.getChild2();
            treeNode three = newNode;
            treeNode temp;
            if(one.getKey1() > two.getKey1()) {
                temp = one;
                one = two;
                two = temp;
            }
            if(one.getKey1() > three.getKey1()) {
                temp = one;
                one = three;
                three = temp;
            }
            if(two.getKey1() > three.getKey1()) {
                temp = two;
                two = three;
                three = temp;
            }
            spot.setChild1(one);
            spot.setChild2(two);
            spot.setChild3(three);
            one.setFather(spot);
            two.setFather(spot);
            three.setFather(spot);
            spot.setKey1(findMinSubtree(spot.getChild2()));
            spot.setKey2(findMinSubtree(spot.getChild3()));
            if(!isRoot(spot) && spot == spot.getFather().getChild2() || !isRoot(spot) && spot == spot.getFather().getChild3())
                UpdateFather(spot.getFather());
        }
        else {
            treeNode one = spot.getChild1();
            treeNode two = spot.getChild2();
            treeNode three = spot.getChild3();
            treeNode four = newNode;
            treeNode temp;
            if(one.getKey1() > two.getKey1()) {
                temp = one;
                one = two;
                two = temp;
            }
            if(three.getKey1() > four.getKey1()){
                temp = three;
                three = four;
                four = temp;
            }
            if(one.getKey1() > three.getKey1()) {
                temp = one;
                one = three;
                three = temp;
            }
            if(two.getKey1() > four.getKey1()){
                temp = two;
                two = four;
                four = temp;
            }
            if(two.getKey1() > three.getKey1()) {
                temp = two;
                two = three;
                three = temp;
            }
            treeNode Sibling = new treeNode(-1, -1, null, null, null, spot.getFather());
            spot.setChild1(one);
            spot.setChild2(two);
            spot.setChild3(null);
            one.setFather(spot);
            two.setFather(spot);
            Sibling.setChild1(three);
            Sibling.setChild2(four);
            three.setFather(Sibling);
            four.setFather(Sibling);
            Sibling.setChild3(null);
            spot.setKey1(findMinSubtree(spot.getChild2()));
            spot.setKey2(-1);
            Sibling.setKey1(findMinSubtree(Sibling.getChild2()));
            Sibling.setKey2(-1);
            if(spot.getFather() == null) {
                makeNewRoot(spot, Sibling);
                UpdateFather(this.Root);
            }
            else {
                treeInsert(spot.getFather(), Sibling);
            }
            if(!isRoot(Sibling) && Sibling == Sibling.getFather().getChild2() || !isRoot(Sibling) && Sibling == Sibling.getFather().getChild3()) {
                UpdateFather(spot.getFather());
            }
            if(!isRoot(Sibling) && Sibling == Sibling.getFather().getChild2() || !isRoot(Sibling) && Sibling == Sibling.getFather().getChild3()) {
                UpdateFather(Sibling.getFather());
            }

        }
    }

    int findMinSubtree(treeNode node) {
        if(node == null)
            return -1;
        if(isLeaf(node))
            return node.getKey1();
        else
            return findMinSubtree(node.getChild1());
    }

    void UpdateFather(treeNode fatherNode) {
        if(fatherNode == null)
            return;
        fatherNode.setKey1(findMinSubtree(fatherNode.getChild2()));
        fatherNode.setKey2(findMinSubtree(fatherNode.getChild3()));
        UpdateFather(fatherNode.getFather());
    }

    void makeNewRoot(treeNode spot, treeNode sibling) {
        treeNode root = new treeNode(-1, -1, spot, sibling, null, null);
        spot.setFather(root);
        sibling.setFather(root);
        Root = root;
    }
}
