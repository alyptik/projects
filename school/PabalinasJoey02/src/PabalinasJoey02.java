/**
 * This program creates a class for the
 * Hawaii Star Compass Houses, instantiates
 * a 7-length array of those objects,
 * loops over the array, setting and printing
 * each object's attributes, then finally
 * mutates those attributes and prints out
 * the final values.
 *
 * @author Pabalinas, Joey
 * ICS 111 Assignment 2
 * 08/21/17
 */

import java.util.ArrayList;

class House {
	// used to bind mutate()'s method parameters to fields
	private static House[] input;

	// attributes
	String name, star;
	int compassDegree;

	// constructor
	House(String name, String star, int compassDegree)
	{
		this.name = name;
		this.star = star;
		this.compassDegree = compassDegree;
	}

	// apply ad-hoc list comprehension to an array of House objects
	static void mutate(final House[] input)
	{
		// bind parameters to fields
		House.input = input;
		new ArrayList<House>() {{
			// lambda to apply
			for (House current : House.input) {
				// add 0x5 to ascii value of first letter
				current.name = String.valueOf((char)(current.name.toCharArray()[0] + 0x5) +
					current.name.substring(1));
				// uppercase string
				current.star = current.star.toUpperCase();
				// do some random math operations then mask to keep value under 360
				current.compassDegree |= ~(current.compassDegree ^ 0xdeadbeef);
				current.compassDegree >>= 0x02;
				current.compassDegree &= 0x1ff;
			}
		}};
	}
}

public class PabalinasJoey02 {
	/**
	* The main() method signifies this is
	* a program and not a library.
	*
	* @param args The commandline arguments are not used.
	*/
	public static void main(String[] args) {
		// initialize array of houses
		House[] compassHouses = new House[7];
		compassHouses[6] = new House("Kauluakoko", "Betelguese", 70);
		compassHouses[5] = new House("Puana\t", "Procyon\t", 80);
		compassHouses[0] = new House("Lā\t\t", "Sun\t\t", 90);
		compassHouses[1] = new House("Puanakau", "Rigel\t", 100);
		compassHouses[2] = new House("Hikialania", "Spica\t", 110);
		compassHouses[3] = new House("A'a\t\t", "Sirius\t", 120);
		compassHouses[4] = new House("Lehuakona", "Antares\t", 140);

		// print the theme
		System.out.print("\nHawaiian Star Compass Houses\n");

		// print out the indices and attritbutes
		System.out.printf("\n%s\t\t%s\t\t\t\t\t%s\t\t\t\t\t%18s\n",
			"index",
			"name",
			"star",
			"compass degree");
		for (int i = 0; i < compassHouses.length; i++) {
			System.out.printf("%d\t\t\t%s\t\t\t\t%s\t\t\t\t\t%d\n", i,
				compassHouses[i].name,
				compassHouses[i].star,
				compassHouses[i].compassDegree);
		}

		// mutate objects
		House.mutate(compassHouses);

		// loop over the indices and print the new values
		System.out.printf("\n%s\t\t%s\t%s\t\t\t\t%18s\n",
			"index",
			"name(add 0x5 to ascii)",
			"star(all caps)",
			"compass degree(obfuscated)");
		for (int i = 0; i < compassHouses.length; i++) {
			System.out.printf("%d\t\t\t%s\t\t\t\t%s\t\t\t\t\t%d\n", i,
				compassHouses[i].name,
				compassHouses[i].star,
				compassHouses[i].compassDegree);
		}
	}
}
