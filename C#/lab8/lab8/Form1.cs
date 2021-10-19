using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab8
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Pen mypen = new Pen(Color.Black, 3);
            int x1=10,y1=10;
            int x2=500,y2=10;
            int x3=500, y3=500;
            int x4=10,y4=500;
            double t, p = 0.08;
            for(int i=0; i<50; i++)
            {
                e.Graphics.DrawLine(mypen,x1,y1,x2,y2);
                e.Graphics.DrawLine(mypen,x2,y2,x3,y3);
                e.Graphics.DrawLine(mypen,x3,y3,x4,y4);
                e.Graphics.DrawLine(mypen,x4,y4,x1,y1);
                int x = x1, y = y1;
                x1=(int)(x1+(x2-x1)*0.08);
                y1=(int)(y1+(y2-y1)*0.08);
                x2=(int)(x2+(x3-x2)*0.08);
                y2=(int)(y2+(y3-y2)*0.08);
                x3=(int)(x3+(x4-x3)*0.08);
                y3=(int)(y3+(y4-y3)*0.08);
                x4=(int)(x4+(x-x4)*0.08);
                y4=(int)(y4+(y-y4)*0.08);
                
            }
        }
    }
}
