package gos.experimental.xml_xsd_generation;

import javax.xml.parsers.ParserConfigurationException;

/**
 * Hello world!
 *
 */
public class App {
  
  private final static String SerivceXsdNsPrefix = "iws";

  private final static String SerivceXsdNamespace =
      "http://www.nov.com/schemas/integration/witsml/service.xsd";
  
  public static void main(String[] args) throws ParserConfigurationException {
    
    XsdGenerator generator = new XsdGenerator();
    
    generator.StartFormXsd(SerivceXsdNamespace, SerivceXsdNsPrefix);
    
    generator.AddSchemaAnnotation(
        "<h2>Australian Census 2011 extract</h2>",
        "<p>Thanks for your time.</p>");
    
    generator.AddVersionSimpleType(new String[]{ "1.0" });
    
    generator.AddEnumerationSimpleType("Source", new String[] { "A", "B", "C" });
    
    System.out.println(generator.toString());
    
  }
}
