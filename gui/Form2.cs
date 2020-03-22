using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace PairUI
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void Form2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Panel1_Paint(object sender, PaintEventArgs e)
        {
            string[] points = File.ReadAllLines("points.pair");
            string[] lines = File.ReadAllLines("lines.pair");
            List<Geo> geos = new List<Geo>();
            foreach (string elm in points)
            {
                string[] part = Regex.Split(elm, " ");
                switch (part[0][0])
                {
                    case 'P':
                        float[] tmp5 = { Convert.ToSingle(part[1]), Convert.ToSingle(part[2]) };
                        geos.Add(new Geo(4, tmp5));
                        break;
                    default:
                        break;
                }
            }

            foreach (string elm in lines)
            {
                string[] part = Regex.Split(elm, " ");
                switch (part[0][0])
                {
                    case 'L':
                        float[] tmp1 = { Convert.ToSingle(part[1]), Convert.ToSingle(part[2]), Convert.ToSingle(part[3]), Convert.ToSingle(part[4]) };
                        geos.Add(new Geo(0, tmp1));
                        break;
                    case 'R':
                        float[] tmp2 = { Convert.ToSingle(part[1]), Convert.ToSingle(part[2]), Convert.ToSingle(part[3]), Convert.ToSingle(part[4]) };
                        geos.Add(new Geo(1, tmp2));
                        break;
                    case 'S':
                        float[] tmp3 = { Convert.ToSingle(part[1]), Convert.ToSingle(part[2]), Convert.ToSingle(part[3]), Convert.ToSingle(part[4]) };
                        geos.Add(new Geo(2, tmp3));
                        break;
                    case 'C':
                        float[] tmp4 = { Convert.ToSingle(part[1]), Convert.ToSingle(part[2]), Convert.ToSingle(part[3]) };
                        geos.Add(new Geo(3, tmp4));
                        break;
                    default:
                        break;
                }
            }
            float maxx, maxy, minx, miny;
            maxx = geos[0].x1;
            minx = geos[0].x1;
            maxy = geos[0].y1;
            miny = geos[0].y1;
            foreach (Geo geo in geos)
            {
                if (geo.type < 3 && geo.type > 0)
                {
                    if (geo.x1 > maxx)
                    {
                        maxx = geo.x1;
                    }
                    if (geo.x2 > maxx)
                    {
                        maxx = geo.x2;
                    }
                    if (geo.y1 > maxy)
                    {
                        maxy = geo.y1;
                    }
                    if (geo.y2 > maxy)
                    {
                        maxy = geo.y2;
                    }
                    if (geo.x1 < minx)
                    {
                        minx = geo.x1;
                    }
                    if (geo.x2 < minx)
                    {
                        minx = geo.x2;
                    }
                    if (geo.y1 < miny)
                    {
                        miny = geo.y1;
                    }
                    if (geo.y2 < miny)
                    {
                        miny = geo.y2;
                    }
                }
                else if (geo.type == 3)
                {
                    if (geo.x1 + geo.x2 > maxx)
                    {
                        maxx = geo.x1 + geo.x2;
                    }
                    if (geo.y1 + geo.x2 > maxy)
                    {
                        maxy = geo.y1 + geo.x2;
                    }
                    if (geo.x1 - geo.x2 < minx)
                    {
                        minx = geo.x1 - geo.x2;
                    }
                    if (geo.y1 - geo.x2 < miny)
                    {
                        miny = geo.y1 - geo.x2;
                    }
                }
                else if (geo.type == 4)
                {
                    if (geo.x1 > maxx)
                    {
                        maxx = geo.x1;
                    }
                    if (geo.y1 > maxy)
                    {
                        maxy = geo.y1;
                    }
                    if (geo.x1 < minx)
                    {
                        minx = geo.x1;
                    }
                    if (geo.y1 < miny)
                    {
                        miny = geo.y1;
                    }
                }
            }

            float k, dx, dy;
            if (maxx - minx < 1 && maxy - miny < 1)
            {
                k = 1;
                dx = minx;
                dy = miny;
            }
            else
            {
                if ((maxx - minx) > (maxy - miny))
                {
                    k = maxx - minx;
                    dx = minx;
                    dy = miny - (maxx - maxy - minx + miny) / 2;
                }
                else
                {
                    k = maxy - miny;
                    dx = minx - (-maxx + maxy + minx - miny) / 2;
                    dy = miny;
                }
            }

            label1.Text = (dy + k).ToString();
            label2.Text = (dy).ToString();
            label3.Text = (dx).ToString();
            label4.Text = (dx + k).ToString();
            label5.Text = (dy + k / 2).ToString();
            label6.Text = (dx + k / 2).ToString();

            List<Geo> newgeos = new List<Geo>();
            foreach (Geo geo in geos)
            {
                geo.reshape(k, dx, dy);
                newgeos.Add(geo);
            }
            Graphics g = e.Graphics;
            Pen axis = new Pen(Color.Black, 2);
            Pen line = new Pen(Color.Blue, 2);
            float xaxis = -dx * 700 / k + 10;
            float yaxis = -dy * 700 / k + 10;
            g.DrawLine(axis, xaxis, 0, xaxis, 720);
            g.DrawLine(axis, 0, 720 - yaxis, 720, 720 - yaxis);

            foreach (Geo geo in newgeos)
            {
                switch (geo.type)
                {
                    case 0:
                    case 1:
                    case 2:
                        g.DrawLine(line, geo.x1, 720 - geo.y1, geo.x2, 720 - geo.y2);
                        if (geo.type > 0)
                        {
                            g.FillEllipse(Brushes.Brown, geo.x1 - 4, 720 - geo.y1 - 4, 8, 8);
                            if (geo.type == 2)
                            {
                                g.FillEllipse(Brushes.Brown, geo.x2 - 4, 720 - geo.y2 - 4, 8, 8);
                            }
                        }
                        break;
                    case 3:
                        g.DrawEllipse(line, geo.x1 - geo.x2, 720 - geo.y1 - geo.x2, 2 * geo.x2, 2 * geo.x2); break;
                    default:
                        break;
                }
            }

            foreach (Geo geo in newgeos)
            {
                if (geo.type == 4)
                {
                    g.FillEllipse(Brushes.Red, geo.x1 - 4, 720 - geo.y1 - 4, 8, 8);
                }
            }
        
        }
    }

    public class Geo
    {
        public int type;
        public float x1;
        public float y1;
        public float x2;
        public float y2;
        public Geo(int t, float[] paras)
        {
            type = t;
            switch (t)
            {
                case 0: // 直线
                case 1: // 射线
                case 2: // 线段
                    x1 = paras[0];
                    y1 = paras[1];
                    x2 = paras[2];
                    y2 = paras[3];
                    break;
                case 3: // 圆
                    x1 = paras[0];
                    y1 = paras[1];
                    x2 = paras[2];
                    y2 = 0;
                    break;
                case 4: // 交点
                    x1 = paras[0];
                    y1 = paras[1];
                    x2 = 0;
                    y2 = 0;
                    break;
            }
        }

        public void reshape(float k, float dx, float dy)
        {
            x1 = (x1 - dx) * 700 / k + 10;
            y1 = (y1 - dy) * 700 / k + 10;
            if (type < 3)
            {
                x2 = (x2 - dx) * 700 / k + 10;
                y2 = (y2 - dy) * 700 / k + 10;
            }
            else
            {
                x2 = x2 * 700 / k;
            }
            if (x2 - x1 > 1e-5)
            {
                switch (type)
                {
                    case 0:
                        float xl = (y2 - y1) / (x2 - x1);
                        y1 = y1 - xl * x1;
                        y2 = y2 - xl * x2 + xl * 720;
                        x1 = 0;
                        x2 = 720;
                        break;
                    case 1:
                        float xl2 = (y2 - y1) / (x2 - x1);
                        y2 = y1 - xl2 * x1 + xl2 * 720;
                        x2 = 720;
                        break;
                    default:
                        break;
                }
            }
            else if (x1 - x2 > 1e-5)
            {
                switch (type)
                {
                    case 0:
                        float xl = (y2 - y1) / (x2 - x1);
                        y1 = y1 - xl * x1;
                        y2 = y2 - xl * x2 + xl * 720;
                        x1 = 0;
                        x2 = 720;
                        break;
                    case 1:
                        float xl2 = (y2 - y1) / (x2 - x1);
                        y2 = y1 - xl2 * x1;
                        x2 = 0;
                        break;
                    default:
                        break;
                }
            }
            else
            {
                switch (type)
                {
                    case 0:
                        y1 = 0;
                        y2 = 720;
                        break;
                    case 1:
                        if (y1 < y2)
                        {
                            y2 = 720;
                        }
                        else
                        {
                            y2 = 0;
                        }
                        break;
                    default:
                        break;
                }
            }

        }
    }
}
