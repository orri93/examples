import board
import digitalio
import time

# ——— Setup ———

# Button on D4 with pull-up
button = digitalio.DigitalInOut(board.D17)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

# LEDs on D5, D6, D7 as outputs
led_pins = [board.D5, board.D6, board.D13]
leds = []
for pin in led_pins:
  led = digitalio.DigitalInOut(pin)
  led.direction = digitalio.Direction.OUTPUT
  leds.append(led)

# ——— Main Loop ———

while True:
  # button.value == False when pressed (pulled LOW)
  if not button.value:
    print ("Turn on")
    # Turn all LEDs on
    for led in leds:
      led.value = True
  else:
    print ("Turn off")
    # Turn all LEDs off
    for led in leds:
      led.value = False

  # small debounce delay
  time.sleep(0.05)
