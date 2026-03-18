namespace lab2
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
        public void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.MainMenu = new System.Windows.Forms.MenuStrip();
            this.File = new System.Windows.Forms.ToolStripMenuItem();
            this.OpenFile = new System.Windows.Forms.ToolStripMenuItem();
            this.SaveResult = new System.Windows.Forms.ToolStripMenuItem();
            this.CaesarEncryptAndDecrypt = new System.Windows.Forms.ToolStripMenuItem();
            this.PasswordEncryptAndDecrypt = new System.Windows.Forms.ToolStripMenuItem();
            this.EnglishUsed = new System.Windows.Forms.ToolStripMenuItem();
            this.RussianUsed = new System.Windows.Forms.ToolStripMenuItem();
            this.UkrainianUsed = new System.Windows.Forms.ToolStripMenuItem();
            this.QuestionsAndAnswersOfStudents = new System.Windows.Forms.ToolStripMenuItem();
            this.ShowInformationAboutText = new System.Windows.Forms.ToolStripMenuItem();
            this.OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.SaveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.source = new System.Windows.Forms.RichTextBox();
            this.ContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.MenuPaste = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuSelectAll = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.MenuDeleteAll = new System.Windows.Forms.ToolStripMenuItem();
            this.data = new System.Windows.Forms.SplitContainer();
            this.result = new System.Windows.Forms.RichTextBox();
            this.MainMenu.SuspendLayout();
            this.ContextMenu.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.data)).BeginInit();
            this.data.Panel1.SuspendLayout();
            this.data.Panel2.SuspendLayout();
            this.data.SuspendLayout();
            this.SuspendLayout();
            // 
            // MainMenu
            // 
            this.MainMenu.Dock = System.Windows.Forms.DockStyle.None;
            this.MainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.File});
            this.MainMenu.Location = new System.Drawing.Point(0, 0);
            this.MainMenu.Name = "MainMenu";
            this.MainMenu.Size = new System.Drawing.Size(85, 33);
            this.MainMenu.TabIndex = 0;
            this.MainMenu.Text = "menuStrip1";
            // 
            // File
            // 
            this.File.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.OpenFile,
            this.SaveResult,
            this.CaesarEncryptAndDecrypt,
            this.PasswordEncryptAndDecrypt,
            this.EnglishUsed,
            this.RussianUsed,
            this.UkrainianUsed,
            this.QuestionsAndAnswersOfStudents,
            this.ShowInformationAboutText});
            this.File.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.File.Name = "File";
            this.File.Size = new System.Drawing.Size(77, 29);
            this.File.Text = "Меню";
            // 
            // OpenFile
            // 
            this.OpenFile.Name = "OpenFile";
            this.OpenFile.Size = new System.Drawing.Size(530, 30);
            this.OpenFile.Text = "Відкрити файл";
            this.OpenFile.Click += new System.EventHandler(this.OpenFile_Click);
            // 
            // SaveResult
            // 
            this.SaveResult.Name = "SaveResult";
            this.SaveResult.Size = new System.Drawing.Size(530, 30);
            this.SaveResult.Text = "Зберегти результат";
            this.SaveResult.Click += new System.EventHandler(this.SaveFile_Click);
            // 
            // CaesarEncryptAndDecrypt
            // 
            this.CaesarEncryptAndDecrypt.Name = "CaesarEncryptAndDecrypt";
            this.CaesarEncryptAndDecrypt.Size = new System.Drawing.Size(530, 30);
            this.CaesarEncryptAndDecrypt.Text = "Зашифрувати та розшифрувати методом Цезаря";
            this.CaesarEncryptAndDecrypt.Click += new System.EventHandler(this.CaesarEncryptAndDecrypt_Click);
            // 
            // PasswordEncryptAndDecrypt
            // 
            this.PasswordEncryptAndDecrypt.Name = "PasswordEncryptAndDecrypt";
            this.PasswordEncryptAndDecrypt.Size = new System.Drawing.Size(530, 30);
            this.PasswordEncryptAndDecrypt.Text = "Зашифрувати та розшифрувати за допогою пароля";
            this.PasswordEncryptAndDecrypt.Click += new System.EventHandler(this.PasswordEncryptAndDecrypt_Click);
            // 
            // EnglishUsed
            // 
            this.EnglishUsed.Checked = true;
            this.EnglishUsed.CheckOnClick = true;
            this.EnglishUsed.CheckState = System.Windows.Forms.CheckState.Checked;
            this.EnglishUsed.Name = "EnglishUsed";
            this.EnglishUsed.Size = new System.Drawing.Size(530, 30);
            this.EnglishUsed.Text = "English";
            this.EnglishUsed.Click += new System.EventHandler(this.SelectLanguages);
            // 
            // RussianUsed
            // 
            this.RussianUsed.CheckOnClick = true;
            this.RussianUsed.Name = "RussianUsed";
            this.RussianUsed.Size = new System.Drawing.Size(530, 30);
            this.RussianUsed.Text = "Русский язык";
            this.RussianUsed.Click += new System.EventHandler(this.SelectRussian);
            // 
            // UkrainianUsed
            // 
            this.UkrainianUsed.Checked = true;
            this.UkrainianUsed.CheckOnClick = true;
            this.UkrainianUsed.CheckState = System.Windows.Forms.CheckState.Checked;
            this.UkrainianUsed.Name = "UkrainianUsed";
            this.UkrainianUsed.Size = new System.Drawing.Size(530, 30);
            this.UkrainianUsed.Text = "Українська мова";
            this.UkrainianUsed.Click += new System.EventHandler(this.SelectLanguages);
            // 
            // QuestionsAndAnswersOfStudents
            // 
            this.QuestionsAndAnswersOfStudents.Name = "QuestionsAndAnswersOfStudents";
            this.QuestionsAndAnswersOfStudents.Size = new System.Drawing.Size(530, 30);
            this.QuestionsAndAnswersOfStudents.Text = "Конструктор питань та відповідей студентів";
            this.QuestionsAndAnswersOfStudents.Click += new System.EventHandler(this.QuestionsAndAnswersOfStudents_Click);
            // 
            // ShowInformationAboutText
            // 
            this.ShowInformationAboutText.Name = "ShowInformationAboutText";
            this.ShowInformationAboutText.Size = new System.Drawing.Size(530, 30);
            this.ShowInformationAboutText.Text = "Показати детальну інформацію про текст";
            this.ShowInformationAboutText.Click += new System.EventHandler(this.ShowInformationAboutText_Click);
            // 
            // OpenFileDialog
            // 
            this.OpenFileDialog.FileName = "openFileDialog1";
            // 
            // source
            // 
            this.source.ContextMenuStrip = this.ContextMenu;
            this.source.Dock = System.Windows.Forms.DockStyle.Fill;
            this.source.Font = new System.Drawing.Font("Courier New", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.source.Location = new System.Drawing.Point(0, 0);
            this.source.Name = "source";
            this.source.Size = new System.Drawing.Size(183, 222);
            this.source.TabIndex = 1;
            this.source.Text = "";
            // 
            // ContextMenu
            // 
            this.ContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuPaste,
            this.MenuCopy,
            this.MenuSelectAll,
            this.toolStripSeparator1,
            this.MenuDeleteAll});
            this.ContextMenu.Name = "ContextMenu";
            this.ContextMenu.Size = new System.Drawing.Size(148, 98);
            this.ContextMenu.Text = "ty6";
            // 
            // MenuPaste
            // 
            this.MenuPaste.Name = "MenuPaste";
            this.MenuPaste.Size = new System.Drawing.Size(147, 22);
            this.MenuPaste.Text = "Вставити";
            this.MenuPaste.Click += new System.EventHandler(this.MenuPaste_Click);
            // 
            // MenuCopy
            // 
            this.MenuCopy.Name = "MenuCopy";
            this.MenuCopy.Size = new System.Drawing.Size(147, 22);
            this.MenuCopy.Text = "Копіювати";
            this.MenuCopy.Click += new System.EventHandler(this.MenuCopy_Click);
            // 
            // MenuSelectAll
            // 
            this.MenuSelectAll.Name = "MenuSelectAll";
            this.MenuSelectAll.Size = new System.Drawing.Size(147, 22);
            this.MenuSelectAll.Text = "Виділити все";
            this.MenuSelectAll.Click += new System.EventHandler(this.MenuSelectAll_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(144, 6);
            // 
            // MenuDeleteAll
            // 
            this.MenuDeleteAll.Name = "MenuDeleteAll";
            this.MenuDeleteAll.Size = new System.Drawing.Size(147, 22);
            this.MenuDeleteAll.Text = "Видалити все";
            this.MenuDeleteAll.Click += new System.EventHandler(this.MenuDeleteAll_Click);
            // 
            // data
            // 
            this.data.Location = new System.Drawing.Point(12, 36);
            this.data.Name = "data";
            // 
            // data.Panel1
            // 
            this.data.Panel1.Controls.Add(this.source);
            // 
            // data.Panel2
            // 
            this.data.Panel2.Controls.Add(this.result);
            this.data.Size = new System.Drawing.Size(376, 222);
            this.data.SplitterDistance = 183;
            this.data.TabIndex = 2;
            // 
            // result
            // 
            this.result.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.result.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.result.ContextMenuStrip = this.ContextMenu;
            this.result.Dock = System.Windows.Forms.DockStyle.Fill;
            this.result.Font = new System.Drawing.Font("Courier New", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.result.Location = new System.Drawing.Point(0, 0);
            this.result.Name = "result";
            this.result.ReadOnly = true;
            this.result.Size = new System.Drawing.Size(189, 222);
            this.result.TabIndex = 4;
            this.result.Text = "";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(408, 269);
            this.Controls.Add(this.data);
            this.Controls.Add(this.MainMenu);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.MainMenu;
            this.Name = "MainForm";
            this.Text = "lab2";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Resize += new System.EventHandler(this.MainForm_Resize);
            this.MainMenu.ResumeLayout(false);
            this.MainMenu.PerformLayout();
            this.ContextMenu.ResumeLayout(false);
            this.data.Panel1.ResumeLayout(false);
            this.data.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.data)).EndInit();
            this.data.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip MainMenu;
        private System.Windows.Forms.ToolStripMenuItem SaveResult;
        private System.Windows.Forms.ToolStripMenuItem CaesarEncryptAndDecrypt;
        private System.Windows.Forms.ToolStripMenuItem OpenFile;
        private System.Windows.Forms.OpenFileDialog OpenFileDialog;
        private System.Windows.Forms.ToolStripMenuItem PasswordEncryptAndDecrypt;
        public System.Windows.Forms.ToolStripMenuItem RussianUsed;
        public System.Windows.Forms.ToolStripMenuItem UkrainianUsed;
        public System.Windows.Forms.ToolStripMenuItem File;
        public System.Windows.Forms.ToolStripMenuItem EnglishUsed;
        public System.Windows.Forms.RichTextBox source;
        public System.Windows.Forms.RichTextBox result;
        public System.Windows.Forms.SplitContainer data;
        public System.Windows.Forms.ContextMenuStrip ContextMenu;
        private System.Windows.Forms.ToolStripMenuItem MenuSelectAll;
        private System.Windows.Forms.ToolStripMenuItem MenuDeleteAll;
        private System.Windows.Forms.ToolStripMenuItem MenuCopy;
        private System.Windows.Forms.ToolStripMenuItem MenuPaste;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem QuestionsAndAnswersOfStudents;
        private System.Windows.Forms.SaveFileDialog SaveFileDialog;
        private System.Windows.Forms.ToolStripMenuItem ShowInformationAboutText;
    }
}

