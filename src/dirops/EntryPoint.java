package dirops;

public class EntryPoint {
    public static void main (String[] args) {
        String filePath = "D:/Emulation/The Legend of Zelda Twilight Princess.iso";
        String directoryPath = "D:/Emulation";

        long fileSize = DirectoryOperator.getFileSize(filePath);
        long directorySize = DirectoryOperator.getDirectorySize(directoryPath);

        System.out.println(fileSize);
        System.out.println(directorySize);
    }
}
