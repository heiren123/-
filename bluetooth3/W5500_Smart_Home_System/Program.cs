using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace W5500_Smart_Home_System
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            if(DateTime.Now.Year > 2017||DateTime.Now.Month>11){
                MessageBox.Show("该软件已经超过期限，请联系管理员解锁！QQ:1364474738");
                System.Environment.Exit(0);
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
