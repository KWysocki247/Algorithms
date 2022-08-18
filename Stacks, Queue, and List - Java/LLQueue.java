

import java.io.*;  
import java.util.Scanner; 

public class LLQueue {

	private listNode head;
	private listNode tail;
	
	public LLQueue() {
		listNode dummy = new listNode(-99999);
		dummy.setNext(null);
		this.head = dummy;
		this.tail = dummy;
	}
	
	public void insertQ(listNode newNode) {
		this.tail.setNext(newNode);
		this.tail = newNode;
	}
	
	public listNode deleteQ() {
		if(this.head == this.tail) {
			System.out.println("There is nothing on the Queue to delete. Returning Null");
			return null;
		}
		listNode temp = this.head.getNext();
		head = head.getNext();
		return temp;
	}
	
	public boolean isEmpty() {
		if(this.head == this.tail)
			return true;
		return false;
	}
	
	public static LLQueue buildQueue(String inFile) throws IOException {
		LLQueue Q = new LLQueue();
		FileReader fReader = new FileReader(inFile);
		Scanner input = new Scanner(fReader);
		while(input.hasNextInt()) {
			listNode nextNode = new listNode(input.nextInt());
			Q.insertQ(nextNode);
		}
		input.close();
		fReader.close();
		return Q;
	}
		
	public void dumpQueue(LLQueue Q, String outFile2) throws IOException{
		FileWriter fWriter = new FileWriter(outFile2);
		while(!Q.isEmpty()) {
			fWriter.write(Integer.toString(Q.deleteQ().getData()) + "\n");
		}
		fWriter.close();
	}
}
