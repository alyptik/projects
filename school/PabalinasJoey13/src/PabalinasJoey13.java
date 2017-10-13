/**
 * This program reads lines from
 * a text file into an array
 * of String objects, uses the
 * eval() method to parse and
 * evaluate each line (using the
 * Shunting-yard algorithm),
 * finally printing the infix/postfix
 * expressions and the result of
 * evaluation.
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment 13
 * 10/12/17
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

		// sanity check
		if (args.length < 1) {
			System.out.println("Please enter a filename");
			exit(1);
		}

		// error checking for commandline input
		try {
			// read fields from the file
			if ((exprList = readFile(args[0])) == null)
				throw new NullPointerException();

			// parse and evaluate each line as one expression
			for (String expr : exprList) {
				// evaluate lines
				ArrayList<String> result = eval(expr);
				result.add(evalInfix(expr) + "\n");
				// print results
				System.out.println("Infix expression = "
					+ expr);
				System.out.println("Postfix expression = "
					+ result.get(0));
				System.out.println("Evaluation result (postfix) = "
					+ result.get(1));
				System.out.println("Evaluation result (infix) = "
					+ result.get(2));
			}

		// catch exceptions
		} catch (Exception e) {
			System.out.println(e.getLocalizedMessage());
		}
	}

	/**
	 * This method converts an infix
	 * expression to RPN and returns
	 * the postfix expression and
	 * the result of evaluating it
	 *
	 * @param inputStr the expression
	 * @return the result
	 */
	private static ArrayList<String> eval(final String inputStr) throws EmptyStackException
	{
		return new Object() {
			int pos = -1, ch;
			String str = "", exprRPN = "";
			ArrayStack<Character> outputStack = new ArrayStack<>();
			ArrayStack<Character> operatorStack = new ArrayStack<>();
			ArrayStack<Character> finalStack = new ArrayStack<>();

			/**
			 * This method increments the string index
			 *
			 */
			void nextChar()
			{
				ch = (++pos < str.length()) ? str.charAt(pos) : -1;
			}

			/**
			 * This method parses an infix expression
			 *
			 * @return the result
			 */
			ArrayList<String> parse()
			{
				str = inputStr;
				nextChar();
				while (ch != -1) {
					// number
					if (ch >= '0' && ch <= '9') {
						outputStack.push((char)ch);
						nextChar();
						continue;

					// no operators on the stack
					} else if (operatorStack.empty()) {
						operatorStack.push((char)ch);
						nextChar();
						continue;
					}

					// otherwise there is a operator to be parsed
					int cur = operatorStack.peek();
					switch (ch) {
					// open grouping
					case '(':
						operatorStack.push((char)ch);
						break;

					// addition ops
					case '+': /* fallthrough */
					case '-':
						while (!operatorStack.empty()
								&& (cur == '+'
								|| cur == '-'
								|| cur == 'x'
								|| cur == 'X'
								|| cur == '*'
								|| cur == '/'
								|| cur == '%')) {
							outputStack.push(operatorStack.pop());
							cur = operatorStack.peek();
						}
						operatorStack.push((char)ch);
						break;

					// multiplication ops
					case 'x': /* fallthrough */
					case 'X': /* fallthrough */
					case '*': /* fallthrough */
					case '/': /* fallthrough */
					case '%':
						while (!operatorStack.empty()
								&& (cur == 'x'
								|| cur == 'X'
								|| cur == '*'
								|| cur == '/'
								|| cur == '%')) {
							outputStack.push(operatorStack.pop());
							cur = operatorStack.peek();
						}
						operatorStack.push((char)ch);
						break;

					// close grouping
					case ')':
						while (!operatorStack.empty()
								&& cur != '(') {
							outputStack.push(operatorStack.pop());
							cur = operatorStack.peek();
						}
						operatorStack.pop();
						break;

					// error
					default:
						throw new RuntimeException("Unexpected: " + (char)ch);
					}
					nextChar();
				}

				// pop operator stack onto output stack
				while (!operatorStack.empty())
					outputStack.push(operatorStack.pop());
				// reverse order of final stack
				while (!outputStack.empty())
					finalStack.push(outputStack.pop());
				// create an expression string from the final stack
				while (!finalStack.empty())
					exprRPN += finalStack.pop() + " ";

				// return the generated postfix expression and the evaluated result
				return new ArrayList<>() {{
					add(exprRPN);
					add(calculateRPN());
				}};
			}

			/**
			 * This method evaluates an
			 * RPN expression
			 *
			 * @return the result
			 */
			String calculateRPN() {
				double a, b;
				ArrayStack<Double> evalStack = new ArrayStack<>();
				pos = -1;
				str = exprRPN;
				nextChar();
				while (ch != -1) {
					// number
					if (ch >= '0' && ch <= '9') {
						evalStack.push(Double.parseDouble(str.substring(pos, pos + 1)));
						nextChar();
						continue;

					// skip spaces
					} else if (ch == ' ') {
						nextChar();
						continue;
					}

					// otherwise there is a operator to be parsed
					switch (ch) {
						// a + b
						case '+':
							b = evalStack.pop();
							a = evalStack.pop();
							evalStack.push(a + b);
							break;

						// a - b
						case '-':
							b = evalStack.pop();
							a = evalStack.pop();
							evalStack.push(a - b);
							break;

						// a * b
						case 'x': /* fallthrough */
						case 'X': /* fallthrough */
						case '*':
							b = evalStack.pop();
							a = evalStack.pop();
							evalStack.push(a * b);
							break;

						// a / b
						case '/':
							b = evalStack.pop();
							a = evalStack.pop();
							evalStack.push(a / b);
							break;

						// a % b
						case '%':
							b = evalStack.pop();
							a = evalStack.pop();
							evalStack.push(a % b);
							break;

						// error
						default:
							throw new RuntimeException("Unexpected: " + (char)ch);
					}
					nextChar();
				}
				return Double.toString(evalStack.pop());
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
					if (eat('x')
						|| eat('X')
						|| eat('*')) {
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
				double x;
				int startPos = pos;

				// unary plus/minus
				if (eat('+'))
					return parseFactor();
				if (eat('-'))
					return -parseFactor();

				// parentheses
				if (eat('(')) {
					x = parseExpression();
					eat(')');

				// numbers
				} else if ((ch >= '0' && ch <= '9') || ch == '.') {
					while ((ch >= '0' && ch <= '9') || ch == '.') {
						nextChar();
					}
					x = Double.parseDouble(str.substring(startPos, pos));

				// functions
				} else if (ch >= 'a' && ch <= 'z') {
					while (ch >= 'a' && ch <= 'z') nextChar();
					String func = str.substring(startPos, pos);
					x = parseFactor();
					switch (func) {
					case "sqrt":
						x = Math.sqrt(x);
						break;

					case "sin":
						x = Math.sin(Math.toRadians(x));
						break;

					case "cos":
						x = Math.cos(Math.toRadians(x));
						break;

					case "tan":
						x = Math.tan(Math.toRadians(x));
						break;

					default:
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
