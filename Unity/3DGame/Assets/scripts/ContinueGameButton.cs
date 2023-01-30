using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
public class ContinueGameButton : MonoBehaviour
{
    void Start()
    {		
		if(!File.Exists("GamePrefs.ini"))
		{
			Button myButton = this.GetComponent<Button>();
			myButton.interactable=false;
		}
    }
	public void action()
	{
		Cursor.visible = false;
		SceneManager.LoadScene("MainScene");
	}
}
