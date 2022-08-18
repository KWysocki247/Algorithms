

import java.io.*;  

public class Main {
	
	public static void main(String[] args) {
		String inputFile = args[0] ;
		String outputName1 = args[1] ;
		String outputName2 = args[2];
		String outputName3 = args[3];
		
		try{	
			LLStack S = LLStack.buildStack(inputFile);
			S.dumpStack(S, outputName1);
		}catch(IOException ie) {
			System.out.println(ie);
		}
		//System.out.println("done"); - Printed so that I know the code finished with the Stack 
		
		try {
			LLQueue Q = LLQueue.buildQueue(inputFile);
			Q.dumpQueue(Q, outputName2);
		}catch(IOException ie) {
			System.out.println(ie);
		}
		//System.out.println("done2"); - Printed so that I know the code finished with the Queue 
		
		try{
			LList list = LList.buildList(inputFile);
			list.printList(outputName3);
		}
		catch(IOException ie) {
			System.out.println(ie);
		}
		//System.out.println("done3"); - Printed so that I know the code finished with the List
	}
}
