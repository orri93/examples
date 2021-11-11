package gos.example.mongodb;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

@Service
public class ApplicationPropertiesService {
  @Value("${example.mongo.server}")
  private String mongoServer;

  @Value("${example.mongo.port:27017}")
  private int mongoPort;

  @Value("${example.mongo.database}")
  private String mongoDatabase;

  public String getServer() {
    return this.mongoServer;
  }

  public int getPort() {
    return this.mongoPort;
  }

  public String getDatabase() {
    return this.mongoDatabase;
  }
}
