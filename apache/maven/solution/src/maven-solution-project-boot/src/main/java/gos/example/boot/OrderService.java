package gos.example.boot;

import java.util.Optional;
import java.util.Random;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import gos.examples.example.project.boot.items.Book;
import gos.examples.example.project.boot.items.Order;

@Component
public class OrderService {
	Logger Log = LoggerFactory.getLogger(OrderService.class);

	@Autowired
	private BookRepository books;

	private final Random amount = new Random();
	
	public Book generateBook(int id) {
		return createBook(id);
	}

	public Order generateOrder() {
		Order order = new Order();
		order.setAmount(amount.nextInt(10) + 1);
		int id = amount.nextInt(2) + 1;
		if(!books.existsById(id)) {
			Log.info("Adding book no. {}", id);
			addBook(id);
		}
		if(books.existsById(id)) {
			Optional<Book> book = books.findById(id);
			if(book.isPresent()) {
				order.setBook(book.get());
			}
		} else {
			Log.warn("Book no. {} doesn't exist", id);
		}
		return order;
	}
	
	private void addBook(int id) {
		Book book = createBook(id);
		books.save(book);
	}

	private void addBook(int id, String item, String description) {
		Book book = createBook(id, item, description);
		books.save(book);
	}
	
	private Book createBook(int id) {
		return createBook(id, String.format("New book no. {}", id),
		    String.format("New book no. {} by Orri", id));
	}
	
	private Book createBook(int id, String item, String description) {
		Book book = new Book();
		book.setId(id);
		book.setItem(item);
		book.setDescription(description);
		return book;
	}

}
