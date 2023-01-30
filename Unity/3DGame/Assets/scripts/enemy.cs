using System;
using System.IO;
using UnityEngine;
public class enemy : MonoBehaviour
{
	const float distance=(float)5.0;
    public static float SpeedOfMovement;
	float SpeedOfRotation=500.0f;
	Vector3 StartPosition;
	Vector3 velocity;
	void Start()
	{
		StartPosition = transform.position;
		StreamReader file=File.OpenText("GamePrefs.ini");
		SpeedOfMovement=Convert.ToInt32(file.ReadLine())*(float)10.0;
		file.Close();
        velocity = Vector3.right * SpeedOfMovement;
	}
	void Update()
	{
		if(transform.position.x > StartPosition.x + distance)
			velocity.x = -SpeedOfMovement;
		else
			if(transform.position.x < StartPosition.x - distance)
				velocity.x = SpeedOfMovement;
		transform.position += velocity * Time.deltaTime;
		transform.Rotate(Vector3.up*SpeedOfRotation*Time.deltaTime,Space.World);
	}
}