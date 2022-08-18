
public class LLQueue {

	private listNode head;
	private listNode tail;
	
	public LLQueue() {
		listNode dummy = new listNode("dummyNode");
		dummy.setNext(null);
		this.head = dummy;
		this.tail = dummy;
	}
	
	public void insertQ(listNode newNode) {
		this.tail.setNext(newNode);
		this.tail = newNode;
	}

	public listNode getNode(){
		return head.getNext();
	}

	public listNode deleteQ() {
		if(this.head.getNext() == this.tail) {
			listNode temp = head.getNext();
			head.setNext(null);
			tail = head;
			return temp;
		}
		listNode temp = this.head.getNext();
		head.setNext(head.getNext().getNext());
		return temp;
	}
	
	public boolean isEmpty() {
		if(this.head == this.tail)
			return true;
		return false;
	}


	public static String printQueue(LLQueue whichTable){
		String data = "";
		listNode iterator = whichTable.head;
		if(iterator.getNext() == null){
			data = data + "(" + iterator.getData() + ", NULL) --> NULL";
			return data;
		}
		while(iterator.getNext() != null){
			data = data + "(" + iterator.getData() + ", " + iterator.getNext().getData() + ") -->";
			iterator = iterator.getNext();
			if(iterator.getNext() == null){
				return data + "(" + iterator.getData() + ", NULL) --> NULL";
			}
		}
		return data + ", NULL) --> NULL";
	}


}
