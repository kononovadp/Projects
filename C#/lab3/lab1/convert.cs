using System;
using System.Globalization;
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
    public partial class convert : Form
    {
        bool[]BlockedClients=new bool[32767];        
        public convert()
        {
            InitializeComponent();
            PhoneNumber.Select();
            PhoneNumber.MaxLength = 10;
            amount.MaxLength = 5;
            BlockingClient.MaxLength = 5;
            rate.SelectedIndex = 0;
            quality.SelectedIndex = 0;
            FrequencyOfToppingUp.SelectedIndex = 0;
            ToolTip toolTip1 = new ToolTip();
            toolTip1.AutoPopDelay = 5000;
            toolTip1.InitialDelay = 100;
            toolTip1.SetToolTip(PhoneNumberInt, "Номер телефону лише в числовому форматі (без зайвих знаків та символу \"0\" попереду).");
            toolTip1.SetToolTip(ConvertNumberToStrAndGetSumOfDigits,"Перетворення:\r\n1. неявне: char-> long;\r\n2. явне: ulong-> sbyte.");
            toolTip1.SetToolTip(DepositAccount,"УВАГА! Комісія складає 3 грн 25 коп, сума повинна бути не меше 5.");
            toolTip1.SetToolTip(CheckNumber,"Перевірити чи красивий номер");
            for(int i=0; i<32767; i++)
                BlockedClients[i]=false;
        }

        private void button1_Click(object sender, EventArgs e)
        {            
            char[]s=PhoneNumber.Text.ToCharArray(0,PhoneNumber.Text.Length);
            int i,n=s.Length;
            if(n<10)
            {
                MessageBox.Show("Номер не може складатись менше ніж з 10 цифр.","Помилка");
                return;
            }
            try
            {
                string tempstr=PhoneNumber.Text;
                long temp=Int64.Parse(tempstr);
            }
            catch(FormatException)
            {
                MessageBox.Show("Номер містить нечислові символи, які будуть опущені.","Попередження");
            }            
            long ten=1,res=0;
            ulong SumOfDigits=0;
            sbyte SbyteSumOfDigits;
            for(i=0; i<n; i++)
                if(Char.IsDigit(s[i]))
                    ten*=10;
            for(i=0,ten/=10; i<n; i++)
                if(Char.IsDigit(s[i]))
                {
                    res=res+((s[i]-'0')*ten);
                    SumOfDigits=SumOfDigits+((ulong)s[i]-'0');
                    ten/=10;
                }
            SbyteSumOfDigits=(sbyte)SumOfDigits;
            DigitsSum.Text=SbyteSumOfDigits.ToString();
            PhoneNumberInt.Text=res.ToString();
        }

        private void CheckNumber_Click(object sender, EventArgs e)
        {
            string s=PhoneNumberInt.Text;
            int i;
            bool[]b=new bool[15];
            Int16 ZeroCount=0,max=0;
            for(i=0; i<s.Length; i++)
                b[i]=Convert.ToBoolean(Convert.ToInt32(s[i]-'0'));
            for(i=0; i<s.Length; i++)
            {
                if(b[i]==false)
                    ZeroCount++;
                else
                    ZeroCount=0;
                if(ZeroCount>max)
                    max=ZeroCount;
            }
            if(max>3)
                MessageBox.Show("Ваш номер є красивим, оскільки містить "+Convert.ToString(max)+" символів '0' підряд.");
            else
                MessageBox.Show("Ваш номер не є золотим.");
        }
        private void DepositAccount_Click(object sender, EventArgs e)
        {
            int n;
            string a=amount.Text;
            try
            {
                n=Int32.Parse(a);
            }
            catch(FormatException)
            {
                MessageBox.Show("Введіть коректну суму.","Помилка");
                return;
            }
            if(n<5)
            {
                MessageBox.Show("Сума не повинна бути меншою за 5.","Помилка");
                state.Text=Convert.ToString(false);
                balance.Text="0";
                return;
            }
            n-=3;
            state.Text=Convert.ToString(Convert.ToBoolean(n));
            balance.Text=Convert.ToString(n-0.25);
        }

        private void CalcTime_Click(object sender, EventArgs e)
        {
            double sum=Convert.ToDouble(balance.Text);
            if(sum==0)
            {
                MessageBox.Show("Ваш рахунок порожній.","Повідомлення");
                return;
            }
            double time=(sum/(Convert.ToDouble(rate.Text)/100))/60;
            if(time>255)
            {
                MessageBox.Show("При обраному тарифі ви можете дуже довго розмовляти.","Повідомлення");
                return;
            }
            byte Btime=Convert.ToByte(time);
            string res;
            if(Btime<1)
                res="У вас залишилось повних "+Convert.ToString(Convert.ToByte(time*60))+" хвилин.";
            else
                res="У вас залишилось повних "+Convert.ToString(Btime)+" годин.";
            MessageBox.Show(res,"Повідомлення");
        }

        private void ClientsCount_Scroll(object sender, EventArgs e)
        {
            ClientsCountInt16.Text=Convert.ToString(ClientsCount.Value);
            BlockedClientsCountInt16.Text="0";
            BlockedClientsCount.Value=0;
            BlockedClientsCount.Maximum=ClientsCount.Value;
            BlockedClientsCount.TickFrequency=ClientsCount.Value/10;            
        }

        private void ManualBlock_CheckedChanged(object sender, EventArgs e)
        {
            BlockingClient.Enabled=true;
            BlockedClientsCount.Enabled=false;
        }

        private void RandomBlock_CheckedChanged(object sender, EventArgs e)
        {
            BlockingClient.Enabled=false;
            BlockedClientsCount.Enabled=true;
            ToolTip toolTip1 = new ToolTip();
            toolTip1.SetToolTip(BlockedClientsCount,"Блокує абонентів за випадковим номером.\r\nУВАГА! Кількість реально заблокованих клієнтів може бути меншою за встановлену!");
        }
        private Int16 CheckInt16(string s)
        {
            Int16 n;
            try
            {
                n=Int16.Parse(s);
            }
            catch(FormatException)
            {
                MessageBox.Show("Введіть коректне число","Помилка");
                return -1;
            }
            catch(OverflowException)
            {
                MessageBox.Show("Номер абонента не може перевищувати 32767.","Помилка");
                return -1;
            }
            if(n>ClientsCount.Value)
            {
                MessageBox.Show("Номер блоковного абонента повинен бути меншим за загальну кількість абонентів","Помилка");
                return -1;
            }
            return n;
        }

        private void block_Click(object sender, EventArgs e)
        {
            string s=BlockingClient.Text;
            Int16 n=CheckInt16(s);
            if(n>-1)
                BlockedClients[n]=true;           
        }

        private void CheckStatus_Click(object sender, EventArgs e)
        {
            string s=ClientNumber.Text;
            Int16 n=CheckInt16(s);
            if(n==-1)
                return;
            if(BlockedClients[n]==true)
                MessageBox.Show("Абонент заблокований.","Повідомлення");
            else
                MessageBox.Show("Абонент не заблокований.","Повідомлення");
        }

        private void GetBlockedClientsCount_Click(object sender, EventArgs e)
        {
            string s=ClientsCountInt16.Text;
            Int16 i,count=Convert.ToInt16(s),n=0;            
            for(i=0; i<count; i++)
                n+=Convert.ToInt16(BlockedClients[i]);
            if(n==0)
                MessageBox.Show("Усі абоненти розблоковані.","Повідомлення");
            else
                MessageBox.Show("Заблоковано "+Convert.ToString(n)+" абонентів.","Повідомлення");
        }

        private void BlockedClientsCount_Scroll(object sender, EventArgs e)
        {
            BlockedClientsCountInt16.Text=Convert.ToString(BlockedClientsCount.Value);
            Random rnd=new Random();
            int n=rnd.Next(BlockedClientsCount.Value);
            BlockedClients[n]=true;
        }

        private void GetDateOfTheNextPayment_Click(object sender, EventArgs e)
        {
            string s=DateOfPreviousPayment.Text;
            DateTime dt;
            try
            {
                dt=Convert.ToDateTime(s);
            }
            catch
            {
                MessageBox.Show("Введіть коректну дату!","Помилка");
                return;
            }
            switch(FrequencyOfToppingUp.Text)
            {
                case "кожний тиждень": dt=dt.AddDays(7.0); break;
                case "кожний місяць": dt=dt.AddMonths(1); break;
                case "кожний рік": dt=dt.AddYears(1); break;
            }
            MessageBox.Show("Дата наступного платежу: "+Convert.ToString(dt.Day)+"."+Convert.ToString(dt.Month)+"."+Convert.ToString(dt.Year)+".","Повідомлення");
        }

        private void CountOfListenedClientsUInt32_MouseClick(object sender, MouseEventArgs e)
        {
            CountOfListenedClientsUInt32.SelectionStart=0;
        }

        private void DateOfPreviousPayment_MouseClick(object sender, MouseEventArgs e)
        {
            DateOfPreviousPayment.SelectionStart=0;
        }

        private void CountOfListenedClients_Scroll(object sender, EventArgs e)
        {
            CountOfListenedClientsUInt32.Text=Convert.ToString(CountOfListenedClients.Value);
        }

        private void CountOfListenedClientsUInt32_TextChanged(object sender, EventArgs e)
        {
            string s=CountOfListenedClientsUInt32.Text;
            if(s.Length>0)
                CountOfListenedClients.Value=Convert.ToInt32(s);
        }

        private void CalcVolume_Click(object sender, EventArgs e)
        {
            string slc=CountOfListenedClientsUInt32.Text;
            string shc=HoursOfConversation.Text;
            string qs=quality.Text;
            UInt32 hc=Convert.ToUInt32(shc);
            UInt32 lc=Convert.ToUInt32(slc);
            UInt32 q=Convert.ToUInt32(qs);
            UInt32 kb=hc*q*lc;
            decimal mb=Convert.ToDecimal(kb)/1024;
            decimal gb=Convert.ToDecimal(kb)/1048576;
            MessageBox.Show("Для збереження розмов "+
                Convert.ToString(lc)+" людей, кожен з яких розмовляє "+
                Convert.ToString(hc)+" годин у якості "+
                Convert.ToString(q)+" кб/с потрібно\r\n"+
                Convert.ToString(kb)+" кб;\r\n"+
                Convert.ToString(mb)+" мб;\r\n"+
                Convert.ToString(gb)+" гб.\r\n","Результат");
        }
    }
}
