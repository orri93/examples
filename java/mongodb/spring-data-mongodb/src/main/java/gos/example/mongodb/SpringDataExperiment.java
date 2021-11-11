package gos.example.mongodb;

import com.mongodb.ConnectionString;
import com.mongodb.MongoClientSettings;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;

import org.bson.Document;
import org.bson.conversions.Bson;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class SpringDataExperiment implements CommandLineRunner {
  private static final Logger LOGGER = LoggerFactory.getLogger(SpringDataExperiment.class);

  private static final String CONNECTION_STRING_FORMAT = "mongodb://%s:%d/%s";

  @Autowired
  private ApplicationPropertiesService applicationProperties;

  public static void main(String[] args) {
    SpringApplication.run(SpringDataExperiment.class, args);
  }

  @Override
  public void run(String... args) throws Exception {
    LOGGER.info("Starting Spring Data MongoDB Experiments");
    LOGGER.info("Server: {}", applicationProperties.getServer());
    LOGGER.info("Port: {}", applicationProperties.getPort());
    LOGGER.info("Database Name: {}", applicationProperties.getDatabase());

    MongoClient client = createMongoClient(applicationProperties);

    MongoDatabase database = client.getDatabase(applicationProperties.getDatabase());

    MongoCollection<Document> collection = database.getCollection("Configuration");

    Bson query = Filters.eq("configTag", "efd_configuration");

    Document first = collection.find(query).first();

    String json = first.toJson();

    System.out.println(json);

    client.close();
  }

  private static MongoClient createMongoClient(ApplicationPropertiesService applicationProperties) {
    String connectionText = String.format(
      CONNECTION_STRING_FORMAT,
      applicationProperties.getServer(),
      applicationProperties.getPort(),
      applicationProperties.getDatabase());
    LOGGER.info("Connection Text is {}", connectionText);
    ConnectionString connectionString = new ConnectionString(connectionText);
    MongoClientSettings mongoClientSettings = MongoClientSettings.builder()
      .applyConnectionString(connectionString)
      .build();
    return MongoClients.create(mongoClientSettings);
  }
}
