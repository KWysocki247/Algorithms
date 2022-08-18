import java.io.*;

public class LLStack {

	private listNode top;
	
	public LLStack() {
		this.top = null;
	}

	public void push(listNode newNode) {
		newNode.setNext(this.top);
		this.top = newNode;
	}

	public listNode pop() {
		if(this.top.getNext() == null) {
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

	
	public void dumpStack(LLStack S,FileWriter outFile2) throws IOException{
		outFile2.write("Starting to print the stack: \n");
		while(!S.isEmpty()) {
			outFile2.write(S.pop().getData() + "\n");
		}
		outFile2.write(S.pop().getData() + "\n");
		outFile2.write("End of the stack printing \n");
	}
}
