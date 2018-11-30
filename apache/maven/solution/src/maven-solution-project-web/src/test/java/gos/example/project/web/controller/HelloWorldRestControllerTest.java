package gos.example.project.web.controller;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/")
public class HelloWorldRestControllerTest {
    
  @ResponseBody
  @RequestMapping(method=RequestMethod.GET, headers="Accept=text/html")
  public String forms() throws IOException, ParserConfigurationException, TransformerException {
  	StringBuilder builder = new StringBuilder();
  	FileReader file = new FileReader("webapp/index.html");
  	BufferedReader reader = new BufferedReader(file);
  	String line = reader.readLine();
  	if(line != null)
  	{
  		builder.append(line);
  		line = reader.readLine();
  	}
  	reader.close();
    return builder.toString();
  }
}