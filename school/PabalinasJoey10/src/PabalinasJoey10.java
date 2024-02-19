/**
 * This program reads fields from
 * a .csv file into an array
 * of StarHouses objects, appropriately
 * sets their data members, and
 * prints the results. It then
 * instantiates a new array of objects
 * which it initialized with the mutated
 * fields of the first array and prints
 * the the now mutated array of
 * StarHouseWithInfo objects containing
 * two extra fields.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment 10
 * 09/26/17
 *
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import static java.lang.System.*;

public class PabalinasJoey10 {
	// constants
	private static final int MAX = 1024;
	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args)
	{
		// declare variables to hold arguments
		StarHousesWithStarInfo[] houses, mutated;
		Collection<Object> starInfoStream;

		if (args.length < 1) {
			System.out.println("Please enter a filename");
			exit(1);
		}

		// error checking for commandline input
		try {
			// read fields from the file
			if ((houses = readFile(args[0])) == null)
				throw new NullPointerException();

			// for (int i = 0; i < houses.length; i++)
			//	starInfoStream.add(houses[i]);

			// declare array to hold new, mutated objects
			mutated = houses;
			// print fields
			for (int i = 0; i < houses.length; i++) {
				// houses[i].stream().map(h -> ((StarHouses)h).
				System.out.printf("%d\t%s\n", i, houses[i].getFields());

				// uppercase whole name
				// mutated[i].forEach(h -> houses[0].forEach(j -> ((StarHouses)j).
				mutated[i].updateName(houses[i].
					updateName("").toUpperCase());
				// uppercase first two letters
				// mutated[i].forEach(h -> houses[0].forEach(j -> ((StarHouses)j). updateStar(((StarHouses)j).
				mutated[i].updateStar(houses[i].
					updateStar("").toUpperCase().substring(0, 1) +
					houses[i].updateStar("").substring(2));
				// obfuscate with bitwise operations and mod 360
				// mutated[i].forEach(h -> houses[0].forEach(j -> ((StarHouses)j).
				mutated[i].updateDegree(houses[i].
						updateDegree(houses[i].
							updateDegree(0) ^
							((int)(((System.nanoTime() % 360) << 3)
							& 0xdeadbeef) >> 2) % 360));
			}

			// print mutated fields
			System.out.println("");
			for (int i = 0; i < mutated.length; i++) {
				// mutated[i].forEach(h -> System.out.print(((StarHouses) h).getFields()));
				System.out.printf("%d\t%s\n", i, mutated[i].getFields());
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
	private static StarHousesWithStarInfo[] readFile(String inputFile) {
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
			StarHousesWithStarInfo houseArrInfo[] = new StarHousesWithStarInfo[size];

			for (int i = 0; i < size; i++) {
				houseArr[i] = new StarHouses();
				houseArrInfo[i] = new StarHousesWithStarInfo();
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

/**
 * Class StarHouses stores and displays the data for each StarHouses object
 *
 * @author Pabalinas, Joey
 */
class StarHouses {
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


class StarHousesWithStarInfo extends StarHouses {
	// data fields
	private String constellation;
	private long starAge;

	/**
	 * The constructor for StarHouses
	 */
	StarHousesWithStarInfo()
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
	private StarHousesWithStarInfo(String inName, String inStar, int inDegree, String inConst, long intAge)
	{
		name = inName;
		star = inStar;
		degree = inDegree;
	}

	/**
	 * The setter/getter for consellation
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
