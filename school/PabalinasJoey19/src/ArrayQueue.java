/**
 * A Queue class implemented with a circular array
 * 
 * @author William McDaniel Albritton
 */
public class ArrayQueue<T> implements QueueInterface<T> {
	// data fields
	// Index of element at front of the queue
   protected int frontIndex = 0;
	// Index of element at end of the queue
	// Value is -1, because we have not added any elements yet.
   protected int endIndex = -1;
	// Current number of elements in queue
   protected int currentSize = 0;
	// Maximum number of elements in queue (set by constructor)
   protected int maxSize = 0;
	// Array to store elements of T type
   protected T array[ ];

	/**
	 * Constructor
	 * 
	 * @param max is the maximum number of elements in the queue
	 */
   public ArrayQueue(int max) {
      maxSize = max;
   	// Have to do casting, because we cannot instantiate
   	// an array unless we know its type.
   	// Casting is putting a class name in parenthesis,
   	// which tells the compiler that a variable
   	// is of a specific type.
   	// protected T array[] = new T[arraySize]; //wrong syntax
   	//
      // May create following error message, but can't be avoided with arrays.
      // Note: ArrayQueue.java uses unchecked or unsafe operations.
      // Note: Recompile with -Xlint:unchecked for details.
      array = (T[ ]) new Object[maxSize];
   }

	/**
	 * Tests if the Queue is empty
	 * 
	 * @return true/false if empty/not empty
	 */
   public boolean empty() {
   	// see if size of array is 0
      boolean emptyArray = (currentSize == 0);
      return emptyArray;
   }

	/**
	 * Tests if the Queue is full
	 * 
	 * @return true/false if full/not full
	 */
   private boolean full() {
   	// See if size of array is at maximum
      boolean fullArray = (currentSize == maxSize);
      return fullArray;
   }

	/**
	 * Adds an element to the end of the Queue
	 * 
	 * @param element is added to the end of the Queue
	 * @return true if it was possible to add the element to Queue, else false
	 */
   public boolean offer(T element) {
   	// check to see if full
      if (!this.full()) {
      	// increment the endIndex
      	// use modulus to "wrap around" the array
         endIndex = (endIndex + 1) % maxSize;
      	// assign element to array
         array[endIndex] = element;
      	// increment current size of queue
         currentSize++;
      	// successfully added to array
         return true;
      }
   	// if full, cannot add to array
      return false;
   }

	/**
	 * Retrieves and removes the from the front of Queue, or null if Queue is empty
	 * 
	 * @return the front of Queue, or null if Queue is empty
	 */
   public T poll() {
   	// create a variable of class T
      T element = null;
   	// if array is not empty, then get element from front of queue
      if (!this.empty()) {
      	// get the front element's address
         element = array[frontIndex];
      	// increment frontIndex
      	// take the modulus to wrap around the array
         frontIndex = (frontIndex + 1) % maxSize;
      	// decrement current size of queue
         currentSize--;
      }
   	// return either null or the element
      return element;
   }

	/**
	 * Retrieves, but does not remove, from the frontIndex of Queue, or null if Queue is empty
	 * 
	 * @return the frontIndex of Queue, or null if Queue is empty
	 */
   public T peek() {
   	// create a variable
      T element = null;
   	// check to see if not empty
      if (!this.empty()) {
      	// get the address of front element
         element = array[frontIndex];
      }
   	// return either null or element
      return element;
   }

}// end of class definition 


