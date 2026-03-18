using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace timetable
{
    public partial class SelectDateForm : Form
    {
        public SelectDateForm()
        {
            InitializeComponent();
        }

        private void SelectDateForm_Load(object sender, EventArgs e)
        {
            MainForm mf = this.Owner as MainForm;
            StreamsCount.Value=(mf.timetable.ColumnCount-2)/6;
            StartDate.Value=Convert.ToDateTime(mf.timetable.Rows[1].Cells[0].Value);
            EndDate.Value=Convert.ToDateTime(mf.timetable.Rows[mf.timetable.RowCount-6].Cells[0].Value);
        }

        private void SelectDateCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void SelectDate_Click(object sender, EventArgs e)
        {
            if(EndDate.Value<StartDate.Value)
            {
                MessageBox.Show("Введіть коректну дату завершення сесії");
                return;
            }
            MainForm mf = this.Owner as MainForm;
            mf.ChangeCalendar(StartDate.Value,EndDate.Value,Convert.ToInt32(StreamsCount.Value));
            this.Close();
        }
    }
}
