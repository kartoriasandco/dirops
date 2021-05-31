using System;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

[assembly: ComVisible(true)]
[assembly: AssemblyDelaySign(false)]
[assembly: AssemblyKeyFile("DirOpsKeyPair.snk")]
namespace MSRDirOps
{
    [Guid("34B32470-4C35-4A0A-B42B-931A2D6180E5")]
    [ComVisible(true)]
    public interface IDirOps
    {
        double getFileSize(string filePath);
        double getDirectorySize(string filePath);
    }

    [Guid("FF06507E-6A0D-482F-96D8-3A4A696248E3")]
    [ClassInterface(ClassInterfaceType.None)]
    [ComSourceInterfaces(typeof(IDirOps))]
    [ComVisible(true)]
    public class DirOps:IDirOps
    {
        private Scripting.FileSystemObject fso;

        public DirOps()
        {
            fso = new Scripting.FileSystemObject();
        }

        public double getFileSize(string filePath)
        {
            Scripting.File file = fso.GetFile(filePath);
            Int64 fileSize = (Int64)file.Size;
            double dFileSize = BitConverter.Int64BitsToDouble(fileSize);
            return dFileSize;
        }

        public double getDirectorySize(string filePath)
        {
            Scripting.Folder folder = fso.GetFolder(filePath);
            Int64 folderSize = (Int64)folder.Size;
            double dFolderSize = BitConverter.Int64BitsToDouble(folderSize);
            return dFolderSize;
        }
    }
}
