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
    Constants.DevelopmentAuthentication(auth);
  }

  @Override
  protected void configure(HttpSecurity http) throws Exception {
    
    http.authorizeRequests().antMatchers(Constants.RootPath).permitAll();

    for (String path : Constants.RestPathList) {
      http.authorizeRequests().antMatchers(path + Constants.RestMatch)
          .permitAll();
    }

    for (String path : Constants.ResourcePathList) {
      http.authorizeRequests().antMatchers(path + Constants.ResourceMatch)
          .permitAll();
    }

    for (String path : Constants.AdminPathList) {
      http.authorizeRequests().antMatchers(path + Constants.AdminMatch)
          .hasRole(Constants.AdminRole);
    }

    // add this line to use H2 web console
    http.csrf().disable();
    http.headers().frameOptions().disable();
  }

}
