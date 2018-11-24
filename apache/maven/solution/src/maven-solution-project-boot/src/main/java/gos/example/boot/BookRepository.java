package gos.example.boot;

import org.springframework.data.repository.CrudRepository;

import gos.examples.example.project.boot.items.Book;

public interface BookRepository extends CrudRepository<Book, Integer> {

}
