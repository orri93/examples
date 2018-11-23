package gos.examples.xsd.forms.generator;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.FactoryConfigurationError;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.XMLConstants;


import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Attr;

public class XsdGenerator {

  private static final String XsdDemo = "/xsd/demo.xsd";
  
  private static final String XmlNs = "xmlns";
  
  private final static String SerivceXsdNamespace =
      "http://www.nov.com/schemas/integration/witsml/service.xsd";
  private final static String XsdFormsNamespace =
      "http://moten.david.org/xsd-forms";
  
  private final static String NS_PREFIX = "xsd:";
  private final static String StringXsdFormsNs = "i";
  
  public InputStream SelectSource() throws ParserConfigurationException, TransformerException
  {
    //InputStream stream = this.getClass().getResourceAsStream(XsdDemo);
    Document document = StartXsd();
    InputStream stream = ToInputStream(document);
    return stream;
  }
  
  public String SelectSourceString() throws ParserConfigurationException, TransformerException, IOException
  {
    //InputStream stream = this.getClass().getResourceAsStream(XsdDemo);
    Document document = StartXsd();
    return ToString(document);
  }

  
  private Document StartXsd() throws ParserConfigurationException
  {
    final String Xsd = XMLConstants.W3C_XML_SCHEMA_NS_URI;
    
    DocumentBuilderFactory documentBuilderFactory =
        DocumentBuilderFactory.newInstance();
    DocumentBuilder documentBuilder =
        documentBuilderFactory.newDocumentBuilder();

    Document document = documentBuilder.newDocument(); 

    Element schemaRoot = document.createElementNS(Xsd, NS_PREFIX + "schema");
    Attr targetNamespace = document.createAttribute("targetNamespace");
    targetNamespace.setValue(SerivceXsdNamespace);
    schemaRoot.setAttributeNode(targetNamespace);
    Attr elementFormDefault = document.createAttribute("elementFormDefault");
    elementFormDefault.setValue("qualified");
    schemaRoot.setAttributeNode(elementFormDefault);
    
    document.appendChild(schemaRoot);

    return document;
  }
  
  private InputStream ToInputStream(Document document) throws TransformerException
  {
    ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
    Result target = new StreamResult(outputStream);
    Transform(document, target);
    InputStream inputStream =
        new ByteArrayInputStream(outputStream.toByteArray());
    return inputStream;
  }
  
  private String ToString(Document document) throws TransformerException, IOException
  {
    StringWriter writer = new StringWriter();
    StreamResult target = new StreamResult(writer);
    Transform(document, target);
    return writer.toString();
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
