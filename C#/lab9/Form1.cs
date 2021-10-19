using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab9
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void DrawSierpinskiTriangle(int ax,int ay,int bx,int by,int cx,int cy,int iter,PaintEventArgs e,Pen mypen)
        {
            if(iter==0)
                return;
            e.Graphics.DrawLine(mypen,ax,ay,bx,by);
            e.Graphics.DrawLine(mypen,bx,by,cx,cy);
            e.Graphics.DrawLine(mypen,cx,cy,ax,ay);
            DrawSierpinskiTriangle(bx,ay,bx-((cx-ax)/2),by-((by-ay)/2),bx+((cx-ax)/2),cy-((by-ay)/2),iter-1,e,mypen);
            DrawSierpinskiTriangle(cx,ay,cx-((cx-bx)/4),by-((by-ay)/2),cx+((cx-bx)/4),cy-((by-ay)/2),iter-1,e,mypen);
            DrawSierpinskiTriangle(ax,by,ax-((cx-bx)/4),by+((by-ay)/2),ax+((cx-bx)/4),cy+((by-ay)/2),iter-1,e,mypen);
        }
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Pen mypen = new Pen(Color.Black,1);            
            int x = 600;
            e.Graphics.DrawLine(mypen, x/2, 0, x, x);
            e.Graphics.DrawLine(mypen, x/2, 0, 0, x);
            e.Graphics.DrawLine(mypen, 0, x, x, x);
            DrawSierpinskiTriangle(x/2,x,x/4,x/2,x-(x/4),x/2,6,e,mypen);
        }
    }
}
