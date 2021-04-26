public class JNIClient {

    static{
        System.loadLibrary("JNIClient");
    }

    public native void testMethod(int a);

    public static void main(String[] args) {
        new JNIClient().testMethod(5);
        System.out.println("Done");
    }
}
