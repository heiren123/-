
//#include "iostream.h"
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.IO.Ports;//用到了串口
using System.Linq;
 
namespace W5500_Smart_Home_System
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private SerialPort comm = new SerialPort();
        private bool Listening = false;//是否没有执行完invoke相关操作
        private bool Closing = false;//是否正在关闭串口，执行Application.DoEvents，并阻止再次invoke
        private StringBuilder builder = new StringBuilder();//避免在事件处理方法中反复的创建，定义到外面
        private long received_count = 0;//接收计数
        private long send_count = 0;//发送计数 

        bool seriaport_open = false; //串口是否打开

        private bool SerialPort_Open() //打开串口函数,成功返回true，失败返回false
        {
            //根据当前串口对象，来判断操作
            if (comm.IsOpen)
            {
                Closing = true;
                while (Listening) Application.DoEvents();
                //打开时点击，则关闭串口
                comm.Close();
                return false;
            }
            else
            {
                //关闭时点击，则设置好端口，波特率后打开
                comm.PortName = comboBox1.Text;
                comm.BaudRate = Convert.ToInt32(comboBox2.Text.Trim());//从comboBox2获得波特率
                try
                {
                    comm.Open();
                    return true;
                }
                catch (Exception ex)
                {
                    //捕获到异常信息，创建一个新的comm对象，之前的不能用了
                    comm = new SerialPort();
                    //现实异常信息给客户(一般为串口被占用了)
                    MessageBox.Show(ex.Message);
                    return false;
                }
            }
        }

        private void SerialPort_Close() //关闭串口函数
        {
            comm.Close();
        }

        void comm_DataSend(string s) //串口发送数据函数
        {
            comm.WriteLine(s);
        }

        void comm_DataReceived(object sender, SerialDataReceivedEventArgs e) //串口DataReceived事件
        {
            if (Closing) return;//如果正在关闭，忽略操作，直接返回，尽快的完成串口监听线程的一次循环
            try
            {
                Listening = true;//设置标记，说明我已经开始处理数据，一会儿要使用系统UI的。
                int n = comm.BytesToRead;//先记录下来，避免某种原因，人为的原因，操作几次之间时间长，缓存不一致
                byte[] buf = new byte[n];//声明一个临时数组存储当前来的串口数据
                received_count += n;//增加接收计数
                comm.Read(buf, 0, n);//读取缓冲数据
                builder.Clear();//清除字符串构造器的内容
                //因为要访问ui资源，所以需要使用invoke方式同步ui。
                this.Invoke((EventHandler)(delegate
                {
                    //判断是否是显示为16进制
                    if (false)
                    {
                        //依次的拼接出16进制字符串
                        foreach (byte b in buf)
                        {
                            builder.Append(b.ToString("X2") + " ");
                        }
                    }
                    else
                    {
                        //直接按ASCII规则转换成字符串
                        // builder.Append(Encoding.Default.GetString(buf));
                        builder.Append(buf.ToString());
                    }
                    //追加的形式添加到文本框末端，并滚动到最后。
                    //this.txGet.AppendText(builder.ToString());
                    this.richTextBox1.AppendText(builder.ToString()+"\n");
                    // MessageBox.Show("串口读取数据："+builder.ToString());
                    //修改接收计数
                    //labelGetCount.Text = "Get:" + received_count.ToString();
                    

                    //拆分字符串
                    /*
                    String str = builder.ToString();
                    String[] strnew = str.Split( ',');
                   //温度显示
                    this.textBox1.Text = Convert.ToInt32(strnew[2].ToString(), 16).ToString() +"."+ Convert.ToInt32(strnew[3].ToString(), 16).ToString();
                    //湿度显示
                    this.textBox2.Text = Convert.ToInt32(strnew[4].ToString(), 16).ToString() + "." + Convert.ToInt32(strnew[5].ToString(), 16).ToString();
                    //co
                    this.textBox3.Text = (Convert.ToInt32(strnew[6].ToString(), 16)*256+ Convert.ToInt32(strnew[7].ToString(), 16)).ToString();
                    //PM
                    double pm = Convert.ToInt32(strnew[8].ToString(), 16) * 256 + Convert.ToInt32(strnew[9].ToString(), 16);
                this.textBox4.Text = pm.ToString();

                    // double pm = Double.Parse(builder.ToString());
                    //this.textBox4.Text = builder.ToString();
                    if (pm > 300)
                    {
                        pictureBox1.BackColor = Color.Magenta;
                         this.textBox5.Text = "六级";
                         this.textBox6.Text = "严重污染";
                    }
                    else if (pm > 200)
                    {
                        pictureBox1.BackColor = Color.Purple;
                        this.textBox5.Text = "五级";
                        this.textBox6.Text = "重度污染";
                    }
                    else if (pm > 150)
                    {
                        pictureBox1.BackColor = Color.Red;
                        this.textBox5.Text = "四级";
                        this.textBox6.Text = "中度污染";
                    }
                    else if (pm > 100)
                    {
                        pictureBox1.BackColor = Color.Orange;
                        this.textBox5.Text = "三级";
                        this.textBox6.Text = "轻度污染";
                    }
                    else if (pm > 50)
                    {
                        pictureBox1.BackColor = Color.Yellow;
                        this.textBox5.Text = "二级";
                        this.textBox6.Text = "良";
                    }
                    else if (pm > 0)
                    {
                        pictureBox1.BackColor = Color.Green;
                        this.textBox5.Text = "一级";
                        this.textBox6.Text = "优";
                    }
                    else
                    {
                        MessageBox.Show("PM2.5数据出现错误"+pm);
                    }
                    */

                   
                }));
            }
            finally
            {
                Listening = false;//我用完了，ui可以关闭串口了。
            }
        }
        private void button1_Click(object sender, EventArgs e)//打开串口按钮
        {
            if (comboBox1.Text == "")
            {
                MessageBox.Show("请选择串口号");
            }
            else
            {
                if (seriaport_open == false)
                {
                    //打开串口操作
                    if (SerialPort_Open()) //如果串口打开成功
                    {
                        seriaport_open = true;
                        pictureBox_seriaport.BackColor = Color.Red;
                        button1.Text = "关闭串口";
                    }
                }
                else
                {
                    //关闭串口操作
                    SerialPort_Close();//关闭串口函数
                    seriaport_open = false;
                    pictureBox_seriaport.BackColor = Color.White;
                    button1.Text = "打开串口";
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)//窗体加载函数
        {
            //初始化下拉串口名称列表框
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            comboBox1.Items.AddRange(ports);
            //初始化SerialPort对象
            comm.NewLine = "\r\n";
            comm.RtsEnable = true;//根据实际情况吧
            //添加串口DataReceived事件注册
            comm.DataReceived += comm_DataReceived;
        }        

     
        
        private void button4_Click(object sender, EventArgs e)//清空显示
        {
            richTextBox1.Text = "";
        }

        private void button2_Click(object sender, EventArgs e)//手动发送字符串
        {
            if (seriaport_open == true)//串口已经打开
            {
                if (textBox7.Text.Trim() == "")
                {
                    MessageBox.Show("字符串不能为空");
                    textBox7.Focus();
                }
                else
                {
                    comm_DataSend(textBox7.Text.Trim());
                    //System.Threading.Thread.Sleep(180);
                }
            }
            else
            {
                MessageBox.Show("请先打开串口");
            }

        }

        private void groupBox4_Enter(object sender, EventArgs e)
        {

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }
    }
}
