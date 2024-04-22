# Example of using the Fast Fourier Transform functionality
# See https://rpubs.com/raulvalerio/intro_fourier_in_R
#


# ############################################################################
# Chapter 2: Key Functions for FFT in R

# Example of using the fft() function
signal <-  c(10, 12, 15, 18, 21, 24, 27, 25, 22, 18, 15, 12)
fft_result <- fft(signal)
print(fft_result)

# Visualization
par(mfrow = c(2, 1))
plot(signal, type = "l", main = "Original Signal")
plot(Mod(fft_result), type = "l", main = "FFT Magnitudes")


# ############################################################################
# Chapter 3: Analyzing a Sine Wave with FFT

# Analyzing a sine wave using FFT

period <- 4  ## that is freq is 1/4

time <- seq(0, 10, by = 0.1)
sine_wave <- sin(2 * pi * time / period)

## Apply fft function
fft_result <- fft(sine_wave)

# Visualization
par(mfrow = c(2, 1))
plot(time, sine_wave, type = "l", main = "Original Sine Wave")
plot(Mod(fft_result), type = "l", main = "FFT Magnitudes")

magnitudes<- abs(fft_result)  ## or mod()

# Find the frequency with the largest amplitude
max_index_sine <- which.max(magnitudes)

paste("magnitude value: ", magnitudes[max_index_sine] )

paste("index position: ",max_index_sine)


# ############################################################################
# Experimental

# Dependencies
library(tidyverse)

fs <- 200
nsecs <- 10
lx <- fs * nsecs
t <- seq(0, nsecs, length.out =  lx)
#### signal of 5 Hz + 12 Hz + noise
x <- (sin(2 * pi * 5 * t) + sin(2 * pi * 12 * t) + runif(lx))
fftres <- fft(x)

res <- data.frame(t)
res <- res %>% mutate(f = 1/t)
res <- cbind(res, fftres)
