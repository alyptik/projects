/**
 * This program reads a file, scans
 * it for Integers, adds them to an
 * array, and then prints out the
 * results while handling any
 * exceptions thrown.
 *
 * @author Pabalinas, Joey
 * ICS 111 Assignment #03
 * 08/22/17
 */

import java.util.Scanner;
// needed for file IO
import java.io.*;

public class PabalinasJoey03 {
	/**
	 * Reads and prints out Integers from a file after
	 * reading and storing them into an array
	 *
	 * @param args The element args[0] is the file name to read
	 */
	public static void main(String [] args) {
		// usage information string literal
		final String usage = "Error: no input file specified!\n" +
			"usage: java -cd . " + PabalinasJoey03.class.getName() + " <filename>";

		// catch exceptions
		try {
			// throw exception if no argument is provided
			if (args.length < 1) {
				throw new FileNotFoundException();
			}
			// read the integers from args[0]
			Integer[] array = PabalinasJoey03.readFileReturnIntegers(args[0]);
			// print the results
			PabalinasJoey03.printArrayAndIntegerCount(array, args[0]);
		} catch (FileNotFoundException notFoundException) {
			// print usage information
			System.out.println(usage);
		} catch (Exception e) {
			// catch unhandled exceptions
			System.out.println(e.getMessage());
		}
	}

	/**
	 * Read Integers from a file and return and array of those Integer objects
	 *
	 * @param filename The name of the file to read
	 */
	private static Integer[] readFileReturnIntegers(String filename) throws FileNotFoundException, IndexOutOfBoundsException {
		// initialize Scanner objects
		Scanner reader = new Scanner(new File(filename));
		Integer[] array = new Integer[10000];
		int i = 0, errors = 0;

		// read the integers
		while (reader.hasNextLine()) {
			// check if index is valid, then add to the array
			if (i > array.length - 1)
				throw new IndexOutOfBoundsException();
			// try to parse an Integer
			try {
				array[i] = Integer.parseInt(reader.next());
				i++;
			// increment error count
			} catch (Exception e) { errors++; }
		}
		// print error total
		System.out.println("There were " + errors + " non-integers found during scanning.");
		// cleanup and return
		reader.close();
		return array;
	}

	/**
	 * Print out and array of integers and the filename they were read from
	 *
	 * @param filename Name of the file read from
	 * @param array Array of Integers results
	 *
	 */
	private static void printArrayAndIntegerCount(Integer[] array, String filename){
		// counter
		int counter = 0;

		// print out the filename
		System.out.println("Integers read from \"" + filename + "\": ");
		// print the integers
		for (int i = 0; i < array.length; i++) {
			// don't print nulls
			if (array[i] == null)
				continue;
			// increment counter for non-nulls
			System.out.println("index = " + counter++ + ", " +
				"element = " + array[i].toString() + " ");
		}
		// print integer total
		System.out.println("There were a total of " + counter + " integers found.");
	}
}

