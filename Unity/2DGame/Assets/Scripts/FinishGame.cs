using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class FinishGame:MonoBehaviour
{
    void Awake()
    {
        GetComponent<Collider2D>().isTrigger = true;		
    }
    void OnTriggerEnter2D(Collider2D player)
    {
        if(player.CompareTag("Player"))                  
            SceneManager.LoadScene("GameFinished");
    }
}