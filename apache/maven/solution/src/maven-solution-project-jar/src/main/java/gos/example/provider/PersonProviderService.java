package gos.example.provider;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class PersonProviderService {
  // use a tree map so they become sorted
  private final Map<String, PersonProvider> providers =
  		new TreeMap<String, PersonProvider>();
  
  @SuppressWarnings("unused")
  private static final Log LOG =
  		LogFactory.getLog(PersonProviderService.class);

  public PersonProviderService() {
      providers.put("123", new PersonProvider(123, "John", "Doe", "555-555-5555", "000 Deer St. Edison, NJ", "11111"));
      providers.put("456", new PersonProvider(456, "Donald", "Duck", "123-456-7890", "100 Disleyland Way Orlando, FL", "11111"));
      providers.put("789", new PersonProvider(789, "Barack", "Obama", "201-867-5309", "1500 Pennsylvania Av. Washington D.C.", "11112"));
  }

  /**
   * Gets a user by the given id
   *
   * @param id  the id of the user
   * @return the user, or <code>null</code> if no user exists
   */
  public PersonProvider getProvider(String id) {
      return providers.get(id);
  }

  /**
   * List all users
   *
   * @return the list of all users
   */
  public Collection<PersonProvider> listProviders() {
      return providers.values();
  }

  /**
   * Updates or creates the given user
   *
   * @param user the user
   */
  public String updateProvider(PersonProvider user) {
      providers.put("" + user.getId(), user);
      return "Added: " + user.getLastName() + ", " + user.getFirstName();
  }
  
  public Collection<PersonProvider> searchByZip(String zip) {
  	zip.trim();
  	List<PersonProvider> searchResults = new ArrayList<PersonProvider>();
  	for (Map.Entry<String, PersonProvider> entry : providers.entrySet())
  	{
  		if (entry.getValue().getZipCode().equalsIgnoreCase(zip))
  		{
  			searchResults.add(entry.getValue());
  		}
  	}    	
  	return searchResults;
  }

}
