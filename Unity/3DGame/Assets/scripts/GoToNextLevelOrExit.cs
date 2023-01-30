using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;
public class GoToNextLevelOrExit : MonoBehaviour
{
    public TMP_Text level;
	void Start()
    {
        level=GetComponent<TextMeshProUGUI>();
		level.text="Press ENTER to go\nto level "+player.level.ToString()+"\nor ESC to exit: ";
    }
    void Update()
    {
        
    }
}
