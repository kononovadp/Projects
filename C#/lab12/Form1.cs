using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab12
{
    public partial class Form1 : Form
    {
        byte ShowIcon;
        Point[] block1;
        Point[] block2;
        Point[] block3;
        Point ImageCorner;
        private void ShowGraphic()
        {            
            graph.Image = new Bitmap(graph.Width, graph.Height);
            Graphics g = Graphics.FromImage(graph.Image);
            Image newImage;
            if(ShowIcon==1)
                newImage = Image.FromFile("image.ico");
            else
                newImage = Image.FromFile("image.jpg");
            Pen RedPen = new Pen(Color.Red, 3);
            g.DrawImage(newImage,ImageCorner);
            g.DrawPolygon(RedPen,block1);
            g.DrawPolygon(RedPen,block2);
            g.DrawPolygon(RedPen,block3);
        }
        public Form1()
        {
            ShowIcon=1;
            InitializeComponent();
            block1=new Point[4];
            block1[0]=new Point(graph.Width/2-50,graph.Height/2+50);
            block1[1]=new Point(block1[0].X,block1[0].Y-100);
            block1[2]=new Point(block1[0].X+100,block1[1].Y);
            block1[3]=new Point(block1[2].X,block1[0].Y);
            block2=new Point[4];
            block2[0]=new Point(block1[2].X+50,graph.Height/2+25);
            block2[1]=new Point(block2[0].X,block2[0].Y-50);
            block2[2]=new Point(block2[1].X+200,block2[1].Y);
            block2[3]=new Point(block2[2].X,block2[1].Y+50);            
            block3=new Point[4];
            block3[0]=new Point(graph.Width/2-150,Height/2+150);
            block3[1]=new Point(block3[0].X,Height/2-150);
            block3[2]=new Point(block3[0].X+50,block3[1].Y);
            block3[3]=new Point(block3[2].X,block3[0].Y);
            ImageCorner=new Point(0, graph.Height-128);
            ShowGraphic();
        }
        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Right)
            {                
                int RightX=ImageCorner.X+128;                
                int LowerY=ImageCorner.Y+128;
                int UpperY=ImageCorner.Y;
                int NewX=RightX;
                if(NewX<graph.Width+120)
                    if((NewX<block3[0].X || (NewX<block3[0].X || UpperY>block3[0].Y) || LowerY<block3[1].Y) || NewX>block3[2].X)
                            ImageCorner.X+=10;
            }
            else
                if(e.KeyCode == Keys.Left)
                {
                    int LeftX=ImageCorner.X;
                    int LowerY=ImageCorner.Y+128;
                    int UpperY=ImageCorner.Y;
                    int NewX=LeftX;
                    if(LeftX+110>0)
                            if(NewX<block3[0].X || (NewX>block3[2].X || (NewX>block3[2].X || UpperY>block3[0].Y) || LowerY<block3[1].Y) && ((NewX>block1[2].X || (NewX>block1[2].X || UpperY>block1[0].Y) || LowerY<block1[1].Y)) && (((NewX>block2[2].X || (NewX>block2[2].X || UpperY>block2[0].Y) || LowerY<block2[1].Y))))
                                ImageCorner.X-=10;
                }
                else
                    if(e.KeyCode == Keys.Up)
                    {
                        int UpperY=ImageCorner.Y;
                        int RightX=ImageCorner.X+128;
                        int LeftX=ImageCorner.X;
                        int NewY=UpperY-10;
                        if(ImageCorner.Y+100>0)
                            if((NewY>block3[0].Y) || (NewY>block3[0].Y || RightX<block3[0].X) || (LeftX>block3[2].X && NewY>block1[0].Y) || (LeftX>block1[2].X && NewY>block2[0].Y) || (LeftX>block2[2].X) || (ImageCorner.Y<block2[1].Y))
                                ImageCorner.Y-=10;
                    }
                    else
                        if(e.KeyCode == Keys.Down)
                        {
                            int LowerY=ImageCorner.Y+128;
                            int RightX=ImageCorner.X+128;
                            int LeftX=ImageCorner.X;
                            int NewY=LowerY+10;
                            if(ImageCorner.Y+30<graph.Height)
                                if((NewY<block3[1].Y) || (NewY<block3[1].Y || RightX<block3[0].X) || (LeftX>block3[2].X && NewY<block1[1].Y) || (LeftX>block1[2].X && NewY<block2[1].Y) || (LeftX>block2[2].X) || (ImageCorner.Y>block2[1].Y))
                                    ImageCorner.Y+=10;
                        }
            ShowGraphic();
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if(e.KeyChar == (char)Keys.Enter)
            {
                if(ShowIcon==0)
                    ShowIcon=1;
                else
                    if(ShowIcon==1)
                    ShowIcon=0;
                ShowGraphic();
            }
        }
    }
}
