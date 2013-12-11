package datastruct;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;
import junit.framework.TestCase;
import java.util.ArrayList;

/**
 * Class test for the Bag Collection
 */
public class BagTest extends TestCase {
//Attributes
	private Bag<Integer> emptyBag;
	private Bag<Integer> normalBag;
	private Bag<Integer> testInsertBag;
	private Bag<Integer> cloneNormalBag;
	private Bag<Integer> partNormalBag;
	private Bag<Integer> cloneEmptyBag;



//Method ran before each test case
	@Before
	public void setUp() {
		emptyBag = new Bag<Integer>();
		normalBag = new Bag<Integer>();
		testInsertBag = new Bag<Integer>();
		cloneNormalBag = new Bag<Integer>();
		partNormalBag = new Bag<Integer>();
		cloneEmptyBag = new Bag<Integer>();

		//Addings
		normalBag.add(1);
		normalBag.add(2);
		normalBag.add(3);
		normalBag.add(4);
		normalBag.add(5);
		normalBag.add(6);
		normalBag.add(7);
		normalBag.add(8);
		normalBag.add(9);
		normalBag.add(10);

		cloneNormalBag.add(1);
		cloneNormalBag.add(2);
		cloneNormalBag.add(3);
		cloneNormalBag.add(4);
		cloneNormalBag.add(5);
		cloneNormalBag.add(6);
		cloneNormalBag.add(7);
		cloneNormalBag.add(8);
		cloneNormalBag.add(9);
		cloneNormalBag.add(10);

		partNormalBag.add(1);
		partNormalBag.add(3);
		partNormalBag.add(4);
		partNormalBag.add(6);
		partNormalBag.add(7);
		partNormalBag.add(9);
	}


//Methods tests
//getSize() will be tested in parallel of add() and remove()

//Test of add()
	@Test
	public void testAddBag() {
		System.out.println("Test of a normal add:");
		assertEquals(0, testInsertBag.size());
		assertEquals(true, testInsertBag.add(1));
		assertEquals(1, testInsertBag.size());
		assertEquals(true, testInsertBag.add(2));
		assertEquals(2, testInsertBag.size());
		assertEquals(true, testInsertBag.add(3));
		assertEquals(3, testInsertBag.size());
		System.out.println("OK \n");
	}

	@Test
	public void testAddEmptyBag() {
		System.out.println("Test of an add in an empty bag:");
		assertEquals(0, emptyBag.size());
		assertEquals(true, emptyBag.add(1));
		assertEquals(1, emptyBag.size());
		System.out.println("OK \n");
	}


//Test of toString()
	@Test
	public void testToStringEmptyBag() {
		System.out.println("Test of displaying an empty bag:");
		System.out.println(emptyBag.toString());
		System.out.println("OK \n");
	}

	@Test
	public void testToStringNormalBag() {
		System.out.println("Test of displaying a normal bag:");
		System.out.println(normalBag.toString());
		System.out.println("OK \n");
	}


//Test of isEmpty()
	@Test
	public void testIsEmptyWithEmptyBag() {
		System.out.println("Test of isEmpty() with an empty bag:");
		assertEquals(true, emptyBag.isEmpty());
		System.out.println("OK \n");
	}

	@Test
	public void testIsEmptyWithNormalBag() {
		System.out.println("Test of isEmpty() with a normal bag:");
		assertEquals(false, normalBag.isEmpty());
		System.out.println("OK \n");
	}


//Test of contains()
	@Test
	public void testContainsWithEmptyBag() {
		System.out.println("Test of contains() with an empty bag:");
		assertEquals(false, emptyBag.contains(1));
		System.out.println("OK \n");
	}

	@Test
	public void testContainsWithNormalBag() {
		System.out.println("Test of contains() with a normal bag and an element contained in it:");
		assertEquals(true, normalBag.contains(1));
		System.out.println("\n");
	}

	@Test
	public void testContainsWithNormalBagNotContaining() {
		System.out.println("Test of contains() with a normal bag and an element non present in it:");
		assertEquals(false, normalBag.contains(42));
		System.out.println("OK \n");
	}


//Test of toArray() number one
	@Test
	public void testToArrayNumberOneNormal() {
		System.out.println("Test of the first toArray() with a normal bag:");
		Object[] array = normalBag.toArray();

		//Parsing the array obtained
		for (int i = 0; i < array.length; i++) {
			assertEquals(true, normalBag.contains(array[i]));
		}

		System.out.println("OK \n");
	}

	@Test
	public void testToArrayNumberOneEmpty() {
		System.out.println("Test of the first toArray() with an empty bag:");
		Object[] array = emptyBag.toArray();
		assertEquals(0, array.length);
		System.out.println("OK \n");
	}


//Test of toArray() number two
	/* DUNNO HOW IT WORKS
	@Test
	public void testToArrayNumberTwoNormal() {
		System.out.println("Test of the second toArray() with a normal bag:");
		int[] array = normalBag.toArray(new int[10]);
	}

	@Test
	public void testToArrayNumberTwoEmpty() {
		System.out.println("Test of the second toArray() with an empty bag:");
		int[] array = emptyBag.toArray(new int[0]);
		assertEquals(0, array.length);
		System.out.println("OK \n");
	}
	*/


//Test of remove()


//Test of containsAll()
	@Test
	public void testContainsAllEmpty() {
		System.out.println("Test of containsAll() with an empty bag:");
		assertEquals(true, emptyBag.containsAll(cloneEmptyBag));
		System.out.println("OK \n");
	}

	@Test
	public void testContainsAllNormal() {
		System.out.println("Test of containsAll() with a normal bag:");
		assertEquals(true, normalBag.containsAll(cloneNormalBag));
	}

	@Test
	public void testContainsAllOnlyAPart() {
		System.out.println("Test of containsAll() with only a part of the bag:");
		assertEquals(false, normalBag.containsAll(partNormalBag));
		System.out.println("OK \n");
	}

	@Test
	public void testContainsAllNonTrue() {
		System.out.println("Test of containsAll() with an empty bag compared to a non empty one:");
		assertEquals(false, normalBag.containsAll(emptyBag));
		assertEquals(false, emptyBag.containsAll(normalBag));
	}


//Test of addAll()
	@Test
	public void testAddAllOnEmptyBag() {
		System.out.println("Test of addAll() with an empty bag:" + "\n" + "Before:");
		System.out.println(emptyBag.toString() + "\n");
		emptyBag.addAll(normalBag);
		System.out.println("After:" + "\n" + emptyBag.toString());
		System.out.println("OK \n");
	}

	@Test
	public void testAddAllOnNormalBag() {
		System.out.println("Test of addAll() with a normal bag:" + "\n" + "Before:");
		System.out.println(normalBag.toString() + "\n");
		normalBag.addAll(partNormalBag);
		System.out.println("After:" + "\n" + normalBag.toString());
		System.out.println("OK \n");
	}

	@Test
	public void testAddAllOnNormalBagAddingAnEmptyBag() {
		System.out.println("Test of addAll() with a normal bag adding an empty bag:" + "\n" + "Before:");
		System.out.println(normalBag.toString() + "\n");
		normalBag.addAll(emptyBag);
		System.out.println("After:" + "\n" + normalBag.toString());
		System.out.println("OK \n");
	}


//Test of removeAll()



//Test of retainAll()


//Test of clear()
}