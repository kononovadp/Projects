using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;
public class PlayerController : MonoBehaviour
{
    public float speed;
	public bool RightDirection=true;
    public bool IsGround;
    public int JumpForce=10;
	public static int score;
    private float moveInput;
    private Rigidbody2D Rigidbody;
    private Animator anim;
	private GameObject GameOverScreen;   
    void Start()
    {
        Rigidbody=GetComponent<Rigidbody2D>();
        anim=GetComponent<Animator>();
		GameOverScreen = GameObject.FindWithTag("Finish");
		Cursor.visible = false;
		score=0;
    }
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();        
		if(Input.GetKeyDown(KeyCode.RightControl) && IsGround==false)
				Rigidbody.AddForce(transform.up*JumpForce,ForceMode2D.Impulse);        
		GameObject playerObj = GameObject.Find("Player");
		if(playerObj.transform.position.y<-10.0f)		
			SceneManager.LoadScene("GameOverScene");
    }
	private void FixedUpdate()
    {
        moveInput=Input.GetAxis("Horizontal");
        Rigidbody.velocity=new Vector2(moveInput*speed, Rigidbody.velocity.y);
        if(moveInput == 0)        
            anim.SetBool("Walking", false);        
        else        
            anim.SetBool("Walking", true);
		if((RightDirection == false && moveInput>0) || (RightDirection==true && moveInput<0))
		{
			RightDirection=!RightDirection;
			Vector3 Scaler=transform.localScale;
			Scaler.x*=-1;
			transform.localScale=Scaler;
		}        
    }    
}
