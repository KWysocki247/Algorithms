

import java.io.*;  
import java.util.Scanner; 

public class LLStack {

	private listNode top;
	
	public LLStack() {
		listNode dummy = new listNode(-99999);
		dummy.setNext(null);
		this.top = dummy;
	}
	
	public void push(listNode newNode) {
		newNode.setNext(this.top);
		this.top = newNode;
	}
	
	public listNode pop() {
		if(this.top.getNext() == null) {
			System.out.println("The stack is empty and cannot pop anything else");
			return this.top;
		}
		else {
			listNode temp = this.top;
			this.top = this.top.getNext();
			return temp;
		}
	}
	
	public boolean isEmpty() {
		if(this.top.getNext() == null) {
			return true;
		}
		return false;
	}

	public void printTop() {
		System.out.println("The data at the top of the stack is: " + top.getData());
	}
	
	public static LLStack buildStack(String inFile) throws IOException{
		LLStack S = new LLStack();
		FileReader fReader = new FileReader(inFile);
		Scanner input = new Scanner(fReader);
		while(input.hasNextInt()) {
			listNode nextNode = new listNode(input.nextInt());
			S.push(nextNode);
		}
		input.close();
		fReader.close();
		return S;
	}
	
	public void dumpStack(LLStack S,String outFile1) throws IOException{
		FileWriter fWriter = new FileWriter(outFile1);
		while(!S.isEmpty()) {
			//S.printTop(); ///Used to test what data is currently at the top and being written to the file 
			fWriter.write(Integer.toString(S.pop().getData()) + "\n");
		}
		fWriter.close();
	}
}
