package gos.example.configuration;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.builders.WebSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;

@EnableWebSecurity
public class SecurityConfiguration extends WebSecurityConfigurerAdapter {

  @Autowired
  public void configureGlobal(AuthenticationManagerBuilder auth)
      throws Exception {
    Constants.DevelopmentAuthentication(auth);
  }
  
  /*
  @Override
  public void configure(WebSecurity web) throws Exception {
    //web.ignoring().antMatchers("/")
    web.ignoring().antMatchers("/rest/form/css/**");
    web.ignoring().antMatchers("/rest/form/css/**");
    web.ignoring().antMatchers("/rest/form/js/**");
    web.ignoring().antMatchers("/rest/css/**");
    web.ignoring().antMatchers("/rest/js/**");
    web.ignoring().antMatchers("/form/css/**");
    web.ignoring().antMatchers("/form/js/**");
    web.ignoring().antMatchers("/static/css/**");
    web.ignoring().antMatchers("/static/js/**");
    web.ignoring().antMatchers("/css/**");
    web.ignoring().antMatchers("/js/**");
  }
  */

  @Override
  protected void configure(HttpSecurity http) throws Exception {
    
    http.authorizeRequests().antMatchers(Constants.RootPath).permitAll();
    
    //http.authorizeRequests().antMatchers("/rest/api/**").permitAll();
    //http.authorizeRequests().antMatchers("/rest/form/**").permitAll();
    //http.authorizeRequests().antMatchers("/rest/**").permitAll();
        
    http.authorizeRequests().antMatchers("/rest/form/css/**").permitAll();
    http.authorizeRequests().antMatchers("/rest/form/js/**").permitAll();
    http.authorizeRequests().antMatchers("/rest/css/**").permitAll();
    http.authorizeRequests().antMatchers("/rest/js/**").permitAll();
    http.authorizeRequests().antMatchers("/form/css/**").permitAll();
    http.authorizeRequests().antMatchers("/form/js/**").permitAll();
    http.authorizeRequests().antMatchers("/static/css/**").permitAll();
    http.authorizeRequests().antMatchers("/static/js/**").permitAll();
    http.authorizeRequests().antMatchers("/public/css/**").permitAll();
    http.authorizeRequests().antMatchers("/public/js/**").permitAll();
    http.authorizeRequests().antMatchers("/public/form-items/css/**").permitAll();
    http.authorizeRequests().antMatchers("/public/form-items/js/**").permitAll();
    http.authorizeRequests().antMatchers("/webapp/static/css/**").permitAll();
    http.authorizeRequests().antMatchers("/webapp/static/js/**").permitAll();
    http.authorizeRequests().antMatchers("/webapp/public/css/**").permitAll();
    http.authorizeRequests().antMatchers("/webapp/public/js/**").permitAll();
    http.authorizeRequests().antMatchers("/webapp/public/form-items/css/**").permitAll();
    http.authorizeRequests().antMatchers("/webapp/public/form-items/js/**").permitAll();
    //http.authorizeRequests().antMatchers("/css/**").permitAll();
    //http.authorizeRequests().antMatchers("/js/**").permitAll();

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
