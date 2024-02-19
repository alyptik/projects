//An interface used to compare two objects
//Must implement method compareTo()
import java.lang.Comparable;

/**
 * A comparable person with ssn, tax, and name data fields
 * 
 * @author William McDaniel Albritton
 * */
public class Person implements Comparable {
	// data fields
   private int ssn = 0;
   private double tax = 0.0;
   private String name = new String("name");

	/**
	 * Constructor
	 * 
	 * @param ssnParameter is the person's ssn
	 * @param taxParameter is the person's tax
	 * @param nameParameter is the person's name
    * @exception PersonException if the SSN is not 4 digits
	 */
   public Person(int ssnParameter, double taxParameter, String nameParameter)throws PersonException {
   	// ssn error checking
   	// for simplicity, we keep the ssn number to 4 digits
      if (ssnParameter < 1000 || ssnParameter > 9999) {
         throw new PersonException(
            	"Please keep the SSN as a 4-digit number.");
      }
      ssn = ssnParameter;
      tax = taxParameter;
      name = nameParameter;
   }

	/**
	 * Overloaded constructor for String data input
	 * 
	 * @param ssnParameter is the person's ssn
	 * @param taxParameter is the person's tax
	 * @param nameParameter is the person's name
    * @exception PersonException if the SSN is not 4 digits    
	 */
   public Person(String ssnParameter, String taxParameter, String nameParameter) throws PersonException {
   	// calls the 1st constructor
   	// converts strings to appropriate data type
      this(Integer.parseInt(ssnParameter), 
         	Double.parseDouble(taxParameter),
         	nameParameter);
   }

	/**
	 * Overloaded constructor for "searchKey" Person (only contains the SSN, which is the search key)
	 * 
	 * @param ssnParameter is the person's ssn
    * @exception PersonException if the SSN is not 4 digits  
	 */
   public Person(int ssnParameter) throws PersonException {
   	// calls 1st constructor
      this(ssnParameter, 0.0, "SEARCH KEY");
   }

	/**
	 * Overloaded constructor for "searchKey" Person (only contains the SSN, which is the search key)
	 * 
	 * @param ssnParameter is the person's ssn
	 */
   public Person(String ssnParameter) throws PersonException {
   	// convert from string & call 1st constructor
   	// put in placeholder values
      this(Integer.parseInt(ssnParameter), 0.0, "SEARCH KEY");
   }

	/**
	 * Automatically called by println() or print() 
    * Used to make a CSV (comma separated values) excel database
	 * 
	 * @return a String of the Person
	 */
   public String toString() {
      String csvFormat = ssn + "," + tax + "," + name;
      return csvFormat;
   }

	/**
	 * Method to compare objects
	 * 
	 * @param object2 is a second Person
	 * @return 0 if equal, negative if(person1<person2), positive if(person1>person2)
	 */
   public int compareTo(Object object2) {
      Person person2 = (Person) object2;
      int difference = ssn - person2.getSSN();
      return difference;
   }

	/**
	 * Accessor method
	 * 
	 * @return the Person's SSN
	 */
   public int getSSN() {
      return ssn;
   }

	/**
	 * Accessor method
	 * 
	 * @return the Person's tax
	 */
   public double getTax() {
      return tax;
   }	

	/**
	 * Accessor method
	 * 
	 * @return the Person's name
	 */
   public String getName() {
      return name;
   }
	
	/**
	 * Mutator method
	 * 
	 * @param taxParameter is the person's tax
	 */
   public void setTax(double taxParameter) {
      tax = taxParameter;
   }

	/**
	 * Mutator method
	 * 
	 * @param taxParameter is the person's tax
	 */
   public void setTax(String taxParameter) {
   	// convert from string and call 1st setTax() method
      this.setTax(Double.parseDouble(taxParameter));
   }

}// end class definition

