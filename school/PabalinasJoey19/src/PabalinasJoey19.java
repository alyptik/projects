/**
 * This program reads text fields
 * from a newline-delimited file into a
 * MyQueue<String> object, displays
 * the stored Strings, displays a menu
 * for operation-dispatch based on a
 * selection, and writes out the
 * final queue to an output file
 * specified on the command-line.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment #19
 * 11/11/17
 *
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import javax.swing.*;
import static java.lang.System.*;

public class PabalinasJoey19 {
	// max number of items in the queue
	private static final int MAX = 10;

	/**
	 * The "main" method starts the program
	 *
	 * @param args Takes 2 file names as the commandline input.
	 *             The first file name (args[0]) is the input file.
	 *             The second file name (args[1]) is the output file.
	 */
	public static void main(String[] args)
	{
		// check if exactly two arguments are given
		if (args.length < 2) {
			System.out.println("Please enter two filenames");
			exit(1);
		}

		// main try block
		try {
			MyQueue<String> queue = generateQueue(args[0]);
			// make sure queue isn't empty
			assert queue != null;
			// display objects in the queue
			JOptionPane.showMessageDialog(null, queue.toString());
			// loop menu of choices
			showMenu(queue);
			// write out final queue results
			saveQueueToFile(args[1], queue);

		// catch exceptions
		} catch (Exception e) {
			System.out.println(e.getLocalizedMessage());
		}
	}

	/**
	 * reads a file and returns a queue containing its contents
	 *
	 * @param input the file to operate on
	 * @return the queue operated on
	 */
	private static MyQueue<String> generateQueue(String input)
		throws FileNotFoundException
	{
		MyQueue<String> queue = new MyQueue<>(MAX);
		File file = new File(input);
		Scanner scanFile = null;

		try {
			// open the file
			scanFile = new Scanner(file);

		} catch (FileNotFoundException exception) {
			// Print error message.
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.print("ERROR: File not found for \"");
			System.out.println(input + "\"");
		}

		// if made connection to file, read from file, else return null
		if (scanFile == null)
			return null;

		//first line of file is the headers, so don't store in the arrays
		while (scanFile.hasNextLine())
			queue.offer(scanFile.nextLine());

		// return final queue
		return queue;
	}

	/**
	 * displays a menu and performs an action
	 * based on the choice selected
	 *
	 * @param queue the queue to operate on
	 */
	private static void showMenu(MyQueue<String> queue)
	{
		// list of choices (array of Strings)
		String[] array = {
			"Offer Person", "Poll Person",
			"Peek Person", "Display List",
			"Exit Program",
		};
		int choice = 0;

		// display loop
		for (;;) {
			choice = JOptionPane.showOptionDialog(null,
				"Press a Button",
				"Example Menu",
				JOptionPane.YES_NO_CANCEL_OPTION,
				JOptionPane.QUESTION_MESSAGE,
				null,
				array,
				array[array.length - 1]);

			// don't display choice when exiting'
			if (choice != -1 && choice != 4) {
				// display selection
				JOptionPane.showMessageDialog(null,
					"You selected: " + array[choice]);
			}

			switch (choice) {
			// offer person
			case 0: {
				String person = null;
				while (person == null) {
					person = JOptionPane.showInputDialog(null,
						"Please enter a name: ");
				}
				queue.offer(person);
				break;
			}

			// poll person
			case 1: {
				String person = queue.poll();
				// if empty then exit
				if (person == null) {
					JOptionPane.showMessageDialog(null,
						"No more people.");
					return;
				}
				JOptionPane.showMessageDialog(null,
					person);
				break;
			}

			// peek person
			case 2: {
				String person = queue.peek();
				// if empty then exit
				if (person == null) {
					JOptionPane.showMessageDialog(null,
						"No more people.");
					return;
				}
				JOptionPane.showMessageDialog(null,
					person);
				break;
			}

			// show list
			case 3:
				JOptionPane.showMessageDialog(null,
					queue.toString());
				break;

			// exit
			case 4: /* fallthrough */
			case -1:
				JOptionPane.showMessageDialog(null,
					"Exiting.");
				return;
			}
		}
	}

	/**
	 * write out a queue to a file
	 *
	 * @param filename the file to operate on
	 * @param queue the queue to operate on
	 */
	private static void saveQueueToFile(String filename, MyQueue<String> queue)
		throws FileNotFoundException
	{
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
			fileWriter = new PrintWriter(filename);

		} catch (FileNotFoundException exception) {
			// Print error message.
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.print("ERROR: File not found for \"");
			System.out.println(filename + "\"");
		}

		// if file opened successfully, then below code executes..
		// continue program if writeToFile is not "null"
		if (fileWriter == null)
			return;

		// write out data and close file
		fileWriter.print(queue.toString());
		fileWriter.close();
	}
}

/**
 * Class MyQueue stores a list of T
 * in a queue data structure
 *
 * @author Pabalinas, Joey
 */
class MyQueue<T> extends ArrayQueue<T>{

	/**
	 * The constructor for MyQueue
	 *
	 * @param max initialize the maxSize member
	 */
	MyQueue(int max)
	{
		super(max);
	}

	/**
	 * generate a newline delimited string of the queue
	 */
	public String toString()
	{
		String result = "";

		// loop over items
		for (int idx = frontIndex, cnt = 0;
				(idx % maxSize) != endIndex + 1 && cnt < currentSize;
				idx++, cnt++) {
			// break early if queue empty
			if (endIndex == -1)
				break;
			// append current index
			result += array[idx] + "\n";
		}

		return result;
	}
}
