using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab5
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            x.Select();
        }

        private void calculate_Click(object sender, EventArgs e)
        {
            int parsedResult;
            int.TryParse(x.Text, out parsedResult);
            if (parsedResult == 0)
            {
                MessageBox.Show("Введіть коректне ціле число.", "Помилка");
                x.Text = "";
                return;
            }
            int n = Convert.ToInt32(x.Text);
            double root1 = (25 * n + Math.Exp(n + 1)) / 2 * Math.Cos(8*n);
            root1 = root1 * Math.Exp(n + 5) + Math.Exp(n) * (2 * Math.Cos(3 * n));
            root1 = 2*Math.Log(Math.Sqrt(root1));
            double root2 = Math.Sqrt(Math.Exp(n + 1) * Math.Sin(n));
            double res = root1 / root2 + Math.Abs(10 * n + Math.Pow(n, n));
            if(Double.IsNaN(res))
            {
                MessageBox.Show("Результат виразу не коректний.");
                result.Text = "0";
            }
            else
                result.Text = res.ToString("N3");
        }

    }}
