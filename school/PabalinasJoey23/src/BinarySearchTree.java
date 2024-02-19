/**
 * Generic class for a binary search tree
 *
 * @author Pabalinas, Joey
 * ICS 211 Assignment #23
 * 12/1/17
 *
 */

//An interface used to compare two objects
//Must implement method compareTo()
import java.lang.Comparable;

public class BinarySearchTree<T extends Comparable> {
	// data fields
	private BinaryNode<T> root = null;

	/**
	 * find the node with the specified key starting from the root
	 *
	 * @param key the item with the key value only
	 */
	private BinaryNode<T> getNode(T key) throws TreeException
	{
		return getNode(root, key, 0);
	}

	/**
	 * find the node with the specified key
	 *
	 * @param node the node to start from
	 * @param key the item with the key value only
	 */
	private BinaryNode<T> getNode(BinaryNode<T> node, T key, int depth) throws TreeException
	{
		// if not found, throw exception
		if (node == null)
			throw new TreeException("Item not found!");

		// if the search key matches, return the node
		if (key.compareTo(node.getData()) == 0) {
			//display the data stored in the current node
			System.out.println("current node = " +  node.toString());
			// display the depth
			System.out.println("depth = " + depth);
			return node;
		// if the search key of the key is less than the node,
		// then search the left subtree
		} else if (key.compareTo(node.getData()) < 0) {
			return getNode(node.getLeftChild(), key, ++depth);
		// if the search key of the key is greater than the node,
		// then search the right subtree
		} else {
			return getNode(node.getRightChild(), key, ++depth);
		}
	}

	/**
	 * Your programming assignment code goes in class
	 * BinarySearchTree in the method body below
	 *
	 * @param searchKey the item with the key value only
	 */
	public void nodeInformation(T searchKey) throws TreeException
	{
		//below this line, write the outputs for assignments #22 and #23
		BinaryNode<T> node = getNode(searchKey);

		// if not found, throw exception
		if (node == null)
			throw new TreeException("Item not found!");

		// check for left and right children
		BinaryNode<T> leftChild = node.getLeftChild();
		BinaryNode<T> rightChild = node.getRightChild();

		// check if same object as the root node
		if (node == root) {
			System.out.println("node type = root");
		// check if leaf node
		} else if (leftChild == null && rightChild == null) {
			System.out.println("node type = leaf");
		// check if internal node
		} else {
			System.out.println("node type = internal");
		}

		// print out pre-order traversal of left descendants
		if (leftChild == null) {
			System.out.println("left descendants = (nil)");
		} else {
			System.out.print("left descendants = \n" + preOrder(leftChild)
				.replaceAll("\n", "\n\t\t")
				.replaceAll("^", "\t\t")
				.replaceAll("\t\t$", ""));
		}

		// print out pre-order traversal of right children
		if (rightChild == null) {
			System.out.println("right children = (nil)");
		} else {
			System.out.print("right children = \n" + preOrder(rightChild)
				.replaceAll("\n", "\n\t\t")
				.replaceAll("^", "\t\t")
				.replaceAll("\t\t$", ""));
		}
	}

	/**
	 * constructor
	 * */
	BinarySearchTree()
	{
		// data fields already initialized
	}

	/**
	 * adds an item to the tree
	 *
	 * @param item is the object to be added
	 */
	public void add(T item) {
		// calls a recursive, private method
		// cannot get direct access to the root outside the class
		 root = add(root, item);
	}

	/**
	 * adds an item to the tree
	 *
	 * @param node is the root of the tree/subtree
	 * @param item is the object to be added
	 * @return a node which is the root of a subtree with a new node containing the new item
	 */
	private BinaryNode<T> add(BinaryNode<T> node, T item) {
	// base case: empty tree or end of a leaf
		 if (node == null) {
			  return new BinaryNode<T>(item, null, null);
		 }
		 // base case: duplicate node, so throw exception
		 else if (item.compareTo(node.getData()) == 0) {
			  throw new TreeException("No duplicate items are allowed!");
		 }
		 // recursive case: if item is less than current node
		 // then move to left child node
		 else if (item.compareTo(node.getData()) < 0) {
		 // set the node's left child to the
		 // left subtree with item added
			  node.setLeftChild(this.add(node.getLeftChild(), item));
			  return node;
		 }
		 // recursive case: if item is greater than current node
		 // then traverse to right child node
		 else {
		 // set the node's right child to the
		 // right subtree with item added
			  node.setRightChild(this.add(node.getRightChild(), item));
			  return node;
		 }
	}

	/**
	 * called automatically by println/print method
	 *
	 * @return an inorder String of the tree
	 */
	public String toString() {
					   return this.inOrder(root);
					     }

	/**
	 * inOrder display of nodes, with newline between each node
	 *
	 * @param node is the root of the tree/subtree
	 * @return an inorder String of the tree
	 */
	private String inOrder(BinaryNode<T> node)
	{
		 String displayNodes = "";
		 if (node != null) {
			  displayNodes = displayNodes +
			     this.inOrder(node.getLeftChild());
			  displayNodes = displayNodes + node.toString() + "\n";
			  displayNodes = displayNodes +
			     this.inOrder(node.getRightChild());
		 }
		 return displayNodes;
	}

	/**
	 * preOrder traversal
	 *
	 * @return an preOrder String of the tree
	 */
	public String preOrder() {
		 return this.preOrder(root);
	}

	/**
	* preOrder display of nodes, with newline between each node
	*
	* @param node is the root of the tree/subtree
	* @return an preOrder String of the tree
	*/
	private String preOrder(BinaryNode<T> node) {
		String displayNodes = "";

		if (node != null) {
			displayNodes = displayNodes + node.toString() + "\n";
			displayNodes = displayNodes +
			this.preOrder(node.getLeftChild());
			displayNodes = displayNodes +
			this.preOrder(node.getRightChild());
		}

		return displayNodes;
	}

	/**
	 * postOrder traversal
	 *
	 * @return an postOrder String of the tree
	 */
	public String postOrder() {
					    return this.postOrder(root);
		}

	/**
	 * postOrder display of nodes, with newline between each node
	 *
	 * @param node is the root of the tree/subtree
	 * @return an postOrder String of the tree
	 */
	private String postOrder(BinaryNode<T> node) {
		 String displayNodes = "";
		 if (node != null) {
			  displayNodes = displayNodes + this.postOrder(node.getLeftChild());
			  displayNodes = displayNodes + this.postOrder(node.getRightChild());
			  displayNodes = displayNodes + node + "\n";
		 }
		 return displayNodes;
	}

	/**
	 * gets an item from the tree with the same search key
	 *
	 * @param searchKey1 is an object storing only the search key
	 */
	public T get(T searchKey1) {
		// cannot get direct access to the root outside the class
		 return this.get(root, searchKey1);
	}

	/**
	 * gets an item from the tree with the same search key
	 *
	 * @param node is the root of the tree/subtree
	 * @param searchKey2 is an object storing only the search key
	 * @return an item containing the same search key
	 */
	private T get(BinaryNode<T> node, T searchKey2) {
	// if not found, throw exception
		 if (node == null) {
			  throw new TreeException("Item not found!");
		 }
		 else {
		 // if the search key matches, return the item's address
			  if (searchKey2.compareTo(node.getData()) == 0) {
			     return node.getData();
			  }
			  // if the search key of the searchKey is less than the node,
			  // then search the left subtree
			  else if (searchKey2.compareTo(node.getData()) < 0) {
			     return this.get(node.getLeftChild(), searchKey2);
			  }
			  // if the search key of the searchKey is greater than the node,
			  // then search the right subtree
			  else {
			     return this.get(node.getRightChild(), searchKey2);
			  }
		 }
	}

/**
 * Calls a recursive method that removes an item from the tree with the same search key
 *
 * @param searchKey3 is an object storing only the search key
 */
public void remove(T searchKey3) {
			 root = this.remove(root, searchKey3);
		}

/**
 * Finds the item to be removed from the tree with the same search key
 *
 * @param node is the root of the tree/subtree
 * @param searchKey4 is an object storing only the search key
 * @return a node which is the root of a subtree without the node containing the search key
 */
	private BinaryNode<T> remove(BinaryNode<T> node, T searchKey4) {
	// if item not found, throw exception
		 if (node == null) {
			  throw new TreeException("Item not found!");
		 }
		 // if search key is less than node's search key,
		 // continue to left subtree
		 else if (searchKey4.compareTo(node.getData()) < 0) {
			  node.setLeftChild(this.remove(node.getLeftChild(), searchKey4));
			  return node;
		 }
		 // if search key is greater than node's search key,
		 // continue to right subtree
		 else if (searchKey4.compareTo(node.getData()) > 0) {
			  node.setRightChild(this.remove(node.getRightChild(), searchKey4));
			  return node;
		 }
		 // found node containing object with same search key,
		 // so delete it
		 else {
		 // call private method remove
			  node = this.remove(node);
			  return node;
		 }
	}

/**
 * Removes leaf nodes, and nodes with one child node from the tree with the
 * same search key and removes 2 child nodes too
 *
 * @param node is the root of the tree/subtree
 */
	private BinaryNode<T> remove(BinaryNode<T> node) {
	// if node is a leaf,return null
		 if (node.getLeftChild() == null && node.getRightChild() == null) {
			  return null;
		 }
		 // if node has a single right child node,
		 // then return a reference to the right child node
		 else if (node.getLeftChild() == null) {
			  return node.getRightChild();
		 }
		 // if node has a single left child node,
		 // then return a reference to the left child node
		 else if (node.getRightChild() == null) {
			  return node.getLeftChild();
		 }
		 // if the node has two child nodes
		 else {
		 // get next Smaller Item, which is Largest Item in Left Subtree
		 // The next Smaller Item is stored at the rightmost node in the left
		 // subtree.
			  T largestItemInLeftSubtree = this.getItemWithLargestSearchKey(node.getLeftChild());
		 // replace the node's item with this item
			  node.setData(largestItemInLeftSubtree);
		 // delete the rightmost node in the left subtree
			  node.setLeftChild(this.removeNodeWithLargestSearchKey(node.getLeftChild()));
			  return node;
		 }
	}

/**
 * Returns the address of the item with the largest search key in the tree
 *
 * @param node is the root of the tree/subtree
 */
	private T getItemWithLargestSearchKey(BinaryNode<T> node) {
	// if no right child, then this node contains the largest item
		 if (node.getRightChild() == null) {
			  return node.getData();
		 }
		 // if not, keep looking on the right
		 else {
			  return this.getItemWithLargestSearchKey(node.getRightChild());
		 }
	}

/**
 * Removes the node with the largest search key
 *
 * @param node is the root of the tree/subtree
 */
	private BinaryNode<T> removeNodeWithLargestSearchKey(BinaryNode<T> node) {
	// if no right child, then this node contains the largest item
	// so replace it with its left child
		 if (node.getRightChild() == null) {
			  return node.getLeftChild();
		 }
		 // if not, keep looking on the right
		 else {
			  node.setRightChild(this.removeNodeWithLargestSearchKey(node.getRightChild()));
			  return node;
		 }
	}

}// end of class

