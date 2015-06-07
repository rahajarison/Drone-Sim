using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class DroneController : MonoBehaviour {
	public Text	throttleText;
	public Text	yawText;
	public Text	pitchText;
	public Text	rollText;

	public ArduinoCommunicator	arduino;
	public MotorSimulator motors;

	public delegate void pong();

	float throttle = 0f;
	float yaw = 0f;
	float pitch = 0f;
	float roll = 0f;

	bool	sended = false;

	float	maxInputValue = 0.016f;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		throttle = Input.GetAxis("Throttle") * Time.deltaTime;
		yaw = Input.GetAxisRaw ("Yaw") * Time.deltaTime;
		pitch = Input.GetAxisRaw("Pitch") * Time.deltaTime;
		roll = Input.GetAxisRaw("Roll") * Time.deltaTime;
	
		throttleText.text = "Gaz : " + throttle;
		yawText.text = "Lacet : " + yaw;
		pitchText.text = "Angle d attaque : " + pitch;
		rollText.text = "Roulis : " + roll;
		motors.setGeneralThrottle(calculatePercentage(throttle, 0, maxInputValue) / 100f);
		motors.setPitchAngle(calculatePercentage(pitch, -maxInputValue, maxInputValue) / 100f);
		// pingArduino ();
	}


	byte calculatePercentage(float value, float min, float max)
	{
		value = Mathf.Clamp(value, min, max);
		if (min >= 0)
			return (byte) Mathf.RoundToInt((value * 100) / (max - min));
		else
			return (byte) Mathf.RoundToInt((value + max * 100) / (max - min));
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
