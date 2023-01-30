using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
public class HealthPack : MonoBehaviour
{
	const float RotationSpeed=500;
	void Update()
	{
		transform.Rotate(Vector3.up*RotationSpeed*Time.deltaTime,Space.World);
	}
	void OnTriggerEnter(Collider other)
	{
		if(other.tag == "Player")
		{
			/*player.score++;
			TMP_Text TextScore=GameObject.FindWithTag("score").GetComponent<TextMeshProUGUI>();
			TextScore.text="Score: "+player.score.ToString();*/
			Destroy(gameObject);
		}
	}
}