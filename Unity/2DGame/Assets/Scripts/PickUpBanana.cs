using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class PickUpBanana:MonoBehaviour
{
    void Awake()
    {
        GetComponent<Collider2D>().isTrigger = true;		
    }
    void OnTriggerEnter2D(Collider2D player)
    {
        if(player.CompareTag("Player"))
        {
            PlayerController.score++;
            Destroy(gameObject);
        }
    }
}