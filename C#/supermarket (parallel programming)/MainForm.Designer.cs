namespace supermarket
{
    partial class MainForm
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
            this.NormalMode = new System.Windows.Forms.RadioButton();
            this.EpidemicMode = new System.Windows.Forms.RadioButton();
            this.CountOfCheckoutsLabel = new System.Windows.Forms.Label();
            this.CountOfCheckouts = new System.Windows.Forms.NumericUpDown();
            this.CountOfCashiersLabel = new System.Windows.Forms.Label();
            this.CountOfCashiers = new System.Windows.Forms.NumericUpDown();
            this.CountOfBuyersLabel = new System.Windows.Forms.Label();
            this.CountOfBuyers = new System.Windows.Forms.NumericUpDown();
            this.MaximumCountOfBuyersInShopLabel = new System.Windows.Forms.Label();
            this.MaximumCountOfBuyersInShop = new System.Windows.Forms.NumericUpDown();
            this.ok = new System.Windows.Forms.Button();
            this.cancel = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfCheckouts)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfCashiers)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfBuyers)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MaximumCountOfBuyersInShop)).BeginInit();
            this.SuspendLayout();
            // 
            // NormalMode
            // 
            this.NormalMode.AutoSize = true;
            this.NormalMode.Location = new System.Drawing.Point(12, 0);
            this.NormalMode.Name = "NormalMode";
            this.NormalMode.Size = new System.Drawing.Size(275, 28);
            this.NormalMode.TabIndex = 0;
            this.NormalMode.TabStop = true;
            this.NormalMode.Text = "Нормальний режим роботи";
            this.NormalMode.UseVisualStyleBackColor = true;
            this.NormalMode.MouseClick += new System.Windows.Forms.MouseEventHandler(this.NormalMode_MouseClick);
            // 
            // EpidemicMode
            // 
            this.EpidemicMode.AutoSize = true;
            this.EpidemicMode.Location = new System.Drawing.Point(293, 0);
            this.EpidemicMode.Name = "EpidemicMode";
            this.EpidemicMode.Size = new System.Drawing.Size(164, 28);
            this.EpidemicMode.TabIndex = 1;
            this.EpidemicMode.TabStop = true;
            this.EpidemicMode.Text = "Режим епідемії";
            this.EpidemicMode.UseVisualStyleBackColor = true;
            this.EpidemicMode.MouseClick += new System.Windows.Forms.MouseEventHandler(this.EpidemicMode_MouseClick);
            // 
            // CountOfCheckoutsLabel
            // 
            this.CountOfCheckoutsLabel.AutoSize = true;
            this.CountOfCheckoutsLabel.Location = new System.Drawing.Point(8, 31);
            this.CountOfCheckoutsLabel.Name = "CountOfCheckoutsLabel";
            this.CountOfCheckoutsLabel.Size = new System.Drawing.Size(130, 24);
            this.CountOfCheckoutsLabel.TabIndex = 2;
            this.CountOfCheckoutsLabel.Text = "Кількість кас:";
            // 
            // CountOfCheckouts
            // 
            this.CountOfCheckouts.Location = new System.Drawing.Point(192, 26);
            this.CountOfCheckouts.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.CountOfCheckouts.Name = "CountOfCheckouts";
            this.CountOfCheckouts.Size = new System.Drawing.Size(66, 29);
            this.CountOfCheckouts.TabIndex = 3;
            this.CountOfCheckouts.Value = new decimal(new int[] {
            15,
            0,
            0,
            0});
            // 
            // CountOfCashiersLabel
            // 
            this.CountOfCashiersLabel.AutoSize = true;
            this.CountOfCashiersLabel.Location = new System.Drawing.Point(537, 26);
            this.CountOfCashiersLabel.Name = "CountOfCashiersLabel";
            this.CountOfCashiersLabel.Size = new System.Drawing.Size(167, 24);
            this.CountOfCashiersLabel.TabIndex = 4;
            this.CountOfCashiersLabel.Text = "Кількість касирів:";
            // 
            // CountOfCashiers
            // 
            this.CountOfCashiers.Location = new System.Drawing.Point(710, 23);
            this.CountOfCashiers.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.CountOfCashiers.Name = "CountOfCashiers";
            this.CountOfCashiers.Size = new System.Drawing.Size(66, 29);
            this.CountOfCashiers.TabIndex = 5;
            this.CountOfCashiers.Value = new decimal(new int[] {
            12,
            0,
            0,
            0});
            // 
            // CountOfBuyersLabel
            // 
            this.CountOfBuyersLabel.AutoSize = true;
            this.CountOfBuyersLabel.Location = new System.Drawing.Point(8, 61);
            this.CountOfBuyersLabel.Name = "CountOfBuyersLabel";
            this.CountOfBuyersLabel.Size = new System.Drawing.Size(178, 24);
            this.CountOfBuyersLabel.TabIndex = 6;
            this.CountOfBuyersLabel.Text = "Кількість покупців:";
            // 
            // CountOfBuyers
            // 
            this.CountOfBuyers.Location = new System.Drawing.Point(192, 58);
            this.CountOfBuyers.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.CountOfBuyers.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.CountOfBuyers.Name = "CountOfBuyers";
            this.CountOfBuyers.Size = new System.Drawing.Size(66, 29);
            this.CountOfBuyers.TabIndex = 7;
            this.CountOfBuyers.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // MaximumCountOfBuyersInShopLabel
            // 
            this.MaximumCountOfBuyersInShopLabel.AutoSize = true;
            this.MaximumCountOfBuyersInShopLabel.Location = new System.Drawing.Point(264, 61);
            this.MaximumCountOfBuyersInShopLabel.Name = "MaximumCountOfBuyersInShopLabel";
            this.MaximumCountOfBuyersInShopLabel.Size = new System.Drawing.Size(440, 24);
            this.MaximumCountOfBuyersInShopLabel.TabIndex = 8;
            this.MaximumCountOfBuyersInShopLabel.Text = "Максимальна кількість покупців у супермаркеті:";
            // 
            // MaximumCountOfBuyersInShop
            // 
            this.MaximumCountOfBuyersInShop.Location = new System.Drawing.Point(710, 59);
            this.MaximumCountOfBuyersInShop.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.MaximumCountOfBuyersInShop.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.MaximumCountOfBuyersInShop.Name = "MaximumCountOfBuyersInShop";
            this.MaximumCountOfBuyersInShop.Size = new System.Drawing.Size(66, 29);
            this.MaximumCountOfBuyersInShop.TabIndex = 9;
            this.MaximumCountOfBuyersInShop.Value = new decimal(new int[] {
            90,
            0,
            0,
            0});
            // 
            // ok
            // 
            this.ok.Location = new System.Drawing.Point(12, 111);
            this.ok.Name = "ok";
            this.ok.Size = new System.Drawing.Size(121, 37);
            this.ok.TabIndex = 10;
            this.ok.Text = "ОК";
            this.ok.UseVisualStyleBackColor = true;
            this.ok.Click += new System.EventHandler(this.ok_Click);
            // 
            // cancel
            // 
            this.cancel.Location = new System.Drawing.Point(655, 111);
            this.cancel.Name = "cancel";
            this.cancel.Size = new System.Drawing.Size(121, 37);
            this.cancel.TabIndex = 11;
            this.cancel.Text = "Відмінити";
            this.cancel.UseVisualStyleBackColor = true;
            this.cancel.Click += new System.EventHandler(this.cancel_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(793, 172);
            this.Controls.Add(this.cancel);
            this.Controls.Add(this.ok);
            this.Controls.Add(this.MaximumCountOfBuyersInShop);
            this.Controls.Add(this.MaximumCountOfBuyersInShopLabel);
            this.Controls.Add(this.CountOfBuyers);
            this.Controls.Add(this.CountOfBuyersLabel);
            this.Controls.Add(this.CountOfCashiers);
            this.Controls.Add(this.CountOfCashiersLabel);
            this.Controls.Add(this.CountOfCheckouts);
            this.Controls.Add(this.CountOfCheckoutsLabel);
            this.Controls.Add(this.EpidemicMode);
            this.Controls.Add(this.NormalMode);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainForm";
            this.Text = "Налаштування супермаркету";
            ((System.ComponentModel.ISupportInitialize)(this.CountOfCheckouts)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfCashiers)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfBuyers)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MaximumCountOfBuyersInShop)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton NormalMode;
        private System.Windows.Forms.RadioButton EpidemicMode;
        private System.Windows.Forms.Label CountOfCheckoutsLabel;
        private System.Windows.Forms.NumericUpDown CountOfCheckouts;
        private System.Windows.Forms.Label CountOfCashiersLabel;
        private System.Windows.Forms.NumericUpDown CountOfCashiers;
        private System.Windows.Forms.Label CountOfBuyersLabel;
        private System.Windows.Forms.NumericUpDown CountOfBuyers;
        private System.Windows.Forms.Label MaximumCountOfBuyersInShopLabel;
        private System.Windows.Forms.NumericUpDown MaximumCountOfBuyersInShop;
        private System.Windows.Forms.Button ok;
        private System.Windows.Forms.Button cancel;
    }
}