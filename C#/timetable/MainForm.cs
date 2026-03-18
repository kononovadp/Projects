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
    public partial class MainForm : Form
    {
        public string[] days = new string[] {"Понеділок","Вівторок","Середа","Четвер","П'ятниця","Субота", "Неділя"};
        public string[] times = new string[] {"8:30 - 10:05","10:25 - 12:00","12:20 - 13:55","14:15 - 15:50","16:10 - 17:45","18:30 - 20:05","20:20 - 21:55"};
        //public string[] LessonTypes = new string[] {"Лекція","Практичне заняття","Контрольна робота","Залік","Екзамен"};
        public string[] LessonTypes = new string[] {"лек","лаб","к р","зал","екз"};

        public struct subject
        {
            public string name;
            public string lecturer;
        };
        public subject[] subjects = new subject[16]
        {
            new subject() {name="Алгоритми та структури даних",lecturer="Ліхоузова Т. А."},
            new subject() {name="Аналіз даних в ІУС",lecturer="Ліхоузова Т. А."},
            new subject() {name="Архітектура комп'ютера",lecturer="Батрак Е. А."},
            new subject() {name="Бази даних",lecturer="Корнага Я. І."},
            new subject() {name="Вища математика",lecturer="Репета А. А."},
            new subject() {name="Комп'ютерная дискретна математика",lecturer="Солдатова М. А."},
            new subject() {name="КПІ-1. Вступ до ПЗ",lecturer="Вовк Є. А."},
            new subject() {name="КПІ-2 Маделювання ПЗ",lecturer="Мітін С. В."},
            new subject() {name="Організація комп'ютерних мереж",lecturer="Катін П. Ю."},
            new subject() {name="Основи програмування",lecturer="Хмелюк М. С."},
            new subject() {name="Основи back-end технологій",lecturer="Вовк Є. А."},
            new subject() {name="Проектування алгоритмів",lecturer="Солдатова М. А."},
            new subject() {name="Проектування ПЗ",lecturer="Вовк Є. А."},
            new subject() {name="Системне програмування",lecturer="Лісовиченко О. І."},
            new subject() {name="Теорія ймовірностей та мат. статистика",lecturer="Ліхоузова Т. А."},
            new subject() {name="Фізика",lecturer="Якуніна Н. О."}
        };
        public int[] StudentsCounts = new int[] {5,10,15,20,25,30,35,40,50,60,75,100,200,300,500};
        public struct group
        {
            public string name;
            public int StudentsCount;
        };
        public group[] groups = new group[15]
        {
            new group() {name="ЗКІ-01",StudentsCount=30},
            new group() {name="ЗКІ-02",StudentsCount=30},
            new group() {name="ЗКІ-01 та 02",StudentsCount=60},
            new group() {name="ЗКІ-03",StudentsCount=5},
            new group() {name="ЗКІ-04",StudentsCount=10},
            new group() {name="ЗКІ-03 та 04",StudentsCount=15},
            new group() {name="ЗКІ-05",StudentsCount=20},
            new group() {name="ЗКІ-06",StudentsCount=10},
            new group() {name="ЗКІ-05 та 06",StudentsCount=30},
            new group() {name="ЗКІ-07",StudentsCount=35},
            new group() {name="ЗКІ-08",StudentsCount=15},
            new group() {name="ЗКІ-07 та 08",StudentsCount=50},
            new group() {name="ЗКІ-09",StudentsCount=10},
            new group() {name="ЗКІ-10",StudentsCount=25},
            new group() {name="ЗКІ-11",StudentsCount=20}
        };
        public struct room
        {
            public string name;
            public int capacity;
        };
        public room[] rooms = new room[22]
        {
            new room() {name="K-100",capacity=5},
            new room() {name="K-101",capacity=10},
            new room() {name="K-102",capacity=15},
            new room() {name="K-103",capacity=20},
            new room() {name="K-104",capacity=25},
            new room() {name="K-105",capacity=30},
            new room() {name="K-106",capacity=35},
            new room() {name="K-107",capacity=40},
            new room() {name="K-108",capacity=50},
            new room() {name="K-109",capacity=60},
            new room() {name="K-110",capacity=70},
            new room() {name="K-200",capacity=5},
            new room() {name="K-201",capacity=10},
            new room() {name="K-202",capacity=15},
            new room() {name="K-203",capacity=20},
            new room() {name="K-204",capacity=25},
            new room() {name="K-205",capacity=30},
            new room() {name="K-206",capacity=35},
            new room() {name="K-207",capacity=40},
            new room() {name="K-208",capacity=50},
            new room() {name="K-209",capacity=60},
            new room() {name="K-210",capacity=70}            
        };
        public int RoomsCount=22;
        public string ConvertDateToString(DateTime date)
        {
            string result;
            if(date.Day<10)
                result="0";
            else
                result="";
            result+=Convert.ToString(date.Day)+".";
            if(date.Month<10)
                result+="0";
            result+=Convert.ToString(date.Month)+'.'+Convert.ToString(date.Year);
            return result;
        }
        public void ChangeCalendar(DateTime date1,DateTime date2,int NewStreamsCount)
        {
            int i,j,StreamsCount=(timetable.ColumnCount-2)/6;
            TitleLabel.Text="Розклад залікової сесії з "+ConvertDateToString(date1)+" по "+ConvertDateToString(date2);
            if(NewStreamsCount>StreamsCount)
            {
                int StreamNumber=(timetable.ColumnCount-2)/4+1;
                for(i=0; i<NewStreamsCount-StreamsCount; i++,StreamNumber++)
                {
                    DataGridViewComboBoxColumn col1 = new DataGridViewComboBoxColumn();
                    col1.Name="group";                    
                    col1.HeaderText+="Група ";
                    col1.HeaderText+=Convert.ToString(StreamNumber);
                    col1.Width=131;
                    for(j=0; j<15; j++)
                        col1.Items.Add(Convert.ToString(groups[j].name));
                    col1.Items.Add("");
                    timetable.Columns.Add(col1);
                    DataGridViewComboBoxColumn col2 = new DataGridViewComboBoxColumn();
                    col2.Name="StudentsCount";
                    col2.HeaderText="Кількість студентів";
                    col2.Width=85;
                    col2.ValueType = typeof(int);
                    for(j=0; j<15; j++)
                        col2.Items.Add(StudentsCounts[j]);
                    col2.Items.Add("");
                    timetable.Columns.Add(col2);
                    DataGridViewComboBoxColumn col3 = new DataGridViewComboBoxColumn();
                    col3.Name="subject";
                    col3.HeaderText="Предмет";
                    col3.Width=350;
                    for(j=0; j<16; j++)
                        col3.Items.Add(Convert.ToString(subjects[j].name));
                    col3.Items.Add("");
                    timetable.Columns.Add(col3);
                    DataGridViewComboBoxColumn col4 = new DataGridViewComboBoxColumn();
                    col4.Name="LessonType";
                    col4.HeaderText="Тип заняття";
                    col4.Width=74;
                    for(j=0; j<5; j++)
                        col4.Items.Add(Convert.ToString(LessonTypes[j]));
                    col4.Items.Add("");
                    timetable.Columns.Add(col4);
                    DataGridViewTextBoxColumn col5 = new DataGridViewTextBoxColumn();
                    col5.Name="lecturer";                    
                    col5.HeaderText="Викладач";
                    col5.Width=155;
                    col5.ReadOnly=true;
                    col5.SortMode = DataGridViewColumnSortMode.NotSortable;
                    timetable.Columns.Add(col5);                    
                    DataGridViewTextBoxColumn col6 = new DataGridViewTextBoxColumn();
                    col6.Name="room";
                    col6.HeaderText="№ ауд. та місткість";
                    col6.Width=100;
                    col6.ReadOnly=true;
                    col6.SortMode = DataGridViewColumnSortMode.NotSortable;
                    timetable.Columns.Add(col6);                    
                }
            }
            else            
                for(i=0,j=timetable.ColumnCount-1,StreamsCount-=NewStreamsCount; i<StreamsCount; i++,j-=6)
                {
                    timetable.Columns.RemoveAt(j);
                    timetable.Columns.RemoveAt(j-1);
                    timetable.Columns.RemoveAt(j-2);
                    timetable.Columns.RemoveAt(j-3);
                    timetable.Columns.RemoveAt(j-4);
                    timetable.Columns.RemoveAt(j-5);
                }
            int k=0,RowNumber,DayNumber,DaysCount=timetable.RowCount/7,NewDaysCount=(date2-date1).Days;
            if(NewDaysCount<DaysCount)
                for(i=0,j=DaysCount*7-1,DaysCount-=NewDaysCount+1; i<DaysCount; i++)
                    for(k=0; k<7; k++,j--)
                        timetable.Rows.RemoveAt(j);
            else            
                for(i=0,NewDaysCount-=DaysCount,RowNumber=DaysCount; i<=NewDaysCount; i++)
                    for (j=0; j<7; j++,RowNumber++)
                    {
                        timetable.Rows.Add();
                        timetable.Rows[RowNumber].Cells[1].Value = times[j];
                    }
                for(i=0,RowNumber=7,DaysCount=timetable.RowCount/7; i<DaysCount; i++,DayNumber++,RowNumber+=7)
                {
                    DayNumber=Convert.ToByte(date1.DayOfWeek)-1;
                    if(DayNumber==-1)
                        DayNumber=6;
                    timetable.Rows[RowNumber-7].Cells[0].Value = days[DayNumber];
                    timetable.Rows[RowNumber-6].Cells[0].Value = ConvertDateToString(date1);
                    date1=date1.AddDays(1);                    
                }
        }
        public MainForm()
        {
            InitializeComponent();
            timetable.AutoGenerateColumns = false;
            var date1 = new DateTime(2021,01,25);
            var date2 = new DateTime(2021,02,14);
            timetable.ColumnHeadersDefaultCellStyle.Font = new Font("Times New Roman", 13);
            ChangeCalendar(date1,date2,1);
        }
        private void timetable_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            if(e.Control is ComboBox)
            {
                ComboBox comboBox = e.Control as ComboBox;
                comboBox.SelectionChangeCommitted -= TimetableCellValueChanged;
                if(timetable.Columns[timetable.CurrentCell.ColumnIndex].Name=="group")
                {
                    comboBox.SelectionChangeCommitted -= GroupChanged;
                    comboBox.SelectionChangeCommitted += GroupChanged;
                }
                else
                    if(timetable.Columns[timetable.CurrentCell.ColumnIndex].Name=="StudentsCount")
                    {
                        comboBox.SelectionChangeCommitted -= StudentsCountChanged;
                        comboBox.SelectionChangeCommitted += StudentsCountChanged;
                    }
                    else
                        if(timetable.Columns[timetable.CurrentCell.ColumnIndex].Name=="subject")
                        {
                            comboBox.SelectionChangeCommitted -= SubjectChanged;
                            comboBox.SelectionChangeCommitted += SubjectChanged;
                        }
                        else
                            if(timetable.Columns[timetable.CurrentCell.ColumnIndex].Name=="LessonType")
                            {
                                comboBox.SelectionChangeCommitted -= LessonTypeChanged;
                                comboBox.SelectionChangeCommitted += LessonTypeChanged;
                            }
                comboBox.SelectionChangeCommitted += TimetableCellValueChanged;
                //comboBox.DropDown -=new EventHandler(ChangeBackgroundColor);
                //comboBox.DropDown += new EventHandler(ChangeBackgroundColor);               
            }
        }
        private void GroupChanged(object sender, EventArgs e)
        {
            var currentcell = timetable.CurrentCellAddress;
            var sendingCB = sender as DataGridViewComboBoxEditingControl;
            if(timetable.Columns[timetable.CurrentCell.ColumnIndex].Name=="group")
            {
                DataGridViewComboBoxColumn col=(DataGridViewComboBoxColumn)timetable.Columns["group"];
                DataGridViewComboBoxCell StudentsCount = (DataGridViewComboBoxCell)timetable.Rows[currentcell.Y].Cells[currentcell.X+1];
                if(sendingCB.SelectedIndex==15)
                    StudentsCount.Value=null;
                else
                    if(sendingCB.SelectedIndex>-1)
                        StudentsCount.Value=groups[sendingCB.SelectedIndex].StudentsCount;
            }
        }
        private void StudentsCountChanged(object sender, EventArgs e)
        {
            var currentcell = timetable.CurrentCellAddress;
            var sendingCB = sender as DataGridViewComboBoxEditingControl;
            if(sendingCB.SelectedIndex==15 && timetable.Columns[timetable.CurrentCell.ColumnIndex].Name=="StudentsCount")
            {
                DataGridViewComboBoxCell group = (DataGridViewComboBoxCell)timetable.Rows[currentcell.Y].Cells[currentcell.X-1];
                group.Value="";
            }            
        }
        private void SubjectChanged(object sender, EventArgs e)
        {
            var currentcell = timetable.CurrentCellAddress;
            var sendingCB = sender as DataGridViewComboBoxEditingControl;
            if(timetable.Columns[timetable.CurrentCell.ColumnIndex].Name=="subject")
            {                
                DataGridViewTextBoxCell lecturer = (DataGridViewTextBoxCell)timetable.Rows[currentcell.Y].Cells[currentcell.X+2];
                DataGridViewComboBoxCell LessonType = (DataGridViewComboBoxCell)timetable.Rows[currentcell.Y].Cells[currentcell.X+1];
                if(sendingCB.SelectedIndex==16)
                {                    
                    DataGridViewTextBoxCell room = (DataGridViewTextBoxCell)timetable.Rows[currentcell.Y].Cells[currentcell.X+3];
                    room.Value="";
                    lecturer.Value="";
                    LessonType.Value="";
                }
                else
                    if(sendingCB.SelectedIndex>-1 && sendingCB.SelectedIndex<16)
                    {
                        if(Convert.ToString(LessonType.Value).Length==0)
                            LessonType.Value="лек";
                        lecturer.Value = subjects[sendingCB.SelectedIndex].lecturer;
                    }
            }
        }
        private void LessonTypeChanged(object sender, EventArgs e)
        {
            var currentcell = timetable.CurrentCellAddress;
            var sendingCB = sender as DataGridViewComboBoxEditingControl;
            if(timetable.Columns[timetable.CurrentCell.ColumnIndex].Name=="LessonType" && sendingCB.SelectedIndex==5)
            {
                    DataGridViewComboBoxCell mysubject = (DataGridViewComboBoxCell)timetable.Rows[currentcell.Y].Cells[currentcell.X-1];
                    DataGridViewTextBoxCell lecturer = (DataGridViewTextBoxCell)timetable.Rows[currentcell.Y].Cells[currentcell.X+1];
                    mysubject.Value="";
                    lecturer.Value="";
            }
        }
        private void TimetableCellValueChanged(object sender, EventArgs e)
        {
            if(timetable.CurrentCell.RowIndex==timetable.RowCount-1)
                SendKeys.Send("{Tab}");            
            else
                for(int i=0; i<timetable.ColumnCount; i++)
                    SendKeys.Send("{Tab}");            
        }
        private void ChangeBackgroundColor(object sender, EventArgs e)
        {
            ((ComboBox)sender).BackColor = Color.White;
        }
        private void MidTermExamsClick(object sender, EventArgs e)
        {
            int i,j;
            var date1 = new DateTime(2021,01,25);
            var date2 = new DateTime(2021,02,14);
            ChangeCalendar(date1,date2,2);
            for(i=0; i<timetable.RowCount; i++)
                for(j=2; j<timetable.ColumnCount; j++)
                    timetable.Rows[i].Cells[j].Value=null;
            DataGridViewComboBoxColumn group=(DataGridViewComboBoxColumn)timetable.Columns["group"];
            DataGridViewComboBoxColumn subject=(DataGridViewComboBoxColumn)timetable.Columns["subject"];
            DataGridViewComboBoxColumn LessonType=(DataGridViewComboBoxColumn)timetable.Columns["LessonType"];
            timetable.Columns[2].HeaderText = "Групи ЗКІ-01 або ЗКІ-01 разом із ЗКІ-02";
            timetable.Columns[8].HeaderText = "Група ЗКІ-02";
            //25.01.2021
            timetable.Rows[1].Cells[2].Value = group.Items[2];
            timetable.Rows[1].Cells[3].Value = groups[2].StudentsCount;
            timetable.Rows[1].Cells[4].Value = subject.Items[13];
            timetable.Rows[1].Cells[5].Value = LessonType.Items[0];
            timetable.Rows[1].Cells[6].Value = subjects[13].lecturer;
            for(i=2; i<7; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[0];
                timetable.Rows[i].Cells[3].Value = groups[0].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[11];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[6].Value = subjects[11].lecturer;
                timetable.Rows[i].Cells[8].Value = group.Items[1];
                timetable.Rows[i].Cells[9].Value = groups[1].StudentsCount;
                timetable.Rows[i].Cells[10].Value = subject.Items[3];
                timetable.Rows[i].Cells[11].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[12].Value = subjects[3].lecturer;
            }
            //26.01.2021
            timetable.Rows[8].Cells[2].Value = group.Items[0];
            timetable.Rows[8].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[8].Cells[4].Value = subject.Items[13];
            timetable.Rows[8].Cells[5].Value = LessonType.Items[1];
            timetable.Rows[8].Cells[6].Value = subjects[13].lecturer;
            for(i=9; i<14; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[0];
                timetable.Rows[i].Cells[3].Value = groups[0].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[3];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[6].Value = subjects[3].lecturer;
            }
            timetable.Rows[9].Cells[8].Value = group.Items[1];
            timetable.Rows[9].Cells[9].Value = groups[1].StudentsCount;
            timetable.Rows[9].Cells[10].Value = subject.Items[13];
            timetable.Rows[9].Cells[11].Value = LessonType.Items[1];
            timetable.Rows[9].Cells[12].Value = subjects[13].lecturer;
            for(i=10; i<14; i++)
            {
                timetable.Rows[i].Cells[8].Value = group.Items[1];
                timetable.Rows[i].Cells[9].Value = groups[1].StudentsCount;
                timetable.Rows[i].Cells[10].Value = subject.Items[11];
                timetable.Rows[i].Cells[11].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[12].Value = subjects[11].lecturer;
            }
            //27.01.2021
            timetable.Rows[15].Cells[2].Value = group.Items[0];
            timetable.Rows[15].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[15].Cells[4].Value = subject.Items[11];
            timetable.Rows[15].Cells[5].Value = LessonType.Items[1];
            timetable.Rows[15].Cells[6].Value = subjects[11].lecturer;
            for(i=17; i<18; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[0];
                timetable.Rows[i].Cells[3].Value = groups[0].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[2];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[4];
                timetable.Rows[i].Cells[6].Value = subjects[2].lecturer;
            }
            for(i=16; i<18; i++)
            {
                timetable.Rows[i].Cells[8].Value = group.Items[1];
                timetable.Rows[i].Cells[9].Value = groups[1].StudentsCount;
                timetable.Rows[i].Cells[10].Value = subject.Items[11];
                timetable.Rows[i].Cells[11].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[12].Value = subjects[11].lecturer;
            }
            for(i=18; i<19; i++)
            {
                timetable.Rows[i].Cells[8].Value = group.Items[1];
                timetable.Rows[i].Cells[9].Value = groups[1].StudentsCount;
                timetable.Rows[i].Cells[10].Value = subject.Items[2];
                timetable.Rows[i].Cells[11].Value = LessonType.Items[4];
                timetable.Rows[i].Cells[12].Value = subjects[2].lecturer;
            }
            //28.01.2021
            timetable.Rows[22].Cells[2].Value = group.Items[0];
            timetable.Rows[22].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[22].Cells[4].Value = subject.Items[13];
            timetable.Rows[22].Cells[5].Value = LessonType.Items[1];
            timetable.Rows[22].Cells[6].Value = subjects[13].lecturer;
            for(i=23; i<26; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[0];
                timetable.Rows[i].Cells[3].Value = groups[0].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[14];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[6].Value = subjects[14].lecturer;
            }
            timetable.Rows[26].Cells[2].Value = group.Items[0];
            timetable.Rows[26].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[26].Cells[4].Value = subject.Items[14];
            timetable.Rows[26].Cells[5].Value = LessonType.Items[3];
            timetable.Rows[26].Cells[6].Value = subjects[14].lecturer;
            timetable.Rows[22].Cells[8].Value = group.Items[1];
            timetable.Rows[22].Cells[9].Value = groups[0].StudentsCount;
            timetable.Rows[22].Cells[10].Value = subject.Items[0];
            timetable.Rows[22].Cells[11].Value = LessonType.Items[3];
            timetable.Rows[22].Cells[12].Value = subjects[0].lecturer;
            timetable.Rows[23].Cells[8].Value = group.Items[1];
            timetable.Rows[23].Cells[9].Value = groups[0].StudentsCount;
            timetable.Rows[23].Cells[10].Value = subject.Items[13];
            timetable.Rows[23].Cells[11].Value = LessonType.Items[1];
            timetable.Rows[23].Cells[12].Value = subjects[13].lecturer;
            //29.01.2021
            timetable.Rows[29].Cells[2].Value = group.Items[0];
            timetable.Rows[29].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[29].Cells[4].Value = subject.Items[13];
            timetable.Rows[29].Cells[5].Value = LessonType.Items[3];
            timetable.Rows[29].Cells[6].Value = subjects[13].lecturer;
            timetable.Rows[30].Cells[2].Value = group.Items[0];
            timetable.Rows[30].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[30].Cells[4].Value = subject.Items[0];
            timetable.Rows[30].Cells[5].Value = LessonType.Items[3];
            timetable.Rows[30].Cells[6].Value = subjects[0].lecturer;
            timetable.Rows[30].Cells[8].Value = group.Items[1];
            timetable.Rows[30].Cells[9].Value = groups[0].StudentsCount;
            timetable.Rows[30].Cells[10].Value = subject.Items[13];
            timetable.Rows[30].Cells[11].Value = LessonType.Items[3];
            timetable.Rows[30].Cells[12].Value = subjects[13].lecturer;
            for(i=31; i<34; i++)
            {
                timetable.Rows[i].Cells[8].Value = group.Items[1];
                timetable.Rows[i].Cells[9].Value = groups[0].StudentsCount;
                timetable.Rows[i].Cells[10].Value = subject.Items[14];
                timetable.Rows[i].Cells[11].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[12].Value = subjects[14].lecturer;
            }
            timetable.Rows[34].Cells[8].Value = group.Items[1];
            timetable.Rows[34].Cells[9].Value = groups[0].StudentsCount;
            timetable.Rows[34].Cells[10].Value = subject.Items[14];
            timetable.Rows[34].Cells[11].Value = LessonType.Items[3];
            timetable.Rows[34].Cells[12].Value = subjects[14].lecturer;
            //30.01.2021
            for(i=35; i<38; i++)
            {
                timetable.Rows[i].Cells[8].Value = group.Items[1];
                timetable.Rows[i].Cells[9].Value = groups[1].StudentsCount;
                timetable.Rows[i].Cells[10].Value = subject.Items[6];
                timetable.Rows[i].Cells[11].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[12].Value = subjects[6].lecturer;
            }
            timetable.Rows[36].Cells[2].Value = group.Items[0];
            timetable.Rows[36].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[36].Cells[4].Value = subject.Items[3];
            timetable.Rows[36].Cells[5].Value = LessonType.Items[2];
            timetable.Rows[36].Cells[6].Value = subjects[3].lecturer;
            timetable.Rows[37].Cells[2].Value = group.Items[0];
            timetable.Rows[37].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[37].Cells[4].Value = subject.Items[3];
            timetable.Rows[37].Cells[5].Value = LessonType.Items[4];
            timetable.Rows[37].Cells[6].Value = subjects[3].lecturer;
            for(i=38; i<41; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[0];
                timetable.Rows[i].Cells[3].Value = groups[0].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[6];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[1];
                timetable.Rows[i].Cells[6].Value = subjects[6].lecturer;
            }
            timetable.Rows[38].Cells[8].Value = group.Items[1];
            timetable.Rows[38].Cells[9].Value = groups[1].StudentsCount;
            timetable.Rows[38].Cells[10].Value = subject.Items[3];
            timetable.Rows[38].Cells[11].Value = LessonType.Items[2];
            timetable.Rows[38].Cells[12].Value = subjects[3].lecturer;
            timetable.Rows[39].Cells[8].Value = group.Items[1];
            timetable.Rows[39].Cells[9].Value = groups[1].StudentsCount;
            timetable.Rows[39].Cells[10].Value = subject.Items[3];
            timetable.Rows[39].Cells[11].Value = LessonType.Items[4];
            timetable.Rows[39].Cells[12].Value = subjects[3].lecturer;
            //01.02.2021
            for(i=51; i<53; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[8];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[8].lecturer;
            }
            //02.02.2021
            for(i=57; i<59; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[8];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[8].lecturer;
            }
            for(i=59; i<61; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[7];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[7].lecturer;
            }
            //03.02.2021
            timetable.Rows[66].Cells[2].Value = group.Items[0];
            timetable.Rows[66].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[66].Cells[4].Value = subject.Items[11];
            timetable.Rows[66].Cells[5].Value = LessonType.Items[4];
            timetable.Rows[66].Cells[6].Value = subjects[11].lecturer;
            timetable.Rows[67].Cells[8].Value = group.Items[1];
            timetable.Rows[67].Cells[9].Value = groups[1].StudentsCount;
            timetable.Rows[67].Cells[10].Value = subject.Items[11];
            timetable.Rows[67].Cells[11].Value = LessonType.Items[4];
            timetable.Rows[67].Cells[12].Value = subjects[11].lecturer;
            //04.02.2021
            timetable.Rows[71].Cells[2].Value = group.Items[0];
            timetable.Rows[71].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[71].Cells[4].Value = subject.Items[4];
            timetable.Rows[71].Cells[5].Value = LessonType.Items[4];
            timetable.Rows[71].Cells[6].Value = subjects[4].lecturer;
            timetable.Rows[72].Cells[8].Value = group.Items[1];
            timetable.Rows[72].Cells[9].Value = groups[1].StudentsCount;
            timetable.Rows[72].Cells[10].Value = subject.Items[4];
            timetable.Rows[72].Cells[11].Value = LessonType.Items[4];
            timetable.Rows[72].Cells[12].Value = subjects[4].lecturer;
            //05.02.2021
            for(i=78; i<80; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[0];
                timetable.Rows[i].Cells[3].Value = groups[0].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[5];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[2];
                timetable.Rows[i].Cells[6].Value = subjects[5].lecturer;
                timetable.Rows[i+2].Cells[8].Value = group.Items[1];
                timetable.Rows[i+2].Cells[9].Value = groups[1].StudentsCount;
                timetable.Rows[i+2].Cells[10].Value = subject.Items[5];
                timetable.Rows[i+2].Cells[11].Value = LessonType.Items[2];
                timetable.Rows[i+2].Cells[12].Value = subjects[5].lecturer;
            }
            timetable.Rows[79].Cells[5].Value = LessonType.Items[4];
            timetable.Rows[81].Cells[11].Value = LessonType.Items[4];
            //06.02.2021
            timetable.Rows[84].Cells[2].Value = group.Items[0];
            timetable.Rows[84].Cells[3].Value = groups[0].StudentsCount;
            timetable.Rows[84].Cells[4].Value = subject.Items[6];
            timetable.Rows[84].Cells[5].Value = LessonType.Items[4];
            timetable.Rows[84].Cells[6].Value = subjects[6].lecturer;
            timetable.Rows[85].Cells[8].Value = group.Items[1];
            timetable.Rows[85].Cells[9].Value = groups[1].StudentsCount;
            timetable.Rows[85].Cells[10].Value = subject.Items[6];
            timetable.Rows[85].Cells[11].Value = LessonType.Items[4];
            timetable.Rows[85].Cells[12].Value = subjects[6].lecturer;
            for(i=86; i<88; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[10];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[10].lecturer;
                timetable.Rows[i+2].Cells[2].Value = group.Items[2];
                timetable.Rows[i+2].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i+2].Cells[4].Value = subject.Items[12];
                timetable.Rows[i+2].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i+2].Cells[6].Value = subjects[12].lecturer;
            }
            //08.02.2021
            for(i=99; i<103; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[1];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[1].lecturer;
            }
            AppointRoomsClick(sender,e);
        }
        private void OrientationSessionClick(object sender, EventArgs e)
        {
            int i,j;
            var date1 = new DateTime(2020,10,19);
            var date2 = new DateTime(2020,10,24);
            ChangeCalendar(date1,date2,1);
            for(i=0; i<timetable.RowCount; i++)
                for(j=2; j<timetable.ColumnCount; j++)
                    timetable.Rows[i].Cells[j].Value=null;
            DataGridViewComboBoxColumn group=(DataGridViewComboBoxColumn)timetable.Columns["group"];
            DataGridViewComboBoxColumn subject=(DataGridViewComboBoxColumn)timetable.Columns["subject"];
            DataGridViewComboBoxColumn LessonType=(DataGridViewComboBoxColumn)timetable.Columns["LessonType"];
            timetable.Columns[2].HeaderText = "Групи ЗКІ-01 та ЗКІ-02";
            //19.10.2020
            for(i=1; i<3; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[13];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[13].lecturer;
            }
            for(i=3; i<6; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[11];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[11].lecturer;
            }
            //20.10.2020
            for(i=8; i<14; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[3];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[3].lecturer;
            }
            //21.10.2020
            for(i=17; i<19; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[6];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[6].lecturer;
            }
            //22.10.2020
            for(i=22; i<26; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[14];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[14].lecturer;
            }
            timetable.Rows[26].Cells[2].Value = group.Items[2];
            timetable.Rows[26].Cells[3].Value = groups[2].StudentsCount;
            timetable.Rows[26].Cells[4].Value = subject.Items[0];
            timetable.Rows[26].Cells[5].Value = LessonType.Items[0];
            timetable.Rows[26].Cells[6].Value = subjects[0].lecturer;
            timetable.Rows[27].Cells[2].Value = group.Items[2];
            timetable.Rows[27].Cells[3].Value = groups[2].StudentsCount;
            timetable.Rows[27].Cells[4].Value = subject.Items[2];
            timetable.Rows[27].Cells[5].Value = LessonType.Items[0];
            timetable.Rows[27].Cells[6].Value = subjects[2].lecturer;
            //23.10.2020
            for(i=29; i<31; i++)
            {
                timetable.Rows[i].Cells[2].Value = group.Items[2];
                timetable.Rows[i].Cells[3].Value = groups[2].StudentsCount;
                timetable.Rows[i].Cells[4].Value = subject.Items[11];
                timetable.Rows[i].Cells[5].Value = LessonType.Items[0];
                timetable.Rows[i].Cells[6].Value = subjects[11].lecturer;
            }
            timetable.Rows[31].Cells[2].Value = group.Items[2];
            timetable.Rows[31].Cells[3].Value = groups[2].StudentsCount;
            timetable.Rows[31].Cells[4].Value = subject.Items[5];
            timetable.Rows[31].Cells[5].Value = LessonType.Items[0];
            timetable.Rows[31].Cells[6].Value = subjects[5].lecturer;
            AppointRoomsClick(sender,e);
        }
        private byte FindSubstringInRow(int RowNumber,string substr)
        {
            int i,j,k,ColumnNumber,EqualGroupsCount,SourceLength,SubstrLength=substr.Length,ColumnsCount=(timetable.ColumnCount-2)/6;
            byte res;
            string source;
            for(k=0,ColumnNumber=2,EqualGroupsCount=0; k<ColumnsCount; k++,ColumnNumber+=6)
            {
                source=Convert.ToString(timetable.Rows[RowNumber].Cells[ColumnNumber].Value);
                for(i=0,res=0,SourceLength=source.Length; i<SourceLength && res==0; i++)
                    for(j=0,res=1; j<SubstrLength && i+j<SourceLength && res==1; j++)
                        if(substr[j]!=source[i+j])
                            res=0;
                if(res==1)
                    EqualGroupsCount++;
            }
            if(EqualGroupsCount>1)
            {
                MessageBox.Show("Різні заняття не можуть одночасно відбуватись в однакових групах.");
                return 1;
            }
            return 0;
        }

        private void AppointRoomsClick(object sender, EventArgs e)
        {
            int i,j,k,t,l1,l2,l3,l4,GroupNumber,ColumnsCount=(timetable.ColumnCount-2)/6;            
            string source,substr;
            int EqualLecturersCount,RowNumber=0,MinCapacity,RoomNumber;
            byte FindSubstringResult;
            byte[,] AllocatedRooms = new byte[timetable.RowCount,RoomsCount];
            for(i=0; i<timetable.RowCount; i++)
                for(j=0; j<RoomsCount; j++)
                    AllocatedRooms[i,j]=0;
            for(RowNumber=0; RowNumber<timetable.RowCount; RowNumber++)
                for(i=0,GroupNumber=2; i<ColumnsCount; i++,GroupNumber+=6)
                {                    
                    l1=Convert.ToString(timetable.Rows[RowNumber].Cells[GroupNumber].Value).Length;
                    l2=Convert.ToString(timetable.Rows[RowNumber].Cells[GroupNumber+1].Value).Length;
                    l3=Convert.ToString(timetable.Rows[RowNumber].Cells[GroupNumber+2].Value).Length;
                    l4=Convert.ToString(timetable.Rows[RowNumber].Cells[GroupNumber+3].Value).Length;
                    if((l1>0 && (l2==0 || l3==0 || l4==0)) || (l2>0 && (l1==0 || l3==0 || l4==0))
                        || (l3>0 && (l1==0 || l2==0 && l4==0)) || (l4>0 && (l1==0 || l2==0 || l3==0))) 
                    {
                        MessageBox.Show("Вкажіть повну інформацію про заняття.");
                        return;
                    }                    
                    source=Convert.ToString(timetable.Rows[RowNumber].Cells[GroupNumber].Value);
                    if(source.Length==0)
                        continue;
                    for(j=0; source[j]!='-'; j++);
                    substr=source.Substring(j+1,2);
                    FindSubstringResult=FindSubstringInRow(RowNumber,substr);
                    if(FindSubstringResult==1)
                        return;
                    if(j+3<source.Length)
                    {
                        for(j++; source[j]!=' '; j++);
                        for(j++; source[j]!=' '; j++);
                        substr=source.Substring(j+1,2);
                        FindSubstringResult=FindSubstringInRow(RowNumber,substr);
                        if(FindSubstringResult==1)
                            return;
                    }
                    source=Convert.ToString(timetable.Rows[RowNumber].Cells[GroupNumber+4].Value);
                    if(source.Length==0)
                        continue;
                    for(j=0,k=6,EqualLecturersCount=0; j<ColumnsCount; j++,k+=6)
                        if(Convert.ToString(timetable.Rows[RowNumber].Cells[k].Value)==source)
                            EqualLecturersCount++;
                    if(EqualLecturersCount>1)
                    {
                        MessageBox.Show("Один викладач не може одночасно працювати в кількох групах");
                        return;
                    }
                    for(j=0,MinCapacity=500,RoomNumber=0; j<RoomsCount; j++)
                        if(AllocatedRooms[RowNumber,j]==0
                            && rooms[j].capacity>Convert.ToInt32(timetable.Rows[RowNumber].Cells[GroupNumber+1].Value)
                            && rooms[j].capacity<MinCapacity)
                        {
                            MinCapacity=rooms[j].capacity;
                            RoomNumber=j;
                        }
                    if(MinCapacity==500)
                        timetable.Rows[RowNumber].Cells[GroupNumber+5].Value="немає ауд.";
                    else
                    {
                        AllocatedRooms[RowNumber,RoomNumber]=1;
                        timetable.Rows[RowNumber].Cells[GroupNumber+5].Value=rooms[RoomNumber].name+" ("+Convert.ToString(rooms[RoomNumber].capacity)+")";
                    }
                }
        }

        private void SetDateClick(object sender, EventArgs e)
        {
            SelectDateForm myNewForm = new SelectDateForm();
            myNewForm.Owner=this;
            myNewForm.ShowDialog();
        }
    }
}
