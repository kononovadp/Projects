using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab7
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            //surname
            Pen mypen = new Pen(Color.Black, 3);
            e.Graphics.DrawLine(mypen,5, 5, 5, 100);
            e.Graphics.DrawLine(mypen, 5, 50, 50, 5);
            e.Graphics.DrawLine(mypen, 5, 50, 50, 100);

            e.Graphics.DrawRectangle(mypen, 55, 5, 50, 95);

            mypen.Color = Color.Blue;
            e.Graphics.DrawLine(mypen, 110, 5, 110, 100);
            e.Graphics.DrawLine(mypen, 110, 50, 160, 50);
            e.Graphics.DrawLine(mypen, 160, 5, 160, 100);

            e.Graphics.DrawArc(mypen, 165, 5, 50, 95, 75, 360);

            mypen.Color = Color.Red;
            e.Graphics.DrawLine(mypen, 220, 5, 220, 100);
            e.Graphics.DrawLine(mypen, 220, 50, 270, 50);
            e.Graphics.DrawLine(mypen, 270, 5, 270, 100);

            e.Graphics.DrawArc(mypen, 275, 5, 50, 95, 75, 360);

            mypen.Color = Color.Green;
            e.Graphics.DrawLine(mypen, 330, 5, 330, 100);
            e.Graphics.DrawArc(mypen, 290, 5, 80, 50, 270, 180);
            e.Graphics.DrawArc(mypen, 290, 55, 80, 45, 270, 180);
            //NAME
            mypen.Color = Color.Pink;
            e.Graphics.DrawLine(mypen, 400, 5, 400, 100);
            e.Graphics.DrawLine(mypen, 400, 5, 425, 50);
            e.Graphics.DrawLine(mypen, 425, 50, 450, 5);
            e.Graphics.DrawLine(mypen, 450, 5, 450, 100);

            e.Graphics.DrawLine(mypen, 455, 100, 480, 5);
            e.Graphics.DrawLine(mypen, 480, 5, 505, 100);
            e.Graphics.DrawLine(mypen, 467, 50, 493, 50);

            e.Graphics.DrawLine(mypen, 510, 5, 510, 100);
            e.Graphics.DrawLine(mypen, 510, 50, 550, 5);
            e.Graphics.DrawLine(mypen, 510, 50, 550, 100);

            mypen.Color = Color.Magenta;
            e.Graphics.DrawArc(mypen, 550, 5, 50, 95, 50, 250);

            e.Graphics.DrawLine(mypen, 605, 5, 605, 100);
            e.Graphics.DrawLine(mypen, 605, 100, 655, 5);
            e.Graphics.DrawLine(mypen, 655, 5, 655, 100);

            e.Graphics.DrawLine(mypen, 660, 5, 660, 100);
            e.Graphics.DrawLine(mypen, 660, 5, 685, 50);
            e.Graphics.DrawLine(mypen, 685, 50, 710, 5);
            e.Graphics.DrawLine(mypen, 710, 5, 710, 100);
            //patronymic
            mypen.Color = Color.BlueViolet;
            e.Graphics.DrawLine(mypen, 5, 200, 25, 105);
            e.Graphics.DrawLine(mypen, 25, 105, 50, 200);
            e.Graphics.DrawLine(mypen, 15, 150, 36, 150);

            e.Graphics.DrawLine(mypen, 55, 105, 55, 200);
            e.Graphics.DrawLine(mypen, 55, 150, 100, 150);
            e.Graphics.DrawLine(mypen, 100, 105, 100, 200);

            e.Graphics.DrawLine(mypen, 105, 200, 130, 105);
            e.Graphics.DrawLine(mypen, 130, 105, 155, 200);
            e.Graphics.DrawLine(mypen, 118, 150, 143, 150);

            mypen.Color = Color.Brown;
            e.Graphics.DrawLine(mypen, 155, 105, 205, 105);
            e.Graphics.DrawLine(mypen, 180, 105, 180, 200);

            e.Graphics.DrawArc(mypen, 205, 105, 50, 95, 75, 360);

            e.Graphics.DrawLine(mypen, 260, 200, 285, 105);
            e.Graphics.DrawLine(mypen, 285, 105, 310, 200);

            mypen.Color = Color.BurlyWood;
            e.Graphics.DrawLine(mypen, 327, 105, 327, 200);
            e.Graphics.DrawLine(mypen, 315, 105, 339, 105);
            e.Graphics.DrawLine(mypen, 315, 200, 339, 200);

            e.Graphics.DrawLine(mypen, 344, 112, 344, 200);
            e.Graphics.DrawLine(mypen, 344, 200, 394, 112);
            e.Graphics.DrawLine(mypen, 394, 112, 394, 200);
            e.Graphics.DrawLine(mypen, 356, 105, 380, 105);

            e.Graphics.DrawArc(mypen, 399, 105, 50, 95, 75, 360);

            mypen.Color = Color.Crimson;
            e.Graphics.DrawLine(mypen, 454, 105, 454, 200);
            e.Graphics.DrawArc(mypen, 408, 105, 96, 50, 270, 180);
            e.Graphics.DrawArc(mypen, 408, 155, 96, 45, 270, 180);

            e.Graphics.DrawLine(mypen, 509, 105, 509, 200);
            e.Graphics.DrawLine(mypen, 509, 200, 559, 105);
            e.Graphics.DrawLine(mypen, 559, 105, 559, 200);

            e.Graphics.DrawLine(mypen, 614, 105, 614, 200);
            e.Graphics.DrawArc(mypen, 565, 55, 50, 100, 180, -180);
        }
    }
}
