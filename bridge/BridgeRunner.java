/**
 * Runs all threads
 */

public class BridgeRunner {

	public static void main(String[] args) {

		// TODO - check command line inputs
		// TODO - for now, hardwire
		int numcars = 1;
		int limit = 0;

		// Instantiate the bridge
		Bridge bridge = new OneLaneBridge(limit);

		// Allocate space for threads
		Thread[] cars = new Thread[numcars];

		// Start the threads
		for (int i = 0; i < numcars; i++) {
			cars[i] = new Thread(new Car(i, bridge));
			cars[i].start();
		}

		// Join the car threads
		for (int i = 0; i < numcars; i++) {
			try {
				cars[i].join();
			} catch (InterruptedException e) {
			}
		}

		System.out.println("All cars have crossed!!");
	}

}