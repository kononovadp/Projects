namespace lab2
{
    partial class EncryptAndDecryptWithPassword
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EncryptAndDecryptWithPassword));
            this.FilePath = new System.Windows.Forms.TextBox();
            this.password = new System.Windows.Forms.RichTextBox();
            this.RadioButtonTextFromFile = new System.Windows.Forms.RadioButton();
            this.OpenFile = new System.Windows.Forms.Button();
            this.RadioButtonTextFromForm = new System.Windows.Forms.RadioButton();
            this.LabelPassword = new System.Windows.Forms.Label();
            this.decrypt = new System.Windows.Forms.Button();
            this.encrypt = new System.Windows.Forms.Button();
            this.close = new System.Windows.Forms.Button();
            this.OpenPasswordFile = new System.Windows.Forms.Button();
            this.OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.SaveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.ProgressBar = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // FilePath
            // 
            this.FilePath.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.FilePath.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FilePath.Location = new System.Drawing.Point(12, 46);
            this.FilePath.Name = "FilePath";
            this.FilePath.ReadOnly = true;
            this.FilePath.Size = new System.Drawing.Size(429, 29);
            this.FilePath.TabIndex = 1;
            // 
            // password
            // 
            this.password.Font = new System.Drawing.Font("Courier New", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.password.Location = new System.Drawing.Point(12, 105);
            this.password.Name = "password";
            this.password.Size = new System.Drawing.Size(429, 96);
            this.password.TabIndex = 3;
            this.password.Text = "";
            // 
            // RadioButtonTextFromFile
            // 
            this.RadioButtonTextFromFile.AutoSize = true;
            this.RadioButtonTextFromFile.Checked = true;
            this.RadioButtonTextFromFile.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.RadioButtonTextFromFile.Location = new System.Drawing.Point(12, 12);
            this.RadioButtonTextFromFile.Name = "RadioButtonTextFromFile";
            this.RadioButtonTextFromFile.Size = new System.Drawing.Size(158, 28);
            this.RadioButtonTextFromFile.TabIndex = 4;
            this.RadioButtonTextFromFile.TabStop = true;
            this.RadioButtonTextFromFile.Text = "Текст із файлу";
            this.RadioButtonTextFromFile.UseVisualStyleBackColor = true;
            this.RadioButtonTextFromFile.CheckedChanged += new System.EventHandler(this.RadioButtonTextFromFile_CheckedChanged);
            // 
            // OpenFile
            // 
            this.OpenFile.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OpenFile.Location = new System.Drawing.Point(447, 46);
            this.OpenFile.Name = "OpenFile";
            this.OpenFile.Size = new System.Drawing.Size(35, 29);
            this.OpenFile.TabIndex = 5;
            this.OpenFile.Text = "...";
            this.OpenFile.UseVisualStyleBackColor = true;
            this.OpenFile.Click += new System.EventHandler(this.OpenFile_Click);
            // 
            // RadioButtonTextFromForm
            // 
            this.RadioButtonTextFromForm.AutoSize = true;
            this.RadioButtonTextFromForm.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.RadioButtonTextFromForm.Location = new System.Drawing.Point(172, 12);
            this.RadioButtonTextFromForm.Name = "RadioButtonTextFromForm";
            this.RadioButtonTextFromForm.Size = new System.Drawing.Size(164, 28);
            this.RadioButtonTextFromForm.TabIndex = 6;
            this.RadioButtonTextFromForm.Text = "Текст із форми";
            this.RadioButtonTextFromForm.UseVisualStyleBackColor = true;
            this.RadioButtonTextFromForm.CheckedChanged += new System.EventHandler(this.RadioButtonTextFromForm_CheckedChanged);
            // 
            // LabelPassword
            // 
            this.LabelPassword.AutoSize = true;
            this.LabelPassword.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.LabelPassword.Location = new System.Drawing.Point(12, 78);
            this.LabelPassword.Name = "LabelPassword";
            this.LabelPassword.Size = new System.Drawing.Size(76, 24);
            this.LabelPassword.TabIndex = 2;
            this.LabelPassword.Text = "Пароль";
            // 
            // decrypt
            // 
            this.decrypt.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.decrypt.Location = new System.Drawing.Point(172, 207);
            this.decrypt.Name = "decrypt";
            this.decrypt.Size = new System.Drawing.Size(152, 31);
            this.decrypt.TabIndex = 8;
            this.decrypt.Text = "Розшифрувати";
            this.decrypt.UseVisualStyleBackColor = true;
            this.decrypt.Click += new System.EventHandler(this.decrypt_Click);
            // 
            // encrypt
            // 
            this.encrypt.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.encrypt.Location = new System.Drawing.Point(12, 207);
            this.encrypt.Name = "encrypt";
            this.encrypt.Size = new System.Drawing.Size(152, 31);
            this.encrypt.TabIndex = 9;
            this.encrypt.Text = "Зашифрувати";
            this.encrypt.UseVisualStyleBackColor = true;
            this.encrypt.Click += new System.EventHandler(this.encrypt_Click);
            // 
            // close
            // 
            this.close.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.close.Location = new System.Drawing.Point(330, 207);
            this.close.Name = "close";
            this.close.Size = new System.Drawing.Size(152, 31);
            this.close.TabIndex = 10;
            this.close.Text = "Відмінити";
            this.close.UseVisualStyleBackColor = true;
            this.close.Click += new System.EventHandler(this.close_Click);
            // 
            // OpenPasswordFile
            // 
            this.OpenPasswordFile.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OpenPasswordFile.Location = new System.Drawing.Point(445, 172);
            this.OpenPasswordFile.Name = "OpenPasswordFile";
            this.OpenPasswordFile.Size = new System.Drawing.Size(35, 29);
            this.OpenPasswordFile.TabIndex = 11;
            this.OpenPasswordFile.Text = "...";
            this.OpenPasswordFile.UseVisualStyleBackColor = true;
            this.OpenPasswordFile.Click += new System.EventHandler(this.OpenPasswordFile_Click);
            // 
            // OpenFileDialog
            // 
            this.OpenFileDialog.FileName = "openFileDialog1";
            // 
            // ProgressBar
            // 
            this.ProgressBar.Location = new System.Drawing.Point(343, 12);
            this.ProgressBar.Name = "ProgressBar";
            this.ProgressBar.Size = new System.Drawing.Size(139, 28);
            this.ProgressBar.TabIndex = 21;
            // 
            // EncryptAndDecryptWithPassword
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(492, 247);
            this.Controls.Add(this.ProgressBar);
            this.Controls.Add(this.OpenPasswordFile);
            this.Controls.Add(this.close);
            this.Controls.Add(this.encrypt);
            this.Controls.Add(this.decrypt);
            this.Controls.Add(this.RadioButtonTextFromForm);
            this.Controls.Add(this.OpenFile);
            this.Controls.Add(this.RadioButtonTextFromFile);
            this.Controls.Add(this.password);
            this.Controls.Add(this.LabelPassword);
            this.Controls.Add(this.FilePath);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "EncryptAndDecryptWithPassword";
            this.Text = "Зашифрувати та розшифрувати за допогою пароля";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox FilePath;
        private System.Windows.Forms.RichTextBox password;
        private System.Windows.Forms.RadioButton RadioButtonTextFromFile;
        private System.Windows.Forms.Button OpenFile;
        private System.Windows.Forms.RadioButton RadioButtonTextFromForm;
        private System.Windows.Forms.Label LabelPassword;
        private System.Windows.Forms.Button decrypt;
        private System.Windows.Forms.Button close;
        public System.Windows.Forms.Button encrypt;
        private System.Windows.Forms.Button OpenPasswordFile;
        private System.Windows.Forms.OpenFileDialog OpenFileDialog;
        private System.Windows.Forms.SaveFileDialog SaveFileDialog;
        private System.Windows.Forms.ProgressBar ProgressBar;

    }
}