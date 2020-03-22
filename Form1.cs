using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Runtime.InteropServices;


namespace PairUI
{
    public partial class Form1 : Form
    {
        [DllImport("dll_Test.dll", EntryPoint = "solve", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Solve();
        public static bool IsNum(string value)
        {
            return Regex.IsMatch(value, @"^[+-]?(0|[1-9]\d*)$");
        }

        public Form1()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBox1.SelectedIndex)
            {

                case 0:
                    label6.Visible = true;
                    textBox4.Visible = true;
                    label3.Text = "第一个点坐标x1";
                    label4.Text = "第一个点坐标y1";
                    label5.Text = "第二个点坐标x2";
                    label6.Text = "第二个点坐标y2";
                    break;

                case 1:
                    label6.Visible = true;
                    textBox4.Visible = true;
                    label3.Text = "起点坐标x1";
                    label4.Text = "起点坐标y1";
                    label5.Text = "途径点坐标x2";
                    label6.Text = "途径点坐标y2";
                    break;

                case 2:
                    label6.Visible = true;
                    textBox4.Visible = true;
                    label3.Text = "第一个点坐标x1";
                    label4.Text = "第一个点坐标y1";
                    label5.Text = "第二个点坐标x2";
                    label6.Text = "第二个点坐标y2";
                    break;

                case 3:
                    label6.Visible = false;
                    textBox4.Visible = false;
                    textBox4.Text = "";
                    label3.Text = "圆心坐标x";
                    label4.Text = "圆心坐标y";
                    label5.Text = "圆的半径r";
                    break;

            }
        }

        private void listBox1_add_dup(string text)
        {
            bool dup = false;
            if (listBox1.Items.Count > 0)
            {
                foreach (string elm in listBox1.Items)
                {
                    if (elm == text)
                    {
                        MessageBox.Show("不能添加完全相同的几何图形！", "错误");
                        dup = true;
                        break;
                    }
                }
            }
            if (!dup)
            {
                listBox1.Items.Add(text);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            switch (comboBox1.SelectedIndex)
            {
                case 0:
                    if (IsNum(textBox1.Text) && IsNum(textBox2.Text) && IsNum(textBox3.Text) && IsNum(textBox4.Text))
                    {
                        listBox1_add_dup("L " + textBox1.Text + " " + textBox2.Text + " " + textBox3.Text + " " + textBox4.Text);
                    }
                    else
                    {
                        MessageBox.Show("输入的几何图形参数非法！\n输入必须是没有前导0的整数，可以有正负号。\n", "输入错误");
                    }
                    break;
                case 1:
                    if (IsNum(textBox1.Text) && IsNum(textBox2.Text) && IsNum(textBox3.Text) && IsNum(textBox4.Text))
                    {
                        listBox1_add_dup("R " + textBox1.Text + " " + textBox2.Text + " " + textBox3.Text + " " + textBox4.Text);
                    }
                    else
                    {
                        MessageBox.Show("输入的几何图形参数非法！\n输入必须是没有前导0的整数，可以有正负号。\n", "输入错误");
                    }
                    break;
                case 2:
                    if (IsNum(textBox1.Text) && IsNum(textBox2.Text) && IsNum(textBox3.Text) && IsNum(textBox4.Text))
                    {
                        listBox1_add_dup("S " + textBox1.Text + " " + textBox2.Text + " " + textBox3.Text + " " + textBox4.Text);
                    }
                    else
                    {
                        MessageBox.Show("输入的几何图形参数非法！\n输入必须是没有前导0的整数，可以有正负号。\n", "输入错误");
                    }
                    break;
                case 3:
                    if (IsNum(textBox1.Text) && IsNum(textBox2.Text) && IsNum(textBox3.Text))
                    {
                        listBox1_add_dup("C " + textBox1.Text + " " + textBox2.Text + " " + textBox3.Text);
                    }
                    else
                    {
                        MessageBox.Show("输入的几何图形参数非法！\n输入必须是没有前导0的整数，可以有正负号。", "输入错误");
                    }
                    break;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedItems.Count > 0)
            {
                List<string> itemValues = new List<string>();
                foreach (string elm in listBox1.SelectedItems)
                {
                    itemValues.Add(elm);
                }
                
                foreach (string elm in itemValues)
                {
                    listBox1.Items.Remove(elm);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.ShowDialog();
            textBox5.Text = ofd.FileName;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (File.Exists(textBox5.Text))
            {
                if (Regex.IsMatch(textBox5.Text, ".txt$"))
                {
                    int dupCount = 0;
                    string[] points = File.ReadAllLines(textBox5.Text);
                    for (int i = 1; i < points.Length; i++)
                    {
                        bool dup = false;
                        if (listBox1.Items.Count > 0)
                        {
                            foreach (string elm in listBox1.Items)
                            {
                                if (elm == points[i])
                                {
                                    dupCount++;
                                    dup = true;
                                    break;
                                }
                            }
                        }
                        if (!dup)
                        {
                            listBox1.Items.Add(points[i]);
                        }  
                    }

                    if (dupCount > 0)
                    {
                        MessageBox.Show("检测到" + dupCount.ToString() + "个输入上完全相同的几何图形。\n重复的几何图形不会被重复加入列表。", "通知");
                    }
                }
                else
                {
                    MessageBox.Show("请选择扩展名为.txt的文件！", "错误"); 
                }
            }
            else
            {
                MessageBox.Show("文件路径为空或文件不存在！", "错误");
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (listBox1.Items.Count > 0)
            {
                File.WriteAllText("lines.pair", listBox1.Items.Count.ToString() + "\n");
                File.AppendAllLines("lines.pair", listBox1.Items.Cast<string>().ToArray());
                int sb = Solve();
                if (sb < 0)
                {
                    string str;
                    switch (sb)
                    {
                        case -1:
                            str = "线段之间存在重合！";
                            break;
                        case -2:
                            str = "线段和射线之间存在重合！";
                            break;
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
                        default:
                            str = "未知错误！";
                            break;
                    }
                    MessageBox.Show("求解时发生错误！\n" + str);
                } else
                {
                    MessageBox.Show("求解结束，得到" + sb.ToString() + "个交点。\n点击“确定”开始绘图。");
                    Form2 form2 = new Form2();
                    form2.ShowDialog();
                }
            } else
            {
                MessageBox.Show("请添加可以绘制的几何图形！", "错误");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}