/**
 * JNITest
 */
public class JNITest {
    public native boolean testMethod(int a, int b);

    public static void main(String[] args) {
        System.loadLibrary("jnitest");
        System.out.println(new JNITest().testMethod(1, 0) ? "True" : "False");
    }
}