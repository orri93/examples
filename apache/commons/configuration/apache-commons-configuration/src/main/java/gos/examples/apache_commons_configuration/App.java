package gos.examples.apache_commons_configuration;

import org.apache.commons.configuration2.ex.ConfigurationException;

/**
 * Hello world!
 *
 */
public class App {
	public static void main(String[] args) {
		try {
			ConfigurationExample.Development();
		} catch (ConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Hello World!");
	}
}
