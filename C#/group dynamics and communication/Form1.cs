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
    public partial class MainForm : Form
    {                
        public char[] english=  {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        public char[] russian=  {'А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я','а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я'};
        public char[] ukrainian={'А','Б','В','Г','Ґ','Д','Е','Є','Ж','З','И','І','Ї','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ь','Ю','Я','а','б','в','г','ґ','д','е','є','ж','з','и','і','ї','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ь','ю','я'};
        public struct CharacterNumber
        {
            public int language;
            public int number;
        };
        public static CharacterNumber[] NumbersOfCharacters;
        public static char[][] CaesarEncrypt,CaesarDecrypt;
        public static char[][][] PasswordEncrypt,PasswordDecrypt;
        void FillCaesarArrays(char[] LanguageCharacters,int size,byte LanguageNumber)
        {            
            CaesarEncrypt[LanguageNumber]=new char[size+1];
            CaesarDecrypt[LanguageNumber]=new char[size+1];
            int SmallLetterEncryptIndex=size/2,SmallLetterDecryptIndex=size-1;
            int CapitalLetterEncryptIndex=0,CapitalLetterDecryptIndex=size/2-1,n,i,j;
            for(n=size/2-3; CapitalLetterEncryptIndex<n; CapitalLetterEncryptIndex++,CapitalLetterDecryptIndex--,SmallLetterEncryptIndex++,SmallLetterDecryptIndex--)
            {
                CaesarEncrypt[LanguageNumber][CapitalLetterEncryptIndex]=LanguageCharacters[CapitalLetterEncryptIndex+3];
                CaesarDecrypt[LanguageNumber][CapitalLetterDecryptIndex]=LanguageCharacters[CapitalLetterDecryptIndex-3];
                CaesarEncrypt[LanguageNumber][SmallLetterEncryptIndex]=LanguageCharacters[SmallLetterEncryptIndex+3];
                CaesarDecrypt[LanguageNumber][SmallLetterDecryptIndex]=LanguageCharacters[SmallLetterDecryptIndex-3];
            }
            for(i=0,j=size/2-1,CapitalLetterDecryptIndex=2; i<3; CapitalLetterEncryptIndex++,CapitalLetterDecryptIndex--,SmallLetterEncryptIndex++,SmallLetterDecryptIndex--,i++,j--)
            {
                CaesarEncrypt[LanguageNumber][CapitalLetterEncryptIndex]=LanguageCharacters[i];
                CaesarDecrypt[LanguageNumber][CapitalLetterDecryptIndex]=LanguageCharacters[j];
                CaesarEncrypt[LanguageNumber][SmallLetterEncryptIndex]=LanguageCharacters[size/2+i];
                CaesarDecrypt[LanguageNumber][SmallLetterDecryptIndex]=LanguageCharacters[size-i-1];
            }           
        }
        void FillPasswordArrays(char[] characters,int size,byte LanguageNumber)
        {            
            int i,j,EncryptCharacter,DecryptCharacter;
            PasswordEncrypt[LanguageNumber]=new char[size][];
            PasswordDecrypt[LanguageNumber]=new char[size][];
            for(i=0; i<size; i++)
            {
                PasswordEncrypt[LanguageNumber][i]=new char[size];
                PasswordDecrypt[LanguageNumber][i]=new char[size];
            }
            for(i=0; i<size; i++)
            {
                for(j=i+1,EncryptCharacter=0; j<size; j++,EncryptCharacter++)
                {
                    PasswordEncrypt[LanguageNumber][i][EncryptCharacter]=characters[j];
                    PasswordDecrypt[LanguageNumber][j][i]=characters[EncryptCharacter];
                }
                for(j=0,DecryptCharacter=i-1; j<=i; j++,EncryptCharacter++,DecryptCharacter--)
                {
                    PasswordEncrypt[LanguageNumber][i][EncryptCharacter]=characters[j];
                    PasswordDecrypt[LanguageNumber][j][i]=characters[EncryptCharacter];
                }
            }
        }
        public MainForm()
        {
            InitializeComponent();
            source.ScrollBars = RichTextBoxScrollBars.ForcedBoth;
            result.ScrollBars = RichTextBoxScrollBars.ForcedBoth;
            OpenFileDialog.Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
            SaveFileDialog.Filter = "Text files(*.txt)|*.txt";
            NumbersOfCharacters=new CharacterNumber[65536];
            for(int i=0; i<65536; i++)
                NumbersOfCharacters[i].language=-1;            
            SelectLanguages(null,null);			
            CaesarEncrypt=new char[3][];
            CaesarDecrypt=new char[3][];            
            FillCaesarArrays(english,english.Length,0);
            FillCaesarArrays(russian,russian.Length,1);
            FillCaesarArrays(ukrainian,ukrainian.Length,2);
            PasswordEncrypt=new char[3][][];
            PasswordDecrypt=new char[3][][];
            FillPasswordArrays(english,english.Length,0);
            FillPasswordArrays(russian,russian.Length,1);
            FillPasswordArrays(ukrainian,ukrainian.Length,2);            
        }
        private void MainForm_Resize(object sender, EventArgs e)
        {
            data.Width=this.Width-20;
            data.Height=this.Height-60;
        }
        private void OpenFile_Click(object sender, EventArgs e)
        {
            if(OpenFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            if(source.Text.Length>0)
                source.Text=source.Text.Remove(0);
            if(result.Text.Length>0)
                result.Text=result.Text.Remove(0);
            source.Text=System.IO.File.ReadAllText(OpenFileDialog.FileName,Encoding.GetEncoding(1251));
        }        
        private void SaveFile_Click(object sender, EventArgs e)//https://rsdn.org/forum/dotnet/1696599.all
        {
            if(SaveFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            System.IO.File.WriteAllText(SaveFileDialog.FileName,result.Text.Replace("\n","\r\n")/* + Environment.NewLine*/,Encoding.GetEncoding(1251));
        }
        void FillAnArrayWithNumbersOfCharacters(char[] characters,int size,int language)
        {
            int i;
            if(language>-1)
                for(i=0; i<size; i++)
                {
                    NumbersOfCharacters[characters[i]].language=language;
                    NumbersOfCharacters[characters[i]].number=i;
                }
            else
                for(i=0; i<size; i++)
				{
                    NumbersOfCharacters[characters[i]].language=-1;
					NumbersOfCharacters[characters[i]].number=-1;
				}
        }
        void SelectLanguages(object sender, EventArgs e)
        {
            if(UkrainianUsed.Checked==true && RussianUsed.Checked==true)
                RussianUsed.Checked=false;
            if(EnglishUsed.Checked==true)
                FillAnArrayWithNumbersOfCharacters(english,english.Length,0);
            else
                FillAnArrayWithNumbersOfCharacters(english,english.Length,-1);            
            if(UkrainianUsed.Checked==true)
                FillAnArrayWithNumbersOfCharacters(ukrainian,ukrainian.Length,2);
            else
                FillAnArrayWithNumbersOfCharacters(ukrainian,ukrainian.Length,-1);
        }
        void SelectRussian(object sender, EventArgs e)
        {
            if(RussianUsed.Checked==true && UkrainianUsed.Checked==true)
                UkrainianUsed.Checked=false;
            if(RussianUsed.Checked==true)
                FillAnArrayWithNumbersOfCharacters(russian,russian.Length,1);
            else
                FillAnArrayWithNumbersOfCharacters(russian,russian.Length,-1);
        }
        private void PasswordEncryptAndDecrypt_Click(object sender, EventArgs e)
        {
            EncryptAndDecryptWithPassword EncryptWithPassword = new EncryptAndDecryptWithPassword(this);
            EncryptWithPassword.ShowDialog();
        }
        private void CaesarEncryptAndDecrypt_Click(object sender, EventArgs e)
        {
            CaesarEncryptAndDecrypt CaesarEncryptAndDecrypt = new CaesarEncryptAndDecrypt(this);
            CaesarEncryptAndDecrypt.ShowDialog();
        }
        private void MenuSelectAll_Click(object sender, EventArgs e)
        {
            RichTextBox rtb=ContextMenu.SourceControl as RichTextBox;
            rtb.SelectAll();
            rtb.Select();
        }
        private void MenuPaste_Click(object sender, EventArgs e)
        {
            RichTextBox rtb=ContextMenu.SourceControl as RichTextBox;
            rtb.Paste();
            rtb.Select();
        }
        private void MenuCopy_Click(object sender, EventArgs e)
        {
            RichTextBox rtb=ContextMenu.SourceControl as RichTextBox;
            rtb.Copy();
            rtb.Select();
        }
        private void MenuDeleteAll_Click(object sender, EventArgs e)
        {
            RichTextBox rtb=ContextMenu.SourceControl as RichTextBox;
            rtb.Text="";
            rtb.Select();
        }
        private void QuestionsAndAnswersOfStudents_Click(object sender, EventArgs e)
        {
            QuestionsAndAnswersOfStudents QuestionsAndAnswersOfStudents = new QuestionsAndAnswersOfStudents();
            QuestionsAndAnswersOfStudents.ShowDialog();
        }
        private void ShowCountsOfCharacters(int start,int end,int[] CountsOfCharacters)
        {
            for(int i=start; i<end; i++)            
                if(CountsOfCharacters[i]>0)
                    result.Text+=String.Format("{0,12}|{1,5}|{2,18}|\n",Convert.ToChar(i),Convert.ToString(i),Convert.ToString(CountsOfCharacters[i]));
        }
        private void ShowInformationAboutText_Click(object sender, EventArgs e)
        {
            if(source.Text.Length==0)
            {
                MessageBox.Show("Введіть текст у форму.");
                return;
            }
            string SourceText=source.Text;
            int[]CountsOfCharacters=new int[65535];
            int i,SourceTextLength=SourceText.Length;
            int SumOfCharactersInWindows=0,SumOfCharacters=0;            
            for(i=0; i<SourceTextLength; i++)
            {
                CountsOfCharacters[SourceText[i]]++;
                SumOfCharactersInWindows+=SourceText[i];
                if(NumbersOfCharacters[SourceText[i]].language>-1)
                    SumOfCharacters+=NumbersOfCharacters[SourceText[i]].number+1;
            }
            result.Text=String.Format("{0,24}{1,14}\n{2,24}{3,14}\n{4,24}{5,14}\n","Кількість символів:",SourceTextLength+CountsOfCharacters['\n'],"Сума символів:",SumOfCharacters,"Сума символів (Windows):",SumOfCharactersInWindows);
            result.Text+="Частота використання символів:\n      Символ|Номер|Кількість повторів|\n";
            ShowCountsOfCharacters(0,'\n',CountsOfCharacters);
            ShowCountsOfCharacters('\n'+1,' ',CountsOfCharacters);
            ShowCountsOfCharacters(' '+1,65535,CountsOfCharacters);
            if(CountsOfCharacters[' ']>0)
                result.Text+=String.Format("{0,12}|{1,5}|{2,18}|\n","Пробіл",Convert.ToString(Convert.ToInt32(' ')),Convert.ToString(CountsOfCharacters[' ']));
            if(CountsOfCharacters['\n']>0)
                result.Text+=String.Format("{0,12}|{1,5}|{2,18}|\n","Кінець рядка",Convert.ToString(Convert.ToInt32('\n')),Convert.ToString(CountsOfCharacters['\n']));
        }
    }
}
