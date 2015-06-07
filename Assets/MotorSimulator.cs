using UnityEngine;
using System.Collections;

public class MotorSimulator : MonoBehaviour {
	public Rigidbody	motorFR;
	public Rigidbody	motorBR;
	public Rigidbody	motorFL;
	public Rigidbody	motorBL;
	public float		maxThrust = 0.870f; // Maximum thrust of a single motor

	public float		maxPitchAngle = 7f;
	public float		maxRollAngle = 7f;
	public float		maxVerticalSpeed = 0f;
	public float		maxYaxSpeed = 0f;
	public float		maxThrustAuthorized = 0f;

	float				innerThrust = 0f;
	float				generalThrottle;
	float				desiredPitch = 0f;
	float				desiredRoll = 0f;

	// Use this for initialization
	void Start () {
	
	}

	public void setGeneralThrottle(float throttle)
	{
		generalThrottle = throttle;
	}

	public void setPitchAngle(float angle)
	{
		desiredPitch = angle;
	}

	public void setRollAngle(float angle)
	{
		desiredRoll = angle;
	}

	void FixedUpdate()
	{
		Vector3 thrust = new Vector3(0f, generalThrottle * maxThrust * 9.8f / 2f, 0f);

		innerThrust = thrust.y;
		motorFR.AddRelativeForce (thrust, ForceMode.Force);
		motorBR.AddRelativeForce (thrust, ForceMode.Force);
		motorFL.AddRelativeForce (thrust, ForceMode.Force);
		motorBL.AddRelativeForce (thrust, ForceMode.Force);
	}

	Vector3 composeThrust(Vector3 baseThrust, float inputThrust)
	{
		return new Vector3 (0, baseThrust.y * inputThrust, 0);
	}

	// Update is called once per frame
	void Update () {
		Debug.Log ("InnerThrust : " + innerThrust + ", general : " + generalThrottle + ", max: " + maxThrust);
	}
}
