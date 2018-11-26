package gos.example.parser;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.Reader;
import java.util.Map;
import java.util.Properties;

public interface YamlPropertyConverter {
	Map<String, Properties> convert(String filename)
	    throws FileNotFoundException, IOException;

	Map<String, Properties> convert(File file)
	    throws FileNotFoundException, IOException;

	Map<String, Properties> convert(Reader input);
}
