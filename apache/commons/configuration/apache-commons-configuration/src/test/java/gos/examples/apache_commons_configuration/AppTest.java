package gos.examples.apache_commons_configuration;

import static org.mockito.Mockito.*;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.configuration2.Configuration;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

/**
 * Unit test for simple App.
 */
public class AppTest extends TestCase {
	
	private Configuration configuration = mock(Configuration.class);
	
	/**
	 * Create the test case
	 *
	 * @param testName name of the test case
	 */
	public AppTest(String testName) {
		super(testName);
	}

	/**
	 * @return the suite of tests being tested
	 */
	public static Test suite() {
		return new TestSuite(AppTest.class);
	}

	/**
	 * Rigourous Test :-)
	 */
	public void testApp() {
		List<String> sources = new ArrayList<String>();
		
		sources.add("RigSense");
		sources.add("Other");
		
		configuration.addProperty("Sources", sources);
		
		ConfigurationConsumer consumer = new ConfigurationConsumer(configuration);
		
		assertTrue(true);
	}
}
