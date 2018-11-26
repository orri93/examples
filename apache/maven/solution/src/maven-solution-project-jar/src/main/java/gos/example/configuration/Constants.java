package gos.example.configuration;

import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;

public class Constants {

  public static final String RootPath = "/gos-example-web";
  public static final String ServletMappings = RootPath + "/*";
  
  public static final String RestContextPath = "/rest";
  public static final String RestApiContextPath = "/api";  

  public static final String RestMatch = "/**";
  public static final String[] RestPathList = new String[] {
      RootPath + RestContextPath,
      RootPath + RestApiContextPath };

  public static final String ResourceMatch = "/**";
  public static final String[] ResourcePathList = new String[] {
      RootPath + "/imgs", RootPath + "/admin", RootPath + "/console",
      RootPath + "/error" };

  public static final String AdminMatch = "/**";
  public static final String AdminRole = "ADMIN";
  public static final String[] AdminPathList = new String[] {
      RootPath + "/admin" };

  public static void DevelopmentAuthentication(
      AuthenticationManagerBuilder builder) throws Exception {
    builder.inMemoryAuthentication().withUser("orri").password("Bios93")
        .roles("ADMIN", "USER");
    builder.inMemoryAuthentication().withUser("sa").password("").roles("ADMIN",
        "USER");
  }
}
 