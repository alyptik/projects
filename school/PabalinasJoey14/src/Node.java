/**
 * A generic Node class that Stores a reference to Data and the next Node
 * 
 * @author William McDaniel Albritton
 */
public class Node<T> {

	// data fields (reference variables)
	// data stores an object of any class
   private T data;
	// next points to the next node
   private Node<T> next;

	/**
	 * Constructor - Used To Create EAch Object and Initialize DAta Fields.
	 * 
	 * @param data2 initializes the data variable.
	 * @param next2 initializes the next variable..
	 */
   public Node(T data2, Node<T> next2) {
      data = data2;
      next = next2;
   }

	/**
	 * Used to Display The Data Stored In EAch Node.
	 * 
	 * @return a String for the data
	 */
   public String toString() {
      return data.toString();
   }

	/**
	 * This Is An "Accessor" Method - Used To Get A Data Field.
	 * 
	 * @return the data
	 */
   public T getData() {
      return data;
   }

	/**
	 * This Is An "Accessor" Method - Used To Get A Data Field.
	 * 
	 * @return the address to the next node
	 */
   public Node<T> getNext() {
      return next;
   }

	/**
	 * This Is A "Mutator" Method - Used To Set A Data Field.
	 * 
	 * @param data2 is the data stored in the Node object.
	 */
   public void setData(T data2) {
      data = data2;
   }

	/**
	 * This Is A "Mutator" Method - Used To Set A Data Field.
	 * 
	 * @param next2 is a pointer to the next node.
	 */
   public void setNext(Node<T> next2) {
      next = next2;
   }


} // end of class

