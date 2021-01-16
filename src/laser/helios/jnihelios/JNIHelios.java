
package laser.helios.jnihelios;

public class JNIHelios {

    static {
//    	  try {
//    		  String path = "/Users/jennadeboisblanc/Projects/laser/processing_laser/src/laser/helios/jnihelios/libjnihelios.dylib";
//    		  System.load(path);
//    	    } catch (UnsatisfiedLinkError e) {
//    	      System.err.println("Native code library failed to load.\n" + e);
//    	      System.exit(1);
//    	    }
        System.loadLibrary("jnihelios");
    }

    HeliosPoint[][] bufferPoints;
    
    private static int NUM_FRAMES = 30;
    private static int MAX_BUFFER_SIZE = 1000;
    private static int HELIOS_MIN  = 0;
    private static int HELIOS_MAX = 4095;
    private static int HELIOS_PPS = 30000;
    private static byte HELIOS_FLAGS_DEFAULT = 0;
    
    
    private int numDevs = 0;
    private int currentIndex = 0;
	private long nativeObjectPointer;

	
	// Our constructor. The nativeNew() method is called to allocate a new
	// instance of our native object and return its address. The address is
	// assigned to nativeObjectPointer. Just as a note, Java forbids
	// native constructors, so we need a native method to allocate our
	// native object.
	public JNIHelios() {
		nativeObjectPointer = nativeNew();
		bufferPoints = new HeliosPoint[NUM_FRAMES][MAX_BUFFER_SIZE];
		setTestBuffer();
	}
	
	// public static void main(String[] args) {
	// 	JNIHelios helios = new JNIHelios();
	// 	helios.testLaser();
	// }

	
	public void start() {
		numDevs = OpenDevices();
		System.out.println(numDevs + " device(s) found; starting laser(s)");
	}
	
	public void stop() {
		numDevs = 0;
		CloseDevices();
	}
	
	
	public void resetBuffer() {
		for (int j = 0; j < NUM_FRAMES; j++) {
			for (int i = 0; i < MAX_BUFFER_SIZE; i++) {
				bufferPoints[j][i] = new HeliosPoint();
			}
		}
	}
	
	public void setTestBuffer() {
		for (int f = 0; f < NUM_FRAMES; f++) {
			int y = f * HELIOS_MAX / 30;
			int x = 0;
			for (int i = 0; i < MAX_BUFFER_SIZE; i++) {
				if (i < 500)
					x = i * HELIOS_MAX / 500;
				else
					x = HELIOS_MAX - ((i - 500) * HELIOS_MAX / 500);

				addPoint(f, x, y, 150, 255, 150, 255);
			}
		}
	}
	
	public void testLaser() {
		start();
		int i = 0;
		while (true) {
			i++;
			if (i > 20*30) //cancel after 5 cycles, 30 frames each
				break;

			for (int device = 0; device < numDevs; device++)
			{
				//wait for ready status
				for (int k = 0; k < 512; k++)
				{
					if (GetStatus(device) == 1)
						break;
				}
				WriteFrame(device, HELIOS_PPS, HELIOS_FLAGS_DEFAULT, bufferPoints[i % 30], MAX_BUFFER_SIZE); //send the next frame
			}
		}

		//freeing connection
		stop();
	}
	
	public void addPoint(int frame, int x, int y, int r, int g, int b, int intensity) {
		int xmap = (int) mapRange(x, 0, 800, HELIOS_MIN, HELIOS_MAX);
		int ymap = (int) mapRange(y, 800, 0, HELIOS_MIN, HELIOS_MAX);
		bufferPoints[frame][currentIndex] = new HeliosPoint(xmap, ymap, r, g, b, intensity);
		currentIndex++;
		currentIndex %= MAX_BUFFER_SIZE;
	}

	
	public static int ensureRange(int value, int min, int max) {
		return Math.min(Math.max(value, min), max);
	}
	
	public static double mapRange(double input, double input_start, double input_end, double output_start, double output_end) {
		return output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
	}

	// This method is used to allocate an instance of this class at native
	// world and return the address of it.
	private native long nativeNew();
    
    // Declare a native method sayHello() that receives no arguments and returns void
    private native void sayHello();

	//initializes drivers, opens connection to all devices.
	//Returns number of available devices.
	//NB: To re-scan for newly connected DACs after this function has once been called before, you must first call CloseDevices()
	private native int OpenDevices();

	//closes and frees all devices
	private native int CloseDevices();

	//writes and outputs a frame to the speficied dac
	//devNum: dac number (0 to n where n+1 is the return value from OpenDevices() )
	//pps: rate of output in points per second
	//flags: (default is 0)
	//	Bit 0 (LSB) = if 1, start output immediately, instead of waiting for current frame (if there is one) to finish playing
	//	Bit 1 = if 1, play frame only once, instead of repeating until another frame is written
	//  Bit 2 = if 1, don't let WriteFrame() block execution while waiting for the transfer to finish 
	//			(NB: then the function might return 1 even if it fails)
	//	Bit 3-7 = reserved
	//points: pointer to point data. See point structure declaration earlier in this document
	//numOfPoints: number of points in the frame
	private native int WriteFrame(int devNum, int pps, byte flags, HeliosPoint[] points, int numOfPoints);

	//Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it is not
	private native int GetStatus(int devNum);

	//Returns firmware version of DAC
	private native int GetFirmwareVersion(int devNum);

	//Gets name of DAC (populates name with max 32 characters)
	private native int GetName(int devNum, String name);

	//Sets name of DAC (name must be max 31 characters incl. null terminator)
	private native int SetName(int devNum, String name);

	//Stops output of DAC until new frame is written (NB: blocks for 100ms)
	private native int Stop(int devNum);

	//Sets shutter level of DAC

}

