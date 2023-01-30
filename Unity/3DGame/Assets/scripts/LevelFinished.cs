using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class LevelFinished : MonoBehaviour
{
    void Start()
    {
        
    }
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();
		if(Input.GetKeyDown(KeyCode.Return))					
			SceneManager.LoadScene("MainScene");		
    }
}
