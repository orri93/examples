package gos.examples.xsd.forms;

import gos.examples.xsd.forms.configuration.SpringConfiguration;
import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;

public class WebInitializer extends AbstractAnnotationConfigDispatcherServletInitializer {

	@Override
	protected Class<?>[] getRootConfigClasses() {
	  return new Class[] { SpringConfiguration.class };
	}

	@Override
	protected Class<?>[] getServletConfigClasses() {
	  return null;
	}

	@Override
	protected String[] getServletMappings() {
	  return new String[] { "/" };
	}
}