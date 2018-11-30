package orri.examples.camel;

public class Generator {

	public Item generateItem(String name, String last)
	{
		Item item = new Item();
		item.setName(name);
		item.setLast(last);
		return item;
	}
}
