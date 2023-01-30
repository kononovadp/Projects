using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
public class GameOverScript : MonoBehaviour
{    
	void Update()
    {        
		if(Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();
		if(Input.GetKeyDown(KeyCode.Return))
			SceneManager.LoadScene("MainScene");
	}
}