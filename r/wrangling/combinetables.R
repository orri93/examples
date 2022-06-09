# Example of Combining tables
#

# Dependencies
library(data.table)
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

# Convert Data Frames to Data Tables
setDT(d1)
setDT(d2)

# Set a Data Table Keys
setkey(d1, time)
setkey(d2, time)

# Combine the data tables
c <- d1[d2, roll="nearest"]
