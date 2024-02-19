/**
 * A exception class used with the class comparable Person with ssn, tax, & name data fields
 * 
 * @author William McDaniel Albritton
 * 
 */
public class PersonException extends RuntimeException {
	/**
	 * Constructor
	 * 
	 * @param message Describes the cause of the error
	 */
	public PersonException(String message) {
		super(message);
	}
}// end class definition

