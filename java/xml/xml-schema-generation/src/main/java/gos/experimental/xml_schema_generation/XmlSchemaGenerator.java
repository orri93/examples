package gos.experimental.xml_schema_generation;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import javax.xml.transform.stream.StreamSource;

import org.apache.commons.configuration2.Configuration;
import org.apache.ws.commons.schema.XmlSchema;
import org.apache.ws.commons.schema.XmlSchemaCollection;
import org.apache.ws.commons.schema.XmlSchemaEnumerationFacet;
import org.apache.ws.commons.schema.XmlSchemaObjectCollection;
import org.apache.ws.commons.schema.XmlSchemaSimpleType;
import org.apache.ws.commons.schema.XmlSchemaSimpleTypeContent;
import org.apache.ws.commons.schema.XmlSchemaSimpleTypeRestriction;
import org.apache.ws.commons.schema.XmlSchemaType;

public class XmlSchemaGenerator {
  
	public static final String ConfigurationKey =
			"gos.examples.apache.commons.xml.schema.key";
  private static final String SchemaResource = "/xsd/source-selection.xsd";
  private static final String Source = "Source";
  
  XmlSchemaCollection collection;
  ValidationHandler handler;
  XmlSchema schema;
  
  private List<String> list;
  
  protected XmlSchemaGenerator()
  {
    InputStream stream = 
        this.getClass().getResourceAsStream(SchemaResource);
    collection = new XmlSchemaCollection();
    handler = new ValidationHandler();
    schema = collection.read(new StreamSource(stream), handler);
  }
  
  public XmlSchemaGenerator(Configuration configuration)
  {
  	this();
  	this.list = new ArrayList<String>();
  	if(configuration.containsKey(ConfigurationKey))
  	{
  		List<?> objects = configuration.getList(ConfigurationKey);
  		if(objects != null)
  		{
  			for(Object o : objects)
  			{
  				if(o != null && o instanceof String)
  				{
  					this.list.add((String)o);
  				}
  			}
  		}
  	}
  }
  
  public XmlSchemaGenerator(String[] sources)
  {
  	this();
  	this.list = new ArrayList<String>();
  	for(String source : sources)
  	{
  		this.list.add(source);
  	}
  }
  
  public static void Development() {
  	XmlSchemaGenerator generator =
  			new XmlSchemaGenerator(new String[] { "RigSense", "Other" });
  	generator.Create(System.out);
  }
  
  public void Create(OutputStream stream)
  {
  	if(this.list.size() > 0)
  	{
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
          for(String item : this.list)
          {
          	XmlSchemaEnumerationFacet facet =
          			new XmlSchemaEnumerationFacet(item, false);
          	facets.add(facet);
          }
        }
      }
  	}
    schema.write(System.out);  	
  }
}
