package gos.example.repository;

import org.springframework.data.repository.CrudRepository;

import gos.example.item.Order;

@org.springframework.stereotype.Repository
public interface OrderRepository extends CrudRepository<Order, Integer> {

}
