namespace lab10
{
    partial class Form1
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
            this.graph = new System.Windows.Forms.PictureBox();
            this.function = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.graph)).BeginInit();
            this.SuspendLayout();
            // 
            // graph
            // 
            this.graph.Location = new System.Drawing.Point(12, 12);
            this.graph.Name = "graph";
            this.graph.Size = new System.Drawing.Size(700, 400);
            this.graph.TabIndex = 0;
            this.graph.TabStop = false;
            // 
            // function
            // 
            this.function.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.function.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.function.FormattingEnabled = true;
            this.function.Items.AddRange(new object[] {
            "y=tg(x)",
            "y=sin(x)",
            "y=cos(x)",
            "y=ctg(x)"});
            this.function.Location = new System.Drawing.Point(328, 444);
            this.function.Name = "function";
            this.function.Size = new System.Drawing.Size(108, 32);
            this.function.TabIndex = 1;
            this.function.SelectedIndexChanged += new System.EventHandler(this.function_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(324, 415);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 24);
            this.label2.TabIndex = 5;
            this.label2.Text = "Функція";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(733, 488);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.function);
            this.Controls.Add(this.graph);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Лабораторна робота №10";
            ((System.ComponentModel.ISupportInitialize)(this.graph)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox graph;
        private System.Windows.Forms.ComboBox function;
        private System.Windows.Forms.Label label2;
    }
}

