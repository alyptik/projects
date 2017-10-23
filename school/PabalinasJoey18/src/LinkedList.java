/**
 * A generic list of linked nodes
 * 
 * @author William McDaniel Albritton
 */
public class LinkedList<T> implements ListInterface<T> {

	// reference to first node in the linked list (linked nodes)
   protected Node<T> head = null;
	// Total number of items, which is used
	// for error checking and node removal.
   protected Integer size = new Integer(0);

	/**
	 * A constructor with no parameters
	 * 
	 */
   public LinkedList() {
   	// no code, because data fields already initialized
   }

	/**
	 * Adds an item (of any class) to the end of the list
	 * 
	 * @param item is the object that is added to the list
	 */
   public void add(T item) {
   	// case 1: if empty list
      if (head == null) {
      	// list is empty, so add to beginning of list
      	// make new node and assign to head of list
         head = new Node<T>(item, null);
      }
      // if not empty list
      else {
      	// case2: add to end of list
      	// current starts at 2nd node in list
         Node<T> previous = head;
         Node<T> current = head.getNext();
      	// while not at end of list
         while (current != null) {
         	// advance to next node
            previous = current;
            current = current.getNext();
         }
      	// Add new node to end of list:
      	// Make new node that has "null" for next.
      	// A node with "null" is always the last node
         Node<T> node = new Node<T>(item, null);
      	// Point previous node (last node) to new node
         previous.setNext(node);
      }
   	// increase size of list
      size++;
   }

	/**
	 * Gets an item (address to an item) from any position in the list.
	 * 
	 * @param position is the position of an item in the list.
	 * @returns the address to the requested item
	 * @exception ListException if an item does not exist at that position, throws exception
	 */
   public T get(Integer position) throws ListException {
   	// check if empty list
      if (head == null) {
         throw new ListException("Cannot get an item from an empty list!");
      }
   	// if position is outside range, throw exception
      if (position < 1 || position > size) {
         throw new ListException(position + " is outside list range!");
      }
   	// Find node:
   	// counter to keep track of loops
      Integer counter = new Integer(1);
   	// point to current node
      Node<T> current = head;
      while (!counter.equals(position)) {
      	// BAD CODE: while(counter != position){
      	// goto next node for current pointer
         current = current.getNext();
      	// add 1 to counter
         counter++;
      }
   	// return the data (item) stored by the node
      return current.getData();
   }

	/**
	 * Removes an item at any position from the list.
	 * 
	 * @param position is the position of an item in the list.
	 * @exception ListException if an item does not exist at that position, throws exception
	 */
   public void remove(Integer position) throws ListException {
   	// check if empty list
      if (head == null) {
         throw new ListException("cannot remove from empty list");
      }
   	// if position is outside range, throw exception
      if (position < 1 || position > size) {
         throw new ListException(position + " is outside list range.");
      }
   	// if at beginning of list
      if (position.equals(1)) {
      	// remove 1st node
         head = head.getNext();
      }
      // if not at beginning of list
      else {
      	// Find node:
      	// point previous to 1st node
         Node<T> previous = head;
      	// point current to 2nd node
         Node<T> current = head.getNext();
      	// loop position-2 number of times
         for (int i = 2; i < position; i++) {
         	// goto next node for previous and current
            previous = current;
            current = current.getNext();
         }
      	// Point the previous node to node after current node.
      	// This "skips" over one node, thus removing it!
         previous.setNext(current.getNext());
      }
   	// decrease size of list
      size--;
   }

	/**
	 * Automatically called by println() or print()
	 * 
	 * @return a String of the List in CSV (comma separated values) format
	 */
   public String toString() {
   	// instantiate empty string
      String csvFormat = new String("");
   	// display position of each item to user
      Integer position = new Integer(1);
   	// loop through all the nodes in linked list
      for (Node<T> current = head; current != null; current = current.getNext()) {
      	// keep adding to end of string
         csvFormat = csvFormat + position + ", " + current.toString() + "\n";
      	// add one to position for each loop
         position++;
      }
      return csvFormat;
   }

	/**
	 * This Is An "Accessor" Method - Used To Get A Data Field.
	 * 
	 * @return the size of the list
	 */
   public Integer getSize() {
      return size;
   }

}// end of class

