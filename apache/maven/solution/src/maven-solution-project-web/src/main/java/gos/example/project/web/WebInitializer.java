package gos.example.project.web;

import javax.servlet.Filter;
import org.springframework.orm.jpa.support.OpenEntityManagerInViewFilter;
import org.springframework.web.servlet.support.AbstractAnnotationConfigDispatcherServletInitializer;

import gos.example.project.web.configuration.SpringConfiguration;

public class WebInitializer
    extends AbstractAnnotationConfigDispatcherServletInitializer {

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
		return new String[] { "/providerservice/*" };
	}

	/*
	 * Also we have registered OpenEntityManagerInViewFilter to enable lazy
	 * loading of JPA entity graphs in view rendering phase
	 */
	@Override
	protected Filter[] getServletFilters() {
		return new Filter[] { new OpenEntityManagerInViewFilter() };
	}

}