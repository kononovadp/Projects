using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;
//https://coderoad.ru/661561/%D0%9A%D0%B0%D0%BA-%D0%BE%D0%B1%D0%BD%D0%BE%D0%B2%D0%B8%D1%82%D1%8C-GUI-%D0%B8%D0%B7-%D0%B4%D1%80%D1%83%D0%B3%D0%BE%D0%B3%D0%BE-%D0%BF%D0%BE%D1%82%D0%BE%D0%BA%D0%B0
namespace supermarket
{
    
    public partial class RoomOfSupermarket : Form
    {
        CustomProgressBar MainProgressBar;
        struct Buyer
        {
            public byte state;
            public int number;
            public int CountOfGoods;
            public int NumberOfCheckout;
        }
        struct Checkout
        {                        
            public byte state;
            public Queue<int>queue;
            public int CountOfBuyers;
            public int capacity;
        }
        Buyer[] buyers;
        Checkout[] checkouts;
        Thread[] ThreadsOfCheckouts;
        StreamWriter[] FilesOfCheckouts,FilesOfBuyers;
        Label CountOfWorkingCheckoutsLabel;        
        int CountOfCheckouts,CountOfCashiers,CountOfWorkingCheckouts;
        int CountOfBuyers,MaximumCountOfBuyersInShop,CountOfServicedBuyers,CountOfBuyersInShop;
        void WaitFor(int CountOfMileseconds)
        {
            int i,j;
            for(i=0; i<CountOfMileseconds; i++)
                for(j=0; j<500000; j++);
            /*int i=0;
            DateTime CurrentTime=DateTime.Now;
            DateTime NewTime=DateTime.Now;
            for(int j=0; j<5000; j++)
            {
                CurrentTime=DateTime.Now;
                do
                {
                    NewTime=DateTime.Now;
                    i++;
                }while(NewTime.ToString("dd.MM.yyyy hh:mm:ss:fff")==CurrentTime.ToString("dd.MM.yyyy hh:mm:ss:fff"));
            }*/
        }
        void ManageCheckoutClick(object sender, CustomProgressBar ServiceProgress, Button ManageCheckout,int NumberOfCheckout,StreamWriter file)
        {
            Button button=sender as Button;
            if(button.Text=="Закрити касу")
            {
                if(CountOfWorkingCheckouts==1)
                    MessageBox.Show("У супермаркеті має бути хоча б одна працююча каса.");
                else
                    checkouts[NumberOfCheckout].state=0;
            }
            else
            {
                if(CountOfWorkingCheckouts<CountOfCashiers)
                {
                    checkouts[NumberOfCheckout].state=1;
                    ThreadsOfCheckouts[NumberOfCheckout].Abort();
                    ThreadsOfCheckouts[NumberOfCheckout]=new Thread(() => WorkOfCheckout(ServiceProgress,ManageCheckout,NumberOfCheckout,file));
                    ThreadsOfCheckouts[NumberOfCheckout].Name=(Convert.ToString(NumberOfCheckout));
                    ThreadsOfCheckouts[NumberOfCheckout].Start();
                }
                else
                    MessageBox.Show("Кількість працюючих кас не може перевищувати кількість касирів ("+Convert.ToString(CountOfCashiers)+").");
            }
        }
        async void WorkOfCheckout(CustomProgressBar ProgressOfCheckout, Button ManageCheckout,int NumberOfCheckout,StreamWriter file)
        {
            Random RandomNumber=new Random();
            int i,NumberOfBuyer;
            string NumberOfBuyerString,CountOfGoodsString,CurrentTime,NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
            ManageCheckout.Click+=new System.EventHandler((sender,e)=>ManageCheckoutClick(sender,ProgressOfCheckout,ManageCheckout,NumberOfCheckout,file));
            while(!IsHandleCreated)
                await Task.Delay(10);
            while(!ProgressOfCheckout.IsHandleCreated)
                await Task.Delay(10);
            while(!ManageCheckout.IsHandleCreated)
                await Task.Delay(10);
            while(checkouts[NumberOfCheckout].state>0 && CountOfWorkingCheckouts>=CountOfCashiers)
                await Task.Delay(10);
            checkouts[NumberOfCheckout].capacity=RandomNumber.Next(10,20);
            file.Write(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff")+" Каса відкрилась (максимальна кількість покупців: "+Convert.ToString(checkouts[NumberOfCheckout].capacity)+")\r\n");
            CountOfWorkingCheckouts++;
            this.BeginInvoke((MethodInvoker)(()=>
            {
                ProgressOfCheckout.CustomText="Каса очікує покупця";
                ProgressOfCheckout.Refresh();
                ManageCheckout.Text="Закрити касу";
                CountOfWorkingCheckoutsLabel.Text="Кількість працюючих кас: "+Convert.ToString(CountOfWorkingCheckouts);                
            }));            
            while(checkouts[NumberOfCheckout].state>0 && checkouts[NumberOfCheckout].capacity>0)
            {
                for(; checkouts[NumberOfCheckout].state>0 && checkouts[NumberOfCheckout].queue.Count>0; checkouts[NumberOfCheckout].CountOfBuyers--)
                {
                    NumberOfBuyer=checkouts[NumberOfCheckout].queue.Dequeue();
                    if(buyers[NumberOfBuyer].NumberOfCheckout==NumberOfCheckout)
                    {
                        NumberOfBuyerString=Convert.ToString(NumberOfBuyer+1);
                        CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                        this.BeginInvoke((MethodInvoker)(()=>
                        {                        
                            ProgressOfCheckout.CustomText="Очікує товари покупця "+NumberOfBuyerString;
                            CheckoutLog.Text+=CurrentTime+" Очікує товари покупця "+NumberOfBuyerString+"\n";
                            file.Write(CurrentTime+" Очікує товари покупця "+NumberOfBuyerString+"\r\n");
                        }));
                        while(checkouts[NumberOfCheckout].state>0 && buyers[NumberOfBuyer].state>2 && buyers[NumberOfBuyer].NumberOfCheckout==NumberOfCheckout)
                            await Task.Delay(1);
                        CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                        if(checkouts[NumberOfCheckout].state>0 && buyers[NumberOfBuyer].state>0 && buyers[NumberOfBuyer].NumberOfCheckout==NumberOfCheckout)
                        {                        
                            this.BeginInvoke((MethodInvoker)(()=>
                            {                            
                                ProgressOfCheckout.Step=1;
                                ProgressOfCheckout.Value=0;
                                ProgressOfCheckout.Maximum=buyers[NumberOfBuyer].CountOfGoods;
                                ProgressOfCheckout.CustomText="Обслуговується покупець "+NumberOfBuyerString;
                                CheckoutLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" почав обслуговуватись на касі "+NumberOfCheckoutString+"\n";
                                file.Write(CurrentTime+" Покупець "+NumberOfBuyerString+" почав обслуговуватись\r\n");
                            }));
                            CountOfGoodsString=Convert.ToString(buyers[NumberOfBuyer].CountOfGoods);
                            for(i=0,buyers[NumberOfBuyer].state=1; checkouts[NumberOfCheckout].state>0 && buyers[NumberOfBuyer].state>0 && i<buyers[NumberOfBuyer].CountOfGoods; i++)
                            {
                                await Task.Delay(250);
                                this.BeginInvoke((MethodInvoker)(()=>
                                {
                                    ProgressOfCheckout.CustomText="Покупець "+NumberOfBuyerString+" ("+Convert.ToString(i)+" товарів з "+CountOfGoodsString+")";
                                    ProgressOfCheckout.PerformStep();
                                }));
                            }
                            buyers[NumberOfBuyer].state=0;
                            CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                            if(checkouts[NumberOfCheckout].state==0 || i<buyers[NumberOfBuyer].CountOfGoods)
                                this.BeginInvoke((MethodInvoker)(()=>
                                {                                    
                                    CheckoutLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" пішов з каси "+NumberOfCheckoutString+"\n";
                                    file.Write(CurrentTime+" Покупець "+NumberOfBuyerString+" пішов з каси\r\n");
                                }));
                            else
                                this.BeginInvoke((MethodInvoker)(()=>
                                {                                    
                                    CheckoutLog.Text+=CurrentTime+" Каса "+NumberOfCheckoutString+" завершила обслуговування покупця "+NumberOfBuyerString+"\n";
                                    file.Write(CurrentTime+" Каса завершила обслуговування покупця "+NumberOfBuyerString+"\r\n");
                                }));
                            this.BeginInvoke((MethodInvoker)(()=>
                            {                            
                                ProgressOfCheckout.Step=1;
                                ProgressOfCheckout.Value=0;
                                ProgressOfCheckout.CustomText="Каса очікує покупця";
                                ProgressOfCheckout.Refresh();
                            }));
                        }
                        else
                            this.BeginInvoke((MethodInvoker)(()=>
                            {
                                CheckoutLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" пішов з каси "+NumberOfCheckoutString+"\n";
                                file.Write(CurrentTime+" Покупець "+NumberOfBuyerString+" пішов з каси\r\n");
                            }));
                        checkouts[NumberOfCheckout].capacity--;
                    }
                }
                await Task.Delay(10);
            }
            checkouts[NumberOfCheckout].state=0;
            CountOfWorkingCheckouts--;            
            while(checkouts[NumberOfCheckout].queue.Count>0)
            {
                NumberOfBuyer=checkouts[NumberOfCheckout].queue.Dequeue();
                buyers[NumberOfBuyer].state=3;
            }
            checkouts[NumberOfCheckout].CountOfBuyers=0;
            this.BeginInvoke((MethodInvoker)(()=>
            {
                ProgressOfCheckout.CustomText="Каса не працює";
                ProgressOfCheckout.Refresh();
                ManageCheckout.Text="Відкрити касу";
                CountOfWorkingCheckoutsLabel.Text="Кількість працюючих кас: "+Convert.ToString(CountOfWorkingCheckouts);
                file.Write(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff")+" Каса закрилась (максимальна кількість покупців: "+Convert.ToString(checkouts[NumberOfCheckout].capacity)+")\r\n");
            }));
        }
        void WorkOfCheckoutEpidemicMode(CustomProgressBar ProgressOfCheckout, Button ManageCheckout,int NumberOfCheckout,StreamWriter file)
        {
            Random RandomNumber=new Random();
            int i,NumberOfBuyer;
            string NumberOfBuyerString,CountOfGoodsString,CurrentTime,NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
            ManageCheckout.Click+=new System.EventHandler((sender,e)=>ManageCheckoutClick(sender,ProgressOfCheckout,ManageCheckout,NumberOfCheckout,file));
            while(!IsHandleCreated)
                WaitFor(10);
            while(!ProgressOfCheckout.IsHandleCreated)
                WaitFor(10);
            while(!ManageCheckout.IsHandleCreated)
                WaitFor(10);
            while(checkouts[NumberOfCheckout].state>0 && CountOfWorkingCheckouts>=CountOfCashiers)
                WaitFor(10);
            checkouts[NumberOfCheckout].capacity=RandomNumber.Next(10,20);
            file.Write(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff")+" Каса відкрилась (максимальна кількість покупців: "+Convert.ToString(checkouts[NumberOfCheckout].capacity)+")\r\n");
            CountOfWorkingCheckouts++;
            this.BeginInvoke((MethodInvoker)(()=>
            {
                ProgressOfCheckout.CustomText="Каса очікує покупця";
                ProgressOfCheckout.Refresh();
                ManageCheckout.Text="Закрити касу";
                CountOfWorkingCheckoutsLabel.Text="Кількість працюючих кас: "+Convert.ToString(CountOfWorkingCheckouts);                
            }));            
            while(checkouts[NumberOfCheckout].state>0 && checkouts[NumberOfCheckout].capacity>0)
            {
                for(; checkouts[NumberOfCheckout].state>0 && checkouts[NumberOfCheckout].queue.Count>0; checkouts[NumberOfCheckout].CountOfBuyers--)
                {
                    NumberOfBuyer=checkouts[NumberOfCheckout].queue.Dequeue();
                    if(buyers[NumberOfBuyer].NumberOfCheckout==NumberOfCheckout)
                    {
                        NumberOfBuyerString=Convert.ToString(NumberOfBuyer+1);
                        CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                        this.BeginInvoke((MethodInvoker)(()=>
                        {                        
                            ProgressOfCheckout.CustomText="Очікує товари покупця "+NumberOfBuyerString;
                            CheckoutLog.Text+=CurrentTime+" Очікує товари покупця "+NumberOfBuyerString+"\n";
                            file.Write(CurrentTime+" Очікує товари покупця "+NumberOfBuyerString+"\r\n");
                        }));
                        while(checkouts[NumberOfCheckout].state>0 && buyers[NumberOfBuyer].state>2 && buyers[NumberOfBuyer].NumberOfCheckout==NumberOfCheckout)
                            WaitFor(1);
                        CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                        if(checkouts[NumberOfCheckout].state>0 && buyers[NumberOfBuyer].state>0 && buyers[NumberOfBuyer].NumberOfCheckout==NumberOfCheckout)
                        {                        
                            this.BeginInvoke((MethodInvoker)(()=>
                            {                            
                                ProgressOfCheckout.Step=1;
                                ProgressOfCheckout.Value=0;
                                ProgressOfCheckout.Maximum=buyers[NumberOfBuyer].CountOfGoods;
                                ProgressOfCheckout.CustomText="Обслуговується покупець "+NumberOfBuyerString;
                                CheckoutLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" почав обслуговуватись на касі "+NumberOfCheckoutString+"\n";
                                file.Write(CurrentTime+" Покупець "+NumberOfBuyerString+" почав обслуговуватись\r\n");
                            }));
                            CountOfGoodsString=Convert.ToString(buyers[NumberOfBuyer].CountOfGoods);
                            for(i=0,buyers[NumberOfBuyer].state=1; checkouts[NumberOfCheckout].state>0 && buyers[NumberOfBuyer].state>0 && i<buyers[NumberOfBuyer].CountOfGoods; i++)
                            {
                                WaitFor(250);
                                this.BeginInvoke((MethodInvoker)(()=>
                                {
                                    ProgressOfCheckout.CustomText="Покупець "+NumberOfBuyerString+" ("+Convert.ToString(i)+" товарів з "+CountOfGoodsString+")";
                                    ProgressOfCheckout.PerformStep();
                                }));
                            }
                            buyers[NumberOfBuyer].state=0;
                            CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                            if(checkouts[NumberOfCheckout].state==0 || i<buyers[NumberOfBuyer].CountOfGoods)
                                this.BeginInvoke((MethodInvoker)(()=>
                                {                                    
                                    CheckoutLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" пішов з каси "+NumberOfCheckoutString+"\n";
                                    file.Write(CurrentTime+" Покупець "+NumberOfBuyerString+" пішов з каси\r\n");
                                }));
                            else
                                this.BeginInvoke((MethodInvoker)(()=>
                                {                                    
                                    CheckoutLog.Text+=CurrentTime+" Каса "+NumberOfCheckoutString+" завершила обслуговування покупця "+NumberOfBuyerString+"\n";
                                    file.Write(CurrentTime+" Каса завершила обслуговування покупця "+NumberOfBuyerString+"\r\n");
                                }));
                            this.BeginInvoke((MethodInvoker)(()=>
                            {                            
                                ProgressOfCheckout.Step=1;
                                ProgressOfCheckout.Value=0;
                                ProgressOfCheckout.CustomText="Каса очікує покупця";
                                ProgressOfCheckout.Refresh();
                            }));
                        }
                        else
                            this.BeginInvoke((MethodInvoker)(()=>
                            {
                                CheckoutLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" пішов з каси "+NumberOfCheckoutString+"\n";
                                file.Write(CurrentTime+" Покупець "+NumberOfBuyerString+" пішов з каси\r\n");
                            }));
                        checkouts[NumberOfCheckout].capacity--;
                    }
                }
                WaitFor(10);
            }
            checkouts[NumberOfCheckout].state=0;
            CountOfWorkingCheckouts--;            
            while(checkouts[NumberOfCheckout].queue.Count>0)
            {
                NumberOfBuyer=checkouts[NumberOfCheckout].queue.Dequeue();
                buyers[NumberOfBuyer].state=3;
            }
            checkouts[NumberOfCheckout].CountOfBuyers=0;
            this.BeginInvoke((MethodInvoker)(()=>
            {
                ProgressOfCheckout.CustomText="Каса не працює";
                ProgressOfCheckout.Refresh();
                ManageCheckout.Text="Відкрити касу";
                CountOfWorkingCheckoutsLabel.Text="Кількість працюючих кас: "+Convert.ToString(CountOfWorkingCheckouts);
                file.Write(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff")+" Каса закрилась (максимальна кількість покупців: "+Convert.ToString(checkouts[NumberOfCheckout].capacity)+")\r\n");
            }));            
        }
        void RemoveBuyer(Label NumberOfBuyerLabel,CustomProgressBar ProgressOfBuyer,Button DelayBuyer,Button LeaveOrGoToCheckout,int NumberOfBuyer)
        {            
            int i,PointY=DelayBuyer.Location.Y,MaximumCountOfBuyers=Convert.ToInt32(BuyerPanel.Controls[BuyerPanel.Controls.Count-4].Text);
            this.BeginInvoke((MethodInvoker)(()=>
            {
                NumberOfBuyerLabel.Dispose();
                ProgressOfBuyer.Dispose();
                DelayBuyer.Dispose();
                LeaveOrGoToCheckout.Dispose();
                for(i=NumberOfBuyer; i<MaximumCountOfBuyers; i++)
                {
                    Control FoundNumberOfBuyer=BuyerPanel.Controls.Find("NumberOfBuyer"+Convert.ToString(i),true).FirstOrDefault();                    
                    if(FoundNumberOfBuyer!=null)
                    {
                        FoundNumberOfBuyer.Location = new System.Drawing.Point(0, PointY+7);
                        Control FoundProgressOfBuyer=BuyerPanel.Controls.Find("ProgressOfBuyer"+Convert.ToString(i),true).FirstOrDefault();
                        FoundProgressOfBuyer.Location = new System.Drawing.Point(51, PointY);
                        Control FoundDelayBuyer=BuyerPanel.Controls.Find("DelayBuyer"+Convert.ToString(i),true).FirstOrDefault();
                        if(FoundDelayBuyer.IsDisposed==false)
                            FoundDelayBuyer.Location = new System.Drawing.Point(260, PointY);                        
                        Control FoundGoToCheckout=BuyerPanel.Controls.Find("LeaveOrGoToCheckout"+Convert.ToString(i),true).FirstOrDefault();
                        FoundGoToCheckout.Location = new System.Drawing.Point(397, PointY);
                        PointY+=35;
                    }
                }
            }));
        }
        void LeaveOrGoToCheckoutProc(Label NumberOfBuyerLabel,CustomProgressBar ProgressOfBuyer,Button DelayBuyer,Button LeaveOrGoToCheckout,int NumberOfBuyer)
        {
            buyers[NumberOfBuyer].state=0;
        }
        void DelayBuyerProc(CustomProgressBar ProgressOfBuyer)
        {
            ProgressOfBuyer.Maximum+=10;
        }
        async void waitnms(int ms)
        {
            await Task.Delay(ms);
        }
        void SyncWait(int ms)
        {
            Thread thr=new Thread(()=>waitnms(ms));
            thr.Start();
        }
        async void WorkOfBuyer(Label NumberOfBuyerLabel,CustomProgressBar ProgressOfBuyer,Button DelayBuyer,Button LeaveOrGoToCheckout,int NumberOfBuyer,StreamWriter file)
        {
            int i,PlaceInQueue,NumberOfCheckout,CapacityOfCheckout,PrevNumberOfCheckout;
            string NumberOfBuyerString=Convert.ToString(NumberOfBuyer+1),NumberOfCheckoutString,CurrentTime,CountOfGoodsString;
            while(!IsHandleCreated)
                await Task.Delay(10);
            while(!ProgressOfBuyer.IsHandleCreated)
                await Task.Delay(10);
            LeaveOrGoToCheckout.Click+=new System.EventHandler((sender,e)=>LeaveOrGoToCheckoutProc(NumberOfBuyerLabel,ProgressOfBuyer,DelayBuyer,LeaveOrGoToCheckout,NumberOfBuyer));
            DelayBuyer.Click+=new System.EventHandler((sender,e)=>DelayBuyerProc(ProgressOfBuyer));            
            this.BeginInvoke((MethodInvoker)(()=>//BuyerPanel.Invoke((MethodInvoker)delegate
            {
                DelayBuyer.Enabled=false;
                ProgressOfBuyer.CustomText="У черзі в магазин";
            }));
            while(buyers[NumberOfBuyer].state>0 && CountOfBuyersInShop>=MaximumCountOfBuyersInShop)
                await Task.Delay(10);
            if(file.BaseStream!=null)
                file.Write(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff")+" Покупець зайшов у магазин\r\n");
            lock(MainProgressBar)
            {
                CountOfBuyersInShop++;            
                this.BeginInvoke((MethodInvoker)(()=>
                {
                    MainProgressBar.CustomText="Кількість покупців: "+Convert.ToString(CountOfBuyers)+"; у супермаркеті: "+Convert.ToString(CountOfBuyersInShop)+"; обслуговано: "+Convert.ToString(CountOfServicedBuyers);
                    MainProgressBar.Refresh();
                }));
            }
            this.BeginInvoke((MethodInvoker)(()=>
            {
                DelayBuyer.Enabled=true;
                LeaveOrGoToCheckout.Text="Піти на касу";
                ProgressOfBuyer.Step=1;
                ProgressOfBuyer.Value=0;
                ProgressOfBuyer.Maximum=buyers[NumberOfBuyer].CountOfGoods;
                file.Write(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff")+" Покупець почав збирати товари\r\n");
            }));
            for(i=0; buyers[NumberOfBuyer].state>0 && i<ProgressOfBuyer.Maximum; i++)
            {
                await Task.Delay(500);
                this.BeginInvoke((MethodInvoker)(()=>
                {
                    ProgressOfBuyer.PerformStep();
                    ProgressOfBuyer.CustomText="Збирає товари ("+Convert.ToString(i+1)+" з "+Convert.ToString(ProgressOfBuyer.Maximum)+")";
                }));
            }
            buyers[NumberOfBuyer].state=3;
            buyers[NumberOfBuyer].CountOfGoods=i;            
            this.BeginInvoke((MethodInvoker)(()=>
            {
                ProgressOfBuyer.Value=0;
                ProgressOfBuyer.Size=new System.Drawing.Size(340,30);
                ProgressOfBuyer.CustomText="Шукає касу";
                ProgressOfBuyer.Refresh();
                LeaveOrGoToCheckout.Text="Покинути";
            }));
            NumberOfCheckout=-1;
            PlaceInQueue=MaximumCountOfBuyersInShop+1000;
            while(NumberOfCheckout==-1 && buyers[NumberOfBuyer].state>0)
            {
                for(i=0,NumberOfCheckout=-1; i<CountOfCheckouts; i++)
                    if(checkouts[i].state>0 && checkouts[i].capacity>=checkouts[i].queue.Count+1 && checkouts[i].CountOfBuyers<PlaceInQueue)
                    {
                        PlaceInQueue=checkouts[i].CountOfBuyers;
                        NumberOfCheckout=i;
                    }
                await Task.Delay(10);
            }
            if(buyers[NumberOfBuyer].state>0)
            {
                buyers[NumberOfBuyer].NumberOfCheckout=NumberOfCheckout;
                checkouts[NumberOfCheckout].queue.Enqueue(NumberOfBuyer);
                checkouts[NumberOfCheckout].CountOfBuyers++;
                CapacityOfCheckout=checkouts[NumberOfCheckout].capacity;
                NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
                CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                this.BeginInvoke((MethodInvoker)(()=>
                {
                    ProgressOfBuyer.CustomText="У черзі на касу "+NumberOfCheckoutString;
                    ProgressOfBuyer.Refresh();
                    BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" встав у чергу на касу "+NumberOfCheckoutString+"\n";
                    file.Write(CurrentTime+" Покупець встав у чергу на касу "+NumberOfCheckoutString+"\r\n");
                }));
                while(buyers[NumberOfBuyer].state>0 && checkouts[NumberOfCheckout].state==0 && PlaceInQueue>3)
                {
                    PlaceInQueue=PlaceInQueue-(CapacityOfCheckout-checkouts[NumberOfCheckout].capacity);
                    for(i=0,PrevNumberOfCheckout=NumberOfCheckout; i<CountOfCheckouts; i++)
                        if(checkouts[i].state>0 && checkouts[i].capacity<=checkouts[i].queue.Count+1 && checkouts[i].CountOfBuyers<PlaceInQueue)
                        {
                            PlaceInQueue=checkouts[i].CountOfBuyers;
                            NumberOfCheckout=i;
                        }
                    if(NumberOfCheckout!=PrevNumberOfCheckout)
                    {
                        buyers[NumberOfBuyer].NumberOfCheckout=NumberOfCheckout;
                        checkouts[NumberOfCheckout].queue.Enqueue(NumberOfBuyer);
                        checkouts[NumberOfCheckout].CountOfBuyers++;
                        CapacityOfCheckout=checkouts[NumberOfCheckout].capacity;
                        NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
                        CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                        this.BeginInvoke((MethodInvoker)(()=>
                        {
                            ProgressOfBuyer.CustomText="Перейшов чергу на касу "+NumberOfCheckoutString;
                            ProgressOfBuyer.Refresh();
                            BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" перейшов у чергу на іншу касу "+NumberOfCheckoutString+"\n";
                            file.Write(CurrentTime+" Покупець перейшов у чергу на іншу касу "+NumberOfCheckoutString+"\r\n");
                        }));
                    }
                    await Task.Delay(1);
                }
                if(buyers[NumberOfBuyer].state>0)
                {
                    CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                    NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
                    CountOfGoodsString=Convert.ToString(buyers[NumberOfBuyer].CountOfGoods);
                    this.BeginInvoke((MethodInvoker)(()=>
                    {
                        ProgressOfBuyer.Step=1;
                        ProgressOfBuyer.Value=0;
                        ProgressOfBuyer.Maximum=buyers[NumberOfBuyer].CountOfGoods;
                        ProgressOfBuyer.CustomText="Викладає товари";
                        ProgressOfBuyer.Refresh();
                        BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" почав викладати товари на касу "+NumberOfCheckoutString+"\n";
                        file.Write(CurrentTime+" Покупець почав викладати товари на касу "+NumberOfCheckoutString+"\r\n");
                    }));
                    for(i=0; i<buyers[NumberOfBuyer].CountOfGoods && buyers[NumberOfBuyer].state>0 && checkouts[NumberOfCheckout].state>0; i++)
                    {
                        await Task.Delay(250);
                        this.BeginInvoke((MethodInvoker)(()=>
                        {
                            ProgressOfBuyer.PerformStep();
                            ProgressOfBuyer.CustomText="Викладає товари ("+Convert.ToString(i+1)+" з "+CountOfGoodsString+")";
                        }));
                    }
                    if(buyers[NumberOfBuyer].state>0 && checkouts[NumberOfCheckout].state>0)
                    {
                        buyers[NumberOfBuyer].state=2;
                        CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                        this.BeginInvoke((MethodInvoker)(()=>
                        {
                            ProgressOfBuyer.Step=1;
                            ProgressOfBuyer.Value=0;
                            ProgressOfBuyer.CustomText="Очікує обслуговування на касі "+NumberOfCheckoutString;
                            BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" встав у чергу на касу "+NumberOfCheckoutString+" у зв'язку із закриттям попередньої\n";
                            file.Write(CurrentTime+" Покупець виклав товари на касу "+NumberOfCheckoutString+" та очікує на обслуговування\r\n");
                        }));
                        while(buyers[NumberOfBuyer].state>1)
                        {
                            await Task.Delay(1);
                            if(buyers[NumberOfBuyer].state==3)
                            {
                                NumberOfCheckout=-1;
                                while(NumberOfCheckout==-1)
                                {
                                    for(i=0,PlaceInQueue=MaximumCountOfBuyersInShop+1; i<CountOfCheckouts; i++)
                                        if(checkouts[i].state>0 && checkouts[i].capacity<=checkouts[i].queue.Count+1 && checkouts[i].CountOfBuyers<PlaceInQueue)
                                        {
                                            PlaceInQueue=checkouts[i].CountOfBuyers;
                                            NumberOfCheckout=i;
                                        }
                                    await Task.Delay(1);
                                }
                                buyers[NumberOfBuyer].NumberOfCheckout=NumberOfCheckout;
                                checkouts[NumberOfCheckout].queue.Enqueue(NumberOfBuyer);
                                checkouts[NumberOfCheckout].CountOfBuyers++;
                                CapacityOfCheckout=checkouts[NumberOfCheckout].capacity;
                                NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
                                CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                                this.BeginInvoke((MethodInvoker)(()=>
                                {
                                    ProgressOfBuyer.CustomText="У черзі на касу "+NumberOfCheckoutString;
                                    ProgressOfBuyer.Refresh();
                                    BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" встав у чергу на касу "+NumberOfCheckoutString+" у зв'язку із закриттям попередньої\n";
                                    file.Write(CurrentTime+" Покупець встав у чергу на касу "+NumberOfCheckoutString+" у зв'язку із закриттям попередньої\r\n");
                                }));                                
                            }
                        }
                        if(buyers[NumberOfBuyer].state==1)
                        {
                            CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                            this.BeginInvoke((MethodInvoker)(()=>
                            {
                                ProgressOfBuyer.CustomText="Обслуговується на касі "+NumberOfCheckoutString;
                                ProgressOfBuyer.Refresh();
                                BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" обслуговується на касі "+NumberOfCheckoutString+"\n";
                                file.Write(CurrentTime+" Покупець обслуговується на касі "+NumberOfCheckoutString+"\r\n");
                            }));
                            while(buyers[NumberOfBuyer].state>0)
                                await Task.Delay(1);                            
                        }
                    }
                }
            }
            buyers[NumberOfBuyer].state=0;
            RemoveBuyer(NumberOfBuyerLabel,ProgressOfBuyer,DelayBuyer,LeaveOrGoToCheckout,NumberOfBuyer);
            lock(MainProgressBar)
            {
                CountOfBuyersInShop--;
                CountOfServicedBuyers++;
                this.BeginInvoke((MethodInvoker)(()=>
                {
                    MainProgressBar.Value--;
                    MainProgressBar.CustomText="Кількість покупців: "+Convert.ToString(CountOfBuyers)+"; у супермаркеті: "+Convert.ToString(CountOfBuyersInShop)+"; обслуговано: "+Convert.ToString(CountOfServicedBuyers);
                    MainProgressBar.Refresh();
                }));
            }
            CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
            this.BeginInvoke((MethodInvoker)(()=>
            {
                BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" покинув супермаркет\n";
                file.Write(CurrentTime+" Покупець покинув супермаркет\r\n");
            }));
        }
        void WorkOfBuyerEpidemicMode(Label NumberOfBuyerLabel,CustomProgressBar ProgressOfBuyer,Button DelayBuyer,Button LeaveOrGoToCheckout,int NumberOfBuyer,StreamWriter file)
        {
            int i,PlaceInQueue,NumberOfCheckout,CapacityOfCheckout,PrevNumberOfCheckout;
            string NumberOfBuyerString=Convert.ToString(NumberOfBuyer+1),NumberOfCheckoutString,CurrentTime,CountOfGoodsString;
            while(!IsHandleCreated)
                WaitFor(10);
            while(!ProgressOfBuyer.IsHandleCreated)
                WaitFor(10);
            LeaveOrGoToCheckout.Click+=new System.EventHandler((sender,e)=>LeaveOrGoToCheckoutProc(NumberOfBuyerLabel,ProgressOfBuyer,DelayBuyer,LeaveOrGoToCheckout,NumberOfBuyer));
            DelayBuyer.Click+=new System.EventHandler((sender,e)=>DelayBuyerProc(ProgressOfBuyer));            
            this.BeginInvoke((MethodInvoker)(()=>//BuyerPanel.Invoke((MethodInvoker)delegate
            {
                DelayBuyer.Enabled=false;
                ProgressOfBuyer.CustomText="У черзі в магазин";
            }));
            while(buyers[NumberOfBuyer].state>0 && CountOfBuyersInShop>=MaximumCountOfBuyersInShop)
                WaitFor(10);
            if(file.BaseStream!=null)
                file.Write(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff")+" Покупець зайшов у магазин\r\n");
            lock(MainProgressBar)
            {
                CountOfBuyersInShop++;            
                this.BeginInvoke((MethodInvoker)(()=>
                {
                    MainProgressBar.CustomText="Кількість покупців: "+Convert.ToString(CountOfBuyers)+"; у супермаркеті: "+Convert.ToString(CountOfBuyersInShop)+"; обслуговано: "+Convert.ToString(CountOfServicedBuyers);
                    MainProgressBar.Refresh();
                }));
            }
            this.BeginInvoke((MethodInvoker)(()=>
            {
                DelayBuyer.Enabled=true;
                LeaveOrGoToCheckout.Text="Піти на касу";
                ProgressOfBuyer.Step=1;
                ProgressOfBuyer.Value=0;
                ProgressOfBuyer.Maximum=buyers[NumberOfBuyer].CountOfGoods;
                file.Write(DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff")+" Покупець почав збирати товари\r\n");
            }));
            for(i=0; buyers[NumberOfBuyer].state>0 && i<ProgressOfBuyer.Maximum; i++)
            {
                WaitFor(500);
                this.BeginInvoke((MethodInvoker)(()=>
                {
                    ProgressOfBuyer.PerformStep();
                    ProgressOfBuyer.CustomText="Збирає товари ("+Convert.ToString(i+1)+" з "+Convert.ToString(ProgressOfBuyer.Maximum)+")";
                }));
            }
            buyers[NumberOfBuyer].state=3;
            buyers[NumberOfBuyer].CountOfGoods=i;            
            this.BeginInvoke((MethodInvoker)(()=>
            {
                ProgressOfBuyer.Value=0;
                ProgressOfBuyer.Size=new System.Drawing.Size(340,30);
                ProgressOfBuyer.CustomText="Шукає касу";
                ProgressOfBuyer.Refresh();
                LeaveOrGoToCheckout.Text="Покинути";
            }));
            NumberOfCheckout=-1;
            PlaceInQueue=MaximumCountOfBuyersInShop+1000;
            while(NumberOfCheckout==-1 && buyers[NumberOfBuyer].state>0)
            {
                for(i=0,NumberOfCheckout=-1; i<CountOfCheckouts; i++)
                    if(checkouts[i].state>0 && checkouts[i].capacity>=checkouts[i].queue.Count+1 && checkouts[i].CountOfBuyers<PlaceInQueue)
                    {
                        PlaceInQueue=checkouts[i].CountOfBuyers;
                        NumberOfCheckout=i;
                    }
                WaitFor(10);
            }
            if(buyers[NumberOfBuyer].state>0)
            {
                buyers[NumberOfBuyer].NumberOfCheckout=NumberOfCheckout;
                checkouts[NumberOfCheckout].queue.Enqueue(NumberOfBuyer);
                checkouts[NumberOfCheckout].CountOfBuyers++;
                CapacityOfCheckout=checkouts[NumberOfCheckout].capacity;
                NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
                CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                this.BeginInvoke((MethodInvoker)(()=>
                {
                    ProgressOfBuyer.CustomText="У черзі на касу "+NumberOfCheckoutString;
                    ProgressOfBuyer.Refresh();
                    BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" встав у чергу на касу "+NumberOfCheckoutString+"\n";
                    file.Write(CurrentTime+" Покупець встав у чергу на касу "+NumberOfCheckoutString+"\r\n");
                }));
                while(buyers[NumberOfBuyer].state>0 && checkouts[NumberOfCheckout].state==0 && PlaceInQueue>3)
                {
                    PlaceInQueue=PlaceInQueue-(CapacityOfCheckout-checkouts[NumberOfCheckout].capacity);
                    for(i=0,PrevNumberOfCheckout=NumberOfCheckout; i<CountOfCheckouts; i++)
                        if(checkouts[i].state>0 && checkouts[i].capacity<=checkouts[i].queue.Count+1 && checkouts[i].CountOfBuyers<PlaceInQueue)
                        {
                            PlaceInQueue=checkouts[i].CountOfBuyers;
                            NumberOfCheckout=i;
                        }
                    if(NumberOfCheckout!=PrevNumberOfCheckout)
                    {
                        buyers[NumberOfBuyer].NumberOfCheckout=NumberOfCheckout;
                        checkouts[NumberOfCheckout].queue.Enqueue(NumberOfBuyer);
                        checkouts[NumberOfCheckout].CountOfBuyers++;
                        CapacityOfCheckout=checkouts[NumberOfCheckout].capacity;
                        NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
                        CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                        this.BeginInvoke((MethodInvoker)(()=>
                        {
                            ProgressOfBuyer.CustomText="Перейшов чергу на касу "+NumberOfCheckoutString;
                            ProgressOfBuyer.Refresh();
                            BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" перейшов у чергу на іншу касу "+NumberOfCheckoutString+"\n";
                            file.Write(CurrentTime+" Покупець перейшов у чергу на іншу касу "+NumberOfCheckoutString+"\r\n");
                        }));
                    }
                    WaitFor(1);
                }
                if(buyers[NumberOfBuyer].state>0)
                {
                    CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                    NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
                    CountOfGoodsString=Convert.ToString(buyers[NumberOfBuyer].CountOfGoods);
                    this.BeginInvoke((MethodInvoker)(()=>
                    {
                        ProgressOfBuyer.Step=1;
                        ProgressOfBuyer.Value=0;
                        ProgressOfBuyer.Maximum=buyers[NumberOfBuyer].CountOfGoods;
                        ProgressOfBuyer.CustomText="Викладає товари";
                        ProgressOfBuyer.Refresh();
                        BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" почав викладати товари на касу "+NumberOfCheckoutString+"\n";
                        file.Write(CurrentTime+" Покупець почав викладати товари на касу "+NumberOfCheckoutString+"\r\n");
                    }));
                    for(i=0; i<buyers[NumberOfBuyer].CountOfGoods && buyers[NumberOfBuyer].state>0 && checkouts[NumberOfCheckout].state>0; i++)
                    {
                        WaitFor(250);
                        this.BeginInvoke((MethodInvoker)(()=>
                        {
                            ProgressOfBuyer.PerformStep();
                            ProgressOfBuyer.CustomText="Викладає товари ("+Convert.ToString(i+1)+" з "+CountOfGoodsString+")";
                        }));
                    }
                    if(buyers[NumberOfBuyer].state>0 && checkouts[NumberOfCheckout].state>0)
                    {
                        buyers[NumberOfBuyer].state=2;
                        CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                        this.BeginInvoke((MethodInvoker)(()=>
                        {
                            ProgressOfBuyer.Step=1;
                            ProgressOfBuyer.Value=0;
                            ProgressOfBuyer.CustomText="Очікує обслуговування на касі "+NumberOfCheckoutString;
                            BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" встав у чергу на касу "+NumberOfCheckoutString+" у зв'язку із закриттям попередньої\n";
                            file.Write(CurrentTime+" Покупець виклав товари на касу "+NumberOfCheckoutString+" та очікує на обслуговування\r\n");
                        }));
                        while(buyers[NumberOfBuyer].state>1)
                        {
                            WaitFor(1);
                            if(buyers[NumberOfBuyer].state==3)
                            {
                                NumberOfCheckout=-1;
                                while(NumberOfCheckout==-1)
                                {
                                    for(i=0,PlaceInQueue=MaximumCountOfBuyersInShop+1; i<CountOfCheckouts; i++)
                                        if(checkouts[i].state>0 && checkouts[i].capacity<=checkouts[i].queue.Count+1 && checkouts[i].CountOfBuyers<PlaceInQueue)
                                        {
                                            PlaceInQueue=checkouts[i].CountOfBuyers;
                                            NumberOfCheckout=i;
                                        }
                                    WaitFor(1);
                                }
                                buyers[NumberOfBuyer].NumberOfCheckout=NumberOfCheckout;
                                checkouts[NumberOfCheckout].queue.Enqueue(NumberOfBuyer);
                                checkouts[NumberOfCheckout].CountOfBuyers++;
                                CapacityOfCheckout=checkouts[NumberOfCheckout].capacity;
                                NumberOfCheckoutString=Convert.ToString(NumberOfCheckout+1);
                                CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                                this.BeginInvoke((MethodInvoker)(()=>
                                {
                                    ProgressOfBuyer.CustomText="У черзі на касу "+NumberOfCheckoutString;
                                    ProgressOfBuyer.Refresh();
                                    BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" встав у чергу на касу "+NumberOfCheckoutString+" у зв'язку із закриттям попередньої\n";
                                    file.Write(CurrentTime+" Покупець встав у чергу на касу "+NumberOfCheckoutString+" у зв'язку із закриттям попередньої\r\n");
                                }));                                
                            }
                        }
                        if(buyers[NumberOfBuyer].state==1)
                        {
                            CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
                            this.BeginInvoke((MethodInvoker)(()=>
                            {
                                ProgressOfBuyer.CustomText="Обслуговується на касі "+NumberOfCheckoutString;
                                ProgressOfBuyer.Refresh();
                                BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" обслуговується на касі "+NumberOfCheckoutString+"\n";
                                file.Write(CurrentTime+" Покупець обслуговується на касі "+NumberOfCheckoutString+"\r\n");
                            }));
                            while(buyers[NumberOfBuyer].state>0)
                                WaitFor(1);                            
                        }
                    }
                }
            }
            buyers[NumberOfBuyer].state=0;
            RemoveBuyer(NumberOfBuyerLabel,ProgressOfBuyer,DelayBuyer,LeaveOrGoToCheckout,NumberOfBuyer);
            lock(MainProgressBar)
            {
                CountOfBuyersInShop--;
                CountOfServicedBuyers++;
                this.BeginInvoke((MethodInvoker)(()=>
                {
                    MainProgressBar.Value--;
                    MainProgressBar.CustomText="Кількість покупців: "+Convert.ToString(CountOfBuyers)+"; у супермаркеті: "+Convert.ToString(CountOfBuyersInShop)+"; обслуговано: "+Convert.ToString(CountOfServicedBuyers);
                    MainProgressBar.Refresh();
                }));
            }
            CurrentTime=DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss:fff");
            this.BeginInvoke((MethodInvoker)(()=>
            {
                BuyerLog.Text+=CurrentTime+" Покупець "+NumberOfBuyerString+" покинув супермаркет\n";
                file.Write(CurrentTime+" Покупець покинув супермаркет\r\n");
            }));
        }
        public RoomOfSupermarket(int NewCountOfCheckouts,int NewCountOfCashiers,int NewCountOfBuyers,int NewMaximumCountOfBuyersInShop,byte EpidemicMode)
        {
            InitializeComponent();
            int i,j,NumberOfCountOfGoods,PointY;
            CountOfCheckouts=NewCountOfCheckouts;
            CountOfCashiers=NewCountOfCashiers;
            CountOfBuyers=NewCountOfBuyers;
            MaximumCountOfBuyersInShop=NewMaximumCountOfBuyersInShop;
			Random RandomNumber=new Random();
            MainProgressBar=new supermarket.CustomProgressBar();
            MainProgressBar.Name="MainProgressBar";
            MainProgressBar.Location = new System.Drawing.Point(475, 0);
            MainProgressBar.Size=new System.Drawing.Size(545,30);
            MainProgressBar.Step=1;
            MainProgressBar.Value=CountOfBuyers;
            MainProgressBar.Maximum=CountOfBuyers;
            Controls.Add(MainProgressBar);
            MainProgressBar.BringToFront();
            DirectoryInfo dirInfo = new DirectoryInfo("Logs\\");
            foreach (FileInfo file in dirInfo.GetFiles())
                file.Delete();
            FilesOfCheckouts=new StreamWriter[CountOfCheckouts];
            FilesOfBuyers=new StreamWriter[CountOfBuyers];
            ThreadsOfCheckouts=new Thread[CountOfCheckouts];
            checkouts=new Checkout[CountOfCheckouts];
            Label NumberOfCheckout=new Label();    
            NumberOfCheckout.Location = new System.Drawing.Point(0, 30);
            NumberOfCheckout.AutoSize=true;
            NumberOfCheckout.Text="№";
            SplitContainer.Panel1.Controls.Add(NumberOfCheckout);
            Label ConditionOfCheckout=new Label();    
            ConditionOfCheckout.Location = new System.Drawing.Point(27, 30);
            ConditionOfCheckout.AutoSize=true;
            ConditionOfCheckout.Text="Стан каси";
            SplitContainer.Panel1.Controls.Add(ConditionOfCheckout);
            Label ManagementOfCheckout=new Label();    
            ManagementOfCheckout.Location = new System.Drawing.Point(310, 30);
            ManagementOfCheckout.AutoSize=true;
            ManagementOfCheckout.Text="Управління касою";
            SplitContainer.Panel1.Controls.Add(ManagementOfCheckout);
            Label NumberOfBuyer=new Label();
            NumberOfBuyer.Location = new System.Drawing.Point(475, 30);
            NumberOfBuyer.AutoSize=true;
            NumberOfBuyer.Text="№";
            SplitContainer.Panel1.Controls.Add(NumberOfBuyer);
            Label ConditionOfBuyer=new Label();
            ConditionOfBuyer.Location = new System.Drawing.Point(521, 30);
            ConditionOfBuyer.AutoSize=true;
            ConditionOfBuyer.Text="Стан покупця";
            SplitContainer.Panel1.Controls.Add(ConditionOfBuyer);
            Label ActionsOfBuyer=new Label();
            ActionsOfBuyer.Location = new System.Drawing.Point(734, 30);
            ActionsOfBuyer.AutoSize=true;
            ActionsOfBuyer.Text="Дії покупця";
            SplitContainer.Panel1.Controls.Add(ActionsOfBuyer);
            for(i=0,PointY=0; i<CountOfCheckouts; i++,PointY+=35)
            {
                Label NewNumberOfCheckout=new Label();
                NewNumberOfCheckout.Location = new System.Drawing.Point(0, PointY+7);
                NewNumberOfCheckout.AutoSize=true;
                NewNumberOfCheckout.Text=Convert.ToString(i+1);
                CheckoutPanel.Controls.Add(NewNumberOfCheckout);
                CustomProgressBar NewProgressOfCheckout=new CustomProgressBar();
                NewProgressOfCheckout.Name="ProgressOfCheckout"+Convert.ToString(i);
                NewProgressOfCheckout.Location=new System.Drawing.Point(33, PointY);
                NewProgressOfCheckout.Size=new System.Drawing.Size(270,30);
                NewProgressOfCheckout.CustomText="Каса не працює";
                CheckoutPanel.Controls.Add(NewProgressOfCheckout);
                Button NewManagementOfCheckout=new Button();
                NewManagementOfCheckout.Name="ManagementOfCheckout"+Convert.ToString(i);
                NewManagementOfCheckout.Location = new System.Drawing.Point(313, PointY);
                NewManagementOfCheckout.Size=new System.Drawing.Size(139,30);
                NewManagementOfCheckout.Text="Відкрити касу";
                NewManagementOfCheckout.Tag=Convert.ToString(i);
                CheckoutPanel.Controls.Add(NewManagementOfCheckout);
                checkouts[i].state=1;
                checkouts[i].CountOfBuyers=0;
                checkouts[i].queue=new Queue<int>();
                int OriginalI=i;//https://www.cyberforum.ru/csharp-beginners/thread1884668.html
                FilesOfCheckouts[OriginalI]=new StreamWriter("Logs\\checkout "+Convert.ToString(OriginalI+1)+".txt");
                if(EpidemicMode==1)
                    ThreadsOfCheckouts[OriginalI]=new Thread(() => WorkOfCheckoutEpidemicMode(NewProgressOfCheckout,NewManagementOfCheckout,OriginalI,FilesOfCheckouts[OriginalI]));
                else
                    ThreadsOfCheckouts[OriginalI]=new Thread(() => WorkOfCheckout(NewProgressOfCheckout,NewManagementOfCheckout,OriginalI,FilesOfCheckouts[OriginalI]));
                ThreadsOfCheckouts[OriginalI].Name=Convert.ToString(i);
            }
            Label CountOfCashiersLabel=new Label();
            CountOfCashiersLabel.Location = new System.Drawing.Point(0,5);
            CountOfCashiersLabel.Text="Кількість операторів кас: "+Convert.ToString(CountOfCashiers);
            CountOfCashiersLabel.Size=new System.Drawing.Size(212,21);
            SplitContainer.Panel1.Controls.Add(CountOfCashiersLabel);
            CountOfCashiersLabel.BringToFront();
            CountOfWorkingCheckoutsLabel=new Label();
            CountOfWorkingCheckoutsLabel.Location = new System.Drawing.Point(217,5);
            CountOfWorkingCheckoutsLabel.AutoSize=true;
            SplitContainer.Panel1.Controls.Add(CountOfWorkingCheckoutsLabel);            
            CountOfWorkingCheckoutsLabel.BringToFront();
            CountOfWorkingCheckouts=0;
            for(i=0; i<CountOfCheckouts; i++)
            {
                j=RandomNumber.Next(i,CountOfCheckouts);
                Thread temp=ThreadsOfCheckouts[i];
                ThreadsOfCheckouts[i]=ThreadsOfCheckouts[j];
                ThreadsOfCheckouts[j]=temp;
                ThreadsOfCheckouts[i].Start();
            }
            for(int CountOfStoppedCheckouts=CountOfCheckouts-RandomNumber.Next(1,CountOfCashiers-1); CountOfStoppedCheckouts>0; CountOfStoppedCheckouts--)
                checkouts[Convert.ToInt32(ThreadsOfCheckouts[CountOfStoppedCheckouts].Name)].state=0;
            //---------------------------------------------------------------------------------------            
            int[] CountsOfGoods=new int[100];
            for(i=0; i<100; i++)
                CountsOfGoods[i]=i;
            for(i=0; i<100; i++)
            {
                j=RandomNumber.Next(i,100);
                int temp=CountsOfGoods[i];
                CountsOfGoods[i]=CountsOfGoods[j];
                CountsOfGoods[j]=temp;
            }
            buyers=new Buyer[NewCountOfBuyers];
            MainProgressBar.CustomText="Кількість покупців: "+Convert.ToString(CountOfBuyers)+"; у супермаркеті: "+Convert.ToString(CountOfBuyersInShop)+"; обслуговано: "+Convert.ToString(CountOfServicedBuyers);
            for(i=0,PointY=0,NumberOfCountOfGoods=0; i<CountOfBuyers; i++,PointY+=35)
            {
                string NumberOfControl=Convert.ToString(i);
                Label NewNumberOfBuyer=new Label();
                NewNumberOfBuyer.Name="NumberOfBuyer"+NumberOfControl;
                NewNumberOfBuyer.Location = new System.Drawing.Point(0, PointY+7);
                NewNumberOfBuyer.Size=new System.Drawing.Size(46,21);
                NewNumberOfBuyer.Text=Convert.ToString(i+1);
                BuyerPanel.Controls.Add(NewNumberOfBuyer);
                CustomProgressBar NewProgressOfBuyer=new CustomProgressBar();
                NewProgressOfBuyer.Name="ProgressOfBuyer"+NumberOfControl;
                NewProgressOfBuyer.Location = new System.Drawing.Point(51, PointY);
                NewProgressOfBuyer.Size=new System.Drawing.Size(203,30);
                NewProgressOfBuyer.CustomText="Іде у магазин";
                NewProgressOfBuyer.Tag="1";
                BuyerPanel.Controls.Add(NewProgressOfBuyer);
                Button NewDelayBuyer=new Button();
                NewDelayBuyer.Name="DelayBuyer"+NumberOfControl;
                NewDelayBuyer.Location = new System.Drawing.Point(260, PointY);
                NewDelayBuyer.Size=new System.Drawing.Size(131,30);
                NewDelayBuyer.Text="Затриматись";
                BuyerPanel.Controls.Add(NewDelayBuyer);
                Button NewGoToCashDesk=new Button();
                NewGoToCashDesk.Name="LeaveOrGoToCheckout"+NumberOfControl;
                NewGoToCashDesk.Location = new System.Drawing.Point(397, PointY);
                NewGoToCashDesk.Size=new System.Drawing.Size(131,30);
                NewGoToCashDesk.Text="Покинути";
                BuyerPanel.Controls.Add(NewGoToCashDesk);            
                int OriginalI=i;//https://www.cyberforum.ru/csharp-beginners/thread1884668.html                
                buyers[OriginalI]=new Buyer();
                buyers[OriginalI].state=4;
                buyers[OriginalI].number=OriginalI;
                buyers[OriginalI].CountOfGoods=CountsOfGoods[NumberOfCountOfGoods];
                FilesOfBuyers[OriginalI]=new StreamWriter("Logs\\buyer "+Convert.ToString(OriginalI+1)+".txt");
                if(EpidemicMode==1)
                    ThreadPool.QueueUserWorkItem(new WaitCallback((o)=>WorkOfBuyerEpidemicMode(NewNumberOfBuyer,NewProgressOfBuyer,NewDelayBuyer,NewGoToCashDesk,OriginalI,FilesOfBuyers[OriginalI])));
                else
                    ThreadPool.QueueUserWorkItem(new WaitCallback((o)=>WorkOfBuyer(NewNumberOfBuyer,NewProgressOfBuyer,NewDelayBuyer,NewGoToCashDesk,OriginalI,FilesOfBuyers[OriginalI])));
                NumberOfCountOfGoods++;
                if(NumberOfCountOfGoods==100)
                    NumberOfCountOfGoods=0;
            }
        }
        private void MainForm_SizeChanged(object sender, EventArgs e)
        {
            CheckoutPanel.Size=new System.Drawing.Size(CheckoutPanel.Size.Width,SplitContainer.SplitterDistance-50);
        }
        private void CheckoutPanel_MouseHover(object sender, EventArgs e)
        {
            CheckoutPanel.Focus();
        }
        private void BuyerPanel_MouseHover(object sender, EventArgs e)
        {
            BuyerPanel.Focus();
        }
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            int i;
            for(i=0; i<CountOfCheckouts; i++)
                checkouts[i].state=0;
            for(i=0; i<CountOfCheckouts; i++)
                FilesOfCheckouts[i].Close();
            for(i=0; i<CountOfBuyers; i++)
                FilesOfBuyers[i].Close();
        }
        private void LogSplitContainer_SizeChanged(object sender, EventArgs e)
        {
            CheckoutPanel.Size=new System.Drawing.Size(CheckoutPanel.Size.Width,SplitContainer.SplitterDistance-50);
            BuyerPanel.Size=new System.Drawing.Size(BuyerPanel.Size.Width,SplitContainer.SplitterDistance-50);
        }
        private void CheckoutLog_TextChanged(object sender, EventArgs e)
        {
            CheckoutLog.SelectionStart = CheckoutLog.Text.Length;
            CheckoutLog.ScrollToCaret();
        }
        private void BuyerLog_TextChanged(object sender, EventArgs e)
        {
            BuyerLog.SelectionStart = BuyerLog.Text.Length;
            BuyerLog.ScrollToCaret();
        }
    }
}
