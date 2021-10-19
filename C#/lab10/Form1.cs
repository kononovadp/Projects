using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab10
{
    public partial class Form1 : Form
    {
        private float scale = 1;
        NumericUpDown numericUpDown;
        public void DrawAxis(Graphics g)
        {            
            Pen BlackPen = new Pen(Color.Black, 3);
            g.Clear(graph.BackColor);
            g.DrawLine(BlackPen,graph.Width/2,0,graph.Width/2,graph.Height);
            g.DrawLine(BlackPen,0,graph.Height/2,graph.Width,graph.Height/2);
            int dist,MarksCount=20;
            for(dist=graph.Width/MarksCount; dist<graph.Width; dist=dist+graph.Width/MarksCount)
                g.DrawLine(BlackPen,dist,graph.Height/2-5,dist,graph.Height/2+5);
            for(dist=graph.Height/MarksCount; dist<graph.Height; dist=dist+graph.Height/MarksCount)
                g.DrawLine(BlackPen,graph.Width/2-5,dist,graph.Width/2+5,dist);
        }

        public Form1()
        {
            InitializeComponent();
            function.SelectedIndex = 0;  
            DrawTan();
        }
        public void DrawSin()
        {
            graph.Image = new Bitmap(graph.Width, graph.Height);
            Pen RedPen = new Pen(Color.Red, 3);
            Graphics g = Graphics.FromImage(graph.Image);            
            int i,cx = graph.Width,cy = graph.Height,WavesCount = 4;
            PointF[] ptf = new PointF[cx];
            DrawAxis(g);       
            for (i = 0; i < cx; i++)
            {
                ptf[i].X = i;
                ptf[i].Y= (float)((cy / 2) * (1 - Math.Sin(i * WavesCount * Math.PI / (cx - 1))));
            }
            g.DrawLines(RedPen, ptf);
            g.Dispose();
        }

        public void DrawCos()
        {
            graph.Image = new Bitmap(graph.Width, graph.Height);
            Pen RedPen = new Pen(Color.Red, 3);
            Graphics g = Graphics.FromImage(graph.Image);
            int i,cx = graph.Width,cy = graph.Height,WavesCount = 4;
            PointF[] ptf = new PointF[cx];
            DrawAxis(g);            
            for (i = 0; i < cx; i++)
            {
                ptf[i].X = i;
                ptf[i].Y = (float)((cy / 2) * (1 - Math.Cos(i * WavesCount * Math.PI / (cx - 1))));
            }
            g.DrawLines(RedPen, ptf);
            g.Dispose();
        }

        public void DrawTan()
        {
            graph.Image = new Bitmap(graph.Width, graph.Height);
            Pen RedPen = new Pen(Color.Red, 3);
            Graphics g = Graphics.FromImage(graph.Image);            
            int i,j,cx = graph.Width,cy = graph.Height,WavesCount = 2;
            PointF[] ptf = new PointF[cx];
            float x,y;
            DrawAxis(g);            
            for (i = 0; i < cx; i++)
            {
                ptf[i].X = i;
                ptf[i].Y = (float)((cy / 2) * (1 - Math.Tan(i * WavesCount * Math.PI / (cx - 1))));
            }           
            g.DrawLines(RedPen, ptf);
            g.Dispose();
        }

        public void DrawCTan()
        {
            graph.Image = new Bitmap(graph.Width, graph.Height);
            Pen RedPen = new Pen(Color.Red, 3);
            Graphics g = Graphics.FromImage(graph.Image);            
            int i,j,cx = graph.Width,cy = graph.Height,WavesCount = 2;
            PointF[] ptf = new PointF[cx];
            float x,y;
            DrawAxis(g);            
            for (i = 0; i < cx; i++)
            {
                ptf[i].X = i;
                ptf[i].Y = (float)((cy / 2) * (1 + Math.Tan(i * WavesCount * Math.PI / (cx - 1))));
            }           
            g.DrawLines(RedPen, ptf);
            g.Dispose();
        }

        private void function_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(function.Text=="y=sin(x)")
                DrawSin();
            else
                if(function.Text=="y=cos(x)")
                    DrawCos();
                else
                    if(function.Text=="y=tg(x)")
                        DrawTan();
                    else
                        DrawCTan();
        }        
    }
}
