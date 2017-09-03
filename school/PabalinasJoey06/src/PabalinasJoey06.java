/**
 * this program takes an integer
 * argument and performs five TCO
 * (Tail Call Optimized) recursive
 * methods, passing that integer
 * as an argument to each method
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment #06
 * 08/31/2017
 */

public class PabalinasJoey06 {
	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args) {
		// declare int to hold argument
		int number;
		// check if an argument is given
		if (args.length < 1) {
			System.out.println("Please enter a positive integer");
			return;
		}

		// try block for arg parsing
		try {
			//convert 1st commandline argument from string to integer
			number = Integer.parseInt(args[0]);
			// check if integer is positive
			if (number < 0)
				throw new IllegalArgumentException();

		// non-integer argument
		} catch (NumberFormatException e) {
			System.out.println("Invalid integer - " +
				e.getLocalizedMessage());
			return;
		// negative integer argument
		} catch (IllegalArgumentException e) {
			System.out.println("Please enter a positive integer");
			return;
		// wat
		} catch (Exception e) {
			System.out.println("Error parsing integer argument - " +
				e.getLocalizedMessage());
			return;
		}

		// try block for methods
		try {
			// method 1
			System.out.printf("%s\n%s\n\n",
				"Row of *:",
				rowOfAsterisks(number, ""));
			// method 2
			System.out.printf("%s\n%s\n\n",
				"Decrementing list:",
				decrementingList(number, ""));
			// method 3
			System.out.printf("%s\n%s\n\n",
				"Incrementing list:",
				incrementingList(number, ""));
			// method 4
			System.out.printf("%s\n%d\n\n",
				"Series sum:",
				seriesSum(number, 0));
			// method 5
			System.out.printf("%s\n%d\n\n",
				"Binary powers sum:",
				binaryPowersSum(number, 0));

		// stack overflow!!!
		} catch (StackOverflowError e) {
			System.out.println("STACK OVERFLOWWWWWWWWWW");
		// wat
		} catch (Exception e) {
			System.out.println("Unknown error during program execution - " +
				e.getLocalizedMessage());
		}
	}

	/**
	 * the "rowOfAsterisks" method returns a row of asterisks
	 * @param number number of asterisks to return
	 * @param result parameter to hold state for tail call optimization
	 */
	private static String rowOfAsterisks(int number, String result) {
		// terminating condition
		return (number > 0) ?
			rowOfAsterisks(number - 1, result + "*") :
			result;
	}

	/**
	 * the "decrementingList" method returns a row of decrementing numbers
	 * @param number number to start at
	 * @param result parameter to hold state for tail call optimization
	 */
	private static String decrementingList(int number, String result) {
		// terminating condition
		return String.valueOf((number > 0) ?
			decrementingList(number - 1, result +
				// don't add a , to head of the list
				((result.matches("^$")) ? "" : ", ") +
					number) :
				result + ", " + 0);
	}

	/**
	 * the "incrementingList" method returns a row of incrementing numbers
	 * @param number number to end at
	 * @param result parameter to hold state for tail call optimization
	 */
	private static String incrementingList(int number, String result) {
		// terminating condition
		return String.valueOf((number > 0) ?
			incrementingList(number - 1, number +
				// don't add a , to tail of the list
				((result.matches("^$")) ? "" : ", ")
					+ result) :
				0 + ", " + result);
	}

	/**
	 * the "seriesSum" method returns a sum of incrementing numbers
	 * @param number number to end the series at
	 * @param result parameter to hold state for tail call optimization
	 */
	private static int seriesSum(int number, int result) {
		// terminating condition
		return (number > 0) ?
			seriesSum(number - 1, result + number) :
			result + number;
	}

	/**
	 * the "binaryPowersSum" method returns a sum of incrementing powers of two
	 * @param number power of two to end the series at
	 * @param result parameter to hold state for tail call optimization
	 */
	private static int binaryPowersSum(int number, int result) {
		// terminating condition
		return (number > 0) ?
			binaryPowersSum(number - 1, result + (1 << number)) :
			result + 1;
	}

}

