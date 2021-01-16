package laser.helios.jnihelios;

public class HeliosPoint {

    short x, y;
    byte r, g, b, intensity;
    private static int HELIOS_MIN  = 0;
    private static int HELIOS_MAX = 4095;
    
    public HeliosPoint() {
        this(0, 0, 0, 0, 0, 0);
    }
    
    public HeliosPoint(int x, int y, int r, int g, int b, int i) {
		this.x = (short) ensureRange(x, HELIOS_MIN, HELIOS_MAX); // Y is UP
		this.y = (short) ensureRange(y, HELIOS_MIN, HELIOS_MAX); 
		this.r = (byte) ensureRange(r, 0, 255);
		this.g = (byte) ensureRange(g, 0, 255);
		this.b = (byte) ensureRange(b, 0, 255);
		this.intensity = (byte) ensureRange(i, 0, 255);
    }
    
    public HeliosPoint(short x, short y, byte r, byte g, byte b, byte i) {
        this.x = x;
        this.y = y;
        this.r = r;
        this.g = g;
        this.b = b;
        this.intensity = i;
    }
    
    public static int ensureRange(int value, int min, int max) {
		return Math.min(Math.max(value, min), max);
	}
}