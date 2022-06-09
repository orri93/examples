# Data Reshape example including Melting data
# https://www.statmethods.net/management/reshape.html
# https://r-lang.com/how-to-append-data-frames-in-r/
#

# Dependencies
library(reshape2)
library(ggplot2)

# Create the data
d1 <- data.frame(
  time = c(1, 2, 3, 4, 5),
  a1 = c( 0, 2, 4,  6, 8),
  b1 = c(NA, 4, 2, NA, 8),
  c1 = c( 3, 5, 7,  3, 5))
d2 <- data.frame(
  time = c(1, 2, 3, 4, 5),
  a2 = c( 9, 5, 4,  2, 3),
  b2 = c(NA, 3, 4,  3, 5),
  c2 = c( 3, 5, 7, NA, 2))

# Melt the data
m1 <- melt(d1, id="time", na.rm=TRUE)
m2 <- melt(d2, id="time", na.rm=TRUE)

# Combine the data
c <- rbind(m1, m2)

# Plot the data
ggplot(data = c, mapping = aes(x = time, y = value, color = variable)) + geom_point() + theme_light()

# Example of cassting the data
u <- dcast(c, time~variable, mean)
u
