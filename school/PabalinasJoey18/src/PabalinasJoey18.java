/**
 * This program reads fields
 * from a .csv file into a
 * MyLinkedList<StarHouses>
 * object, appropriately sets
 * the data members of each
 * node of the list, prints the
 * results, dictionary sorts the
 * list using the bubbleSort()
 * method, and finally prints
 * the sorted list. It then
 * loops and reads user
 * input with the deleteNode()
 * method and deletes the specified node
 * after error-checking user
 * input until the user passes
 * a '0' to quit or until the
 * MyLinkedList<StarHouses> has
 * no more members.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment #18
 * 10/22/17
 *
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import static java.lang.System.*;

public class PabalinasJoey18 {
	// constants
	private static final int MAX = 1024;

	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args)
	{
		// declare variables to hold arguments
		MyLinkedList<StarHouses> houses;

		// check if exactly two arguments are given
		if (args.length < 1) {
			System.out.println("Please enter a filename");
			exit(1);
		}

		// error checking for commandline input
		try {
			// read fields from the file
			if ((houses = readFile(args[0])) == null)
				throw new NullPointerException();

			// print the fields of each node
			for (int i = 1; i <= houses.getSize(); i++)
				System.out.printf("%d\t%s\n", i, houses.get(i).getFields());


			// sort the list
			houses.bubbleSort();
			System.out.println("\nSorted list (alphabetical order):");

			// print the fields of each node
			for (int i = 1; i <= houses.getSize(); i++)
				System.out.printf("%d\t%s\n", i, houses.get(i).getFields());

			// loop until user passes a '0' to quit
			while (houses.getSize() != 0 && deleteNode(houses) != 0) {
				// print the fields of each node after deletion
				for (int i = 1; i <= houses.getSize(); i++)
					System.out.printf("%d\t%s\n", i, houses.get(i).getFields());
			}

			// print graceful termination message
			System.out.println("\nExiting...");

		// catch exceptions
		} catch (Exception e) {
			System.out.println(e.getLocalizedMessage());
		}
	}

	/**
	 * The "deleteNode" method deletes a node from the MyLinkedList<StarHouses>
	 * @param houses linked list to operate on
	 */
	private static int deleteNode(MyLinkedList<StarHouses> houses)
	{
		// connect to stdin
		Scanner in = new Scanner(System.in);
		// initialize variables to hold state and current line
		int row = 0, valid = 0;
		String line = null;

		// loop until valid input is given
		while (valid == 0) {
			try {
				// try to parse row number
				System.out.print("\nEnter the row number of the object to be deleted (0 to quit): ");
				line = in.next();
				row = Integer.parseInt(line);

				// exit early if user inputs a '0'
				if (row == 0)
					return 0;
				// throw out of bounds exception if index is out of range
				if (row < 0 || row > houses.getSize())
					throw new ArrayIndexOutOfBoundsException();
				// set flag if parsed a valid row number
				valid = 1;

				//if it is not an integer, then use zero (0) as default
			} catch (ArrayIndexOutOfBoundsException exception) {
				System.out.println("ERROR: " + row
					+ " is not a valid row!");

				//if it is not an integer, then use zero (0) as default
			} catch (NumberFormatException exception) {
				System.out.println("ERROR: " + line
					+ " is not a valid number!");
			}
		}

		// print row to be deleted
		System.out.println("\nDeleting:\t" + houses.get(row).getFields());
		System.out.println("");
		// delete row
		houses.remove(row);

		// return non-zero on successful deletion
		return row;
	}

	/**
	 * The "readFile" reads data from a file
	 * @param inputFile the file to read
	 */
	private static MyLinkedList<StarHouses> readFile(String inputFile)
	{
		// connect to file (does NOT create new file)
		File file = new File(inputFile);
		Scanner scanFile = null;

		try {
			scanFile = new Scanner(file);
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.println("\nRead from file: " + inputFile + "\n");
		} catch (FileNotFoundException exception) {
			// Print error message.
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.print("ERROR: File not found for \"");
			System.out.println(inputFile + "\"");
		}

		// if made connection to file, read from file
		if (scanFile != null) {
			//first line of file is the headers, so don't store in the arrays
			String header = scanFile.nextLine();

			// divides each line by commas
			Scanner headerInput = new Scanner(header).useDelimiter(",");
			//get the name, count, and store from one line in the file
			String name = headerInput.next();
			String star =  headerInput.next();
			String deg = headerInput.next();
			// print header
			System.out.printf("%s\t%10s\t%10s\t%10s\n\n", "idx", name, star, deg);

			// initialize buffers
			String[] names = new String[MAX];
			String[] stars = new String[MAX];
			int[] degrees = new int[MAX];
			int size = 0;

			// keeps looping if file has more lines..
			while (scanFile.hasNextLine()) {
				// exit if too many lines
				if (size >= MAX - 1) {
					System.out.println("Error: file too large");
					exit(1);
				}

				// get a line of text..
				String line = scanFile.nextLine();

				// divides each line by commas
				Scanner lineInput = new Scanner(line).useDelimiter(",");
				//get the name, count, and store from one line in the file
				names[size] = lineInput.next();
				stars[size] = lineInput.next();
				String degreeStr = lineInput.next();
				int degree = 0;

				try {
					degree = Integer.parseInt(degreeStr);
				} catch (NumberFormatException exception) {
					//if it is not an integer, then use zero (0) as default
					System.out.println("ERROR: " + degree + " is not a number!");
				}

				// increment size
				degrees[size] = degree;
				size++;
			}

			// set fields
			MyLinkedList<StarHouses> houseList = new MyLinkedList<>();
			for (int i = 0; i < size; i++) {
				StarHouses house = new StarHouses();
				// set fields
				house.setFields(names[i], stars[i], degrees[i]);
				houseList.add(house);
			}

			return houseList;
		}

		return null;
	}
}

/**
 * Class StarHouses stores and displays the data for each StarHouses object
 *
 * @author Pabalinas, Joey
 */
class StarHouses implements Comparable<StarHouses> {
	// data fields
	private int degree;
	private String name, star;

	/**
	 * The overloaded constructor for StarHouses
	 */
	StarHouses() {
		this(null, null, 0);
	}

	/**
	 * The constructor for StarHouses
	 * @param inputName the house name
	 * @param inputStar the house star
	 * @param inputDegree the house compass degree
	 */
	private StarHouses(String inputName, String inputStar, int inputDegree)
	{
		name = inputName;
		star = inputStar;
		degree = inputDegree;
	}

	/**
	 * The setter for StarHouses
	 * @param inputName the house name
	 * @param inputStar the house star
	 * @param inputDegree the house compass degree
	 */
	void setFields(String inputName, String inputStar, int inputDegree)
	{
		name = inputName;
		star = inputStar;
		degree = inputDegree;
	}

	/**
	 * The getter for StarHouses
	 * @return formatted string of the data fields
	 */
	String getFields()
	{
		return String.format("%10s\t%10s\t%10d", name, star, degree);
	}

	/**
	 * The getter for StarHouses name
	 * @return the name member of this object
	 */
	private String getName()
	{
		return name;
	}

	/**
	 * Compares this object with the specified object for order.  Returns a
	 * negative integer, zero, or a positive integer as this object is less
	 * than, equal to, or greater than the specified object.
	 * <p>
	 * <p>The implementor must ensure
	 * {@code sgn(x.compareTo(y)) == -sgn(y.compareTo(x))}
	 * for all {@code x} and {@code y}.  (This
	 * implies that {@code x.compareTo(y)} must throw an exception iff
	 * {@code y.compareTo(x)} throws an exception.)
	 * <p>
	 * <p>The implementor must also ensure that the relation is transitive:
	 * {@code (x.compareTo(y) > 0 && y.compareTo(z) > 0)} implies
	 * {@code x.compareTo(z) > 0}.
	 * <p>
	 * <p>Finally, the implementor must ensure that {@code x.compareTo(y)==0}
	 * implies that {@code sgn(x.compareTo(z)) == sgn(y.compareTo(z))}, for
	 * all {@code z}.
	 * <p>
	 * <p>It is strongly recommended, but <i>not</i> strictly required that
	 * {@code (x.compareTo(y)==0) == (x.equals(y))}.  Generally speaking, any
	 * class that implements the {@code Comparable} interface and violates
	 * this condition should clearly indicate this fact.  The recommended
	 * language is "Note: this class has a natural ordering that is
	 * inconsistent with equals."
	 * <p>
	 * <p>In the foregoing description, the notation
	 * {@code sgn(}<i>expression</i>{@code )} designates the mathematical
	 * <i>signum</i> function, which is defined to return one of {@code -1},
	 * {@code 0}, or {@code 1} according to whether the value of
	 * <i>expression</i> is negative, zero, or positive, respectively.
	 *
	 * @param house the object to be compared.
	 * @return a negative integer, zero, or a positive integer as this object
	 * is less than, equal to, or greater than the specified object.
	 * @throws NullPointerException if the specified object is null
	 * @throws ClassCastException   if the specified object's type prevents it
	 *                              from being compared to this object.
	 */
	@Override
	public int compareTo(StarHouses house)
	{
		// convert names to lowercase
		String a = getName().toLowerCase();
		String b = house.getName().toLowerCase();
		// compare the two names (String has its own compareTo() method)
		return a.compareTo(b);
	}
}

class MyLinkedList<T extends java.lang.Comparable<T>> extends LinkedList<T> {

	/**
	 * sets an item (address to an item) from any position in the list.
	 *
	 * @param position is the position of an item in the list.
	 * @returns the old item at the requested index
	 * @exception ListException if an item does not exist at that position, throws exception
	 */
	private T set(Integer position, T value) throws ListException {
		// check if empty list
		if (head == null) {
			throw new ListException("Cannot get an item from an empty list!");
		}
		// if position is outside range, throw exception
		if (position < 1 || position > size) {
			throw new ListException(position + " is outside list range!");
		}
		// Find node:
		// counter to keep track of loops
		Integer counter = 1;
		// point to current node
		Node<T> current = head;
		while (!counter.equals(position)) {
			// BAD CODE: while(counter != position){
			// goto next node for current pointer
			current = current.getNext();
			// add 1 to counter
			counter++;
		}
		// return the data (item) stored by the node

		T temp = current.getData();
		current.setData(value);
		return temp;
	}

	/**
	 * bubble sort a LinkedList<T>
	 *
	 */
	void bubbleSort()
	{
		int start = 1, end = getSize();
		//flag to see if an item was swapped or not
		boolean swap = false;
		// loop size - 1 times
		for (int i = start + 1; i <= end; i++) {
			swap = false;
			//loop from beginning of array to (last element - i)
			for (int j = 1; j <= end - i + 1; j++) {
				// swap if 1st item greater than 2nd item
				if (get(j).compareTo(get(j + 1)) > 0) {
					// swap
					T temp = set(j, get(j + 1));
					set(j + 1, temp);
					swap = true;
				}
			}

			//if no swap, list is in order
			//so break out of loop early
			if (!swap) {
				break;
			}
		}

	}
}
