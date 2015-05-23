using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class DroneController : MonoBehaviour {
	public Text	throttleText;
	public Text	yawText;
	public Text	pitchText;
	public Text	rollText;

	public ArduinoCommunicator	arduino;
	public delegate void pong();

	float throttle = 0f;
	float yaw = 0f;

	bool	sended = false;

	float	maxInputValue = 0.016f;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		throttle = Input.GetAxis("Throttle") * Time.deltaTime;
		yaw = Input.GetAxisRaw ("Yaw") * Time.deltaTime;

	

		throttleText.text = "Gaz : " + throttle;
		yawText.text = "Lacet : " + yaw;
		pitchText.text = "Angle d attaque : " + Input.GetAxisRaw("Pitch") * Time.deltaTime;
		rollText.text = "Roulis : " + Input.GetAxisRaw("Roll") * Time.deltaTime;
	
		pingArduino ();
	}


	byte calculatePercentage(float value, float min, float max)
	{
		return (byte) Mathf.RoundToInt(((value + max) * 100) / (max - min));
	}

	void			sendCommand(byte toSend)
	{
		arduino.sendByte(toSend);
		sended = true;
		Invoke ("pongArduino", 0.5f);
	}

	void		  pingArduino()
	{
		if (!sended) {
			byte convertedThrottle;

			convertedThrottle = calculatePercentage (throttle, -maxInputValue, maxInputValue);
			if (convertedThrottle > 80)
			{
				sendCommand(convertedThrottle);
			}
//			else if (yaw > 0.013f)
//			{
//				sendCommand((byte)'Y');
//			}

		}
	}

	void pongArduino()
	{
		byte response = (byte) arduino.readByte();
		Debug.Log (response);
		sended = false;
	}
}
