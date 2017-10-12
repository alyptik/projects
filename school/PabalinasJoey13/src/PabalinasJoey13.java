/**
 * This program reads fields from
 * a .txt file into an array
 * of String objects, uses the
 * Sorting.quickSort() method to
 * sort the array, and finally prints
 * out the sorted list of Strings.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment 13
 * 10/11/17
 *
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import static java.lang.System.*;

public class PabalinasJoey13 {
	/**
	 * The "main" method starts the program
	 * @param args the first argument is passed to the methods
	 */
	public static void main(String[] args)
	{
		// declare variables to hold arguments
		String[] exprList;

		if (args.length < 1) {
			System.out.println("Please enter a filename");
			exit(1);
		}

		// error checking for commandline input
		try {
			// read fields from the file
			if ((exprList = readFile(args[0])) == null)
				throw new NullPointerException();

			// print fields
			//printSortedStrings(args[0], wordList);

			for (int i = 0; i < exprList.length; i++) {
				// evaluate lines
				double result = evalInfix(exprList[i]);
				System.out.println("Infix expression = " + exprList[i]);
				System.out.println("Result = " + result + "\n");
			}

		// catch exceptions
		} catch (Exception e) {
			System.out.println(e.getLocalizedMessage());
		}
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
	 * This method evaluates a postfix expression
	 * and returns the result
	 *
	 * @param str the expression
	 * @return the result
	 */
	private static double evalPostfix(final String str) throws EmptyStackException
	{
		return new Object() {
			int pos = -1, ch;
			ArrayStack<Character> outputStack = new ArrayStack<>();
			ArrayStack<Character> operatorStack = new ArrayStack<>();

			void nextChar()
			{
				ch = (++pos < str.length()) ? str.charAt(pos) : -1;
			}

			double parse()
			{
				String exprRPN = null;

				nextChar();
				while (ch != -1) {
					if (ch >= '0' && ch <= '9') {
						// outputStack.push(str.charAt(pos));
						outputStack.push((char)ch);
					} else if (operatorStack.empty()) {
						// operatorStack.push(str.charAt(pos));
						operatorStack.push((char)ch);
					} else {
						int cur = operatorStack.peek();

						switch (ch) {
						case '(':
							operatorStack.push((char)cur);
							break;
						case '+': /* fallthrough */
						case '-':
							while (!operatorStack.empty() &&
									(cur == '+' ||
									cur == '-' ||
									cur == '*' ||
									cur == '/' ||
									cur == '%')) {
								outputStack.push((char)cur);
								operatorStack.pop();
							}
							operatorStack.push((char)ch);
							break;

						case '*': /* fallthrough */
						case '/': /* fallthrough */
						case '%':
							while (!operatorStack.empty() &&
									(cur == '*' ||
									cur == '/' ||
									cur == '%')) {
								outputStack.push((char)cur);
								operatorStack.pop();
							}
							operatorStack.push((char)ch);
							break;

						case ')':
							while (!operatorStack.empty() &&
									cur != '(') {
								outputStack.push((char)cur);
								operatorStack.pop();
							}
							operatorStack.pop();
							break;

						}

					}

					nextChar();
				}

				return calcReversePolishNotation(exprRPN);
			}

			double calcReversePolishNotation(String expr) {
				double result = Double.parseDouble(expr);
				result++;

				return result;
			}

			boolean eat(int charToEat) {
				while (ch == ' ')
					nextChar();
				if (ch == charToEat) {
					nextChar();
					return true;
				}
				return false;
			}

			// Grammar:
			// expression = term | expression `+` term | expression `-` term
			// term = factor | term `*` factor | term `/` factor
			// factor = `+` factor | `-` factor | `(` expression `)`
			//        | number | functionName factor | factor `^` factor

			double parseExpression()
			{
				double x = parseTerm();
				for (;;) {
					// addition
					if (eat('+')) {
						x += parseTerm();
					// subtraction
					} else if (eat('-')) {
						x -= parseTerm();
					} else {
						break;
					}
				}
				return x;
			}

			double parseTerm()
			{
				double x = parseFactor();
				for (;;) {
					// multiplication
					if (eat('*')) {
						x *= parseFactor();
						// division
					} else if (eat('/')) {
						x /= parseFactor();
						// modulus
					} else if (eat('%')) {
						x %= parseFactor();
					} else {
						break;
					}
				}
				return x;
			}

			double parseFactor()
			{
				// unary plus
				if (eat('+'))
					return parseFactor();
				if (eat('-'))
					return -parseFactor();

				double x;
				int startPos = this.pos;
				// parentheses
				if (eat('(')) {
					x = parseExpression();
					eat(')');
					// numbers
				} else if ((ch >= '0' && ch <= '9') || ch == '.') {
					while ((ch >= '0' && ch <= '9') || ch == '.') {
						nextChar();
					}
					x = Double.parseDouble(str.substring(startPos, this.pos));
					// functions
				} else if (ch >= 'a' && ch <= 'z') {
					while (ch >= 'a' && ch <= 'z') nextChar();
					String func = str.substring(startPos, this.pos);
					x = parseFactor();
					if (func.equals("sqrt")) {
						x = Math.sqrt(x);
					} else if (func.equals("sin")) {
						x = Math.sin(Math.toRadians(x));
					} else if (func.equals("cos")) {
						x = Math.cos(Math.toRadians(x));
					} else if (func.equals("tan")) {
						x = Math.tan(Math.toRadians(x));
					} else {
						throw new RuntimeException("Unknown function: " + func);
					}
				} else {
					throw new RuntimeException("Unexpected: " + (char)ch);
				}

				// exponentiation
				if (eat('^')) {
					x = Math.pow(x, parseFactor());
				}

				return x;
			}

		}.parse();
	}

	/**
	 * This method evaluates an infix expression
	 * and returns the result
	 *
	 * @param str the expression
	 * @return the result
	 */
	private static double evalInfix(final String str) throws EmptyStackException
	{
		return new Object() {
			int pos = -1, ch;

			void nextChar()
			{
				ch = (++pos < str.length()) ? str.charAt(pos) : -1;
			}

			boolean eat(int charToEat) {
				while (ch == ' ') nextChar();
				if (ch == charToEat) {
					nextChar();
					return true;
				}
				return false;
			}

			double parse()
			{
				nextChar();
				double x = parseExpression();
				if (pos < str.length()) throw new RuntimeException("Unexpected: " + (char)ch);
				return x;
			}

			// Grammar:
			// expression = term | expression `+` term | expression `-` term
			// term = factor | term `*` factor | term `/` factor
			// factor = `+` factor | `-` factor | `(` expression `)`
			//        | number | functionName factor | factor `^` factor

			double parseExpression()
			{
				double x = parseTerm();
				for (;;) {
					// addition
					if (eat('+')) {
						x += parseTerm();
						// subtraction
					} else if (eat('-')) {
						x -= parseTerm();
					} else {
						break;
					}
				}
				return x;
			}

			double parseTerm()
			{
				double x = parseFactor();
				for (;;) {
					// multiplication
					if (eat('*')) {
						x *= parseFactor();
						// division
					} else if (eat('/')) {
						x /= parseFactor();
						// modulus
					} else if (eat('%')) {
						x %= parseFactor();
					} else {
						break;
					}
				}
				return x;
			}

			double parseFactor()
			{
				// unary plus
				if (eat('+'))
					return parseFactor();
				if (eat('-'))
					return -parseFactor();

				double x;
				int startPos = this.pos;
				// parentheses
				if (eat('(')) {
					x = parseExpression();
					eat(')');
					// numbers
				} else if ((ch >= '0' && ch <= '9') || ch == '.') {
					while ((ch >= '0' && ch <= '9') || ch == '.') {
						nextChar();
					}
					x = Double.parseDouble(str.substring(startPos, this.pos));
					// functions
				} else if (ch >= 'a' && ch <= 'z') {
					while (ch >= 'a' && ch <= 'z') nextChar();
					String func = str.substring(startPos, this.pos);
					x = parseFactor();
					if (func.equals("sqrt")) {
						x = Math.sqrt(x);
					} else if (func.equals("sin")) {
						x = Math.sin(Math.toRadians(x));
					} else if (func.equals("cos")) {
						x = Math.cos(Math.toRadians(x));
					} else if (func.equals("tan")) {
						x = Math.tan(Math.toRadians(x));
					} else {
						throw new RuntimeException("Unknown function: " + func);
					}
				} else {
					throw new RuntimeException("Unexpected: " + (char)ch);
				}

				// exponentiation
				if (eat('^')) {
					x = Math.pow(x, parseFactor());
				}

				return x;
			}
		}.parse();
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
		ArrayList<String> lines = new ArrayList<>();

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
				lines.add(scanFile.nextLine());
			}

			String[] ret = new String[lines.size()];
			for (int i = 0; i < lines.size(); i++)
				ret[i] = lines.get(i);
			return ret;
		}

		return null;
	}
}
