package orri.examples.camel;

import static org.junit.Assert.*;

import org.junit.Test;

public class ItemTest {

	private static final String First = "Geirmundur";
	private static final String Last = "Sigurdsson";

	@Test
	public void testItem()
	{
		Item item = new Item();
		item.setName(First);
		item.setLast(Last);
		assertEquals(First, item.getName());
		assertEquals(Last, item.getLast());
	}
}
