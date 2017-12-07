import java.lang.Comparable;

/**
 * A PriorityQueue class roughly based on Java API's PriorityQueue class
 * @author William McDaniel Albritton
 */
public class PriorityQueue<T extends Comparable<T>> implements QueueInterface<T>{
	// data fields
   protected Heap<T> heap = new Heap<T>(); 

	/** constructor */
   public PriorityQueue() {
      // data fields already initialized
   }

	/**
	 * Tests if the Queue is empty
    *
	 * @return true/false if empty/not empty
	 */
   public boolean empty() {
      return heap.empty();
   }

	/**
	 * offers an element to the PriorityQueue
    *
	 * @param element is offered to the PriorityQueue
	 * @return true if it was possible to offer the element to PriorityQueue, else false
	 */
   public boolean offer(T element) {
      try {
         heap.add(element);
      } 
      catch (HeapException exception) {
         return false;
      }
      return true;
   }

	/**
	 * Retrieves and removes the from the top of PriorityQueue, or null if PriorityQueue is empty
    *
	 * @return the top of PriorityQueue, or null if PriorityQueue is empty
	 */
   public T poll() {
      try {
         return heap.remove();
      } 
      catch (HeapException exception) {
         return null;
      }
   }

	/**
	 * Retrieves, but does not remove, from the top of PriorityQueue, or null if PriorityQueue is empty
    *
	 * @return the top of PriorityQueue, or null if PriorityQueue is empty
	 */
   public T peek() {
      try {
         return heap.get();
      } 
      catch (HeapException exception) {
         return null;
      }
   }
}// end class definition

