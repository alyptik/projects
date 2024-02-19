/**
 * This program reads fields from
 * a .txt file into an array
 * of String objects, uses the
 * Sorting.quickSort() method to
 * sort the array, and finally prints
 * out the sorted list of Strings.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment 12
 * 10/08/17
 *
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import static java.lang.System.*;

public class PabalinasJoey12 {
	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args)
	{
		// declare variables to hold arguments
		String[] wordList;

		if (args.length < 1) {
			System.out.println("Please enter a filename");
			exit(1);
		}

		// error checking for commandline input
		try {
			// read fields from the file
			if ((wordList = readFile(args[0])) == null)
				throw new NullPointerException();

			// print fields
			printSortedStrings(args[0], wordList);

		// catch exceptions
		} catch (Exception e) {
			System.out.println(e.getLocalizedMessage());
		}
	}

	/**
	 * The "readFile" method reads data from a file and
	 * returns an array of Strings
	 * @param inputFile the file to read
	 * @return the array
	 */
	private static String[] readFile(String inputFile) {
		// connect to file (does NOT create new file)
		File file = new File(inputFile);
		Scanner scanFile = null;
		ArrayList<String> words = new ArrayList<>();

		try {
			scanFile = new Scanner(file);
		} catch (FileNotFoundException exception) {
			// Print error message.
			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.print("ERROR: File not found for \"");
			System.out.println(inputFile + "\"");
		}

		// if made connection to file, read from file
		if (scanFile != null) {
			while (scanFile.hasNextLine()) {
				// get a line of text..
				String line = scanFile.nextLine();
				// divides each line byspaces
				Scanner lineInput = new Scanner(line).useDelimiter(" ");
				while (lineInput.hasNext()) {
					String word = lineInput.next();
					words.add(word);
				}
			}

			String[] ret = new String[words.size()];
			for (int i = 0; i < words.size(); i++)
				ret[i] = words.get(i);
			return ret;
		}

		return null;
	}

	/**
	 * This method sorts and prints a String[]
	 *
	 * @param fileName the name of the file that was sorted
	 * @param array the array to print
	 */
	private static void printSortedStrings(String fileName, String[] array)
	{
		int idx = 0;
		Sorting.display = false;
		Sorting.quickSort(array, 0, array.length - 1);
		System.out.println("\nSorted array of Strings read from \"" + fileName + "\"\n");
		for (String word : array)
			System.out.println("index = [" + idx++ + "]:\t\"" + word + "\"");
	}

	/**
	 * This method compares two Strings
	 *
	 * @param a the first String
	 * @param b the second String
	 * @return this method returns -1, 0, and 1 for
	 * a if less than b, equal to b, and greater than b
	 * respectively
	 */
	private static int compareTo(String a, String b)
	{
		int ret = (a.charAt(0) > b.charAt(0) ? 1 : 0) - (a.charAt(0) < b.charAt(0) ? 1 : 0);

		if (a.length() < 2 && b.length() < 2) {
			return 0;
		} else if (b.length() > 2) {
			return -1;
		} else if (a.length() > 2) {
			return 1;
		} else {
			return ((ret != 0) ? ret : compareTo(a.substring(1), b.substring(1)));
		}
	}

}
