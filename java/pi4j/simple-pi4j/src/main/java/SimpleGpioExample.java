import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.Pin;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;

public class SimpleGpioExample {

	public static void main(String args[]) throws Exception {

		System.out.println("<--Pi4J--> Simple Example ... started.");

		// Create gpio controller
		final GpioController gpio = GpioFactory.getInstance();
		
		Pin led = RaspiPin.GPIO_04;

		GpioPinDigitalOutput output =
				gpio.provisionDigitalOutputPin(led, "Led", PinState.LOW);

		
		
		// Keep this sample program running for 10 minutes
		for (int count = 0; count < 600; count++) {
			Thread.sleep(1000);
		}

		// When your program is finished, make sure to stop all GPIO
		// activity/threads by shutting
		// down the GPIO controller (this method will forcefully shutdown all GPIO
		// monitoring threads
		// and background scheduled tasks)
		gpio.shutdown();

		System.out.println("Exiting MCP3208GpioExample");
	}
}
