namespace supermarket
{
    partial class RoomOfSupermarket
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
            this.SplitContainer = new System.Windows.Forms.SplitContainer();
            this.BuyerPanel = new System.Windows.Forms.Panel();
            this.CheckoutPanel = new System.Windows.Forms.Panel();
            this.LogSplitContainer = new System.Windows.Forms.SplitContainer();
            this.CheckoutLog = new System.Windows.Forms.RichTextBox();
            this.BuyerLog = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.SplitContainer)).BeginInit();
            this.SplitContainer.Panel1.SuspendLayout();
            this.SplitContainer.Panel2.SuspendLayout();
            this.SplitContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LogSplitContainer)).BeginInit();
            this.LogSplitContainer.Panel1.SuspendLayout();
            this.LogSplitContainer.Panel2.SuspendLayout();
            this.LogSplitContainer.SuspendLayout();
            this.SuspendLayout();
            // 
            // SplitContainer
            // 
            this.SplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SplitContainer.Location = new System.Drawing.Point(0, 0);
            this.SplitContainer.Name = "SplitContainer";
            this.SplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // SplitContainer.Panel1
            // 
            this.SplitContainer.Panel1.Controls.Add(this.BuyerPanel);
            this.SplitContainer.Panel1.Controls.Add(this.CheckoutPanel);
            // 
            // SplitContainer.Panel2
            // 
            this.SplitContainer.Panel2.Controls.Add(this.LogSplitContainer);
            this.SplitContainer.Size = new System.Drawing.Size(963, 451);
            this.SplitContainer.SplitterDistance = 365;
            this.SplitContainer.TabIndex = 7;
            // 
            // BuyerPanel
            // 
            this.BuyerPanel.AutoScroll = true;
            this.BuyerPanel.Location = new System.Drawing.Point(475, 50);
            this.BuyerPanel.Name = "BuyerPanel";
            this.BuyerPanel.Size = new System.Drawing.Size(545, 334);
            this.BuyerPanel.TabIndex = 15;
            this.BuyerPanel.MouseHover += new System.EventHandler(this.BuyerPanel_MouseHover);
            // 
            // CheckoutPanel
            // 
            this.CheckoutPanel.AutoScroll = true;
            this.CheckoutPanel.Location = new System.Drawing.Point(0, 50);
            this.CheckoutPanel.Name = "CheckoutPanel";
            this.CheckoutPanel.Size = new System.Drawing.Size(470, 333);
            this.CheckoutPanel.TabIndex = 0;
            this.CheckoutPanel.MouseHover += new System.EventHandler(this.CheckoutPanel_MouseHover);
            // 
            // LogSplitContainer
            // 
            this.LogSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LogSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.LogSplitContainer.Name = "LogSplitContainer";
            // 
            // LogSplitContainer.Panel1
            // 
            this.LogSplitContainer.Panel1.Controls.Add(this.CheckoutLog);
            // 
            // LogSplitContainer.Panel2
            // 
            this.LogSplitContainer.Panel2.Controls.Add(this.BuyerLog);
            this.LogSplitContainer.Size = new System.Drawing.Size(963, 82);
            this.LogSplitContainer.SplitterDistance = 470;
            this.LogSplitContainer.TabIndex = 0;
            this.LogSplitContainer.SizeChanged += new System.EventHandler(this.LogSplitContainer_SizeChanged);
            // 
            // CheckoutLog
            // 
            this.CheckoutLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CheckoutLog.Location = new System.Drawing.Point(0, 0);
            this.CheckoutLog.Name = "CheckoutLog";
            this.CheckoutLog.Size = new System.Drawing.Size(470, 82);
            this.CheckoutLog.TabIndex = 0;
            this.CheckoutLog.Text = "";
            this.CheckoutLog.TextChanged += new System.EventHandler(this.CheckoutLog_TextChanged);
            // 
            // BuyerLog
            // 
            this.BuyerLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BuyerLog.Location = new System.Drawing.Point(0, 0);
            this.BuyerLog.Name = "BuyerLog";
            this.BuyerLog.Size = new System.Drawing.Size(489, 82);
            this.BuyerLog.TabIndex = 0;
            this.BuyerLog.Text = "";
            this.BuyerLog.TextChanged += new System.EventHandler(this.BuyerLog_TextChanged);
            // 
            // RoomOfSupermarket
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(963, 451);
            this.Controls.Add(this.SplitContainer);
            this.Font = new System.Drawing.Font("Arial Unicode MS", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Margin = new System.Windows.Forms.Padding(5);
            this.Name = "RoomOfSupermarket";
            this.Text = "Супермаркет";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.SizeChanged += new System.EventHandler(this.MainForm_SizeChanged);
            this.SplitContainer.Panel1.ResumeLayout(false);
            this.SplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.SplitContainer)).EndInit();
            this.SplitContainer.ResumeLayout(false);
            this.LogSplitContainer.Panel1.ResumeLayout(false);
            this.LogSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.LogSplitContainer)).EndInit();
            this.LogSplitContainer.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer SplitContainer;
        private System.Windows.Forms.Panel CheckoutPanel;
        private System.Windows.Forms.Panel BuyerPanel;
        private System.Windows.Forms.SplitContainer LogSplitContainer;
        private System.Windows.Forms.RichTextBox CheckoutLog;
        private System.Windows.Forms.RichTextBox BuyerLog;
    }
}

