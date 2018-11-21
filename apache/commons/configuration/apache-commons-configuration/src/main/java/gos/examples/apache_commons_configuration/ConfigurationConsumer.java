package gos.examples.apache_commons_configuration;

import java.util.List;

import org.apache.commons.configuration2.Configuration;

public class ConfigurationConsumer {
	
	private static final String Sources =
			"gos.examples.apache.commons.configuration.sources";
	
	public static final String Key =
			"gos.examples.apache.commons.configuration.list";
	
	public ConfigurationConsumer(Configuration configuration) {
		if(configuration.containsKey(Sources))
		{
			List list = configuration.getList(Sources);
			for(Object o : list)
			{
				if(o instanceof String)
				{
					String source = (String)o;
					System.out.println(source);
				}
			}
		}
	  if(configuration.containsKey(Key))
	  {
	  	List list = configuration.getList(Key);
			for(Object o : list)
			{
				if(o instanceof String)
				{
					String source = (String)o;
					System.out.println(source);
				}
			}
	  }
	}
}