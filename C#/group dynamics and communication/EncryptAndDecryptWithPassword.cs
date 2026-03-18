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
    public partial class EncryptAndDecryptWithPassword : Form
    {
        MainForm MainForm;
        public EncryptAndDecryptWithPassword(MainForm source)
        {
            InitializeComponent();
            MainForm = source;
            if(MainForm.source.Text.Length==0)
                RadioButtonTextFromForm.Enabled=false;
            password.ContextMenuStrip=MainForm.ContextMenu;
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
            int PasswordLength=password.Text.Length,PasswordIndex=0;
            if(PasswordLength==0)
            {
                MessageBox.Show("Введіть пароль.");
                return;
            }
            string SourceText=GetText();
            int TextLength=SourceText.Length;
            if(TextLength==0)
            {
                MessageBox.Show("Файл порожній.");
                return;
            }
            string PasswordText=password.Text;
            ProgressBar.Step=1;
            ProgressBar.Maximum=TextLength;  
            ProgressBar.Value=1;            
            char[] ResultText=new char[TextLength];                   
            for(int i=0; i<TextLength; i++)
            {
                ResultText[i]=SourceText[i];//MainForm.source.Text[i];
                if(MainForm.NumbersOfCharacters[ResultText[i]].language>-1)
                {                    
                    while(PasswordIndex<PasswordLength && MainForm.NumbersOfCharacters[PasswordText[PasswordIndex]].language==-1)
                        PasswordIndex++;                    
                    if(PasswordIndex==PasswordLength)
                        PasswordIndex=0;                    
                    if(MainForm.NumbersOfCharacters[PasswordText[PasswordIndex]].number>=MainForm.PasswordEncrypt[MainForm.NumbersOfCharacters[ResultText[i]].language][MainForm.NumbersOfCharacters[ResultText[i]].number].Length-1)
                    {
                        MessageBox.Show("Даний текст містить символи, які не можуть бути зашифровані такими буквами українського алфавіту: о, п, р, с, т, у, ф, х, ц, ч, ш, щ, ь, ю, я, а також наступними російськими літерами: с, т, у, ф, х, ц, ч, ш, щ, ъ, ы, ь, э, ю, я");
                        return;
                    }
                    ResultText[i]=MainForm.PasswordEncrypt[MainForm.NumbersOfCharacters[ResultText[i]].language][MainForm.NumbersOfCharacters[ResultText[i]].number][MainForm.NumbersOfCharacters[PasswordText[PasswordIndex]].number];
                    PasswordIndex++;
                }
                ProgressBar.PerformStep();
            }
            MainForm.source.Text=SourceText;
            MainForm.result.Text=new String(ResultText);
            this.Close();
        }
        private void decrypt_Click(object sender, EventArgs e)
        {
            int PasswordLength=password.Text.Length,PasswordIndex=0;
            if(PasswordLength==0)
            {
                MessageBox.Show("Введіть пароль.");
                return;
            }
            string SourceText=GetText();
            int TextLength=SourceText.Length;
            if(TextLength==0)
            {
                MessageBox.Show("Файл порожній.");
                return;
            }
            string PasswordText=password.Text;
            ProgressBar.Step=1;
            ProgressBar.Maximum=TextLength;  
            ProgressBar.Value=1;            
            char[] ResultText=new char[TextLength];
            for(int i=0; i<TextLength; i++)
            {
                ResultText[i]=SourceText[i];//MainForm.source.Text[i];
                if(MainForm.NumbersOfCharacters[ResultText[i]].language>-1)
                {                    
                    while(PasswordIndex<PasswordLength && MainForm.NumbersOfCharacters[PasswordText[PasswordIndex]].language==-1)
                        PasswordIndex++;                    
                    if(PasswordIndex==PasswordLength)
                        PasswordIndex=0;                    
                    if(MainForm.NumbersOfCharacters[PasswordText[PasswordIndex]].number>=MainForm.PasswordEncrypt[MainForm.NumbersOfCharacters[ResultText[i]].language][MainForm.NumbersOfCharacters[ResultText[i]].number].Length-1)
                    {
                        MessageBox.Show("Даний текст містить символи, які не можуть бути розшифровані такими буквами українського алфавіту: о, п, р, с, т, у, ф, х, ц, ч, ш, щ, ь, ю, я, а також наступними російськими літерами: с, т, у, ф, х, ц, ч, ш, щ, ъ, ы, ь, э, ю, я");
                        return;
                    }
                    ResultText[i]=MainForm.PasswordDecrypt[MainForm.NumbersOfCharacters[ResultText[i]].language][MainForm.NumbersOfCharacters[ResultText[i]].number][MainForm.NumbersOfCharacters[PasswordText[PasswordIndex]].number];
                    PasswordIndex++;
                }
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
        private void OpenPasswordFile_Click(object sender, EventArgs e)
        {            
            if(OpenFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            password.Text="";
            password.Text=System.IO.File.ReadAllText(OpenFileDialog.FileName,Encoding.GetEncoding(1251));
        }
        private void OpenFile_Click(object sender, EventArgs e)
        {
            if (OpenFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            FilePath.Text = OpenFileDialog.FileName;
        }
    }
}
