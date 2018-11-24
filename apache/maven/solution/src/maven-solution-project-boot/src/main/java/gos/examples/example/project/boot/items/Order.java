package gos.examples.example.project.boot.items;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQuery;
import javax.persistence.Table;

import org.apache.camel.component.jpa.Consumed;

@Entity
@Table(name = "orders")
@NamedQuery(name = "new-orders", query = "select order from Order order where order.processed = false")
public class Order /* extends gos.example.Order */ {

	@Id
	@GeneratedValue
	private int id;

	private int amount;

	@ManyToOne
	private Book book;

	private boolean processed;

	@Consumed
	public void setProcessed() {
		this.processed = true;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public int getAmount() {
		return this.amount;
	}

	public void setAmount(int amount) {
		this.amount = amount;
	}

	public Book getBook() {
		return book;
	}

	public void setBook(Book book) {
		this.book = book;
	}

	public boolean isProcessed() {
		return processed;
	}

	public void setProcessed(boolean processed) {
		this.processed = processed;
	}
}
