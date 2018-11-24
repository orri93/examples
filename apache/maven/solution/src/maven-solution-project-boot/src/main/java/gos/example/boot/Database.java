package gos.example.boot;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import gos.examples.example.project.boot.items.Book;
import gos.examples.example.project.boot.items.Order;

@Component
public class Database {
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
