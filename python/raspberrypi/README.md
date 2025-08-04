# Example of Raspberry Pi GPIO Control with Python

This project demonstrates how to control GPIO pins on a Raspberry Pi using Python. It includes examples for reading from and writing to GPIO pins.

## Python Environment

Create the Virtual Environment

```bash
python -m venv venv
```

Activate the Virtual Environment

```bash
source venv/bin/activate
```

Install the Requirements

```bash
pip install -r requirements.txt
```

## Example 1: Push Button and LEDs (example1.py)

This script reads a momentary push-button on GPIO D17 and controls three LEDs on GPIO D5, D6, and D13 using Adafruit Blinka and CircuitPython libraries.

### Wiring

* **Button**

  * One leg → GPIO D17
  * Other leg → GND
  * Uses internal pull-up resistor (enabled in code)
* **LEDs** (use a 330 Ω resistor in series with each LED)

  * LED 1: GPIO D5  → resistor → LED → GND
  * LED 2: GPIO D6  → resistor → LED → GND
  * LED 3: GPIO D13 → resistor → LED → GND

### Requirements

Ensure `adafruit-blinka` is installed. You can add it to your `requirements.txt` or install directly:

```bash
pip install adafruit-blinka
```

### Running the Example

1. Activate your virtual environment if not already active.
2. Install dependencies:

   ```bash
   pip install adafruit-blinka
   ```
3. Execute the script:

   ```bash
   python example1.py
   ```

When the button on GPIO D4 is pressed, all three LEDs will turn on. Release the button to turn them off.
