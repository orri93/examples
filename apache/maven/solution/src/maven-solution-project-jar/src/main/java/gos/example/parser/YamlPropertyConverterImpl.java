package gos.example.parser;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.events.Event;
import org.yaml.snakeyaml.events.Event.ID;
import org.yaml.snakeyaml.events.ScalarEvent;

public class YamlPropertyConverterImpl implements YamlPropertyConverter {

	@Override
	public Map<String, Properties> convert(String filename)
	    throws FileNotFoundException, IOException {
		File file = new File(filename);
		return convert(file);
	}

	@Override
	public Map<String, Properties> convert(File file)
	    throws FileNotFoundException, IOException {
		Reader reader = new FileReader(file);
		final Map<String, Properties> map = convert(reader);
		reader.close();
		return map;
	}

	@Override
	public Map<String, Properties> convert(Reader input) {
		Yaml y = new Yaml();
		Map<String, Properties> propertiesMap = new HashMap<String, Properties>();
		String currentKey = "";
		String currentEnv = "";
		for (Event event : y.parse(input)) {
			// mapping: scalar
			int level = event.getStartMark().getColumn();
			if (event.is(ID.Scalar)) {
				ScalarEvent s = (ScalarEvent) event;
				if (level == 0) {
					currentKey = s.getValue();
				} else if (level == 2) {
					currentEnv = s.getValue();
				} else {
					Properties properties = propertiesMap.get(currentEnv);
					properties = createIfNoProperties(propertiesMap, currentEnv,
					    properties);
					properties.put(currentKey, s.getValue());
				}

			}
		}

		return propertiesMap;
	}

	private Properties createIfNoProperties(Map<String, Properties> propertiesMap,
	    String currentEnv, Properties properties) {
		if (null == properties) {
			properties = new Properties();
			propertiesMap.put(currentEnv, properties);
		}
		return properties;
	}
}
