package gos.example.provider;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import gos.example.item.Book;
import gos.example.item.Order;
import gos.example.repository.BookRepository;
import gos.example.repository.OrderRepository;

@Component
public class BookOrderAccess {
	
  @Autowired
  BookRepository books;

  @Autowired
  OrderRepository orders;

  public Iterable<Book> findBooks() {
      return books.findAll();
  }

  public Order findOrder(Integer id) {
      return orders.findById(id).get();
  }

}
