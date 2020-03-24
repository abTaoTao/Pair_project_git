using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace PairUI
{
    static class Program
    {
        [DllImport("Dll1.dll", EntryPoint = "run2", CallingConvention = CallingConvention.Cdecl)]
        unsafe public static extern int Command();

        [DllImport("kernel32.dll")]
        static extern bool FreeConsole();
        [DllImport("kernel32.dll")]
        public static extern bool AllocConsole();
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            File.WriteAllText("command.pair", "intersect.exe");
            if (args.Length > 0)
            {
                foreach (string elm in args)
                {
                    File.AppendAllText("command.pair", " " + elm);
                }
                int sb = Command();
                if (sb < 0)
                {
                    string str;
                    switch (sb)
                    {
                        case -1:
                            str = "文件读入异常！";
                            break;
                        case -2:
                            str = "存在重合！";
                            break;
                        /*
                        case -3:
                            str = "射线之间存在重合！";
                            break;
                        case -4:
                            str = "直线与某条线存在重合！";
                            break;
                        case -5:
                            str = "圆与圆重合！";
                            break;
                        case -6:
                            str = "输入了两个重复的点！";
                            break;
                        case -7:
                            str = "坐标超出范围！";
                            break;
                        case -8:
                            str = "请保证圆的半径大于0！";
                            break;
                        case -9:
                            str = "输入图形信息时出错！";
                            break;
                        case -10:
                            str = "第一行不是一个正整数！";
                            break;
                        case -11:
                            str = "几何图形个数与输入个数不匹配！";
                            break;
                        case -12:
                            str = "存在多余的换行符！";
                            break;
                        case -13:
                            str = "命令行参数错误！";
                            break;
                        */
                        default:
                            str = "未知错误！";
                            break;
                    }
                    File.WriteAllText("error.txt", str);
                }
            } else
            {
                File.AppendAllText("command.pair", " -i lines.pair -o output.pair");
                Application.Run(new Form1());
            }
        }
    }
}
