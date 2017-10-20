/**
 * This program reads fields
 * from a .csv file into a
 * LinkedList<StarHouses>
 * object, appropriately sets
 * the data members of each
 * node of the list, and
 * then prints the results.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment #15
 * 10/19/17
 *
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import static java.lang.System.*;

public class PabalinasJoey15 {
	// constants
	private static final int MAX = 1024;

	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args) {
		// declare variables to hold arguments
		LinkedList<StarHouses> houses;

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

		// catch exceptions
		} catch (Exception e) {
			System.out.println(e.getLocalizedMessage());
		}
	}

	/**
	 * The "readFile" read data from a file
	 * @param inputFile the file to read
	 */
	private static LinkedList<StarHouses> readFile(String inputFile) {
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
			LinkedList<StarHouses> houseList = new LinkedList<>();
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
class StarHouses {
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
}




