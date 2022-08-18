import java.io.*;

public class main {

	public static void main(String[] args) {
		String inputFile = args[0] ;
		String outputName1 = args[1] ;
		String outputName2 = args[2];

		RSort raditz = new RSort();
		LLStack S = new LLStack();
		LLStack temp = new LLStack();
		try{
			FileWriter file1 = new FileWriter(outputName1);
			FileWriter file2 = new FileWriter(outputName2);
			raditz.firstReading(inputFile);
			temp = raditz.loadStack(inputFile);
			temp.dumpStack(temp, file2);
			raditz.setCurrentPosition(raditz.getLongestStringLength() -1);
			raditz.setCurrentTable(0);
			S = raditz.loadStack(inputFile);
			raditz.moveStack(S, raditz.getCurrentPosition(), raditz.getCurrentTable());
			while(raditz.getCurrentPosition() > 0) {
				raditz.setCurrentPosition(raditz.getCurrentPosition() - 1 );
				raditz.setNextTable((raditz.getCurrentTable() + 1) % 2);
				int currentQueue = 0;
				while(currentQueue < 256) {
					while(!raditz.getHashTable(raditz.getCurrentTable(), currentQueue).isEmpty()) {
						listNode node = new listNode(raditz.getHashTable(raditz.getCurrentTable(), currentQueue).getNode().getData());
						raditz.getHashTable(raditz.getCurrentTable(), currentQueue).deleteQ();
						char chr = raditz.getChar(node, raditz.getCurrentPosition());
						raditz.setHashIndex((int)chr);
						raditz.setHashTable(raditz.getNextTable(), raditz.getHashIndex(), node);
					}
					currentQueue++;
				}
				raditz.printTable(raditz.getNextTable(),file2);
				raditz.setCurrentTable(raditz.getNextTable());
			}
			raditz.printSortedData(raditz.getNextTable(), file1);
			file1.close();
			file2.close();
		}catch(IOException ie) {
			System.out.println(ie);
		}
	}
}
