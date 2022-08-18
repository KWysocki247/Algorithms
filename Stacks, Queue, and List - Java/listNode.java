

public class listNode {

	private int data;
	private listNode next;
	
	public listNode(int data) {
		this.data = data;
		this.next = null;
	}
	
	public void setNext(listNode next) {
		this.next = next;
	}


	public listNode getNext() {
		return this.next;
	}
	
	public int getData() {
		return this.data;
	}
	
	public String printNode(listNode temp) {
		return  "(" + temp.getData() + ", " + temp.getNext().getData() + ") --->";
	}
}
