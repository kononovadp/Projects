using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class HealthBar : MonoBehaviour
{
    public static Slider healthbar;
    private void Start()
    {
        healthbar=GetComponent<Slider>();
    }
    public static void SetHealth(float health)
    {
        healthbar.value=health;
    }
}