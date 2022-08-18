import java.io.*;
import java.util.*;

public class RSort {
	
	private LLQueue hashTable[][];
	private listNode node;
	private String data;
	private int currentTable;
	private int nextTable;
	private int longestStringLength;
	private int currentPosition;
	private int hashIndex;
	public LLStack S = new LLStack();
	
	public RSort() {
		hashTable = new LLQueue[2][256];
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 256; j++){
				hashTable[i][j] = new LLQueue();
			}
		}
	}

	public void setNextTable(int table) {
		this.nextTable = table;
	}
	
	public void setLongestStringLength(int length) {
		this.longestStringLength = length;
	}

	public void setCurrentPosition(int position) {
		this.currentPosition = position;
	}
	
	public void setHashIndex(int index) {
		this.hashIndex = index;
	}
	
	public void setCurrentTable(int table) {
		this.currentTable = table;
	}
	
	public void setHashTable(int table, int position, listNode node) {
		hashTable[table][position].insertQ(node);
	}
	
	public int getNextTable() {
		return this.nextTable;
	}
	
	public int getLongestStringLength() {
		return this.longestStringLength;
	}

	public int getCurrentPosition() {
		return this.currentPosition;
	}
	
	public int getHashIndex() {
		return this.hashIndex;
	}
	
	public int getCurrentTable() {
		return this.currentTable;
	}
	
	
	public LLQueue getHashTable(int table, int position) {
		return hashTable[table][position];
	}

	public void firstReading(String inFile) throws IOException{
		setLongestStringLength(0);
		FileReader fReader = new FileReader(inFile);
		Scanner input = new Scanner(fReader);
		while(input.hasNext()) {
			int longest = input.next().length();
			if(longest > longestStringLength) {
				longestStringLength = longest;
			}
		}
		fReader.close();
		input.close();
	}
	
	public LLStack loadStack(String inFile) throws IOException{
		FileReader fReader = new FileReader(inFile);
		Scanner input = new Scanner(fReader);
		while(input.hasNext()) {
			listNode newNode = new listNode(padString(input.next()));
			this.S.push(newNode);
		}
		fReader.close();
		input.close();
		return this.S;
	}
	
	public void moveStack(LLStack S, int currentPos, int currentTable) {
		char chr;
		while(!S.isEmpty()) {
			listNode node = new listNode(S.pop().getData());
			chr = getChar(node, currentPos);
			hashIndex = (int)chr;
			hashTable[currentTable][hashIndex].insertQ(node);
		}
	}
	
	public String padString(String data) {
		int difference; 
		if(data.length() < getLongestStringLength()) {
			difference = getLongestStringLength() - data.length();
			for(int i = 0; i < difference; i++){
				data = data + " ";
			}
		}
		return data;
	}
	
	public char getChar(listNode node, int currentPos) {
		return node.getData().charAt(currentPos);
	}
	
	public void printTable(int nextTable, FileWriter outFile2) throws IOException{
		for(int i = 0; i < 256; i++) {
			if (!hashTable[nextTable][i].isEmpty()) {
				outFile2.write("Table [" + nextTable + "][" + i + "]: " + LLQueue.printQueue(hashTable[nextTable][i]) + "\n");
			}
		}
	}
	
	public void printSortedData(int nextTable, FileWriter outFile1) throws IOException{
		for(int i = 0; i < 256; i++) {
			if(!getHashTable(nextTable, i).isEmpty()) {
				outFile1.write("Table [" + currentTable + "][" + i + "]: " + LLQueue.printQueue(hashTable[currentTable][i]) + "\n");
			}
		}
	}
}
