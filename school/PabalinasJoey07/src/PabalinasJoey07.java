/**
 * this program takes an integer
 * and a string argument, then
 * performs five TCO (Tail Call
 * Optimized) recursive methods,
 * passing those arguments to each
 * method as needed
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment #07
 * 09/01/2017
 */

public class PabalinasJoey07 {
	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args) {
		// declare variables to hold arguments
		int number, strLength;
		String str;

		// check if exactly two arguments are given
		if (args.length < 2) {
			System.out.println("Please enter a positive integer and a string");
			return;
		}

		// try block for arg parsing
		try {
			//convert 1st commandline argument from string to integer
			number = Integer.parseInt(args[0]);
			// check if integer is positive
			if (number < 0)
				throw new IllegalArgumentException();
			str = args[1];

		// empty string
		} catch (NullPointerException e) {
			System.out.println("Null string passed as argument - " +
				e.getLocalizedMessage());
			return;
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
			System.out.println("Error during argument parsing - " +
				e.getLocalizedMessage());
			return;
		}

		// calculate string length
		strLength = str.length() - 1;

		// try block for methods
		try {
			// method 1
			System.out.printf("%s\n%s\n\n",
				"String duplication:",
				strDup(number, str, ""));
			// method 2
			System.out.printf("%s\n%s\n\n",
				"Character duplication:",
				charDup(number, str, ""));
			// method 3
			System.out.printf("%s\n%s\n\n",
				"Character doubling:",
				charDouble(str, "", strLength));
			// method 4
			System.out.printf("%s\n%s\n\n",
				"String reverse with character tripling:",
				charTripleReverse(str, "", strLength));
			// method 5
			System.out.printf("%s\n%s\n\n",
				"Integer decrement and character shifting:",
				strShift(number, str, ""));

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
	 * the "strDup" method duplicates a String
	 * @param number number of String copies
	 * @param input input String
	 * @param result parameter to hold state for tail call optimization
	 */
	private static String strDup(int number, String input, String result) {
		// terminating condition
		return (number > 0) ?
			strDup(number - 1, input, result + input) :
			result + input;
	}

	/**
	 * the "charDup" method duplicates the first character of a String
	 * @param number number of character copies
	 * @param input input String
	 * @param result parameter to hold state for tail call optimization
	 */
	private static String charDup(int number, String input, String result) {
		// terminating condition
		return (number > 0) ?
			charDup(number - 1, input, result + input.charAt(0)):
			result + input.charAt(0);
	}

	/**
	 * the "charDouble" method duplicates each character of a String
	 * @param input input String
	 * @param result parameter to hold state for tail call optimization
	 * @param count parameter to hold iteration state for tail call optimization
	 *
	 */
	private static String charDouble(String input, String result, int count) {
		// index of the current character
		int curIndex = input.length() - count - 1;
		// two characters to append
		String chars = String.copyValueOf(new char[]{input.charAt(curIndex)}) +
			String.copyValueOf(new char[]{input.charAt(curIndex)});
		// terminating condition
		return (count > 0) ?
			charDouble(input, result + chars, count - 1) :
			result + chars;
	}

	/**
	 * the "charTripleReverse" method reverses and prints each character of a String three times
	 * @param input input String
	 * @param result parameter to hold state for tail call optimization
	 * @param count parameter to hold iteration state for tail call optimization
	 *
	 */
	private static String charTripleReverse(String input, String result, int count) {
		// three characters to append
		String chars = String.copyValueOf(new char[]{input.charAt(count)}) +
			String.copyValueOf(new char[]{input.charAt(count)}) +
			String.copyValueOf(new char[]{input.charAt(count)});
		// terminating condition
		return (count > 0) ?
			charTripleReverse(input,
				result + chars,
				count - 1) :
			result + chars;
	}

	/**
	 * the "strShift" method deletes the character at the head of a String and counts down
	 * stopping when either number reaches 1 or the String is empty
	 * @param number to start from
	 * @param input input String
	 * @param result parameter to hold state for tail call optimization
	 */
	private static String strShift(int number, String input, String result) {
		// terminating condition
		return (number > 1 && input.length() > 1) ?
			strShift(number - 1, input.substring(1),
				// don't add comma to the head of the list
				result + (result.matches("^$") ? "" : ", ") +
					number + " " + input) :
			result + ", " + number + " " + input;
	}
}

