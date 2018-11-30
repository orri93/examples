package gos.examples.apache_commons_cache;

import java.io.Serializable;

public class City implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1000394604403891984L;

	public String name;
  public String country;
  public int population;

  public City( String name, String country, int population ) 
  {
      this.name = name;
      this.country = country;
      this.population = population;
  }

  @Override
  public String toString() 
  {
      return String.format( "%s is a city in the country %s with a population of %d", name, country, population );
  }

}
