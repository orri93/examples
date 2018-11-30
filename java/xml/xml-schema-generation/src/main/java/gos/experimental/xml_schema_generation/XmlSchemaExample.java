package gos.experimental.xml_schema_generation;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.configuration2.PropertiesConfiguration;
import org.apache.commons.configuration2.builder.FileBasedConfigurationBuilder;
import org.apache.commons.configuration2.builder.fluent.Configurations;
import org.apache.commons.configuration2.ex.ConfigurationException;

public class XmlSchemaExample {
	
  public static void main(String[] args) {
  	
    XmlSchemaGenerator.Development();
    try {
			XmlSchemaExample.Development();
		} catch (ConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
  }
	
	public static void Development() throws ConfigurationException {
		Configurations configurations = new Configurations();
		FileBasedConfigurationBuilder<PropertiesConfiguration> builder =
				configurations.propertiesBuilder("configuration.properties");
		PropertiesConfiguration configuration = builder.getConfiguration();
		List<String> list = new ArrayList<String>();
		list.add("i");
		list.add("j");
		list.add("k");
		configuration.setProperty(XmlSchemaGenerator.ConfigurationKey, list);
		XmlSchemaGenerator generator = new XmlSchemaGenerator(configuration);
		generator.Create(System.out);
	}
	
}
