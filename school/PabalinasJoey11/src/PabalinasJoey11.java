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
 * ICS 211 Assignment 11
 * 10/04/17
 *
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import static java.lang.System.*;

public class PabalinasJoey11 {
	// constants
	private static final int MAX = 1024;
	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args)
	{
		// declare variables to hold arguments
		StarHousesWithSort[] houses, sorted;

		if (args.length < 1) {
			System.out.println("Please enter a filename");
			exit(1);
		}

		// error checking for commandline input
		try {
			// read fields from the file
			if ((houses = readFile(args[0])) == null)
				throw new NullPointerException();

			// print fields
			for (int i = 0; i < houses.length; i++) {
				// houses[i].stream().map(h -> ((StarHouses)h).
				System.out.printf("%d\t%s\n", i, houses[i].getFields());
			}

			// print unsorted fields
			System.out.println("\nunsorted objects:\n");
			for (int i = 0; i < houses.length; i++) {
				// sorted[i].forEach(h -> System.out.print(((StarHouses) h).getFields()));
				System.out.printf("%d\t%s\n", i, houses[i].getFields());
			}

			// assign the sorted array
			sorted = StarHousesWithSort.radixSort(houses);
			System.out.println("\nsorted objects:\n");
			for (int i = 0; i < houses.length; i++) {
				// make sure both arrays were correctly sorted
				if (houses[i].compareTo(sorted[i]) != 0) {
					System.out.println("\narrays not matching at idx: " + i + "\n");
					exit(1);
				}
				// print sorted fields if so
				System.out.printf("%d\t%s\n", i, sorted[i].getFields());
			}

		// catch exceptions
		} catch (Exception e) {
			System.out.println(e.getLocalizedMessage());
		}
	}

	/**
	 * The "readFile" method reads data from a file
	 * @param inputFile the file to read
	 */
	private static StarHousesWithSort[] readFile(String inputFile) {
		// connect to file (does NOT create new file)
		File file = new File(inputFile);
		Scanner scanFile = null;

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
			String[] constellations = new String[MAX];
			long[] starAges  = new long[MAX];
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
				constellations[size] = lineInput.next();
				String ageStr = lineInput.next();
				int degree = 0;
				long age = 0;

				try {
					degree = Integer.parseInt(degreeStr);
					age = Integer.parseInt(ageStr);
				} catch (NumberFormatException exception) {
					//if it is not an integer, then use zero (0) as default
					System.out.println("ERROR: " + degree +
						"/" + age + " is not a number!");
				}

				// increment size
				degrees[size] = degree;
				starAges[size] = age;
				size++;
			}

			// set fields
			StarHouses houseArr[] = new StarHouses[size];
			StarHousesWithSort houseArrInfo[] = new StarHousesWithSort[size];

			for (int i = 0; i < size; i++) {
				houseArr[i] = new StarHouses();
				houseArrInfo[i] = new StarHousesWithSort();
				// print null objects
				System.out.printf("%d\t%s\n", i, houseArr[i].getFields());
				// set fields
				houseArr[i].updateName(names[i]);
				houseArr[i].updateStar(stars[i]);
				houseArr[i].updateDegree(degrees[i]);

				// set inherited class fields
				houseArrInfo[i].updateName(names[i]);
				houseArrInfo[i].updateStar(stars[i]);
				houseArrInfo[i].updateDegree(degrees[i]);
				houseArrInfo[i].updateConst(constellations[i]);
				houseArrInfo[i].updateAge(starAges[i]);
			}

			// In order to print double quotes("),
			// the escape sequence for double quotes (\") must be used.
			System.out.println("\nRead from file: " + inputFile + "\n");

			return houseArrInfo;
		}

		return null;
	}
}

class StarHousesWithSort extends StarHouses implements java.lang.Comparable<StarHousesWithSort>
{
	/* radix sort base */
	private static final int BASE = 10;
	// data fields
	private String constellation;
	private long starAge;

	/**
	 * The constructor for StarHouses
	 */
	StarHousesWithSort()
	{
		this(null, null, 0, null, 0L);
	}

	/**
	 * The constructor for StarHouses
	 *
	 * @param inName   the house name
	 * @param inStar   the house star
	 * @param inDegree the house compass degree
	 */
	private StarHousesWithSort(String inName, String inStar, int inDegree, String inConst, long intAge)
	{
		name = inName;
		star = inStar;
		degree = inDegree;
	}

	/**
	 * This method compares this object to another StarHousesWithSort
	 *
	 * @param cmpTarget the object to compare it to
	 * @return this method returns -1, 0, and 1 for
	 * less than, equals to, and greater than respectively
	 */
	public int compareTo(StarHousesWithSort cmpTarget)
	{
		return (cmpTarget.updateDegree(0) < degree ? 1 : 0) - (cmpTarget.updateDegree(0) > degree ? 1 : 0);
	}

	/**
	 * This compares this object to another StarHousesWithSort
	 * This method gives maximum value in StarHousesWithSort[]
	 *
	 * @param inputArray the array to test
	 * @return the largest member
	 */
	private static int getMax(StarHousesWithSort[] inputArray)
	{
		StarHousesWithSort max = inputArray[0];
		for (int i = 1; i < inputArray.length; i++) {
			if (inputArray[i].compareTo(max) > 0) {
				max = inputArray[i];
			}
		}
		return max.degree;
	}

	/**
	 * This method sorts this an array of StarHousesWithSort
	 *
	 * @param inputArray the array to sort
	 * @return the sorted array
	 */
	static StarHousesWithSort[] radixSort(StarHousesWithSort[] inputArray)
	{
		int radix = 1, len = inputArray.length;
		int largest = StarHousesWithSort.getMax(inputArray);
		StarHousesWithSort[] result = new StarHousesWithSort[len];

		while (largest / radix > 0) {
			int[] idxArray = new int[BASE];

			/* store the count of "keys" or digits in idxArray[] */
			for (int i = 0; i < BASE; i++) {
				idxArray[(inputArray[i].updateDegree(0) / radix) % BASE]++;
			}

			/* change idxArray[i] so that idxArray[i] now contains actual */
			/* position of this digit in result[] */
			for (int i = 1; i < BASE; i++) {
				idxArray[i] += idxArray[i - 1];
			}

			/* build the resulting array */
			for (int i = len - 1; i >= 0; i--) {
				result[(idxArray[(inputArray[i].updateDegree(0) / radix) % BASE]) - 1] = inputArray[i];
				idxArray[(inputArray[i].updateDegree(0) / radix) % BASE]--;
			}

			/* now main array sortedArray[] contains sorted */
			/* objects according to degree digit place */
			System.arraycopy(result, 0, inputArray, 0, len);

			/* move to next digit place */
			radix *= BASE;
		}
		return result;
	}

	/**
	 * The setter/getter for constellation
	 *
	 * @param inConst the constellation
	 * @return the original constellation
	 */
	String updateConst(String inConst) {
		String old = constellation;
		// don't change value if empty string given
		constellation = (inConst.matches("")) ? old : inConst;
		return old;
	}

	/**
	 * The setter/getter for starAge
	 *
	 * @param inAge the input star age
	 * @return the original star age
	 */
	long updateAge(long inAge) {
		long old = starAge;
		// don't change value if 0 given
		starAge = (inAge == 0L) ? old : inAge;
		return old;
	}

	/**
	 * The general getter for StarHouses
	 *
	 * @return formatted string of the data fields
	 */
	public String getFields() {
		return String.format("%10s\t%10s\t%10d\t%10s\t%10d",
			name, star, degree, constellation, starAge);
	}
}

/**
 * Class StarHouses stores and displays the data for each StarHouses object
 *
 * @author Pabalinas, Joey
 */
class StarHouses
{
	// data fields
	int degree;
	String name, star;

	/**
	 * The overloaded constructor for StarHouses
	 */
	StarHouses() {
		this(null, null, 0);
	}

	/**
	 * The constructor for StarHouses
	 * @param inName the house name
	 * @param inStar the house star
	 * @param inDegree the house compass degree
	 */
	private StarHouses(String inName, String inStar, int inDegree)
	{
		name = inName;
		star = inStar;
		degree = inDegree;
	}

	/**
	 * The setter for name
	 * @param inName the house name
	 * @return the original name
	 */
	String updateName(String inName)
	{
		String old = name;
		// don't change value if empty string given
		name = (inName.matches("")) ? old : inName;
		return old;
	}

	/**
	 * The setter/getter for star
	 * @param inStar the star
	 * @return the original star
	 */
	String updateStar(String inStar)
	{
		String old = star;
		// don't change value if empty string given
		star = (inStar.matches("")) ? old : inStar;
		return old;
	}

	/**
	 * The setter/getter for degree
	 * @param inDegree the degree
	 * @return the original degree
	 */
	int updateDegree(int inDegree)
	{
		int old = degree;
		// don't change value if 0 given
		degree = (inDegree == 0) ? old : inDegree;
		return old;
	}

	/**
	 * The general getter for StarHouses
	 * @return formatted string of the data fields
	 */
	public String getFields()
	{
		return String.format("%10s\t%10s\t%10d", name, star, degree);
	}
}
