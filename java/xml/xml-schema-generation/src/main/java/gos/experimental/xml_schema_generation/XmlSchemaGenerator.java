package gos.experimental.xml_schema_generation;

import java.io.InputStream;
import javax.xml.transform.stream.StreamSource;

import org.apache.ws.commons.schema.XmlSchema;
import org.apache.ws.commons.schema.XmlSchemaCollection;
import org.apache.ws.commons.schema.XmlSchemaEnumerationFacet;
import org.apache.ws.commons.schema.XmlSchemaObjectCollection;
import org.apache.ws.commons.schema.XmlSchemaSimpleType;
import org.apache.ws.commons.schema.XmlSchemaSimpleTypeContent;
import org.apache.ws.commons.schema.XmlSchemaSimpleTypeRestriction;
import org.apache.ws.commons.schema.XmlSchemaType;

public class XmlSchemaGenerator {
  
  private static final String SchemaResource = "/xsd/source-selection.xsd";
  private static final String Source = "Source";
  
  public static void Development() {
    InputStream stream = 
        XmlSchemaGenerator.class.getResourceAsStream(SchemaResource);
    XmlSchemaCollection collection = new XmlSchemaCollection();
    ValidationHandler handler = new ValidationHandler();
    XmlSchema schema = collection.read(new StreamSource(stream), handler);
    
    XmlSchemaType source = schema.getTypeByName(Source);
    if(source instanceof XmlSchemaSimpleType)
    {
      XmlSchemaSimpleType simpleSource = (XmlSchemaSimpleType)source;
      XmlSchemaSimpleTypeContent content = simpleSource.getContent();
      
      if(content instanceof XmlSchemaSimpleTypeRestriction)
      {
        XmlSchemaSimpleTypeRestriction restriction =
            (XmlSchemaSimpleTypeRestriction)content;
        XmlSchemaObjectCollection facets = restriction.getFacets();
        facets.add(new XmlSchemaEnumerationFacet("RigSense", false));
        facets.add(new XmlSchemaEnumerationFacet("Other", false));
      }
    }
   
    schema.write(System.out);
  }
}
