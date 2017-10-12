import java.util.EmptyStackException;

/**
* A generic Stack class implemented with an array
*
* @author William McDaniel Albritton
*/
public class ArrayStack<T> implements StackInterface<T> {
   // data fields
   // size of array (size can increase if needed)
   private Integer size = 5;
   // top of the stack is the last element in the array
   private Integer top = -1;
   // When using a generic container class with arrays,
   // we must cast when we instantiate an array.
   private T array[] = (T[])new Object[size];

   /**
   * Constructor
   */
   public ArrayStack(){
       //We don't need any code in constructor,
       //as we already initialized the data fields.
   }

   /**
    * Tests if the stack is empty
    *
    * @return true/false if empty/not empty
    */
   public boolean empty(){
      return top == -1;
   }

   /**
   * Looks at the object at the top of the stack
   * without removing it from the stack.
   *
   * @return an address to the top item on the stack
   * @exception EmptyStackException if the stack is empty
   */
   public T peek() throws EmptyStackException {
      //check to see if empty
      if (this.empty()){
         throw new EmptyStackException();
      }
      //return pointer to top element in array
      //but do NOT take it off the stack!
      return array[top];
   }

   /**
   * Removes the object at the top of stack
   * and returns the address of this object
   *
   * @return an addressed to the top item on the stack
   * @exception EmptyStackException if the stack is empty
   */
   public T pop() throws EmptyStackException{
      //check to see if stack is empty
      if(this.empty()){
         throw new EmptyStackException();
      }
      //return pointer (address) to top element in array
      //and take it off the stack
      return array[top--];
      	//This is the same code as:
      	//int temp = top;
      	//top = top - 1;
      	//return array[temp];
   }

   /**
   * Pushes an item onto the top of this stack
   *
   * @param item the item that is pushed on the stack
   */
   public void push(T item){
       //check to see if the stack is full
      if(top + 1 == size){
         //make the array twice as big!
         Integer size2 = size * 2;
         // When using a generic container class with arrays,
         // we must cast when we instantiate an array.
         T array2[] = (T[]) new Object[size2];
         //copy elements into new array
         System.arraycopy(array, 0, array2, 0, size);
         //reassign the array & size
         size = size2;
         array = array2;
      }
      array[++top] = item;
      	//This is the same code as:
      	//top = top + 1;
      	//array[top] = item;
   }//end of method

}//end class

