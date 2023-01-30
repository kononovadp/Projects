using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;
public class ChangeScoreOnScreen : MonoBehaviour
{
    public TMP_Text TextScore;
	void Start()
	{
		TextScore=GetComponent<TextMeshProUGUI>();
		TextScore.text="Score: "+PlayerController.score.ToString();		
	}	
}