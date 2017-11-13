/**
 * A Queue class implemented with linked nodes 
 * @author William McDaniel Albritton 
 */
public class LinkedQueue<T> implements QueueInterface<T> {
    
   // data fields
   protected Node<T> endNode = null;
   
   /** Constructor */
   public LinkedQueue() {
      // data fields already initialized
   }
   
   /**
    * Tests if the queue is empty
    * 
    * @return true/false if empty/not empty
    */
   public boolean empty() {
      if(endNode == null){
         return true;
      }
      else{
         return false;
      }
   }
   
   /**
    * Adds an element to the end of the Queue
    * 
    * @param element is added to the end of the Queue
    * @return true after adding the element to Queue
    */
   public boolean offer(T element){
       // instantiate a new end node
      Node<T> newEndNode = new Node<T>(element, null);
      // insert into empty Queue
      if(this.empty()){
         // point newEnd to itself
         newEndNode.setNext(newEndNode);
      }
         // insert into non-empty Queue
      else{
         // point newEndNode's next to the front of the queue
         newEndNode.setNext(endNode.getNext());
         // point endNode's next to newEndNode (end of queue)
         endNode.setNext(newEndNode);
      }
      // newEndNode is the end of the queue
      endNode = newEndNode;
      return true;
   }//end of offer()
   
   /**
    * Retrieves, but does not remove, from the front of Queue, or null if Queue is empty
    * 
    * @return the front of Queue, or null if Queue is empty
    */
   public T peek() {
      if (!this.empty()) {
         Node<T> frontNode = endNode.getNext();
         return frontNode.getData();
      }
      // if empty, then return null
      return null;
   }
   
   /**
    * Retrieves and removes the from the front of Queue, or null if Queue is empty
    * 
    * @return the front of Queue, or null if Queue is empty
    */
   public T poll() {
      // if Queue is not empty, then remove from front
      if (!this.empty()) {
         Node<T> frontNode = endNode.getNext();
         // check to see if only 1 node left
         if (frontNode == endNode) {
            endNode = null;
         }
            // if not, then set endNode's next to node after frontNode
         else {
            endNode.setNext(frontNode.getNext());
         }
         return frontNode.getData();
      }
      // if empty, then return null
      return null;
   }
   
}// end class definition

