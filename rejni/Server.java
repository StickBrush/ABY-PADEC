public class Server {
    public static void main(String[] args) {
        NativeMeth nm = new NativeMeth();
        System.out.println(nm.singleInputServer(120, NativeMeth.SingleCircuitType.CIRC_EQUAL.ordinal()));
    }
}
