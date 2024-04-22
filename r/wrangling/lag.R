# Example of using the lag function to calculate the difference between values
# between rows in a data frame
#

# Dependencies
library(tidyverse)

# using a example data set
exam <- cars

# Using lag to calcualte the difference between speed and dist between rows
exam <- exam %>% mutate(speed_diff = speed - lag(speed, default = speed[1]))
exam <- exam %>% mutate(dist_diff = dist - lag(dist, default = dist[1]))

# Calcualate the mean and the sd
dist_diff_mean <- mean(exam$dist_diff)
dist_diff_sd <- sd(exam$dist_diff)

# plot the difference
plot(exam$dist_diff)
