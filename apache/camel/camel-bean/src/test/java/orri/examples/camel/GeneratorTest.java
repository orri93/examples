package orri.examples.camel;

import static org.junit.Assert.*;

import org.junit.Test;

public class GeneratorTest {
	
	private static final String First = "Geirmundur";
	private static final String Last = "Sigurdsson";
	
	@Test
	public void testGenerateItem() {
		Generator generator = new Generator();
		Item item = generator.generateItem(First, Last);
		assertNotNull(item);
		assertEquals(First, item.getName());
		assertEquals(Last, item.getLast());
	}
}
