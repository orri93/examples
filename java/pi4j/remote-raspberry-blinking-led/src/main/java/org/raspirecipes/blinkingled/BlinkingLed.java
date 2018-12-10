package org.raspirecipes.blinkingled;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.RaspiPin;

public class BlinkingLed {
  public static void main( String[] args ) throws InterruptedException
  {
      GpioController gpio = GpioFactory.getInstance();
      GpioPinDigitalOutput pin0 =
      		gpio.provisionDigitalOutputPin(RaspiPin.GPIO_05);
      boolean ledOn = true;
      for(int i = 0; i < 10; i++) {
           pin0.setState(ledOn);
           ledOn = !ledOn;
           Thread.sleep(1000);
      }
  }
}
