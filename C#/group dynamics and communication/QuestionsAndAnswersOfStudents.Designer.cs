namespace lab2
{
    partial class QuestionsAndAnswersOfStudents
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(QuestionsAndAnswersOfStudents));
            this.QuestionsAndAnswersOfStudentsTabs = new System.Windows.Forms.TabControl();
            this.QuestionTab = new System.Windows.Forms.TabPage();
            this.QuestionPanel = new System.Windows.Forms.Panel();
            this.SaveQuestions = new System.Windows.Forms.Button();
            this.CountOfQuestionsNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.CountOfQuestionsLabel = new System.Windows.Forms.Label();
            this.AnswersTab = new System.Windows.Forms.TabPage();
            this.AnswersPanel = new System.Windows.Forms.Panel();
            this.LoadQuestions = new System.Windows.Forms.Button();
            this.SaveAnswers = new System.Windows.Forms.Button();
            this.SaveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.QuestionsAndAnswersOfStudentsTabs.SuspendLayout();
            this.QuestionTab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfQuestionsNumericUpDown)).BeginInit();
            this.AnswersTab.SuspendLayout();
            this.SuspendLayout();
            // 
            // QuestionsAndAnswersOfStudentsTabs
            // 
            this.QuestionsAndAnswersOfStudentsTabs.Controls.Add(this.QuestionTab);
            this.QuestionsAndAnswersOfStudentsTabs.Controls.Add(this.AnswersTab);
            this.QuestionsAndAnswersOfStudentsTabs.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.QuestionsAndAnswersOfStudentsTabs.HotTrack = true;
            this.QuestionsAndAnswersOfStudentsTabs.Location = new System.Drawing.Point(0, 0);
            this.QuestionsAndAnswersOfStudentsTabs.Margin = new System.Windows.Forms.Padding(0);
            this.QuestionsAndAnswersOfStudentsTabs.Name = "QuestionsAndAnswersOfStudentsTabs";
            this.QuestionsAndAnswersOfStudentsTabs.Padding = new System.Drawing.Point(0, 0);
            this.QuestionsAndAnswersOfStudentsTabs.SelectedIndex = 0;
            this.QuestionsAndAnswersOfStudentsTabs.Size = new System.Drawing.Size(695, 310);
            this.QuestionsAndAnswersOfStudentsTabs.TabIndex = 0;
            this.QuestionsAndAnswersOfStudentsTabs.SelectedIndexChanged += new System.EventHandler(this.QuestionsAndAnswersOfStudentsTabs_SelectedIndexChanged);
            // 
            // QuestionTab
            // 
            this.QuestionTab.AutoScroll = true;
            this.QuestionTab.BackColor = System.Drawing.SystemColors.Menu;
            this.QuestionTab.Controls.Add(this.QuestionPanel);
            this.QuestionTab.Controls.Add(this.SaveQuestions);
            this.QuestionTab.Controls.Add(this.CountOfQuestionsNumericUpDown);
            this.QuestionTab.Controls.Add(this.CountOfQuestionsLabel);
            this.QuestionTab.Location = new System.Drawing.Point(4, 33);
            this.QuestionTab.Margin = new System.Windows.Forms.Padding(0);
            this.QuestionTab.Name = "QuestionTab";
            this.QuestionTab.Size = new System.Drawing.Size(687, 273);
            this.QuestionTab.TabIndex = 0;
            this.QuestionTab.Text = "Питання";
            // 
            // QuestionPanel
            // 
            this.QuestionPanel.AutoScroll = true;
            this.QuestionPanel.Location = new System.Drawing.Point(0, 40);
            this.QuestionPanel.Margin = new System.Windows.Forms.Padding(0);
            this.QuestionPanel.Name = "QuestionPanel";
            this.QuestionPanel.Size = new System.Drawing.Size(687, 233);
            this.QuestionPanel.TabIndex = 1;
            // 
            // SaveQuestions
            // 
            this.SaveQuestions.Location = new System.Drawing.Point(236, 0);
            this.SaveQuestions.Name = "SaveQuestions";
            this.SaveQuestions.Size = new System.Drawing.Size(190, 29);
            this.SaveQuestions.TabIndex = 6;
            this.SaveQuestions.Text = "Зберегти питання";
            this.SaveQuestions.UseVisualStyleBackColor = true;
            this.SaveQuestions.Click += new System.EventHandler(this.SaveQuestions_Click);
            // 
            // CountOfQuestionsNumericUpDown
            // 
            this.CountOfQuestionsNumericUpDown.Location = new System.Drawing.Point(171, 1);
            this.CountOfQuestionsNumericUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.CountOfQuestionsNumericUpDown.Name = "CountOfQuestionsNumericUpDown";
            this.CountOfQuestionsNumericUpDown.ReadOnly = true;
            this.CountOfQuestionsNumericUpDown.Size = new System.Drawing.Size(59, 29);
            this.CountOfQuestionsNumericUpDown.TabIndex = 4;
            this.CountOfQuestionsNumericUpDown.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.CountOfQuestionsNumericUpDown.ValueChanged += new System.EventHandler(this.CountOfQuestionsNumericUpDown_ValueChanged);
            // 
            // CountOfQuestionsLabel
            // 
            this.CountOfQuestionsLabel.AutoSize = true;
            this.CountOfQuestionsLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.CountOfQuestionsLabel.Location = new System.Drawing.Point(0, 6);
            this.CountOfQuestionsLabel.Name = "CountOfQuestionsLabel";
            this.CountOfQuestionsLabel.Size = new System.Drawing.Size(165, 24);
            this.CountOfQuestionsLabel.TabIndex = 3;
            this.CountOfQuestionsLabel.Text = "Кількість питань:";
            // 
            // AnswersTab
            // 
            this.AnswersTab.AutoScroll = true;
            this.AnswersTab.BackColor = System.Drawing.SystemColors.Menu;
            this.AnswersTab.Controls.Add(this.AnswersPanel);
            this.AnswersTab.Controls.Add(this.LoadQuestions);
            this.AnswersTab.Controls.Add(this.SaveAnswers);
            this.AnswersTab.Location = new System.Drawing.Point(4, 33);
            this.AnswersTab.Name = "AnswersTab";
            this.AnswersTab.Padding = new System.Windows.Forms.Padding(3);
            this.AnswersTab.Size = new System.Drawing.Size(687, 273);
            this.AnswersTab.TabIndex = 1;
            this.AnswersTab.Text = "Відповіді";
            // 
            // AnswersPanel
            // 
            this.AnswersPanel.AutoScroll = true;
            this.AnswersPanel.Location = new System.Drawing.Point(0, 40);
            this.AnswersPanel.Margin = new System.Windows.Forms.Padding(0);
            this.AnswersPanel.Name = "AnswersPanel";
            this.AnswersPanel.Size = new System.Drawing.Size(687, 233);
            this.AnswersPanel.TabIndex = 9;
            // 
            // LoadQuestions
            // 
            this.LoadQuestions.Location = new System.Drawing.Point(6, 6);
            this.LoadQuestions.Name = "LoadQuestions";
            this.LoadQuestions.Size = new System.Drawing.Size(224, 34);
            this.LoadQuestions.TabIndex = 7;
            this.LoadQuestions.Text = "Завантажити питання";
            this.LoadQuestions.UseVisualStyleBackColor = true;
            this.LoadQuestions.Click += new System.EventHandler(this.LoadQuestions_Click);
            // 
            // SaveAnswers
            // 
            this.SaveAnswers.Location = new System.Drawing.Point(236, 6);
            this.SaveAnswers.Name = "SaveAnswers";
            this.SaveAnswers.Size = new System.Drawing.Size(214, 34);
            this.SaveAnswers.TabIndex = 8;
            this.SaveAnswers.Text = "Зберегти відповіді";
            this.SaveAnswers.UseVisualStyleBackColor = true;
            this.SaveAnswers.Click += new System.EventHandler(this.SaveAnswers_Click);
            // 
            // QuestionsAndAnswersOfStudents
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(692, 320);
            this.Controls.Add(this.QuestionsAndAnswersOfStudentsTabs);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "QuestionsAndAnswersOfStudents";
            this.Text = "Конструктор питань та відповідей студентів";
            this.Shown += new System.EventHandler(this.QuestionsAndAnswersOfStudents_Shown);
            this.QuestionsAndAnswersOfStudentsTabs.ResumeLayout(false);
            this.QuestionTab.ResumeLayout(false);
            this.QuestionTab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CountOfQuestionsNumericUpDown)).EndInit();
            this.AnswersTab.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl QuestionsAndAnswersOfStudentsTabs;
        private System.Windows.Forms.TabPage QuestionTab;
        private System.Windows.Forms.TabPage AnswersTab;
        private System.Windows.Forms.Label CountOfQuestionsLabel;
        private System.Windows.Forms.NumericUpDown CountOfQuestionsNumericUpDown;
        private System.Windows.Forms.Panel QuestionPanel;
        private System.Windows.Forms.Button SaveQuestions;
        private System.Windows.Forms.SaveFileDialog SaveFileDialog;
        private System.Windows.Forms.Button SaveAnswers;
        private System.Windows.Forms.Button LoadQuestions;
        private System.Windows.Forms.Panel AnswersPanel;
        private System.Windows.Forms.OpenFileDialog OpenFileDialog;
    }
}