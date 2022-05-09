# How to Create Animated Plots in R
# https://towardsdatascience.com/how-to-create-animated-plots-in-r-adf53a775961
#

library(gapminder)  # Time Series Example Data set
library(ggplot2)
library(gganimate)  # Adds animation to plots
library(gifski)     # Renders animation as GIF files

gapminder

# Static Scatter Plot
ggplot(gapminder, aes(gdpPercap, lifeExp, size = pop, colour = country)) +
  geom_point(alpha = 0.7, show.legend = FALSE) +
  scale_colour_manual(values = country_colors) +
  scale_size(range = c(2, 12)) +
  scale_x_log10() +
  facet_wrap(~continent) +
  labs(title = 'Year: 1952-2007', x = 'GDP per capita', y = 'Life expectancy')

# Saving the Plot to File
ggsave('tmp/plot_gdpPercap_lifeExp_static.png', width=8, height=8)


# Animated Scatter Plot
p1 <- ggplot(gapminder, aes(gdpPercap, lifeExp, size = pop, colour = country)) +
  geom_point(alpha = 0.7, show.legend = FALSE) +
  scale_colour_manual(values = country_colors) +
  scale_size(range = c(2, 12)) +
  scale_x_log10() +
  facet_wrap(~continent) +
  # Animating the plot
  labs(title = 'Year: {frame_time}', x = 'GDP per capita', y = 'Life expectancy') +
  transition_time(year) +
  ease_aes('linear')
p1
animate(p1)
anim_save('tmp/plot_gdpPercap_lifeExp.gif')

