namespace lab1
{
    partial class convert
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ConvertNumberToStrAndGetSumOfDigits = new System.Windows.Forms.Button();
            this.PhoneNumber = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.PhoneNumberInt = new System.Windows.Forms.TextBox();
            this.amount = new System.Windows.Forms.TextBox();
            this.GetDateOfTheNextPayment = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.DigitsSum = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.balance = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.state = new System.Windows.Forms.TextBox();
            this.DepositAccount = new System.Windows.Forms.Button();
            this.rate = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.CalcTime = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.CheckNumber = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.ClientsCountInt16 = new System.Windows.Forms.TextBox();
            this.ClientsCount = new System.Windows.Forms.TrackBar();
            this.label10 = new System.Windows.Forms.Label();
            this.BlockedClientsCount = new System.Windows.Forms.TrackBar();
            this.ManualBlock = new System.Windows.Forms.RadioButton();
            this.RandomBlock = new System.Windows.Forms.RadioButton();
            this.label11 = new System.Windows.Forms.Label();
            this.BlockingClient = new System.Windows.Forms.TextBox();
            this.block = new System.Windows.Forms.Button();
            this.BlockedClientsCountInt16 = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.ClientNumber = new System.Windows.Forms.TextBox();
            this.CheckStatus = new System.Windows.Forms.Button();
            this.GetBlockedClientsCount = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.FrequencyOfToppingUp = new System.Windows.Forms.ComboBox();
            this.DateOfPreviousPayment = new System.Windows.Forms.MaskedTextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.CountOfListenedClients = new System.Windows.Forms.TrackBar();
            this.CountOfListenedClientsUInt32 = new System.Windows.Forms.MaskedTextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.HoursOfConversation = new System.Windows.Forms.MaskedTextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.quality = new System.Windows.Forms.ComboBox();
            this.CalcVolume = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.ClientsCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BlockedClientsCount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfListenedClients)).BeginInit();
            this.SuspendLayout();
            // 
            // ConvertNumberToStrAndGetSumOfDigits
            // 
            this.ConvertNumberToStrAndGetSumOfDigits.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ConvertNumberToStrAndGetSumOfDigits.Location = new System.Drawing.Point(6, 66);
            this.ConvertNumberToStrAndGetSumOfDigits.Name = "ConvertNumberToStrAndGetSumOfDigits";
            this.ConvertNumberToStrAndGetSumOfDigits.Size = new System.Drawing.Size(279, 53);
            this.ConvertNumberToStrAndGetSumOfDigits.TabIndex = 0;
            this.ConvertNumberToStrAndGetSumOfDigits.Text = "Конвертувати номер в число та отримати суму цифр";
            this.ConvertNumberToStrAndGetSumOfDigits.UseVisualStyleBackColor = true;
            this.ConvertNumberToStrAndGetSumOfDigits.Click += new System.EventHandler(this.button1_Click);
            // 
            // PhoneNumber
            // 
            this.PhoneNumber.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PhoneNumber.Location = new System.Drawing.Point(5, 34);
            this.PhoneNumber.Name = "PhoneNumber";
            this.PhoneNumber.Size = new System.Drawing.Size(137, 26);
            this.PhoneNumber.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(2, 4);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(140, 20);
            this.label1.TabIndex = 2;
            this.label1.Text = "Номер телефону";
            // 
            // PhoneNumberInt
            // 
            this.PhoneNumberInt.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PhoneNumberInt.Location = new System.Drawing.Point(148, 34);
            this.PhoneNumberInt.Name = "PhoneNumberInt";
            this.PhoneNumberInt.ReadOnly = true;
            this.PhoneNumberInt.Size = new System.Drawing.Size(137, 26);
            this.PhoneNumberInt.TabIndex = 3;
            // 
            // amount
            // 
            this.amount.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.amount.Location = new System.Drawing.Point(579, -1);
            this.amount.Name = "amount";
            this.amount.Size = new System.Drawing.Size(75, 26);
            this.amount.TabIndex = 7;
            // 
            // GetDateOfTheNextPayment
            // 
            this.GetDateOfTheNextPayment.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GetDateOfTheNextPayment.Location = new System.Drawing.Point(447, 253);
            this.GetDateOfTheNextPayment.Name = "GetDateOfTheNextPayment";
            this.GetDateOfTheNextPayment.Size = new System.Drawing.Size(172, 49);
            this.GetDateOfTheNextPayment.TabIndex = 17;
            this.GetDateOfTheNextPayment.Text = "Дізнатись дату наступного платежу";
            this.GetDateOfTheNextPayment.UseVisualStyleBackColor = true;
            this.GetDateOfTheNextPayment.Click += new System.EventHandler(this.GetDateOfTheNextPayment_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.Location = new System.Drawing.Point(290, 5);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(97, 20);
            this.label6.TabIndex = 19;
            this.label6.Text = "Сума цифр:";
            // 
            // DigitsSum
            // 
            this.DigitsSum.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.DigitsSum.Location = new System.Drawing.Point(290, 34);
            this.DigitsSum.Name = "DigitsSum";
            this.DigitsSum.ReadOnly = true;
            this.DigitsSum.Size = new System.Drawing.Size(97, 26);
            this.DigitsSum.TabIndex = 20;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label7.Location = new System.Drawing.Point(389, 4);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(184, 20);
            this.label7.TabIndex = 21;
            this.label7.Text = "Сума поповнення (грн):";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label8.Location = new System.Drawing.Point(525, 34);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(174, 20);
            this.label8.TabIndex = 22;
            this.label8.Text = "Отримано на рахунок:";
            // 
            // balance
            // 
            this.balance.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.balance.Location = new System.Drawing.Point(705, 34);
            this.balance.Name = "balance";
            this.balance.ReadOnly = true;
            this.balance.Size = new System.Drawing.Size(76, 26);
            this.balance.TabIndex = 23;
            this.balance.Text = "0";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label9.Location = new System.Drawing.Point(389, 34);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(66, 20);
            this.label9.TabIndex = 24;
            this.label9.Text = "Статус:";
            // 
            // state
            // 
            this.state.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.state.Location = new System.Drawing.Point(461, 31);
            this.state.Name = "state";
            this.state.ReadOnly = true;
            this.state.Size = new System.Drawing.Size(58, 26);
            this.state.TabIndex = 25;
            // 
            // DepositAccount
            // 
            this.DepositAccount.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.DepositAccount.Location = new System.Drawing.Point(393, 66);
            this.DepositAccount.Name = "DepositAccount";
            this.DepositAccount.Size = new System.Drawing.Size(126, 53);
            this.DepositAccount.TabIndex = 26;
            this.DepositAccount.Text = "Поповнити рахунок";
            this.DepositAccount.UseVisualStyleBackColor = true;
            this.DepositAccount.Click += new System.EventHandler(this.DepositAccount_Click);
            // 
            // rate
            // 
            this.rate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.rate.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.rate.FormattingEnabled = true;
            this.rate.Items.AddRange(new object[] {
            "30",
            "50",
            "60",
            "90"});
            this.rate.Location = new System.Drawing.Point(529, 89);
            this.rate.Name = "rate";
            this.rate.Size = new System.Drawing.Size(132, 28);
            this.rate.TabIndex = 27;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(525, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(128, 20);
            this.label2.TabIndex = 28;
            this.label2.Text = "Тариф (коп./хв.)";
            // 
            // CalcTime
            // 
            this.CalcTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CalcTime.Location = new System.Drawing.Point(667, 64);
            this.CalcTime.Name = "CalcTime";
            this.CalcTime.Size = new System.Drawing.Size(185, 53);
            this.CalcTime.TabIndex = 29;
            this.CalcTime.Text = "Дізнатись скільки я можу розмовляти";
            this.CalcTime.UseVisualStyleBackColor = true;
            this.CalcTime.Click += new System.EventHandler(this.CalcTime_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(144, 4);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 20);
            this.label3.TabIndex = 31;
            this.label3.Text = "Число";
            // 
            // CheckNumber
            // 
            this.CheckNumber.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CheckNumber.Location = new System.Drawing.Point(290, 66);
            this.CheckNumber.Name = "CheckNumber";
            this.CheckNumber.Size = new System.Drawing.Size(97, 53);
            this.CheckNumber.TabIndex = 32;
            this.CheckNumber.Text = "Перевірка номера";
            this.CheckNumber.UseVisualStyleBackColor = true;
            this.CheckNumber.Click += new System.EventHandler(this.CheckNumber_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(5, 126);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(157, 20);
            this.label4.TabIndex = 34;
            this.label4.Text = "Кількість абонентів";
            // 
            // ClientsCountInt16
            // 
            this.ClientsCountInt16.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ClientsCountInt16.Location = new System.Drawing.Point(168, 126);
            this.ClientsCountInt16.Name = "ClientsCountInt16";
            this.ClientsCountInt16.ReadOnly = true;
            this.ClientsCountInt16.Size = new System.Drawing.Size(117, 26);
            this.ClientsCountInt16.TabIndex = 35;
            this.ClientsCountInt16.Text = "10";
            // 
            // ClientsCount
            // 
            this.ClientsCount.Location = new System.Drawing.Point(3, 157);
            this.ClientsCount.Maximum = 32767;
            this.ClientsCount.Minimum = 10;
            this.ClientsCount.Name = "ClientsCount";
            this.ClientsCount.Size = new System.Drawing.Size(279, 45);
            this.ClientsCount.TabIndex = 36;
            this.ClientsCount.TickFrequency = 3500;
            this.ClientsCount.Value = 10;
            this.ClientsCount.Scroll += new System.EventHandler(this.ClientsCount_Scroll);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label10.Location = new System.Drawing.Point(288, 182);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(266, 20);
            this.label10.TabIndex = 37;
            this.label10.Text = "Кількість заблокованих абонентів";
            // 
            // BlockedClientsCount
            // 
            this.BlockedClientsCount.Enabled = false;
            this.BlockedClientsCount.Location = new System.Drawing.Point(286, 208);
            this.BlockedClientsCount.Name = "BlockedClientsCount";
            this.BlockedClientsCount.Size = new System.Drawing.Size(279, 45);
            this.BlockedClientsCount.TabIndex = 38;
            this.BlockedClientsCount.Scroll += new System.EventHandler(this.BlockedClientsCount_Scroll);
            // 
            // ManualBlock
            // 
            this.ManualBlock.AutoSize = true;
            this.ManualBlock.Checked = true;
            this.ManualBlock.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ManualBlock.Location = new System.Drawing.Point(290, 126);
            this.ManualBlock.Name = "ManualBlock";
            this.ManualBlock.Size = new System.Drawing.Size(163, 24);
            this.ManualBlock.TabIndex = 39;
            this.ManualBlock.TabStop = true;
            this.ManualBlock.Text = "Ручне блокування";
            this.ManualBlock.UseVisualStyleBackColor = true;
            this.ManualBlock.CheckedChanged += new System.EventHandler(this.ManualBlock_CheckedChanged);
            // 
            // RandomBlock
            // 
            this.RandomBlock.AutoSize = true;
            this.RandomBlock.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.RandomBlock.Location = new System.Drawing.Point(290, 149);
            this.RandomBlock.Name = "RandomBlock";
            this.RandomBlock.Size = new System.Drawing.Size(203, 24);
            this.RandomBlock.TabIndex = 40;
            this.RandomBlock.TabStop = true;
            this.RandomBlock.Text = "Випадкове блокування";
            this.RandomBlock.UseVisualStyleBackColor = true;
            this.RandomBlock.CheckedChanged += new System.EventHandler(this.RandomBlock_CheckedChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label11.Location = new System.Drawing.Point(5, 182);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(227, 20);
            this.label11.TabIndex = 41;
            this.label11.Text = "Номер блоковного абонента";
            // 
            // BlockingClient
            // 
            this.BlockingClient.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.BlockingClient.Location = new System.Drawing.Point(9, 212);
            this.BlockingClient.Name = "BlockingClient";
            this.BlockingClient.Size = new System.Drawing.Size(56, 26);
            this.BlockingClient.TabIndex = 42;
            // 
            // block
            // 
            this.block.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.block.Location = new System.Drawing.Point(71, 212);
            this.block.Name = "block";
            this.block.Size = new System.Drawing.Size(161, 26);
            this.block.TabIndex = 43;
            this.block.Text = "Заблокувати";
            this.block.UseVisualStyleBackColor = true;
            this.block.Click += new System.EventHandler(this.block_Click);
            // 
            // BlockedClientsCountInt16
            // 
            this.BlockedClientsCountInt16.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.BlockedClientsCountInt16.Location = new System.Drawing.Point(560, 179);
            this.BlockedClientsCountInt16.Name = "BlockedClientsCountInt16";
            this.BlockedClientsCountInt16.ReadOnly = true;
            this.BlockedClientsCountInt16.Size = new System.Drawing.Size(59, 26);
            this.BlockedClientsCountInt16.TabIndex = 44;
            this.BlockedClientsCountInt16.Text = "0";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label12.Location = new System.Drawing.Point(525, 126);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(135, 20);
            this.label12.TabIndex = 45;
            this.label12.Text = "Номер абонента";
            // 
            // ClientNumber
            // 
            this.ClientNumber.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ClientNumber.Location = new System.Drawing.Point(529, 147);
            this.ClientNumber.Name = "ClientNumber";
            this.ClientNumber.Size = new System.Drawing.Size(59, 26);
            this.ClientNumber.TabIndex = 46;
            // 
            // CheckStatus
            // 
            this.CheckStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CheckStatus.Location = new System.Drawing.Point(594, 147);
            this.CheckStatus.Name = "CheckStatus";
            this.CheckStatus.Size = new System.Drawing.Size(158, 26);
            this.CheckStatus.TabIndex = 47;
            this.CheckStatus.Text = "Перевірити статус";
            this.CheckStatus.UseVisualStyleBackColor = true;
            this.CheckStatus.Click += new System.EventHandler(this.CheckStatus_Click);
            // 
            // GetBlockedClientsCount
            // 
            this.GetBlockedClientsCount.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.GetBlockedClientsCount.Location = new System.Drawing.Point(625, 182);
            this.GetBlockedClientsCount.Name = "GetBlockedClientsCount";
            this.GetBlockedClientsCount.Size = new System.Drawing.Size(229, 56);
            this.GetBlockedClientsCount.TabIndex = 48;
            this.GetBlockedClientsCount.Text = "Дізнатись кількість заблокованих абонентів";
            this.GetBlockedClientsCount.UseVisualStyleBackColor = true;
            this.GetBlockedClientsCount.Click += new System.EventHandler(this.GetBlockedClientsCount_Click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label13.Location = new System.Drawing.Point(5, 253);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(228, 20);
            this.label13.TabIndex = 49;
            this.label13.Text = "Дата попереднього платежу";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label14.Location = new System.Drawing.Point(239, 253);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(202, 20);
            this.label14.TabIndex = 50;
            this.label14.Text = "Регулярність поповнення";
            // 
            // FrequencyOfToppingUp
            // 
            this.FrequencyOfToppingUp.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.FrequencyOfToppingUp.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FrequencyOfToppingUp.FormattingEnabled = true;
            this.FrequencyOfToppingUp.Items.AddRange(new object[] {
            "кожний тиждень",
            "кожний місяць",
            "кожний рік"});
            this.FrequencyOfToppingUp.Location = new System.Drawing.Point(243, 274);
            this.FrequencyOfToppingUp.Name = "FrequencyOfToppingUp";
            this.FrequencyOfToppingUp.Size = new System.Drawing.Size(198, 28);
            this.FrequencyOfToppingUp.TabIndex = 51;
            // 
            // DateOfPreviousPayment
            // 
            this.DateOfPreviousPayment.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.DateOfPreviousPayment.Location = new System.Drawing.Point(6, 276);
            this.DateOfPreviousPayment.Mask = "00/00/0000";
            this.DateOfPreviousPayment.Name = "DateOfPreviousPayment";
            this.DateOfPreviousPayment.PromptChar = '.';
            this.DateOfPreviousPayment.Size = new System.Drawing.Size(226, 26);
            this.DateOfPreviousPayment.TabIndex = 52;
            this.DateOfPreviousPayment.ValidatingType = typeof(System.DateTime);
            this.DateOfPreviousPayment.MouseClick += new System.Windows.Forms.MouseEventHandler(this.DateOfPreviousPayment_MouseClick);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(5, 305);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(410, 20);
            this.label5.TabIndex = 53;
            this.label5.Text = "Кількість абонентів, розмови яких потрібно записати";
            // 
            // CountOfListenedClients
            // 
            this.CountOfListenedClients.Location = new System.Drawing.Point(9, 329);
            this.CountOfListenedClients.Maximum = 99999;
            this.CountOfListenedClients.Name = "CountOfListenedClients";
            this.CountOfListenedClients.Size = new System.Drawing.Size(300, 45);
            this.CountOfListenedClients.TabIndex = 54;
            this.CountOfListenedClients.TickStyle = System.Windows.Forms.TickStyle.None;
            this.CountOfListenedClients.Scroll += new System.EventHandler(this.CountOfListenedClients_Scroll);
            // 
            // CountOfListenedClientsUInt32
            // 
            this.CountOfListenedClientsUInt32.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CountOfListenedClientsUInt32.Location = new System.Drawing.Point(315, 329);
            this.CountOfListenedClientsUInt32.Mask = "00000";
            this.CountOfListenedClientsUInt32.Name = "CountOfListenedClientsUInt32";
            this.CountOfListenedClientsUInt32.PromptChar = ' ';
            this.CountOfListenedClientsUInt32.Size = new System.Drawing.Size(100, 26);
            this.CountOfListenedClientsUInt32.TabIndex = 55;
            this.CountOfListenedClientsUInt32.Text = "1000";
            this.CountOfListenedClientsUInt32.MouseClick += new System.Windows.Forms.MouseEventHandler(this.CountOfListenedClientsUInt32_MouseClick);
            this.CountOfListenedClientsUInt32.TextChanged += new System.EventHandler(this.CountOfListenedClientsUInt32_TextChanged);
            this.CountOfListenedClientsUInt32.Enter += new System.EventHandler(this.CountOfListenedClientsUInt32_TextChanged);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label15.Location = new System.Drawing.Point(421, 305);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(261, 20);
            this.label15.TabIndex = 56;
            this.label15.Text = "Кількість годин розмови кожного";
            // 
            // HoursOfConversation
            // 
            this.HoursOfConversation.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.HoursOfConversation.Location = new System.Drawing.Point(688, 299);
            this.HoursOfConversation.Mask = "00";
            this.HoursOfConversation.Name = "HoursOfConversation";
            this.HoursOfConversation.PromptChar = ' ';
            this.HoursOfConversation.Size = new System.Drawing.Size(33, 26);
            this.HoursOfConversation.TabIndex = 57;
            this.HoursOfConversation.Text = "10";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label16.Location = new System.Drawing.Point(422, 329);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(202, 20);
            this.label16.TabIndex = 58;
            this.label16.Text = "Якість запису mp3 (кбіт/с)";
            // 
            // quality
            // 
            this.quality.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.quality.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.quality.FormattingEnabled = true;
            this.quality.Items.AddRange(new object[] {
            "56",
            "64",
            "128",
            "160",
            "192",
            "256",
            "320"});
            this.quality.Location = new System.Drawing.Point(622, 328);
            this.quality.Name = "quality";
            this.quality.Size = new System.Drawing.Size(99, 28);
            this.quality.TabIndex = 59;
            // 
            // CalcVolume
            // 
            this.CalcVolume.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CalcVolume.Location = new System.Drawing.Point(729, 299);
            this.CalcVolume.Name = "CalcVolume";
            this.CalcVolume.Size = new System.Drawing.Size(118, 57);
            this.CalcVolume.TabIndex = 60;
            this.CalcVolume.Text = "Розрахувати об\'єм";
            this.CalcVolume.UseVisualStyleBackColor = true;
            this.CalcVolume.Click += new System.EventHandler(this.CalcVolume_Click);
            // 
            // convert
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(859, 368);
            this.Controls.Add(this.CalcVolume);
            this.Controls.Add(this.quality);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.HoursOfConversation);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.CountOfListenedClientsUInt32);
            this.Controls.Add(this.CountOfListenedClients);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.DateOfPreviousPayment);
            this.Controls.Add(this.FrequencyOfToppingUp);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.GetBlockedClientsCount);
            this.Controls.Add(this.CheckStatus);
            this.Controls.Add(this.ClientNumber);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.BlockedClientsCountInt16);
            this.Controls.Add(this.block);
            this.Controls.Add(this.BlockingClient);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.RandomBlock);
            this.Controls.Add(this.ManualBlock);
            this.Controls.Add(this.BlockedClientsCount);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.ClientsCount);
            this.Controls.Add(this.ClientsCountInt16);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.CheckNumber);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.CalcTime);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.rate);
            this.Controls.Add(this.DepositAccount);
            this.Controls.Add(this.state);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.balance);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.DigitsSum);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.GetDateOfTheNextPayment);
            this.Controls.Add(this.amount);
            this.Controls.Add(this.PhoneNumberInt);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.PhoneNumber);
            this.Controls.Add(this.ConvertNumberToStrAndGetSumOfDigits);
            this.MaximizeBox = false;
            this.Name = "convert";
            this.ShowInTaskbar = false;
            this.Text = "Виконання завдання";
            ((System.ComponentModel.ISupportInitialize)(this.ClientsCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BlockedClientsCount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfListenedClients)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ConvertNumberToStrAndGetSumOfDigits;
        private System.Windows.Forms.TextBox PhoneNumber;
        private System.Windows.Forms.Label label1;
        protected System.Windows.Forms.TextBox PhoneNumberInt;
        private System.Windows.Forms.TextBox amount;
        private System.Windows.Forms.Button GetDateOfTheNextPayment;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox DigitsSum;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox balance;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox state;
        private System.Windows.Forms.Button DepositAccount;
        private System.Windows.Forms.ComboBox rate;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button CalcTime;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button CheckNumber;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox ClientsCountInt16;
        private System.Windows.Forms.TrackBar ClientsCount;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TrackBar BlockedClientsCount;
        private System.Windows.Forms.RadioButton ManualBlock;
        private System.Windows.Forms.RadioButton RandomBlock;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox BlockingClient;
        private System.Windows.Forms.Button block;
        private System.Windows.Forms.TextBox BlockedClientsCountInt16;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox ClientNumber;
        private System.Windows.Forms.Button CheckStatus;
        private System.Windows.Forms.Button GetBlockedClientsCount;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.ComboBox FrequencyOfToppingUp;
        private System.Windows.Forms.MaskedTextBox DateOfPreviousPayment;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TrackBar CountOfListenedClients;
        private System.Windows.Forms.MaskedTextBox CountOfListenedClientsUInt32;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.MaskedTextBox HoursOfConversation;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.ComboBox quality;
        private System.Windows.Forms.Button CalcVolume;
    }
}