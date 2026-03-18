namespace timetable
{
    partial class SelectDateForm
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
            this.StartDateLabel = new System.Windows.Forms.Label();
            this.EndDateLabel = new System.Windows.Forms.Label();
            this.StartDate = new System.Windows.Forms.DateTimePicker();
            this.EndDate = new System.Windows.Forms.DateTimePicker();
            this.SelectDate = new System.Windows.Forms.Button();
            this.SelectDateCancel = new System.Windows.Forms.Button();
            this.StreamsCountLabel = new System.Windows.Forms.Label();
            this.StreamsCount = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.StreamsCount)).BeginInit();
            this.SuspendLayout();
            // 
            // StartDateLabel
            // 
            this.StartDateLabel.AutoSize = true;
            this.StartDateLabel.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.StartDateLabel.Location = new System.Drawing.Point(12, 9);
            this.StartDateLabel.Name = "StartDateLabel";
            this.StartDateLabel.Size = new System.Drawing.Size(157, 21);
            this.StartDateLabel.TabIndex = 0;
            this.StartDateLabel.Text = "Дата початку сесії";
            // 
            // EndDateLabel
            // 
            this.EndDateLabel.AutoSize = true;
            this.EndDateLabel.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.EndDateLabel.Location = new System.Drawing.Point(175, 9);
            this.EndDateLabel.Name = "EndDateLabel";
            this.EndDateLabel.Size = new System.Drawing.Size(187, 21);
            this.EndDateLabel.TabIndex = 1;
            this.EndDateLabel.Text = "Дата завершення сесії";
            // 
            // StartDate
            // 
            this.StartDate.CalendarFont = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.StartDate.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.StartDate.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.StartDate.Location = new System.Drawing.Point(16, 33);
            this.StartDate.Name = "StartDate";
            this.StartDate.Size = new System.Drawing.Size(153, 29);
            this.StartDate.TabIndex = 2;
            // 
            // EndDate
            // 
            this.EndDate.CalendarFont = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.EndDate.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.EndDate.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.EndDate.Location = new System.Drawing.Point(179, 33);
            this.EndDate.Name = "EndDate";
            this.EndDate.Size = new System.Drawing.Size(183, 29);
            this.EndDate.TabIndex = 3;
            // 
            // SelectDate
            // 
            this.SelectDate.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.SelectDate.Location = new System.Drawing.Point(179, 66);
            this.SelectDate.Name = "SelectDate";
            this.SelectDate.Size = new System.Drawing.Size(183, 44);
            this.SelectDate.TabIndex = 4;
            this.SelectDate.Text = "ОК";
            this.SelectDate.UseVisualStyleBackColor = true;
            this.SelectDate.Click += new System.EventHandler(this.SelectDate_Click);
            // 
            // SelectDateCancel
            // 
            this.SelectDateCancel.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.SelectDateCancel.Location = new System.Drawing.Point(372, 66);
            this.SelectDateCancel.Name = "SelectDateCancel";
            this.SelectDateCancel.Size = new System.Drawing.Size(122, 44);
            this.SelectDateCancel.TabIndex = 5;
            this.SelectDateCancel.Text = "Скасувати";
            this.SelectDateCancel.UseVisualStyleBackColor = true;
            this.SelectDateCancel.Click += new System.EventHandler(this.SelectDateCancel_Click);
            // 
            // StreamsCountLabel
            // 
            this.StreamsCountLabel.AutoSize = true;
            this.StreamsCountLabel.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.StreamsCountLabel.Location = new System.Drawing.Point(368, 9);
            this.StreamsCountLabel.Name = "StreamsCountLabel";
            this.StreamsCountLabel.Size = new System.Drawing.Size(126, 21);
            this.StreamsCountLabel.TabIndex = 6;
            this.StreamsCountLabel.Text = "Кількість груп";
            // 
            // StreamsCount
            // 
            this.StreamsCount.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StreamsCount.Location = new System.Drawing.Point(372, 33);
            this.StreamsCount.Maximum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.StreamsCount.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.StreamsCount.Name = "StreamsCount";
            this.StreamsCount.Size = new System.Drawing.Size(122, 29);
            this.StreamsCount.TabIndex = 7;
            this.StreamsCount.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // SelectDateForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(500, 122);
            this.Controls.Add(this.StreamsCount);
            this.Controls.Add(this.StreamsCountLabel);
            this.Controls.Add(this.SelectDateCancel);
            this.Controls.Add(this.SelectDate);
            this.Controls.Add(this.EndDate);
            this.Controls.Add(this.StartDate);
            this.Controls.Add(this.EndDateLabel);
            this.Controls.Add(this.StartDateLabel);
            this.MaximizeBox = false;
            this.Name = "SelectDateForm";
            this.Text = "Вибрати дату";
            this.Load += new System.EventHandler(this.SelectDateForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.StreamsCount)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label StartDateLabel;
        private System.Windows.Forms.Label EndDateLabel;
        private System.Windows.Forms.DateTimePicker StartDate;
        private System.Windows.Forms.DateTimePicker EndDate;
        private System.Windows.Forms.Button SelectDate;
        private System.Windows.Forms.Button SelectDateCancel;
        private System.Windows.Forms.Label StreamsCountLabel;
        private System.Windows.Forms.NumericUpDown StreamsCount;
    }
}