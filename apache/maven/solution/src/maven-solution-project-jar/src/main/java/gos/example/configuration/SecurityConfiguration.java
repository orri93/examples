package gos.example.configuration;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;

@EnableWebSecurity
public class SecurityConfiguration extends WebSecurityConfigurerAdapter {
	@Autowired
	public void configureGlobal(AuthenticationManagerBuilder auth)
	    throws Exception {
		auth.inMemoryAuthentication().withUser("orri").password("Bios93")
		    .roles("ADMIN", "USER");
		auth.inMemoryAuthentication().withUser("sa").password("")
    .roles("ADMIN", "USER");
	}

	@Override
	protected void configure(HttpSecurity http) throws Exception {
		http.authorizeRequests().antMatchers("/").permitAll();
		http.authorizeRequests().antMatchers("/rest/**").permitAll();
		http.authorizeRequests().antMatchers("/imgs/**").permitAll();
		http.authorizeRequests().antMatchers("/admin/**").hasRole("ADMIN");
		http.authorizeRequests().antMatchers("/console/**").permitAll();
		http.authorizeRequests().antMatchers("/error/**").permitAll();

		// add this line to use H2 web console
		http.csrf().disable();
		http.headers().frameOptions().disable();
	}

}
