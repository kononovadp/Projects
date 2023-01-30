using System;
using System.IO;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
public class player : MonoBehaviour
{
	float speed = 10.0f;
	float MouseSensitivity = 1.0f;
	public static int score;
	Rigidbody RigidbodyForJump;
	Vector3 MousePosition;
	[DllImport("user32.dll")]
    public static extern bool SetCursorPos(int X, int Y);
	public bool IsGrounded;
	public float health;
	public float HealthStep;
	public static int level;
	void Start()
    {
        RigidbodyForJump=GetComponent<Rigidbody>();
		health=(float)100.0;
        SetCursorPos(0,0);
		
		score=0;		
		StreamReader file=File.OpenText("GamePrefs.ini");
		level=Convert.ToInt32(file.ReadLine());
		file.Close();		
		HealthStep=level*(float)10.0;
	}
	void Update()
	{
		if(Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();
		MousePosition = Input.mousePosition - MousePosition;
		MousePosition = new Vector3(-MousePosition.y * MouseSensitivity, MousePosition.x * MouseSensitivity, 0 );
		MousePosition = new Vector3(transform.eulerAngles.x + MousePosition.x , transform.eulerAngles.y + MousePosition.y, 0);
		transform.eulerAngles = MousePosition;
		MousePosition =  Input.mousePosition;		
		if(Input.GetKeyDown(KeyCode.RightControl) && IsGrounded)		
			RigidbodyForJump.AddForce(transform.up*5,ForceMode.Impulse);		
		Vector3 input = new Vector3();
		if(Input.GetKey (KeyCode.UpArrow))
			input += new Vector3(0,0,1);
		if(Input.GetKey (KeyCode.DownArrow))
			input += new Vector3(0, 0, -1);
		if(Input.GetKey (KeyCode.LeftArrow))
			input += new Vector3(-1, 0, 0);
		if(Input.GetKey (KeyCode.RightArrow))
			input += new Vector3(1, 0, 0);
		input = input * speed* Time.deltaTime;
		Vector3 newPosition = transform.position;
		transform.Translate(input);
		if(transform.position.y<-10.0f)		
			SceneManager.LoadScene("GameOver");
    }
	private void OnCollisionEnter(Collision collision)
	{
		if(collision.gameObject.tag=="Ground")
			IsGrounded = true;
		else
			if(collision.gameObject.tag=="enemy")
			{
				health-=HealthStep;
				HealthBar.SetHealth(health);
				if(health<=0.0)
					SceneManager.LoadScene("GameOver");
			}
			else
				if(collision.gameObject.tag=="health")
				{
					health+=HealthStep;
					HealthBar.SetHealth(health);
				}
				else
					if(collision.gameObject.tag=="Finish")
					{
						level++;
						StreamWriter file = File.CreateText("GamePrefs.ini");
						file.Write(level);
						file.Close();
						SceneManager.LoadScene("LevelFinished");
					}
	}
	private void OnCollisionExit(Collision collision)
	{
		if(collision.gameObject.tag=="Ground")
			IsGrounded = false;
	}
}