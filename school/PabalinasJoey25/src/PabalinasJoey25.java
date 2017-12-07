/**
 * This program reads text fields
 * from a newline-delimited file into a
 * MyQueue<Patient> priority queue object,
 * displays the stored Strings, displays
 * a menu for operation-dispatch based
 * on a selection, and writes out the
 * final queue to an output file
 * specified on the command-line.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment #25
 * 12/06/17
 */

import javax.swing.JOptionPane;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.io.File;
import static java.lang.System.exit;

public class PabalinasJoey25 {
	/**
	 * The "main" method starts the program
	 *
	 * @param args Takes 2 file names as the commandline input.
         *             The first file name (args[0]) is the input file
	 *	       The second file name (args[1]) is the output file.
	 */
	public static void main(String[] args)
	{
		// check if exactly two arguments are given
		if (args.length < 2) {
			System.out.println("Please enter two filenames");
			exit(1);
		}

		try {
                      MyQueue<Patient> queue = readFileAddToQueue(args[0]);
                      queue = displayMenu(queue);
                      writeQueueToFile(args[1], queue);
		} catch(Exception e) {
			JOptionPane.showMessageDialog(null, e);
		}

	}

	/**
	 * reads a file and returns a queue containing its contents
	 *
	 * @param input the file to operate on
	 * @return the queue operated on
	 */
	private static MyQueue<Patient> readFileAddToQueue(String input) throws FileNotFoundException
	{
		MyQueue<Patient> queue = new MyQueue<>();
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
		while (scanFile.hasNextLine()) {
			// skip the header line
			scanFile.nextLine();
			Scanner line = scanFile.useDelimiter(",");
			// read the fields
			while (line.hasNext()) {
				String strPriority = line.next();
				// skip the leading comma
				String name = line.nextLine().substring(1);
				int priority = 0;
				try {
					priority = Integer.parseInt(strPriority);
				} catch (Exception e) {
					JOptionPane.showMessageDialog(null, e);
				}
				// instantiate Patient
				Patient patient = new Patient(name, priority);
				// add to queue
				queue.offer(patient);
			}
		}

		// return final queue
		return queue;
	}

	/**
	 * displays a menu and performs an action
	 * based on the choice selected
	 *
	 * @param queue the queue to operate on
	 */
	private static MyQueue<Patient> displayMenu(MyQueue<Patient> queue)
	{
		int choice;
		String person;
		// list of choices (array of Strings)
		String[] array = {
			"Offer Person", "Poll Person",
			"Peek Person", "Display List",
			"Exit Program"
		};

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
					String name = null, strPriority = null;
					int priority = 0;

					// get patient's name
					while (name == null) {
						name = JOptionPane.showInputDialog(null,
							"Please enter a name: ");
					}

					// get priority
					while (priority <= 0) {
						strPriority = JOptionPane.showInputDialog(null,
							"Please enter a priority: ");
						// try block to parse integer from input
						try {
							priority = Integer.parseInt(strPriority);
						} catch (Exception e) {
							JOptionPane.showMessageDialog(null, e);
						}
					}

					// instantiate Patient
					Patient patient = new Patient(name, priority);
					// add to queue
					queue.offer(patient);
					break;
				}

				// poll person
				case 1:
					// if empty then exit
					if (queue.empty()) {
						JOptionPane.showMessageDialog(null,
							"No more people.");
						return queue;
					}
					person = queue.poll().toString();
					JOptionPane.showMessageDialog(null,
						person);
					break;

				// peek person
				case 2:
					// if empty then exit
					if (queue.empty()) {
						JOptionPane.showMessageDialog(null,
							"No more people.");
						return queue;
					}
					person = queue.peek().toString();
					// if empty then exit
					JOptionPane.showMessageDialog(null,
						person);
					break;

				// show list
				case 3:
					// if empty then exit
					if (queue.empty()) {
						JOptionPane.showMessageDialog(null,
							"No more people.");
						return queue;
					}
					// if empty then exit
					JOptionPane.showMessageDialog(null,
						queue.toString());
					break;

				// exit
				case 4: /* fallthrough */
				case -1:
					JOptionPane.showMessageDialog(null,
						"Exiting.");
					return queue;

				/* wat */
				default:
					JOptionPane.showMessageDialog(null,
						"Please stop breaking my program :(");
					return queue;
			}
		}
	}

	/**
	 * write out a queue to a file
	 *
	 * @param filename the file to operate on
	 * @param queue the queue to operate on
	 */
	private static void writeQueueToFile(String filename, MyQueue<Patient> queue)
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

		} catch (FileNotFoundException e) {
			// Print error message.
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			JOptionPane.showMessageDialog(null,
				"ERROR: Unable to create \"" + filename + "\"");
		}

		// if file opened successfully, then below code executes..
		// continue program if writeToFile is not "null"
		if (fileWriter == null)
			return;

		// write out data and close file
		fileWriter.println("priority,name");
		// reformat output for final writing
		fileWriter.print(queue.toString(1).replaceAll(" - ", ","));
		// close file
		fileWriter.close();
	}
}

/**
 * Class MyQueue stores a list of
 * of T in a priority queue data
 * structure
 *
 * @author Pabalinas, Joey
 */
class MyQueue<T extends java.lang.Comparable<T>> extends PriorityQueue<T>{
	/**
	 * The constructor for MyQueue
	 *
	 */
	MyQueue()
	{
		super();
	}

	/**
	 * overloaded method to generate a newline delimited
	 * string of Patients in the queue
	 *
	 * @return String representation of the queue
	 */
	public String toString()
	{
		return toString(0);
	}

	/**
	 * generate a newline delimited string of Patients in the queue
	 *
	 * @param flag flag to control output format
	 * @return String representation of the queue
	 */
	public String toString(int flag)
	{
		/* queue to save our elements */
		MyQueue<T> saved = new MyQueue<>();
		/* string for result */
		StringBuilder result = new StringBuilder("");

		// if flag not set just use `heap.toString()`
		if (flag != 1)
			return heap.toString();

		/* save each element to a temporary queue while we build the string */
		while (!empty()) {
			T element = poll();
			saved.offer(element);
			// build result
			result.append(element.toString());
			result.append("\n");
		}

		/* rebuild the original queue */
		while (!saved.empty()) {
			T element = saved.poll();
			offer(element);
		}

		// makes output more useful than using `heap.toString()` directly
		return result.toString();
	}
}

/**
 * Class Patient stores a patient's
 * name and priority
 *
 * @author Pabalinas, Joey
 */
class Patient implements java.lang.Comparable<Patient>{
	// data fields for patient priority and name
	private int priority;
	private String name;

	/**
	 * overloaded constructor (deprecated)
	 */
	@Deprecated
	Patient()
	{
		this("Jane Doe", -1);
	}

	/**
	 * constructor
	 */
	Patient(String inputName, int inputPriority)
	{
		name = inputName;
		priority = inputPriority;
	}

	/**
	 * get the name of the patient
	 *
	 * @return the patient's name
	 */
	private String getName()
	{
		return name;
	}

	/**
	 * get the priority of the patient
	 *
	 * @return the patient's priority
	 */
	private int getPriority()
	{
		return priority;
	}

	/**
	 * get a String describing the patient
	 *
	 * @return String representation of the Patient object
	 */
	public String toString()
	{
		return getPriority() + " - " + getName();
	}

	/**
	 * Compare two patients based on priority
         *
	 * @param patient2 is the second patient being compared
	 * @return if priorities are equal, returns 0;
                   if patient1's priority is greater than patient2's priority, returns a positive number;
                   if patient1's priority is lesser than patient2's priority, returns a negative number
	 */
	public int compareTo(Patient patient2)
	{
		return getPriority() - patient2.getPriority();
	}

}


