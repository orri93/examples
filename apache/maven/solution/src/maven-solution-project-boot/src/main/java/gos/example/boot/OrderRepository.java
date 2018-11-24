package gos.example.boot;

import org.springframework.data.repository.CrudRepository;

import gos.examples.example.project.boot.items.Order;

public interface OrderRepository extends CrudRepository<Order, Integer> {

}
