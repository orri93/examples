package gos.example.camel.processor;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.net.URI;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.camel.Exchange;
import org.apache.camel.Message;
import org.apache.camel.Processor;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

@Component
public class FileContentProcessor implements Processor {
	Logger Log = LoggerFactory.getLogger(FileContentProcessor.class);

	@Override
	public void process(Exchange exchange) throws Exception {
		// message body contains filename
		String filename = exchange.getIn().getBody(String.class);
		String filePath = exchange.getIn().getHeader("fileprocessor.filepath",
		    String.class);

		if (filename == null) {
			throw new IllegalArgumentException("filename is undefined");
		}

		if (filePath == null) {
			throw new IllegalArgumentException("filePath is undefined");
		}
		
		Path userDir = Paths.get(System.getProperty("user.dir"));
		Log.debug("User dir is " + userDir.toString());
		
		Path path = Paths.get(userDir.toString(), filePath, filename);
		Log.debug("File path is " + path.toString());
		
		Path absolute = path.toAbsolutePath();
		Log.debug("Absolute file path is " + absolute.toString());

		URI uri = absolute.toUri();
		File file = new File(uri);

		if (!file.exists()) {
			throw new FileNotFoundException(
			    String.format("File %s not found on %s", filename, filePath));
		}
		
		Message out = exchange.getOut();
		out.setBody(new String());
		
		StringBuilder builder = new StringBuilder();
		FileReader fileReader = new FileReader(file);
		try (BufferedReader reader = new BufferedReader(fileReader)) {
			String line = reader.readLine();
			while(line != null) {
				builder.append(line);
				line = reader.readLine();
			}
		}
	
		exchange.getOut().setBody(builder.toString());
		exchange.getOut().setHeaders(exchange.getIn().getHeaders());
	}
}
