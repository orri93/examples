package gos.example.project.web;

import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;

import gos.example.project.web.configuration.SpringConfiguration;

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