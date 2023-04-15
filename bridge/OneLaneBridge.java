
/**
 * The OneLaneBridge class, for instantiating the bridge
 * 
 * @author Penny Rowe
 */
public class OneLaneBridge extends Bridge {
    private Object drive = new Object(); // condition variable
    private int limit;

    /**
     * The child class constructor will take the input limit,
     * so we know how many cars are allowed on the bridge
     * 
     * @param input Maximum number of cars allowed on the bridge
     */
    OneLaneBridge(int limit) {
        super();
        this.limit = limit;
        this.currentTime = 1;
    }

    public void arrive(Car car) {
        // lock on drive condition variable
        synchronized (drive) {

            // If the car is going in the wrong direction, it must wait, and
            // if there are already the limit of cars on the bridge, this car must wait
            while (car.getDirection() != direction || bridge.size() >= limit) {
                // If the bridge is empty, flip bridge direction to direction of this car
                if (bridge.size() == 0) {
                    direction = car.getDirection();
                } else {
                    try {
                        drive.wait(); // unlock drive and wait (atomically!)
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

            // Let this car on the bridge:
            // 1) Use the car’s setEntryTime(currentTime) method to set the entry time.
            // 2) Add the car to the bridge list.
            // 3) Print bridge list to see that there are no more than 3 cars on the bridge.
            // 4) Increment currentTime by 1.
            car.setEntryTime(this.currentTime);
            bridge.add(car);
            System.out.println("Bridge (dir=" + direction + "): " + bridge);
            this.currentTime += 1;

        }
    }

    /**
     * Allow cars to exit the bridge if they are on the bridge
     * and if they are the first car in line.
     * 
     * @param car Instance of a car, which may be on the bridge
     */
    public void exit(Car car) {
        // lock on drive condition variable
        synchronized (drive) {
            while (bridge.get(0) != car) {
                try {
                    drive.wait(); // unlock drive and wait (atomically!)
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            // Car exits the bridge:
            // 1) remove the car from the list.
            // 2) print the bridge list to show one fewer car and car that left was at head
            // 3) signal to other cars that might be waiting to get on the bridge.
            bridge.remove(0);
            System.out.println("Bridge (dir=" + direction + "): " + bridge);
            drive.notifyAll();
        }
    }

    /**
     * @return the current direction cars can go on the bridge
     */
    // public boolean getDirection() {
    // return direction;
    // }

    /**
     * Flip the bridge direction
     */
    public void flipDirection() {
        direction = !direction;
    }

}