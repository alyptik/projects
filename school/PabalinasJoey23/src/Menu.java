import javax.swing.JOptionPane;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.io.File;

/**
 * A console menu for the IRS
 * 
 * @author William McDaniel Albritton
 */
public class Menu {
// data fields
   private BinarySearchTree<Person> tree = new BinarySearchTree<Person>();
   private String ioFile = new String("presidents.csv");

/** No-parameter constructor */
   public Menu() {
   // We don't need any code in constructor,
   // as we already initialized the data fields.
   }

/**
 * Starts the menu.
 * 
 * @param args is not used
 */
   public static void main(String[] args) {
   // Instantiate menu & display menu
      Menu menu = new Menu();
      menu.displayMenu();
   }

/** 
* Displays a menu, asks for choice, executes choice 
*/
   public void displayMenu() {
   // read records from ioFile and store in tree
      try {
         this.readFromIOFile();
      } 
      catch (Exception exception) {
         System.out.println("Error in reading from ioFile: " + exception);
      }
   // list of choices
      String[] choices = { "Add Person", "Edit Person", "Remove Person",
            "Display Person", "Display List", "Exit Program",
            "Node Information" };
   // display loop
      int choice = 0;
      while (choice != choices.length) {
         choice = JOptionPane.showOptionDialog(null, // put in center of
            // screen
            "Select a Command", // message to user
            "Main Menu", // title of window
            JOptionPane.YES_NO_CANCEL_OPTION, // type of option
            JOptionPane.QUESTION_MESSAGE, // type of message
            null, // icon
            choices, // array of strings
            choices[choices.length - 1]); // default choice (last one)
         switch (choice) {
            case 0:
               try {
                  this.add();
               } 
               catch (Exception exception) {
                  // "null" puts message in center of screen
                  JOptionPane.showMessageDialog(null,
                        "Unable to add, because " + exception);
               }
               break;
            case 1:
               try {
                  this.edit();
               } 
               catch (Exception exception) {
                  JOptionPane.showMessageDialog(null,
                        "Unable to edit, because " + exception);
               }
               break;
            case 2:
               try {
                  this.remove();
               } 
               catch (Exception exception) {
                  JOptionPane.showMessageDialog(null,
                        "Unable to remove, because " + exception);
               }
               break;
            case 3:
               try {
                  this.displayOne();
               } 
               catch (Exception exception) {
                  JOptionPane.showMessageDialog(null,
                        "Unable to display, because " + exception);
               }
               break;
            case 4:
               this.displayAll();
               break;
            case 5:
            // quit the program
               choice = choices.length;
               break;
            case 6:
            // Your programming assignment
               try {
                  this.nodeInformation();
               } 
               catch (Exception exception) {
                  JOptionPane.showMessageDialog(null,
                        "Unable to display node information, because "
                        + exception);
               }
               break;
         }
      }
   // write records stored in tree to ioFile
      try {
         this.writeToIOFile();
      } 
      catch (Exception exception) {
         System.out.println("Error in writing to ioFile: " + exception);
         System.out.println("You might need to close the file.");
      }
   }

/** 
* read from a ioFile 
* 
* @exception FileNotFoundException if cannot find the file (incorrect name, incorrect file path, etc.)
*/
   private void readFromIOFile() throws FileNotFoundException {
   // Connect to the file in the current directory
      File file = new File(ioFile);
      Scanner input = new Scanner(file); // may throw FileNotFoundException
   // read from file
      String line = new String("blank");
      String ssn = new String("blank");
      String tax = new String("blank");
      String name = new String("blank");
   // get rid of 1st line
      line = input.nextLine();
   // read contents of file and display on console
      while (input.hasNextLine()) {
         line = input.nextLine();
      // returns all characters up to a comma
         Scanner lineInput = new Scanner(line).useDelimiter(",");
         ssn = lineInput.next();
         tax = lineInput.next();
         name = lineInput.next();
         Person person = new Person(ssn, tax, name);
         tree.add(person);
      }
      input.close();
   }

/**
 * write Person records (objects) from tree and store in ioFile.
 * 
 * @exception FileNotFoundException if cannot find the specified file
 */
   private void writeToIOFile() throws FileNotFoundException {
   // make connection to ioFile
      PrintWriter fileWriter = new PrintWriter(ioFile);
   // write to file: title of each column (top row)
   // with NO spaces between commas (",")
      fileWriter.println("ssn,tax,name");
   // Write to file: all the data in the list.
   // We want PREORDER, so that when we read from the file again,
   // the tree will have the same structure as before.
   // If we use INORDER, then we will have an extremely unbalanced
   // tree (a linked list) when we read from the file again.
   // If we use POSTORDER, then we will have an unbalanced (but not
   // extremely unbalanced) tree when we read from the file again.
      String allData = tree.preOrder();
   //write the data to the file
      fileWriter.print(allData);
   // don't forget to close the file connection!
   // may not write to file if not closed!
      fileWriter.close();
   }// end of writeToIOFile()

/** Prompt user for ssn, tax, and name */
   private void add() {
   // get user input
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
      String tax = JOptionPane.showInputDialog("Enter person's tax");
      String name = JOptionPane.showInputDialog("Enter person's name");
   // instantiate person & add
      Person person = new Person(ssn, tax, name);
      tree.add(person);
   }

/** Prompt user for person's ssn, then change to new tax */
   private void edit() {
   // get user input
   // displays message, and returns a string of text in text box
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
   // get user input
      String tax = JOptionPane.showInputDialog("Enter person's new tax");
   // get reference to real person using searchKey person
   // "searchKey" variable only contains the search key SSN
      Person searchKey = new Person(ssn);
      Person person = tree.get(searchKey); // no casting!!!
   // change the tax
      person.setTax(tax);
   }

/** Prompt user for person's ssn and remove */
   private void remove() {
   // get user input
   // displays message, and returns a string of text from text box
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
   // get reference to real person using searchKey person
   // "searchKey" variable only contains the search key SSN
      Person searchKey = new Person(ssn);
      tree.remove(searchKey);
   }

/** Prompt user for person's ssn, then display data for 1 person */
   private void displayOne() {
   // get user input
   // displays message, and returns a string of text in text box
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
   // get reference to real person using searchKey person
   // "searchKey" variable only contains the search key SSN
      Person searchKey = new Person(ssn);
      Person person = tree.get(searchKey); // no casting!!!
      if (person != null) {
         double tax = person.getTax();
         String name = person.getName();
      // make the output nice and pretty
         String output = new String("");
         output = output + "Name: " + name + "\n";
         output = output + "SSN:  " + ssn + "\n";
         output = output + "Tax: ";
         if (tax < 0) {
            tax = -tax;
            output = output + "-$" + tax + "\n";
         } 
         else {
            output = output + " $" + tax + "\n";
         }
         JOptionPane.showMessageDialog(null, output);
      } 
      else {
      // record does not exist
         JOptionPane.showMessageDialog(null, "ERROR: Record #" + ssn
            + " does not exist!");
      }
   }

/** Display */
   private void displayAll() {
      System.out.println("ssn,tax,name");
      System.out.println("------------");
      System.out.println(tree.toString());
   }

/**
 * Your programming assignment code goes in class BinarySearchTree in the
 * method "void nodeInformation(T searchKey)"
 */
   private void nodeInformation() {
   // get user input
      String ssn = JOptionPane.showInputDialog("Enter person's ssn");
      Person searchKey = new Person(ssn);
      tree.nodeInformation(searchKey);
   }

}// end of class

