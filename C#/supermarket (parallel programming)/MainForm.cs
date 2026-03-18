using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace supermarket
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }
        private void NormalMode_MouseClick(object sender, MouseEventArgs e)
        {
            CountOfCheckouts.Value=15;
            CountOfCheckouts.Maximum=100;
            CountOfCashiers.Value=12;
            CountOfCashiers.Maximum=100;
            CountOfBuyers.Value=100;
            CountOfBuyers.Maximum=500;
            MaximumCountOfBuyersInShop.Value=90;
            MaximumCountOfBuyersInShop.Maximum=500;
        }
        private void EpidemicMode_MouseClick(object sender, MouseEventArgs e)
        {
            CountOfCheckouts.Value=Environment.ProcessorCount/2;
            CountOfCheckouts.Maximum=Environment.ProcessorCount;
            CountOfCashiers.Value=Environment.ProcessorCount/2;
            CountOfCashiers.Maximum=Environment.ProcessorCount;
            CountOfBuyers.Value=Environment.ProcessorCount*2;
            CountOfBuyers.Maximum=Environment.ProcessorCount*3;
            MaximumCountOfBuyersInShop.Value=Environment.ProcessorCount*3;
            MaximumCountOfBuyersInShop.Maximum=Environment.ProcessorCount*3;
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void ok_Click(object sender, EventArgs e)
        {
            byte mode;
            if(EpidemicMode.Checked==true)
                mode=1;
            else
                mode=0;
            RoomOfSupermarket NewRoom=new RoomOfSupermarket(Convert.ToInt32(CountOfCheckouts.Value),Convert.ToInt32(CountOfCashiers.Value),Convert.ToInt32(CountOfBuyers.Value),Convert.ToInt32(MaximumCountOfBuyersInShop.Value),mode);
            NewRoom.ShowDialog();            
        }
    }
}
