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
    public partial class CaesarEncryptAndDecrypt : Form
    {
        MainForm MainForm;
        public CaesarEncryptAndDecrypt(MainForm source)
        {
            InitializeComponent();
            MainForm = source;
            if(MainForm.source.Text.Length==0)
                RadioButtonTextFromForm.Enabled=false;                
        }
        private string GetText()
        {
            if(RadioButtonTextFromForm.Checked==true)
            {
                MainForm.result.Text="";
                return MainForm.source.Text;
            }
            if(FilePath.Text.Length==0)
            {
                MessageBox.Show("Вкажіть файл.");
                return null;
            }
            MainForm.result.Text="";
            MainForm.source.Text="";           
            return System.IO.File.ReadAllText(FilePath.Text,Encoding.GetEncoding(1251));
        }
        private void encrypt_Click(object sender, EventArgs e)
        {            
            string SourceText=GetText();                        
            int TextLength=SourceText.Length;
            if(TextLength==0)
            {
                MessageBox.Show("Файл порожній");
                return;
            }
            char[] ResultText=new char[TextLength];
            ProgressBar.Step=1;
            ProgressBar.Maximum=TextLength;  
            ProgressBar.Value=1;
            for(int i=0; i<TextLength; i++)
            {
                ResultText[i]=SourceText[i];
                if(MainForm.NumbersOfCharacters[ResultText[i]].language>-1)
                    ResultText[i]=MainForm.CaesarEncrypt[MainForm.NumbersOfCharacters[ResultText[i]].language][MainForm.NumbersOfCharacters[ResultText[i]].number];
                ProgressBar.PerformStep();
            }
            MainForm.source.Text=SourceText;
            MainForm.result.Text=new String(ResultText);
            this.Close();
        }
        private void decrypt_Click(object sender, EventArgs e)
        {            
            string SourceText=GetText();                        
            int TextLength=SourceText.Length;
            if(TextLength==0)
            {
                MessageBox.Show("Файл порожній");
                return;
            }
            char[] ResultText=new char[TextLength];
            ProgressBar.Step=1;
            ProgressBar.Maximum=TextLength;  
            ProgressBar.Value=1;
            for(int i=0; i<TextLength; i++)
            {
                ResultText[i]=SourceText[i];
                if(MainForm.NumbersOfCharacters[ResultText[i]].language>-1)
                    ResultText[i]=MainForm.CaesarDecrypt[MainForm.NumbersOfCharacters[ResultText[i]].language][MainForm.NumbersOfCharacters[ResultText[i]].number];
                ProgressBar.PerformStep();
            }
            MainForm.source.Text=SourceText;
            MainForm.result.Text=new String(ResultText);
            this.Close();
        }
        private void RadioButtonTextFromFile_CheckedChanged(object sender, EventArgs e)
        {
            FilePath.Enabled=true;
            OpenFile.Enabled=true;
        }
        private void RadioButtonTextFromForm_CheckedChanged(object sender, EventArgs e)
        {
            FilePath.Enabled=false;
            OpenFile.Enabled=false;
        }
        private void close_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void OpenFile_Click(object sender, EventArgs e)
        {
            if (OpenFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            FilePath.Text = OpenFileDialog.FileName;
        }        
    }
}
