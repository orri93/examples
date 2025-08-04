import board
import digitalio
import time

# Button with pull-up
button = digitalio.DigitalInOut(board.D4)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

# A Led as output
led = digitalio.DigitalInOut(board.D5)
led.direction = digitalio.Direction.OUTPUT

button_state = False

# Main Loop
while True:
  if not button.value:  # Button pressed
    if not button_state:  # Check for state change
      button_state = True
      print("Button pressed!")
      led.value = True  # Turn LED on
  else:
    if button_state:
      button_state = False
      print("Button released!")
      led.value = False

  time.sleep(0.05)  # Small debounce delay
