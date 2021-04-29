public class Server {
    public static void main(String[] args) {
        NativeMeth nm = new NativeMeth();
        System.out.println(nm.multiInputServer(new int[]{0, 0, 6, 6}, NativeMeth.MultiCircuitType.CIRC_WITHIN.ordinal()));
    }
}
