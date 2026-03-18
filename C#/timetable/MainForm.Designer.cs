namespace timetable
{
    partial class MainForm
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.MainMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.AppointRooms = new System.Windows.Forms.ToolStripMenuItem();
            this.SetDate = new System.Windows.Forms.ToolStripMenuItem();
            this.OrientationSession = new System.Windows.Forms.ToolStripMenuItem();
            this.MidTermExams = new System.Windows.Forms.ToolStripMenuItem();
            this.TitleLabel = new System.Windows.Forms.Label();
            this.timetable = new System.Windows.Forms.DataGridView();
            this.date = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.time = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.timetable)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MainMenu});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(669, 29);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // MainMenu
            // 
            this.MainMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.AppointRooms,
            this.SetDate,
            this.OrientationSession,
            this.MidTermExams});
            this.MainMenu.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.MainMenu.Name = "MainMenu";
            this.MainMenu.Size = new System.Drawing.Size(70, 25);
            this.MainMenu.Text = "Меню";
            // 
            // AppointRooms
            // 
            this.AppointRooms.Name = "AppointRooms";
            this.AppointRooms.Size = new System.Drawing.Size(382, 26);
            this.AppointRooms.Text = "Призначити аудиторії";
            this.AppointRooms.Click += new System.EventHandler(this.AppointRoomsClick);
            // 
            // SetDate
            // 
            this.SetDate.Name = "SetDate";
            this.SetDate.Size = new System.Drawing.Size(382, 26);
            this.SetDate.Text = "Встановити дату сесії";
            this.SetDate.Click += new System.EventHandler(this.SetDateClick);
            // 
            // OrientationSession
            // 
            this.OrientationSession.Name = "OrientationSession";
            this.OrientationSession.Size = new System.Drawing.Size(382, 26);
            this.OrientationSession.Text = "Розклад установчої осінньої сесії";
            this.OrientationSession.Click += new System.EventHandler(this.OrientationSessionClick);
            // 
            // MidTermExams
            // 
            this.MidTermExams.Name = "MidTermExams";
            this.MidTermExams.Size = new System.Drawing.Size(382, 26);
            this.MidTermExams.Text = "Розклад екзаменаційної зимової сесії";
            this.MidTermExams.Click += new System.EventHandler(this.MidTermExamsClick);
            // 
            // TitleLabel
            // 
            this.TitleLabel.Dock = System.Windows.Forms.DockStyle.Top;
            this.TitleLabel.Font = new System.Drawing.Font("Times New Roman", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.TitleLabel.Location = new System.Drawing.Point(0, 29);
            this.TitleLabel.Margin = new System.Windows.Forms.Padding(0);
            this.TitleLabel.Name = "TitleLabel";
            this.TitleLabel.Size = new System.Drawing.Size(669, 27);
            this.TitleLabel.TabIndex = 1;
            this.TitleLabel.Text = "Розклад залікової сесії з 25.01.2021 по 14.02.2021";
            this.TitleLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // timetable
            // 
            this.timetable.AllowUserToAddRows = false;
            this.timetable.AllowUserToDeleteRows = false;
            this.timetable.AllowUserToResizeColumns = false;
            this.timetable.AllowUserToResizeRows = false;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Times New Roman", 12.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.timetable.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
            this.timetable.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.timetable.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCellsExceptHeaders;
            this.timetable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.timetable.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.date,
            this.time});
            this.timetable.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            this.timetable.Location = new System.Drawing.Point(12, 59);
            this.timetable.Name = "timetable";
            this.timetable.RowHeadersVisible = false;
            this.timetable.RowTemplate.DefaultCellStyle.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.timetable.ShowCellErrors = false;
            this.timetable.ShowCellToolTips = false;
            this.timetable.ShowEditingIcon = false;
            this.timetable.ShowRowErrors = false;
            this.timetable.Size = new System.Drawing.Size(645, 226);
            this.timetable.TabIndex = 2;
            this.timetable.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.timetable_EditingControlShowing);
            // 
            // date
            // 
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Times New Roman", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.date.DefaultCellStyle = dataGridViewCellStyle2;
            this.date.Frozen = true;
            this.date.HeaderText = "Дата";
            this.date.Name = "date";
            this.date.ReadOnly = true;
            this.date.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.date.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.date.Width = 95;
            // 
            // time
            // 
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Times New Roman", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.time.DefaultCellStyle = dataGridViewCellStyle3;
            this.time.Frozen = true;
            this.time.HeaderText = "Час";
            this.time.Name = "time";
            this.time.ReadOnly = true;
            this.time.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.time.Width = 110;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(669, 297);
            this.Controls.Add(this.timetable);
            this.Controls.Add(this.TitleLabel);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Розклад сесії";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.timetable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem MainMenu;
        private System.Windows.Forms.ToolStripMenuItem SetDate;
        public System.Windows.Forms.Label TitleLabel;
        public System.Windows.Forms.DataGridView timetable;
        private System.Windows.Forms.ToolStripMenuItem MidTermExams;
        private System.Windows.Forms.ToolStripMenuItem OrientationSession;
        private System.Windows.Forms.ToolStripMenuItem AppointRooms;
        private System.Windows.Forms.DataGridViewTextBoxColumn date;
        private System.Windows.Forms.DataGridViewTextBoxColumn time;
    }
}

