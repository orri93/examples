package orri.examples.camel;

import java.io.Serializable;

public class Item implements Serializable {
	private static final long serialVersionUID = 6748001817262840765L;
	private String name;
	private String last;
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getLast() {
		return last;
	}
	public void setLast(String last) {
		this.last = last;
	}
}
