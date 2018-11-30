package gos.examples.apache_commons_configuration;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.configuration2.PropertiesConfiguration;
import org.apache.commons.configuration2.builder.FileBasedConfigurationBuilder;
import org.apache.commons.configuration2.builder.fluent.Configurations;
import org.apache.commons.configuration2.ex.ConfigurationException;

public class ConfigurationExample {
	public static void Development() throws ConfigurationException {
		Configurations configurations = new Configurations();
		FileBasedConfigurationBuilder<PropertiesConfiguration> builder =
				configurations.propertiesBuilder("configuration.properties");
		PropertiesConfiguration configuration = builder.getConfiguration();
		List<String> list = new ArrayList<String>();
		list.add("i");
		list.add("j");
		list.add("k");
		configuration.setProperty(ConfigurationConsumer.Key, list);
		ConfigurationConsumer consumer = new ConfigurationConsumer(configuration);
		builder.save();
	}
}
