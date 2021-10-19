using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void вихідToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void проПрограмуToolStripMenuItem_Click(object sender, EventArgs e)
        {
            about form2 = new about();
            form2.ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            convert form2 = new convert();
            form2.ShowDialog();
        }
    }
}
