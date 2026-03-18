using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
namespace lab2
{
    public partial class QuestionsAndAnswersOfStudents : Form
    {
        decimal PreviousCountOfQuestions;
        int CountOfQuestions,CountOfAnswers,LabelY,TextBoxY;
        public QuestionsAndAnswersOfStudents()
        {
            InitializeComponent();            
            SaveFileDialog.Filter = "Text files(*.txt)|*.txt";
            PreviousCountOfQuestions=CountOfQuestionsNumericUpDown.Value;
            CountOfQuestions=(int)CountOfQuestionsNumericUpDown.Value;            
            LabelY=0;
            TextBoxY=30;
            for(int i=0; i<CountOfQuestions; i++,LabelY+=60,TextBoxY+=60)
            {
                Label NewLabel=new Label();                
                NewLabel.Location = new System.Drawing.Point(0, LabelY);
                NewLabel.AutoSize = true;
                NewLabel.Text="Питання "+Convert.ToString(i+1)+":";
                NewLabel.Name="label"+Convert.ToString(i+1);
                QuestionPanel.Controls.Add(NewLabel);
                TextBox NewTextBox=new TextBox();
                NewTextBox.Size=new System.Drawing.Size(670,30);
                NewTextBox.Location = new System.Drawing.Point(0, TextBoxY);
                NewTextBox.AutoSize = true;
                NewTextBox.MaxLength=65;
                NewTextBox.Name="TextBox"+Convert.ToString(i+1);
                QuestionPanel.Controls.Add(NewTextBox);
            }
        }
        private void CountOfQuestionsNumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            if(CountOfQuestionsNumericUpDown.Value>PreviousCountOfQuestions)
            {
                Label NewLabel=new Label();
                NewLabel.Location = new System.Drawing.Point(5, LabelY);
                NewLabel.AutoSize = true;
                NewLabel.Text="Питання "+Convert.ToString(PreviousCountOfQuestions+1)+":";
                NewLabel.Name="label"+Convert.ToString(PreviousCountOfQuestions+1);
                QuestionPanel.Controls.Add(NewLabel);
                TextBox NewTextBox=new TextBox();
                NewTextBox.Size=new System.Drawing.Size(670,30);
                NewTextBox.Location = new System.Drawing.Point(0, TextBoxY);
                NewTextBox.AutoSize = true;
                NewTextBox.MaxLength=65;
                NewTextBox.Name="TextBox"+Convert.ToString(PreviousCountOfQuestions+1);
                QuestionPanel.Controls.Add(NewTextBox);
                LabelY+=60;
                TextBoxY+=60;
                PreviousCountOfQuestions++;
            }
            else
                if(CountOfQuestionsNumericUpDown.Value<PreviousCountOfQuestions)
                {
                    QuestionPanel.Controls.RemoveByKey("TextBox"+Convert.ToString(PreviousCountOfQuestions));
                    QuestionPanel.Controls.RemoveByKey("label"+Convert.ToString(PreviousCountOfQuestions));
                    LabelY-=60;
                    TextBoxY-=60;
                    PreviousCountOfQuestions--;
                }
        }
        private void SaveQuestions_Click(object sender, EventArgs e)
        {            
            if(SaveFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            string FileName = SaveFileDialog.FileName;
            if(System.IO.File.Exists(FileName))
                System.IO.File.Delete(FileName);
            FileStream FileStream = new FileStream(FileName, FileMode.CreateNew);
            StreamWriter sw=new StreamWriter(FileStream,Encoding.GetEncoding(1251),512);
            for(decimal i=0; i<CountOfQuestionsNumericUpDown.Value; i++)
            {
                Control FoundControl = QuestionPanel.Controls.Find("TextBox"+Convert.ToString(i+1), true).FirstOrDefault();
                sw.WriteLine(Convert.ToString(i+1)+". "+FoundControl.Text);
            }
            sw.Close();
        }
        private void LoadQuestions_Click(object sender, EventArgs e)
        {
            if(OpenFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            string filename = OpenFileDialog.FileName;
            StreamReader file=new StreamReader(filename,Encoding.GetEncoding(1251));            
            String line;
            AnswersPanel.Controls.Clear();
            CountOfAnswers=0;
            int j,MaxLength,LineLength,QuestionNumber=0,QuestionText=30,answer=60,AnswerText=90;            
            do
            {                
                line=file.ReadLine();
                for(j=0,LineLength=line.Length; j<LineLength && Char.IsDigit(line[j]); j++);
                if(j==0 || j==LineLength)
                    continue;
                else
                    if(line[j]!='.')
                        continue;
                Label NewQuestionNumber=new Label();
                NewQuestionNumber.Location = new System.Drawing.Point(0, QuestionNumber);
                NewQuestionNumber.AutoSize = true;
                NewQuestionNumber.Text="Питання "+Convert.ToString(CountOfAnswers+1)+":";
                NewQuestionNumber.Name="QuestionNumber"+Convert.ToString(CountOfAnswers+1);
                AnswersPanel.Controls.Add(NewQuestionNumber);
                TextBox NewQuestionText=new TextBox();
                NewQuestionText.Size=new System.Drawing.Size(670,30);
                NewQuestionText.Location = new System.Drawing.Point(0, QuestionText);
                NewQuestionText.AutoSize = true;
                NewQuestionText.MaxLength=65;
                NewQuestionText.Name="QuestionText"+Convert.ToString(CountOfAnswers+1);
                for(j+=2,MaxLength=65+j; j<LineLength && j<MaxLength; j++)
                    NewQuestionText.Text+=line[j];
                AnswersPanel.Controls.Add(NewQuestionText);
                Label NewAnswer=new Label();                
                NewAnswer.Location = new System.Drawing.Point(0, answer);
                NewAnswer.AutoSize = true;
                NewAnswer.Text="Відповідь:";
                NewAnswer.Name="answer"+Convert.ToString(CountOfAnswers+1);
                AnswersPanel.Controls.Add(NewAnswer);
                RichTextBox NewAnswerText=new RichTextBox();
                NewAnswerText.Location = new System.Drawing.Point(0, AnswerText);
                NewAnswerText.Size=new System.Drawing.Size(670,120);
                NewAnswerText.Name="AnswerText"+Convert.ToString(CountOfAnswers+1);
                AnswersPanel.Controls.Add(NewAnswerText);
                CountOfAnswers++;
                QuestionNumber+=210;
                QuestionText+=210;
                answer+=210;
                AnswerText+=210;
            }while(!file.EndOfStream);
            file.Close();
            AnswersPanel.Focus();
        }
        private void QuestionsAndAnswersOfStudentsTabs_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(QuestionsAndAnswersOfStudentsTabs.SelectedIndex==0)
                QuestionPanel.Focus(); 
            else
                AnswersPanel.Focus();
        }
        private void QuestionsAndAnswersOfStudents_Shown(object sender, EventArgs e)
        {
            QuestionPanel.Focus(); 
        }
        private void SaveAnswers_Click(object sender, EventArgs e)
        {
            if(SaveFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            string FileName = SaveFileDialog.FileName;
            if(System.IO.File.Exists(FileName))
                System.IO.File.Delete(FileName);
            FileStream FileStream = new FileStream(FileName, FileMode.CreateNew);
            StreamWriter sw=new StreamWriter(FileStream,Encoding.GetEncoding(1251),512);
            for(int i=0; i<CountOfAnswers; i++)
            {
                Control QuestionText = AnswersPanel.Controls.Find("QuestionText"+Convert.ToString(i+1), true).FirstOrDefault();
                Control AnswerText = AnswersPanel.Controls.Find("AnswerText"+Convert.ToString(i+1), true).FirstOrDefault();
                sw.WriteLine("Питання "+Convert.ToString(i+1)+": "+QuestionText.Text);
                sw.WriteLine("Відповідь:");
                sw.WriteLine(AnswerText.Text.Replace("\n","\r\n"));                
            }
            sw.Close();
        }
    }
}
