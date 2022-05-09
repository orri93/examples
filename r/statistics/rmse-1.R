# Root Mean Squared Error
# https://www.rdocumentation.org/packages/Metrics/versions/0.1.4/topics/rmse
#
library(Metrics)

actual <- c(1.1, 1.9, 3.0, 4.4, 5.0, 5.6)
predicted <- c(0.9, 1.8, 2.5, 4.5, 5.0, 6.2)
rmse(actual, predicted)
