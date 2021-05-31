package dirops;

public class DirectoryOperator {

    private native long getFileSize(String filePath);
    private native long getDirectorySize(String filePath);
}
