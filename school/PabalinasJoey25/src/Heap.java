import java.lang.Comparable;

/**
 * This is a maxheap
 * @author William McDaniel Albritton
 */
public class Heap<T> {
// data fields
   private final int MAX_ARRAY_SIZE = 100;
   private int indexOfLastElement = -1;
   private T array[] = (T[]) new Object[MAX_ARRAY_SIZE];

/** Constructor */
   public Heap() {
   // data fields already initialized
   }

/**
 * Automatically called by println() or print()
 *
 * @return a String of the Heap, showing the array values
 */
   public String toString() {
      String string = "";
      for (int i = 0; i <= indexOfLastElement; i++) {
         string = string + "array[" + i + "] = " + array[i] + "\n";
      }
      return string;
   }

/**
 * Tests if empty
 *
 * @return true/false if empty/not empty
 */
   public boolean empty() {
      if (indexOfLastElement == -1) {
         return true;
      } 
      else {
         return false;
      }
   }

/**
 * adds an item to the heap
 *
 * @param item is the object to be added
 * @exception HeapException if heap is full
 */
   public void add(T item) {
   // add the new item at the end of the array
      indexOfLastElement++;
      if(MAX_ARRAY_SIZE == (indexOfLastElement+1)){
         throw new HeapException("Cannot add(), because heap is full!");
      }
      array[indexOfLastElement] = item;
   // current item is child
      int indexOfChild = indexOfLastElement;
   // calculate index of parent
      int indexOfParent = (indexOfChild - 1) / 2;
   // "trickle up" the tree
      this.trickleUp(indexOfParent, indexOfChild);
   }

/**
 * trickle up the tree, so the node is in the correct position
 *
 * @param indexOfParent is the index of the parent node
 * @param indexOfChild is the index of the child node
 */
   private void trickleUp(int indexOfParent, int indexOfChild) {
      if ((indexOfParent >= 0)
      	&& (compare(array[indexOfParent], array[indexOfChild]) < 0)) {
      // if parent < child, swap them (maxheap)
         T temporary = array[indexOfParent];
         array[indexOfParent] = array[indexOfChild];
         array[indexOfChild] = temporary;
      // "trickle-up" heap
         indexOfChild = indexOfParent;
         indexOfParent = (indexOfChild - 1) / 2;
         this.trickleUp(indexOfParent, indexOfChild);
      }
   // if no more swapping, stop recursion
   }

/**
 * Since arrays as a whole cannot be cast to Comparable 
 * each element being compared is individually cast to Comparable 
 *
 * @param item1 is the 1st element to be compared 
 * @param item2 is the 2nd element to be compared
 */
   private int compare(T item1, T item2) {
    //cast elements to Comparable 
      Comparable itemOne = (Comparable) item1;
   //call compareTo() method
      int result = itemOne.compareTo(item2);
      return result;
   }

/**
 * gets an item from the top of the heap
 *
 * @exception HeapException if heap is empty
 */
   public T get() throws HeapException {
   // if empty, throw exception
      if (this.empty()) {
         throw new HeapException("Cannot get(), because heap is empty!");
      }
   // get a reference to the root
      T root = array[0];
      return root;
   }

/**
 * removes and returns an item from the heap 
 *
 * @exception HeapException if heap is empty
 */
   public T remove() throws HeapException {
   // if empty, throw exception
      if (this.empty()) {
         throw new HeapException("Cannot remove(), because heap is empty!");
      }
   // save a reference to the root
      T root = array[0];
   // last item in tree assigned to root
      array[0] = array[indexOfLastElement];
   // "delete" last item by decrementing indexOfLastElement
      indexOfLastElement--;
   // trickle down the tree, so the node is in the correct position
      this.trickleDown(0);
   // return the root
      return root;
   }

/**
 * trickle down the tree, so the node is in the correct position
 *
 * @param indexOfParent is the index of the parent node
 */
   private void trickleDown(int indexOfParent) {
   // calculate index of left and right children
      int indexOfLeftChild = 2 * indexOfParent + 1;
      int indexOfRightChild = 2 * indexOfParent + 2;
      int indexOfLargestOfThreeNodes = indexOfParent;
   // if only one child, possible switch
      if (indexOfLeftChild <= indexOfLastElement) {
         if (this.compare(array[indexOfLeftChild], array[indexOfParent]) > 0) {
         // if leftChild > parent, largest = leftChild
            indexOfLargestOfThreeNodes = indexOfLeftChild;
         }
      // if two children, find the largest of two children
         if (indexOfRightChild <= indexOfLastElement) {
         // determine largest child
            if (this.compare(array[indexOfLargestOfThreeNodes],
            	array[indexOfRightChild]) < 0) {
            // if largest < right, then largest = right
               indexOfLargestOfThreeNodes = indexOfRightChild;
            }
         }
      // if the largest child is larger than the parent, then swap
      // if the indexOfLargestOfThreeNodes is not the parent, then swap
         if (indexOfLargestOfThreeNodes != indexOfParent) {
         // if largest > parent, swap them (maxheap)
            T temporary = array[indexOfParent];
            array[indexOfParent] = array[indexOfLargestOfThreeNodes];
            array[indexOfLargestOfThreeNodes] = temporary;
         // keep trickling down
            this.trickleDown(indexOfLargestOfThreeNodes);
         }
      }
   // if parent is a leaf, end of trickle-down, so do nothing
   }

}// end class definition

