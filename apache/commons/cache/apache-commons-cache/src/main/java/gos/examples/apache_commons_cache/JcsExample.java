package gos.examples.apache_commons_cache;

import org.apache.commons.jcs.JCS;
import org.apache.commons.jcs.access.CacheAccess;
import org.apache.commons.jcs.access.exception.CacheException;

/**
 * Hello world!
 *
 */
public class JcsExample {
	
	private CacheAccess<String, City> cache = null;
	
	public static void main(String[] args) {
		JcsExample example = new JcsExample();
		example.testCache();
	}

	public JcsExample() {
		try {
			this.cache = JCS.getInstance("testCache2");
		} catch (CacheException e) {
			System.out.println(String.format("Problem initializing cache: %s", e.getMessage()));
		}
	}

	public void putInCache(City city) {
		String key = city.name;
		try {
			cache.put(key, city);
		} catch (CacheException e) {
			System.out.println(
			    String.format("Problem putting city %s in the cache, for key %s%n%s", city.name, key, e.getMessage()));
		}
	}

	public City retrieveFromCache(String cityKey) {
		return cache.get(cityKey);
	}

	public void testCache() {
		City zurich = new City("Zürich", "Switzerland", 366765);
		putInCache(zurich);

		City berlin = new City("Berlin", "Germany", 3502000);
		putInCache(berlin);

		City johannesburg = new City("Johannesburg", "South Africa", 12200000);
		putInCache(johannesburg);

		City retrievedCity1 = retrieveFromCache("Berlin");
		if (retrievedCity1 != null) {
			System.out.println(retrievedCity1.toString());
		} else {
			System.out.println("No object was found in the cache for the key \"Berlin\"");
		}

		City retrievedCity2 = retrieveFromCache("New York");
		if (retrievedCity2 != null) {
			System.out.println(retrievedCity2.toString());
		} else {
			System.out.println("No object was found in the cache for the key \"New York\"");
		}
	}
}
