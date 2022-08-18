import java.io.*;

public class treeNode {

    private int key1;
    private int key2;
    private treeNode child1;
    private treeNode child2;
    private treeNode child3;
    private treeNode father;
    private twoThreeTree two_three;

    public treeNode(int k1, int k2, treeNode c1, treeNode c2, treeNode c3, treeNode f) {
        key1 = k1;
        key2 = k2;
        child1 = c1;
        child2 = c2;
        child3 = c3;
        father = f;
    }

    int getKey1() {
        return this.key1;
    }

    int getKey2() {
        return this.key2;
    }

    treeNode getChild1() {
        return this.child1;
    }

    treeNode getChild2() {
        return this.child2;
    }

    treeNode getChild3() {
        return this.child3;
    }

    treeNode getFather() {
        return this.father;
    }

    void setKey1(int k1) {
        this.key1 = k1;
    }

    void setKey2(int k2) {
        this.key2 = k2;
    }

    void setChild1(treeNode node) {
        this.child1 = node;
    }

    void setChild2(treeNode node) {
        this.child2 = node;
    }

    void setChild3(treeNode node) {
        this.child3 = node;
    }

    void setFather(treeNode node) {
        this.father = node;
    }

    void printNode(treeNode Tnode, FileWriter outFile) throws IOException{
        if(twoThreeTree.isLeaf(Tnode)){
            outFile.write("(" + Tnode.getKey1() + ", " + Tnode.getKey2()
                    + ", null, null, null, ");
            if(twoThreeTree.isRoot(Tnode)){
                outFile.write("null)");
            }
            else{
                outFile.write(Tnode.getFather().getKey1() + ")");
            }
        }
        if(!twoThreeTree.isLeaf(Tnode) && Tnode.getChild3() != null){
            outFile.write("(" + Tnode.getKey1() + ", " + Tnode.getKey2() + ", " + Tnode.getChild1().getKey1()
                    + ", " + Tnode.getChild2().getKey1() + ", " + Tnode.getChild3().getKey1() + ", ");
            if(twoThreeTree.isRoot(Tnode)){
                outFile.write("null)");
            }
            else{
                outFile.write(Tnode.getFather().getKey1() + ")");
            }
        }
        if(!twoThreeTree.isLeaf(Tnode) && Tnode.getChild3() == null){
            outFile.write("(" + Tnode.getKey1() + ", " + Tnode.getKey2() + ", " + Tnode.getChild1().getKey1() + ", "
                    + Tnode.getChild2().getKey1() + ", null, ");
            if(twoThreeTree.isRoot(Tnode)){
                outFile.write("null)");
            }
            else{
                outFile.write(Tnode.getFather().getKey1() + ")");
            }
        }
    }
}