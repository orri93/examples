package gos.experimental.xml_xsd_generation;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;

import javax.swing.text.Utilities;
import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Attr;
import org.w3c.dom.CDATASection;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class XsdGenerator {
  
  private static final String Xsd = XMLConstants.W3C_XML_SCHEMA_NS_URI;
  
  private final static String XsdPrefix = "xsd";
  private static final String Schema = "schema";
  private static final String XmlNs = "xmlns";  
  private static final String Version = "version";
  private static final String XsdVersion = "1.0";

  private static final String SimpleType = "simpleType";
  
  private static final String Name = "name";
  private static final String Restriction = "restriction";
  private static final String Enumeration = "enumeration";
  private static final String Annotation = "annotation";
  private static final String Value = "value";
  private static final String Base = "base";
  
  private static final String AppInfo = "appinfo";
   
  private static final String XsdString = "xsd:string";

  private static final String True = "true";
  private static final String False = "false";
   
  private final static String XsdFormsNsPrefix = "i";
  private final static String XsdFormsNamespace =
      "http://moten.david.org/xsd-forms";
  
  private final static String numberItems = "numberItems";
  private final static String Header = "header";
  private final static String Footer = "header";
  
  private Document document;
  private Element schema;

  public void StartFormXsd(String namespace, String prefix) throws ParserConfigurationException
  {    
    DocumentBuilderFactory documentBuilderFactory =
        DocumentBuilderFactory.newInstance();
    DocumentBuilder documentBuilder =
        documentBuilderFactory.newDocumentBuilder();

    this.document = documentBuilder.newDocument(); 

    this.schema = this.document.createElementNS(Xsd, Ns(XsdPrefix, Schema));
    Attr targetNamespace = this.document.createAttribute("targetNamespace");
    targetNamespace.setValue(namespace);
    this.schema.setAttributeNode(targetNamespace);
    
    Attr xmlns_i = CreateNsPrefixAttribute(XsdFormsNsPrefix, XsdFormsNamespace);
    this.schema.setAttributeNode(xmlns_i);
    
    Attr xmlns_iws = CreateNsPrefixAttribute(prefix, namespace);
    this.schema.setAttributeNode(xmlns_iws);
        
    Attr elementFormDefault = this.document.createAttribute("elementFormDefault");
    elementFormDefault.setValue("qualified");
    this.schema.setAttributeNode(elementFormDefault);
    
    Attr versionAttribute = CreateVersionAttribute();
    this.schema.setAttributeNode(versionAttribute);
    
    this.document.appendChild(this.schema);
  }
  
  public void AddSchemaAnnotation(String header, String footer)
  {
    Element annotation = this.document.createElementNS(Xsd, Ns(XsdPrefix, Annotation));
    annotation.setAttributeNS(XsdFormsNamespace, Ns(XsdFormsNsPrefix, numberItems), True);
    Element appinfo = this.document.createElementNS(Xsd, Ns(XsdPrefix, AppInfo));
    
    if(header != null)
    {
      Element headerElement = this.document.createElementNS(XsdFormsNamespace, Ns(XsdFormsNsPrefix, Header));
      CDATASection headerData = this.document.createCDATASection(header);
      headerElement.appendChild(headerData);
      appinfo.appendChild(headerElement);
    }
    
    if(footer != null)
    {
      Element footerElement = this.document.createElementNS(XsdFormsNamespace, Ns(XsdFormsNsPrefix, Footer));
      CDATASection footerData = this.document.createCDATASection(footer);
      footerElement.appendChild(footerData);
      appinfo.appendChild(footerElement);
    }
    
    annotation.appendChild(appinfo);
    this.schema.appendChild(annotation);
  }
  
  public void AddVersionSimpleType(String[] versions)
  {
    AddEnumerationSimpleType(FirstUpperCase(Version), versions);
  }
  
  public void AddEnumerationSimpleType(String name, String[] values)
  {
    Element simple = this.document.createElementNS(Xsd, Ns(XsdPrefix, SimpleType));
    simple.setAttribute(Name, name);
    Element restriction = this.document.createElementNS(Xsd, Ns(XsdPrefix, Restriction));
    restriction.setAttribute(Base, XsdString);
    for(String value : values)
    {
      Element enumeration = this.document.createElementNS(Xsd, Ns(XsdPrefix, Enumeration));
      enumeration.setAttribute(Value, value);
      restriction.appendChild(enumeration);
    }
    simple.appendChild(restriction);
    this.schema.appendChild(simple);
  }
  
  public InputStream toInputStream() throws TransformerException
  {
    ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    Result target = new StreamResult(outputStream);
    Transform(document, target);
    InputStream inputStream =
        new ByteArrayInputStream(outputStream.toByteArray());
    return inputStream;
  }
  
  @Override
  public String toString()
  {
    StringWriter writer = new StringWriter();
    StreamResult target = new StreamResult(writer);
    try {
      Transform(this.document, target);
    } catch (TransformerException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
    return writer.toString();
  }
    
  private Attr CreateVersionAttribute()
  {
    Attr attribute = document.createAttribute(Version);
    attribute.setValue(XsdVersion);
    return attribute;
  }
  
  private Attr CreateNsPrefixAttribute(String prefix, String namespace)
  {
    Attr attribute = document.createAttribute(Ns(XmlNs, prefix));
    attribute.setValue(namespace);
    return attribute;
  }
  
  private String Ns(String ns, String text)
  {
    return ns + ":" + text;
  }
  
  private String FirstUpperCase(String text)
  {
    return Character.toUpperCase(text.charAt(0)) + text.substring(1);
  }
    
  private void Transform(Document document, Result target) throws TransformerException
  {
    Source source = new DOMSource(document);
    TransformerFactory factory = TransformerFactory.newInstance();
    Transformer transformer = factory.newTransformer();
    transformer.setOutputProperty(OutputKeys.INDENT, "yes");
    transformer.transform(source, target);
  }
}
