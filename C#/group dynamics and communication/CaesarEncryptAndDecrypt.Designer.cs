namespace lab2
{
    partial class CaesarEncryptAndDecrypt
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CaesarEncryptAndDecrypt));
            this.close = new System.Windows.Forms.Button();
            this.encrypt = new System.Windows.Forms.Button();
            this.decrypt = new System.Windows.Forms.Button();
            this.RadioButtonTextFromForm = new System.Windows.Forms.RadioButton();
            this.OpenFile = new System.Windows.Forms.Button();
            this.RadioButtonTextFromFile = new System.Windows.Forms.RadioButton();
            this.FilePath = new System.Windows.Forms.TextBox();
            this.OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.ProgressBar = new System.Windows.Forms.ProgressBar();
            this.SuspendLayout();
            // 
            // close
            // 
            this.close.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.close.Location = new System.Drawing.Point(328, 81);
            this.close.Name = "close";
            this.close.Size = new System.Drawing.Size(152, 31);
            this.close.TabIndex = 19;
            this.close.Text = "Відмінити";
            this.close.UseVisualStyleBackColor = true;
            this.close.Click += new System.EventHandler(this.close_Click);
            // 
            // encrypt
            // 
            this.encrypt.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.encrypt.Location = new System.Drawing.Point(12, 81);
            this.encrypt.Name = "encrypt";
            this.encrypt.Size = new System.Drawing.Size(152, 31);
            this.encrypt.TabIndex = 18;
            this.encrypt.Text = "Зашифрувати";
            this.encrypt.UseVisualStyleBackColor = true;
            this.encrypt.Click += new System.EventHandler(this.encrypt_Click);
            // 
            // decrypt
            // 
            this.decrypt.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.decrypt.Location = new System.Drawing.Point(170, 81);
            this.decrypt.Name = "decrypt";
            this.decrypt.Size = new System.Drawing.Size(152, 31);
            this.decrypt.TabIndex = 17;
            this.decrypt.Text = "Розшифрувати";
            this.decrypt.UseVisualStyleBackColor = true;
            this.decrypt.Click += new System.EventHandler(this.decrypt_Click);
            // 
            // RadioButtonTextFromForm
            // 
            this.RadioButtonTextFromForm.AutoSize = true;
            this.RadioButtonTextFromForm.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.RadioButtonTextFromForm.Location = new System.Drawing.Point(176, 12);
            this.RadioButtonTextFromForm.Name = "RadioButtonTextFromForm";
            this.RadioButtonTextFromForm.Size = new System.Drawing.Size(164, 28);
            this.RadioButtonTextFromForm.TabIndex = 16;
            this.RadioButtonTextFromForm.Text = "Текст із форми";
            this.RadioButtonTextFromForm.UseVisualStyleBackColor = true;
            this.RadioButtonTextFromForm.CheckedChanged += new System.EventHandler(this.RadioButtonTextFromForm_CheckedChanged);
            // 
            // OpenFile
            // 
            this.OpenFile.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.OpenFile.Location = new System.Drawing.Point(447, 46);
            this.OpenFile.Name = "OpenFile";
            this.OpenFile.Size = new System.Drawing.Size(35, 29);
            this.OpenFile.TabIndex = 15;
            this.OpenFile.Text = "...";
            this.OpenFile.UseVisualStyleBackColor = true;
            this.OpenFile.Click += new System.EventHandler(this.OpenFile_Click);
            // 
            // RadioButtonTextFromFile
            // 
            this.RadioButtonTextFromFile.AutoSize = true;
            this.RadioButtonTextFromFile.Checked = true;
            this.RadioButtonTextFromFile.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.RadioButtonTextFromFile.Location = new System.Drawing.Point(12, 12);
            this.RadioButtonTextFromFile.Name = "RadioButtonTextFromFile";
            this.RadioButtonTextFromFile.Size = new System.Drawing.Size(158, 28);
            this.RadioButtonTextFromFile.TabIndex = 14;
            this.RadioButtonTextFromFile.TabStop = true;
            this.RadioButtonTextFromFile.Text = "Текст із файлу";
            this.RadioButtonTextFromFile.UseVisualStyleBackColor = true;
            this.RadioButtonTextFromFile.CheckedChanged += new System.EventHandler(this.RadioButtonTextFromFile_CheckedChanged);
            // 
            // FilePath
            // 
            this.FilePath.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.FilePath.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.FilePath.Location = new System.Drawing.Point(12, 46);
            this.FilePath.Name = "FilePath";
            this.FilePath.ReadOnly = true;
            this.FilePath.Size = new System.Drawing.Size(429, 29);
            this.FilePath.TabIndex = 11;
            // 
            // ProgressBar
            // 
            this.ProgressBar.Location = new System.Drawing.Point(341, 12);
            this.ProgressBar.Name = "ProgressBar";
            this.ProgressBar.Size = new System.Drawing.Size(139, 28);
            this.ProgressBar.TabIndex = 20;
            // 
            // CaesarEncryptAndDecrypt
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(493, 130);
            this.Controls.Add(this.ProgressBar);
            this.Controls.Add(this.close);
            this.Controls.Add(this.encrypt);
            this.Controls.Add(this.decrypt);
            this.Controls.Add(this.RadioButtonTextFromForm);
            this.Controls.Add(this.OpenFile);
            this.Controls.Add(this.RadioButtonTextFromFile);
            this.Controls.Add(this.FilePath);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "CaesarEncryptAndDecrypt";
            this.Text = "Зашифрувати та розшифрувати методом Цезаря";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button close;
        public System.Windows.Forms.Button encrypt;
        private System.Windows.Forms.Button decrypt;
        private System.Windows.Forms.Button OpenFile;
        private System.Windows.Forms.RadioButton RadioButtonTextFromFile;
        private System.Windows.Forms.TextBox FilePath;
        public System.Windows.Forms.RadioButton RadioButtonTextFromForm;
        private System.Windows.Forms.OpenFileDialog OpenFileDialog;
        private System.Windows.Forms.ProgressBar ProgressBar;
    }
}