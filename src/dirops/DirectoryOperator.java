package dirops;

public class DirectoryOperator {

    private static native long vbrGetFileSize(String filePath);
    private static native long vbrGetDirectorySize(String filePath);

    static {
        try {
            System.load("C:\\dev\\dirops\\MSRDirOps\\x64\\Debug\\MSRDirOpsInterface.dll");
        } catch (UnsatisfiedLinkError ule) {
            throw new IllegalStateException(ule);
        }
    }

    public static long getFileSize(String filePath) {
        return vbrGetFileSize(filePath);
    }

    public static long getDirectorySize(String filePath) {
        return vbrGetDirectorySize(filePath);
    }
}
