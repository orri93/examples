package gos.example.repository;

import org.springframework.data.repository.CrudRepository;

import gos.example.item.Book;

@org.springframework.stereotype.Repository
public interface BookRepository extends CrudRepository<Book, Integer> {

}
