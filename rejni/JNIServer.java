public class JNIServer {

    static {
        System.loadLibrary("JNIServer");
    }

    public native void testMethod(int a);

    public static void main(String[] args) {
        new JNIClient().testMethod(5);
        System.out.println("Done");
    }
}
