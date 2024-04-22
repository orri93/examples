# Example of using the gsignal package
# See https://cran.r-project.org/web/packages/gsignal/vignettes/gsignal.html
#


# ############################################################################
# 1. Introduction

## The package gsignal aims to further stimulate the use of R for signal processing tasks. It is ported from the Octave signal package
library(gsignal)


# ############################################################################
# 2. Signal generation and measurement

op <- par(mfrow = c(2, 2))

## Periodic rectangular pulse
t <- seq(0, 50, 1/1e3)
d <- cbind(seq(0, 60, 2), sin(2 * pi * 0.05 * seq(0, 60, 2)))
y <- pulstran(t, d, 'rectpuls')
plot(t, y, type = "l", xlab = "", ylab = "", main = "Periodic rectangular pulse")

## Assymetric sawtooth waveform
fs <- 1e3
t <- seq(0, 1, 1/fs)
d <- seq(0, 1, 1/3)
x <- tripuls(t, 0.2, -1)
y <- pulstran(t, d, x, fs)
plot(t, y, type = "l", xlab = "", ylab = "", main = "Asymmetric sawtooth ")

## Periodic Gaussian waveform
fs <- 1e7
tc <- 0.00025
t <- seq(-tc, tc, 1/fs)
x <- gauspuls(t, 10e3, 0.5)
ts <- seq(0, 0.025, 1/50e3)
d <- cbind(seq(0, 0.025, 1/1e3), sin(2 * pi * 0.1 * (0:25)))
y <- pulstran(ts, d, x, fs)
plot(ts, y, type = "l", xlab = "", ylab = "", main = "Gaussian pulse")

## Custom pulse trains
fnx <- function(x, fn) sin(2 * pi * fn * x) * exp(-fn * abs(x))
ffs <- 1000
tp <- seq(0, 1, 1 / ffs)
pp <- fnx(tp, 30)
fs <- 2e3
t <- seq(0, 1.2, 1 / fs)
d <- seq(0, 1, 1/3)
dd <- cbind(d, 4^-d)
z <- pulstran(t, dd, pp, ffs)
plot(t, z, type = "l", xlab = "", ylab = "", main = "Custom pulse")

## The function findpeaks can be used to determine (local) minima and maxima in a signal, as the following figures show.
par(op)
t <- 2 * pi * seq(0, 1,length = 1024)
y <- sin(3.14 * t) + 0.5 * cos(6.09 * t) + 0.1 * sin(10.11 * t + 1 / 6) + 0.1 * sin(15.3 * t + 1 / 3)
data1 <- abs(y) # Positive values
peaks1 <- findpeaks(data1)
data2 <- y # Double-sided
peaks2 <- findpeaks(data2, DoubleSided = TRUE)
peaks3 <- findpeaks (data2, DoubleSided = TRUE, MinPeakHeight = 0.5)

op <- par(mfrow=c(1,2))
plot(t, data1, type="l", xlab="", ylab="")
points(t[peaks1$loc], peaks1$pks, col = "red", pch = 1)
plot(t, data2, type = "l", xlab = "", ylab = "")
points(t[peaks2$loc], peaks2$pks, col = "red", pch = 1)
points(t[peaks3$loc], peaks3$pks, col = "red", pch = 4)
par (op)
title("Finding the peaks of smooth data is not a big deal")

##
t <- 2 * pi * seq(0, 1, length = 1024)
y <- sin(3.14 * t) + 0.5 * cos(6.09 * t) + 0.1 * sin(10.11 * t + 1 / 6) + 0.1 * sin(15.3 * t + 1 / 3)
data <- abs(y + 0.1*rnorm(length(y),1))   # Positive values + noise
peaks1 <- findpeaks(data, MinPeakHeight=1)
dt <- t[2]-t[1]
peaks2 <- findpeaks(data, MinPeakHeight=1, MinPeakDistance=round(0.5/dt))
op <- par(mfrow=c(1,2))
plot(t, data, type="l", xlab="", ylab="")
points (t[peaks1$loc],peaks1$pks,col="red", pch=1)
plot(t, data, type="l", xlab="", ylab="")
points (t[peaks2$loc],peaks2$pks,col="red", pch=1)
par (op)
title(paste("Noisy data may need tuning of the parameters.\n", "In the 2nd example, MinPeakDistance is used\n", "as a smoother of the peaks"))


# ############################################################################
# 3. Filter Design

## FIR filters

### FIR filter design by windowing

#### low-pass filter 10 Hz
fs = 256
h <- fir1(40, 10/ (fs / 2), "low")
freqz(h, fs = fs)

#### observe the effect of filter length
h <- fir1(80, 10/ (fs / 2), "low")
freqz(h, fs = fs)

#### fir2 allows specifying arbitrary frequency responses
f <- c(0, 0.3, 0.3, 0.6, 0.6, 1)
m <- c(0, 0, 1, 1/2, 0, 0)
fh <- freqz(fir2(100, f, m))
op <- par(mfrow = c(1, 2))
plot(f, m, type = "b", ylab = "magnitude", xlab = "Frequency")
lines(fh$w / pi, abs(fh$h), col = "blue")
legend("topright", legend = c("specified", "actual"), lty = 1, pch = c(1, NA), col = c("black", "blue"))
#### plot in dB:
plot(f, 20*log10(m+1e-5), type = "b", ylab = "dB", xlab = "Frequency")
lines(fh$w / pi, 20*log10(abs(fh$h)), col = "blue")
par(op)
title("specify arbitrary frequency responses with fir2")

## 


# ############################################################################
# 5. Power spectrum analysis

## The Fourier Transform 

op <- par(mfrow = c(3, 1))
fs <- 200
nsecs <- 10
lx <- fs * nsecs
t <- seq(0, nsecs, length.out =  lx)
#### signal of 5 Hz + 12 Hz + noise
x <- (sin(2 * pi * 5 * t) + sin(2 * pi * 12 * t) + runif(lx))
plot(t, x, type = "l", xlab = "Time (s)", ylab = "", main = "Original signal")
pw <- pwelch(x, window = lx, fs = fs, detrend = "none")
plot(pw, xlim = c(0, 20), main = "PSD estimate using FFT")

py <- pyulear(x, 30, fs = fs)
plot(py, xlim = c(0, 20), main = "PSD estimate using Yule-Walker")

## Welch’s method

op <- par(mfrow = c(3, 1))
fs <- 200
nsecs <- 100
lx <- fs * nsecs
t <- seq(0, nsecs, length.out =  lx)
# sine and cosine of signal of 5 Hz noise
x1 <- cos(2 * pi * 5 * t) + runif(lx)
x2 <- sin(2 * pi * 5 * t) + runif(lx)
x <- cbind(x1, x2)
pw <- pwelch(x, fs = fs)
plot(pw, plot.type = "spectrum", yscale = "dB", xlim = c(0, 50), main = "A sine and a cosine of 5 Hz have the same PSD")
legend("topright", legend = c("Cosine", "Sine"), lty = 1:2, col = 1:2)
rect(3, -35, 7, -4, border = "red", lwd = 3)
plot(pw, plot.type = "phase", xlim = c(0, 50), main = expression(bold(paste("but differ ", pi/2, " radians in phase at 5 Hz"))))
rect(3, -pi, 7, pi, border = "red", lwd = 3)
plot(pw, plot.type = "coherence", xlim = c(0, 50), main = "leading to coherence ~ 1 at 5 Hz")
rect(3, 0, 7, 1, border = "red", lwd = 3)

## Time-frequency analysis

op <- par(mfrow = c(2, 1))

jet <- grDevices::colorRampPalette(c("#00007F", "blue", "#007FFF", "cyan", "#7FFF7F", "yellow", "#FF7F00", "red", "#7F0000"))
sp <- specgram(chirp(seq(0, 5, by = 1/8000), 200, 2, 500, "logarithmic"), fs = 8000)
plot(sp, col = jet(20))

c2w <- grDevices::colorRampPalette(colors = c("red", "white", "blue"))
plot(sp, col = c2w(50))
