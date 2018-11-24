package gos.examples.example.project.boot.items;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "books")
public class Book /* extends gos.example.Book */ {

	@Id
	@GeneratedValue
	private int id;
	
  private String item;

  private String description;

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}
	
  public String getItem() {
      return this.item;
  }

  public void setItem(String item) {
      this.item = item;
  }

  public String getDescription() {
      return this.description;
  }

  public void setDescription(String description) {
      this.description = description;
  }
}
