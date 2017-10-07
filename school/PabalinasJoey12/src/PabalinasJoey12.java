/**
 * This program reads fields from
 * a .csv file into an array
 * of StarHouses objects, appropriately
 * sets their data members, and
 * prints the results. It then
 * instantiates a new array of objects,
 * sorts the original array with a
 * comparison-free radix sort (against
 * the `degree` data field) then instantiates
 * the now-sorted fields of the first array
 * and prints them after using the compareTo()
 * method to make sure the objects were sorrted
 * properly.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment 12
 * 10/06/17
 *
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import static java.lang.System.*;

public class PabalinasJoey12 {
	// range of a byte
	private static final int BASE = 256;
	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args)
	{
		// declare variables to hold arguments
		ArrayList<Integer> wordList = new ArrayList<>();

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
			radixSort(wordList);

		// catch exceptions
		} catch (Exception e) {
			System.out.println(e.getLocalizedMessage());
		}
	}

	/**
	 * The "readFile" method reads data from a file and
	 * returns an array of ArrayList<Integer>
	 * @param inputFile the file to read
	 * @return the array
	 */
	private static ArrayList<Integer> readFile(String inputFile) {
		// connect to file (does NOT create new file)
		File file = new File(inputFile);
		Scanner scanFile = null;
		ArrayList<Integer> words = new ArrayList<>();

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
			int idx = 0;
			while (scanFile.hasNextLine()) {
				// get a line of text..
				String line = scanFile.nextLine();
				// divides each line byspaces
				Scanner lineInput = new Scanner(line).useDelimiter(" ");
				while (lineInput.hasNext()) {
					String word = lineInput.next();
					int intRep = 0;
					// convert string to an array of consecutive ints
					for (int i = 0; i < word.length(); i++) {
						intRep += (((int) (word.charAt(i))) << (i * 8));
						// System.out.println(i + " " + intRep);
					}

					words.add(intRep);
					System.out.println("index = [" + idx + "]:\t" +
						word + ": " + Math.abs(intRep));
					idx++;
				}
			}

			return words;
		}

		return null;
	}


	/**
	 * This method compares two Integers
	 *
	 * @param a the first int
	 * @param b the second int
	 * @return this method returns -1, 0, and 1 for
	 * a if less than b, equal to b, and greater than b
	 * respectively
	 */
	private static int compareTo(int a, int b)
	{
		return (a > b ? 1 : 0) - (a < b ? 1 : 0);
	}

	/**
	 * This method gives maximum value in ArrayList<Integer>
	 *
	 * @param inputArray the map to test
	 * @return the largest member
	 */
	private static int getMax(ArrayList<Integer> inputArray)
	{
		int max = inputArray.get(0);
		for (int i = 1; i < inputArray.size(); i++) {
			if (compareTo(inputArray.get(i), max) > 0) {
				max = inputArray.get(i);
			}
		}
		return max;
	}

	/**
	 * This method sorts this an ArrayList<Integer>
	 *
	 * @param inputArray the array to sort
	 * @return the old array
	 */
	private static ArrayList<Integer> radixSort(ArrayList<Integer> inputArray)
	{
		int radix = 1, len = inputArray.size();
		int largest = getMax(inputArray);
		int[] result = new int[len];
		int[] input = new int[len];
		ArrayList<Integer> sorted = new ArrayList<>();
		ArrayList<String> words = new ArrayList<>();

		for (int i = 0; i < len; i++)
			input[i] = inputArray.get(i);

		while (largest / radix > 0) {
			int[] idxArray = new int[BASE];

			/* store the count of "keys" or digits in idxArray[] */
			for (int i = 0; i < BASE; i++) {
				idxArray[input[i] / radix % BASE]++;
			}

			/* change idxArray[i] so that idxArray[i] now contains actual */
			/* position of this digit in result[] */
			for (int i = 1; i < BASE; i++) {
				idxArray[i] += idxArray[i - 1];
			}

			/* build the resulting array */
			for (int i = len - 1; i >= 0; i--) {
				result[(idxArray[(input[i] / radix) % BASE] - 1)] = input[i];
				idxArray[(input[i] / radix) % BASE]--;
			}

			/* now main array sortedArray[] contains sorted */
			/* objects according to degree digit place */
			System.arraycopy(result, 0, input, 0, len);

			/* move to next digit place */
			radix *= BASE;
		}

		for (int i = result.length - 1; i >= 0; i--) {
			sorted.add(result[i]);
			// convert an array of consecutive ints to string
			int letterIdx = 0;
			char cur = 0;
			StringBuilder word = new StringBuilder();
			while ((cur = (char)((result[i] >> (letterIdx * 8)) & 0xff)) != 0) {
				word.append(cur);
				System.out.println("0x"+cur);
			}
			words.add(word.toString());
			System.out.println("index = [" + i + "]:\t" + words.get(i));
		}

		return sorted;
	}

}
