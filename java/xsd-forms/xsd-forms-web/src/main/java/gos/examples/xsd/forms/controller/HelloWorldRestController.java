package gos.examples.xsd.forms.controller;

import java.io.IOException;
import java.io.InputStream;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import com.github.davidmoten.xsdforms.Generator;

import gos.examples.xsd.forms.generator.XsdGenerator;
import scala.Option;
import scala.Some;

@RestController
@RequestMapping("/")
public class HelloWorldRestController {
  
  private static final String XsdDemo = "/xsd/demo.xsd";
  
  @ResponseBody
  @RequestMapping(method=RequestMethod.GET, headers="Accept=text/html")
  public String forms() throws IOException, ParserConfigurationException, TransformerException {
    XsdGenerator generator = new XsdGenerator();
    InputStream stream = generator.SelectSource();
    Option<String> option = new Some<String>("main");
    String prefix = new String();
    String result;
    if(stream != null)
    {
      result = generator.SelectSourceString();
      //result = Generator.generateHtmlAsString(stream, prefix, option);
    }
    else
    {
      result = "Can't access '" + XsdDemo + "'";
    }
    stream.close();
    return result;
  }
}