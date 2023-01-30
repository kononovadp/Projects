using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class NewGameButton : MonoBehaviour
{
    public void action()
	{
		StreamWriter file = File.CreateText("GamePrefs.ini");
		file.Write("1");
		file.Close();
		Cursor.visible = false;
		SceneManager.LoadScene("MainScene");
	}
}