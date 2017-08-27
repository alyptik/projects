/**
 * Implements a Grocery List
 * using parallel arrays. Ability
 * to read/write a Grocery List
 * consisting of the names, numbers,
 * and stores of a Grocery Item.
 *
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment #04
 * 08/27/17
 */

import java.util.Scanner;
import java.util.InputMismatchException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.lang.Integer;

class PabalinasJoey04 {
/** Stores the first line of the file, which has the headings  */
	private static String firstLineOfFile = "";
	/**
	* The main() Method Starts The Program.
	*
	* @param commandlineArguments 1st argument is INPUT File, 2nd argument is OUTPUT File
	*/
	public static void main(String[] commandlineArguments) {
		// Error Checking For 2 Command Line Arguments..
		if (commandlineArguments.length != 2) {
			System.out.println("Please enter the INPUT file name as the 1st commandline argument.");
			System.out.println("Please enter the OUTPUT file name as the 2nd commandline argument.");
			System.out.println("Please enter exactly two (2) commandline arguments.");
		// Immediately terminates program
			System.exit(1);
		}// end of if
		// if no commandline argument errors, continue program

		// Declare and instantiate array of 100 Strings and Integers
		final Integer MAX_SIZE = new Integer(100);
		String itemNames[] = new String[MAX_SIZE];
		Integer itemNumbers[] = new Integer[MAX_SIZE];
		// array for store names
		String storeNames[] = new String[MAX_SIZE];
		// Set size of grocery list to zero (0) items
		Integer size = new Integer(0);
		// read grocery items from file & store in arrays for grocery list
		try {
			size = PabalinasJoey04.readFromFile(commandlineArguments[0],
				itemNames, itemNumbers, storeNames, size);
		}
		catch (ArrayIndexOutOfBoundsException exception) {
			System.out.print("ERROR: Too many items in input file. ");
			System.out.println("Please limit to " + MAX_SIZE + " items.");
		// Immediately terminates program
			System.exit(1);
		}

		// user's choice for Menu
		Integer choice = new Integer(0);
		// choice for ending program
		final Integer QUIT = new Integer(4);
		// if the user does NOT want to QUIT, keep looping
		while (false == choice.equals(QUIT)) {
		// get the user's choice
			choice = PabalinasJoey04.displayMenu();
		// add grocery item
			if (choice.equals(1)) {
			size = PabalinasJoey04.add(itemNames, itemNumbers, storeNames, size);
			}
			// delete grocery item
			else if (choice.equals(2)) {
			size = PabalinasJoey04.delete(itemNames, itemNumbers, storeNames, size);
			}
				// display grocery item
			else if (choice.equals(3)) {
			PabalinasJoey04.display(itemNames, itemNumbers, storeNames, size);
			}
				// error message
			else if (false == choice.equals(QUIT)) {
			System.out.println("ERROR: Please enter an integer in the range from 1 to 4");
			}
		}// end of "while"

		// write to from grocery list array to OUTPUT file
		PabalinasJoey04.writeToFile(commandlineArguments[1],
			itemNames, itemNumbers, storeNames, size);
	}// end of main() method

	/**
	* Displays the menu for the program and returns user's choice
	*
	* @return the choice of the user (if error, returns 0)
	*/
	private static Integer displayMenu() {
		// display menu
		System.out.println();
		System.out.println("\tGROCERY LIST MENU");
		System.out.println("\t Enter 1 to Add");
		System.out.println("\t Enter 2 to Delete");
		System.out.println("\t Enter 3 to Display");
		System.out.println("\t Enter 4 to Quit");
		System.out.print("\tEnter your choice: ");
		// get input from user
		Scanner keyboardInput = new Scanner(System.in);
		String userInput = new String("");
		Integer choiceOfUser = new Integer(0);
		//get next word from user (hopefully, it is a number)
		userInput = keyboardInput.next();
		try {
			// non-integer input will throw an exception
			choiceOfUser = Integer.parseInt(userInput);
		}
		catch (NumberFormatException exception) {
			System.out.println("ERROR: " + userInput + " is not a number!");
		}
		System.out.println();
		return choiceOfUser;
	}

	/**
	* Reads grocery items from a file and stores items in an array
	*
	* @param inputFile is the INPUT File
	* @param itemNames2 is the array of item names in the grocery list
	* @param itemNumbers2 is the array of item numbers in the grocery list
	* @param storeNames2 is the array of store names in the grocery list
	* @param size is the number of items in Grocery List
	* @return the new size of the grocery list
	* @throws ArrayIndexOutOfBoundsException if array size is less than number of
	*         items in input file
	*/
	private static Integer readFromFile(String inputFile, String[] itemNames2,
	                                    Integer itemNumbers2[], String[] storeNames2, Integer size)
			throws ArrayIndexOutOfBoundsException {
		// connect to file (does NOT create new file)
		File file = new File(inputFile);
		Scanner scanFile = null;
		try {
			scanFile = new Scanner(file);
		}
		catch (FileNotFoundException exception) {
			// Print error message.
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.print("ERROR: File not found for \"");
			System.out.println(inputFile + "\"");
		}
		// if made connection to file, read from file
		if (scanFile != null) {
		//first line of file is the headers, so don't store in the arrays
			firstLineOfFile = scanFile.nextLine();

			// keeps looping if file has more lines..
			while (scanFile.hasNextLine()) {
				// get a line of text..
				String line = scanFile.nextLine();

				// divides each line by commas
				Scanner lineInput = new Scanner(line).useDelimiter(",");
				//get the name, count, and store from one line in the file
				String name = lineInput.next();
				String count1 = lineInput.next();
				String store = lineInput.next();

				//convert the string count to integer count2
				Integer count2 = 0;
				try{
					 count2 = Integer.parseInt(count1);
				}
				catch (NumberFormatException exception) {
					 System.out.println("ERROR: " + count1 + " is not a number!");
					 //if it is not an integer, then use zero (0) as default
				}
				//check for negative numbers
				if (count2 < 0){
					//change to positive integer
					 count2 = -count2;
				}

				//assign and count2 to appropriate arrays
				itemNames2[size] = name;
				itemNumbers2[size] = count2;
				storeNames2[size] = store;

				// increment size
				++size;
			}
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.println("Read from file: " + inputFile);
		}// end of "if" for connecting to file
		return size;
	}

	/**
	* Adds a grocery item to an array
	*
	* @param itemNames3 is the array of item names in the grocery list
	* @param itemNumbers3 is the array of item numbers in the grocery list
	* @param storeNames3 is the array of item numbers in the grocery list
	* @param size is the size of the grocery list
	* @return new size of the grocery list
	*/
	private static Integer add(String[] itemNames3,
	                           Integer[] itemNumbers3, String[] storeNames3, Integer size) {
		// get item from user
		Scanner keyboard = new Scanner(System.in);
		System.out.print("Enter name of item: ");
		String name = keyboard.nextLine();
		System.out.print("Enter number of items: ");
		String count1 = keyboard.nextLine();
		System.out.print("Enter store name of item: ");
		String store = keyboard.nextLine();

		//convert the string count to integer count2
		Integer count2 = 0;
		try{
			count2 = Integer.parseInt(count1);
		}
		catch (NumberFormatException exception) {
			System.out.println("ERROR: " + count2 + " is not a number!");
		//if it is not an integer, then use zero (0) as default
		}
		//check for negative numbers
		if(count2 < 0){
		//change to positive integer
			count2 = -count2;
		}

		//assign name and count2 to appropriate arrays at end
		itemNames3[size] = name;
		itemNumbers3[size] = count2;
		storeNames3[size] = store;

		//give feedback to user to let them know what is being addded
		System.out.println("Added row #" + (size + 1) + ": "
			+ itemNames3[size] + " " + itemNumbers3[size] + " " + storeNames3[size]);

		// add one to the size (one item to end of list)
		return size + 1;
	}

	/**
	* Deletes a grocery item from parallet arrays
	*
	* @param itemNames4 is the item names in the grocery list
	* @param itemNumbers4 is the number of items in the grocery list
	* @param storeNames4 is the store names in the grocery list
	* @param listSize is the size of the grocery list
	* @return new size of the grocery list
	*/
	private static Integer delete(String[] itemNames4,
	                              Integer[] itemNumbers4, String[] storeNames4, Integer listSize) {
		// get user input
		System.out.print("Enter the row number of the item you wish to delete: ");
		Scanner keyboard = new Scanner(System.in);
		try {
			// throws an exception if not an integer
			Integer row = keyboard.nextInt();
			// check for negative integers
			if (row <= 0) {
				System.out.println("ERROR: The row number cannot be negative or zero.");
			}
			// check for row number too big
			else if (row > listSize + 1) {
				System.out.println("ERROR: The row number is too big for the list.");
			}
			else {
			//convert row to an index in the array by subtracting one
			Integer index = row - 1;
			//give feedback to user to let them know what is being deleted
			System.out.println("Deleting row #" + row + ": "
				 + itemNames4[index] + " " + itemNumbers4[index] + " "
				 + storeNames4[index]);

			// delete item by shifting items on the right of the item to the left
			for (int i = index; i < listSize; i++) {
				itemNames4[i] = itemNames4[i + 1];
				itemNumbers4[i] = itemNumbers4[i + 1];
				storeNames4[i] = storeNames4[i + 1];
			}
			// subtract one from the size (one item deleted from list)
			--listSize;
			}
		}
		catch (InputMismatchException exception) {
			System.out.println("ERROR: You must enter an integer to delete an item.");
		}
		return listSize;
	}

	/**
	* Displays a the grocery list
	*
	* @param itemNames5 is the grocery list's item names
	* @param itemNumbers5 is the grocery list's item numbers
	* @param storeNames5 is the grocery list's store names
	* @param listSize is the size of the grocery list
	*/
	private static void display(String[] itemNames5,
	                            Integer[] itemNumbers5, String[] storeNames5, Integer listSize) {
		// divides each line by commas
		Scanner lineInput = new Scanner(firstLineOfFile).useDelimiter(",");
		//get the three headers from the first line of the file
		String header1 = lineInput.next();
		String header2 = lineInput.next();
		String header3 = lineInput.next();

		// display headings
		System.out.println("Row\t\t\t" + header1 + "\t\t\t" + header2 + "\t\t" + header3);
		// loop through the array
		for (int i = 0; i < listSize; i++) {
			// display grocery list items as a numbered list
			System.out.printf("%2d\t\t%8s\t\t\t%d\t\t\t%s\n",
				i+1, itemNames5[i], itemNumbers5[i], storeNames5[i]);
		}
	}

	/**
	* Write grocery list array to file
	*
	* @param names is the grocery list names
	* @param numbers is the grocery list numbers
	* @param stores is the grocery lis tstores
	* @param listSize is the size of the grocery list
	*/
	private static void writeToFile(String outputFile, String[] names,
	                                Integer[] numbers, String[] stores, Integer listSize) {
		// "PrintWriter" is a Class Used To Write to A File.
		PrintWriter fileWriter = null;
		try {
			/*
			* Must use try-catch block, because PrintWriter may throw
			* FileNotFoundException, which is a checked exception. This will connect
			* to a file in the current directory. If the file does not exists, a new
			* file will be created. If the file does exists, the file will be
			* overwritten.
			*/
			fileWriter = new PrintWriter(outputFile);
		}
		catch (FileNotFoundException exception) {
			// Print error message.
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.print("ERROR: File not found for \"");
			System.out.println(outputFile + "\"");
		}
		// if file opened successfully, then below code executes..
		// continue program if writeToFile is not "null"
		if (fileWriter != null) {
			//write the headings to the first line of the file
			fileWriter.println(firstLineOfFile);

			// loop through list (grocery list) and write to file
			for (int i = 0; i < listSize; i++) {
				fileWriter.println(names[i]+","+numbers[i]+","+stores[i]);
			}
			// REMEMBER: always give feedback to the user!
			System.out.println("Wrote to file: " + outputFile);
			// WARNING: don't forget to close the file!
			// will not write to file if not closed!
			fileWriter.close();
		}
	}
}

