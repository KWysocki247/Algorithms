

import java.io.*;  
import java.util.Scanner; 

public class LList {

	private listNode listHead;
	
	public LList() {
		listNode dummy = new listNode(-99999);
		listHead = dummy;
	}
	
	public listNode findSpot(listNode newNode) {
		listNode spot = listHead;
		while(spot.getNext() != null && newNode.getData() > spot.getNext().getData()) {
			spot = spot.getNext();
		}
		return spot;
	}
	
	public void insertOneNode(listNode spot, listNode newNode) {
		newNode.setNext(spot.getNext());
		spot.setNext(newNode);
	}
	
	public static LList buildList(String inFile) throws IOException{
		LList list = new LList();
		FileReader fReader = new FileReader(inFile);
		Scanner input = new Scanner(fReader);
		while(input.hasNextInt()) {
			listNode newNode = new listNode(input.nextInt());			
			listNode spot = list.findSpot(newNode);
			list.insertOneNode(spot, newNode);
		}
		fReader.close();
		input.close();
		return list;
	}
	
	public void printList(String outFile3) throws IOException{
		FileWriter fWriter = new FileWriter(outFile3);
		listNode temp = listHead;
		fWriter.write("listHead --->");
		while(temp.getNext() != null) {
			fWriter.write(temp.printNode(temp));
			temp = temp.getNext();
		}
		fWriter.write(" (" + temp.getData() + ", NULL) ---> NULL");
		fWriter.close();
	}
	

}
