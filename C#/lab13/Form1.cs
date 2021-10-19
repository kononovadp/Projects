using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;
using System.Drawing.Drawing2D;
namespace lab13
{
    public partial class Form1 : Form
    {        
        byte ShowIcon;        
        Point[] octagon;
        Point ImageCorner;
        Point CheckPoint,MousePoint;
        Region OctagonRegion;
        byte MouseClicked;
        int XDistance,YDistance;
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
            g.DrawPolygon(RedPen,octagon);
        }
        public Form1()
        {
            InitializeComponent();
            ShowIcon=0;            
            MouseClicked=0;
            int HalfX=graph.Width/2,HalfY=graph.Height/2;
            octagon=new Point[8];
            octagon[0]=new Point(HalfX-50,HalfY+75);
            octagon[1]=new Point(HalfX-100,HalfY+25);
            octagon[2]=new Point(octagon[1].X,HalfY-25);
            octagon[3]=new Point(octagon[0].X,HalfY-75);            
            octagon[4]=new Point(octagon[3].X+50,octagon[3].Y);
            octagon[5]=new Point(octagon[4].X+50,octagon[4].Y+50);
            octagon[6]=new Point(octagon[5].X,octagon[5].Y+50);
            octagon[7]=new Point(octagon[6].X-50,octagon[6].Y+50);
            ImageCorner=new Point(0, graph.Height-128);
            CheckPoint=new Point(0,0);
            MousePoint=new Point(Cursor.Position.X,Cursor.Position.Y);            
            byte[] _type_vertex = new byte[8];
            _type_vertex[0] = (byte)PathPointType.Start;
            for (int i=1; i<=_type_vertex.Length -1; i++)
                _type_vertex[i] = (byte)PathPointType.Line;
            OctagonRegion = new Region(new GraphicsPath(octagon, _type_vertex));
            ShowGraphic();
        }
        private void graph_MouseClick(object sender, MouseEventArgs e)
        {
            MousePoint.X=Cursor.Position.X;
            MousePoint.Y=Cursor.Position.Y;
            MousePoint=PointToClient(MousePoint);
            int x = MousePoint.X-12;
            int y = MousePoint.Y-12;
            if(MouseClicked==0)
            {
                if((x>=ImageCorner.X && y>=ImageCorner.Y) && (x<=ImageCorner.X+128 && y<=ImageCorner.Y+128))
                {
                    MouseClicked=1;
                    XDistance=x-ImageCorner.X;
                    YDistance=y-ImageCorner.Y;                                        
                    graph.MouseMove += MovePicture;
                }
            }
            else
                MouseClicked=0;
        }
        byte CheckImagePoint(int XStart, int XEnd, int YStart, int YEnd)
        {            
            int i;
            for(i=XStart; i<XEnd; i++)
            {
                CheckPoint.X=i;
                CheckPoint.Y=YStart;
                if (OctagonRegion.IsVisible(CheckPoint))
                    return 1;
            }
            for(i=YStart; i<YEnd; i++)
            {
                CheckPoint.X=XStart;
                CheckPoint.Y=i;
                if (OctagonRegion.IsVisible(CheckPoint))
                    return 1;
            }
            return 0;
        }
        private void MovePicture(object sender, MouseEventArgs e)
        {
            if(MouseClicked==1)
            {                
                MousePoint.X=Cursor.Position.X;
                MousePoint.Y=Cursor.Position.Y;
                MousePoint=PointToClient(MousePoint);
                ImageCorner.X=MousePoint.X-XDistance-12;
                ImageCorner.Y=MousePoint.Y-YDistance-12;
                CheckPoint.X=ImageCorner.X+128;
                CheckPoint.Y=ImageCorner.Y;                
                if(CheckImagePoint(ImageCorner.X,ImageCorner.X+128,ImageCorner.Y,ImageCorner.Y)==0 && CheckImagePoint(ImageCorner.X+128,ImageCorner.X+128,ImageCorner.Y,ImageCorner.Y+128)==0 && CheckImagePoint(ImageCorner.X,ImageCorner.X+128,ImageCorner.Y+128,ImageCorner.Y+128)==0 && CheckImagePoint(ImageCorner.X,ImageCorner.X,ImageCorner.Y,ImageCorner.Y+128)==0)
                    ShowGraphic();
            }
        }
        private void graph_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            MousePoint.X=Cursor.Position.X;
            MousePoint.Y=Cursor.Position.Y;
            MousePoint=PointToClient(MousePoint);
            int x = MousePoint.X-12;
            int y = MousePoint.Y-12;
            if((x>=ImageCorner.X && y>=ImageCorner.Y) && (x<=ImageCorner.X+128 && y<=ImageCorner.Y+128))
            {                
                if(ShowIcon==0)
                    ShowIcon=1;
                else
                    ShowIcon=0;
                ShowGraphic();
            }
        }        
    }
}
