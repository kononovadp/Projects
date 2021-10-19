using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using System.Threading;
namespace lab11//https://www.cyberforum.ru/python-beginners/thread2152031.html
{
    public partial class Form1 : Form
    {
        float x,y,StepSize,XStep,YStep,RandomDistance;
        int RectangleX,RectangleY;
        Point[] triangle;
        Random rnd;
        Image MovingImage;
        Pen RedPen;
        PointF corner;
        Graphics g;
        byte xplus,yplus;
        public Form1()
        {            
            InitializeComponent();
            rnd=new Random();
            x=0;            
            y=graph.Height-128;
            xplus=1;
            yplus=1;
            StepSize=graph.Height/20;            
            RectangleX=graph.Width/2-50;
            RectangleY=graph.Height/2-50;
            triangle=new Point[3];
            triangle[0]=new Point(RectangleX+200,RectangleY+100);
            triangle[1]=new Point(RectangleX+250,RectangleY);
            triangle[2]=new Point(RectangleX+300,RectangleY+100);
            corner=new PointF(x, y);
            MovingImage = Image.FromFile("image.jpg");
            RedPen = new Pen(Color.Red, 3);
            graph.Image = new Bitmap(graph.Width, graph.Height);
            g = Graphics.FromImage(graph.Image);
            timer1.Interval=40;
            timer1.Start();            
        }
        private byte CheckCircle()
        {
            //https://yandex.ru/q/question/kak_pravilno_opredelit_prinadlezhnost_k_e51074a4/
            double SquaredRadius=100*100,xcenter=graph.Width/2,ycenter=graph.Height/2,limit;
            double LeftCorner=graph.Width/2-100,RightCorner=graph.Width/2+100,UpperCorner=graph.Height/2-100,LowerCorner=graph.Height/2+100;
            double NextX=x+XStep,NextY=y+YStep;
            int i,StepsCount;
            if(xplus==1)
                NextX=x+XStep;
            else
                NextX=x-XStep;
            if(yplus==1)
                NextY=y+YStep;
            else
                NextY=y-YStep;
            if(NextX+128<LeftCorner || NextX>RightCorner || NextY+128<UpperCorner || NextY>LowerCorner)
                return 0;
            if(NextX<LeftCorner)
                NextX=LeftCorner;
            if(NextY<UpperCorner)
                NextY+=128;
            for(i=0,StepsCount=Convert.ToInt32(RightCorner)-Convert.ToInt32(NextX); i<StepsCount; i++,NextX++)
                if(((NextX-xcenter)*(NextX-xcenter))+((NextY-ycenter)*(NextY-ycenter))<=SquaredRadius)
                    return 1;
            if(NextY<UpperCorner)
                NextY=UpperCorner;
            for(i=0,StepsCount=Convert.ToInt32(LowerCorner)-Convert.ToInt32(NextY); i<StepsCount; i++,NextY++)
                if(((NextX-xcenter)*(NextX-xcenter))+((NextY-ycenter)*(NextY-ycenter))<=SquaredRadius)
                    return 1;
            return 0;
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            graph.Image = new Bitmap(graph.Width, graph.Height);
            g = Graphics.FromImage(graph.Image);
            g.DrawRectangle(RedPen,0,0,graph.Width-1, graph.Height-1);
            g.DrawEllipse(RedPen,graph.Width/2-100,graph.Height/2-100,200,200);
            //g.DrawRectangle(RedPen, RectangleX, RectangleY, 100, 100);
            //g.DrawPolygon(RedPen,triangle);
            corner.X=x;
            corner.Y=y;
            g.DrawImage(MovingImage,corner);
            if(x<=0 || x>=graph.Width-128 || y<=0 || y>=graph.Height-128 || CheckCircle()==1)
            {
                if(xplus==0)
                {
                    XStep=(rnd.Next(Convert.ToInt32(x+1),graph.Width)-x)/StepSize;
                    xplus=1;
                }
                else
                    if(xplus==1)
                    {
                        XStep=(x-rnd.Next(0,Convert.ToInt32(x)))/StepSize;
                        xplus=0;
                    }
                if(yplus==0)
                {
                    YStep=(graph.Height-128-y)/StepSize;
                    yplus=1;
                }
                else
                    if(yplus==1)
                    {
                        YStep=y/StepSize;
                        yplus=0;
                    }
            }
            if(xplus==1)
                x+=XStep;
            else
                if(xplus==0)
                    x-=XStep;
            if(yplus==1)
                y+=YStep;
            else
                if(yplus==0)
                    y-=YStep;
        }
    }
}
