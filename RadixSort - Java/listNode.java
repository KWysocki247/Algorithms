
public class listNode {

	private String data;
	private listNode next;
	
	public listNode(String data) {
		this.data = data;
		this.next = null;
	}
	
	public void setNext(listNode next) {
		this.next = next;
	}

	public listNode getNext() {
		return this.next;
	}
	
	public String getData() {
		return this.data;
	}

}
