/**
 * Runs all threads
 */

public class BridgeRunner {

	public static void main(String[] args) {

		int limit, numcars;

		// Check command line inputs
		// Make sure there are only 2 inputs
		if (args.length != 2) {
			System.out.println("Usage: java BridgeRunner <bridge limit> <num cars>");
			return;
		}
		// Make sure both are integers
		try {
			limit = Integer.parseInt(args[0]);
			numcars = Integer.parseInt(args[1]);
		} catch (Exception e) {
			System.out.println("Usage: java BridgeRunner <bridge limit> <num cars>");
			return;
		}

		// Do not allow a bridge limit <= 0
		if (limit <= 0) {
			System.out.println("Bridge must allow at least one car");
			System.out.println("Usage: java BridgeRunner <bridge limit> <num cars>");
			return;
		}

		// Do not allow negative number of cars
		if (numcars < 0) {
			System.out.println("Number of cars must be >= 0");
			System.out.println("Usage: java BridgeRunner <bridge limit> <num cars>");
			return;
		}

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