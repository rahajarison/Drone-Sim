using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class ArduinoCommunicator : MonoBehaviour {
	// TODO assurer le singleton

	public string	serialPort = "COM3";
	public int		bauds = 9600;

	SerialPort stream = null;
	// Use this for initialization
	void	Start () {
		connectToArduino ();
	}
	
	// Update is called once per frame
	void	Update () {
	
	}

	void	createConnection()
	{
		stream = new SerialPort(serialPort, bauds);
		stream.Open();
//		stream.DataReceived += dataReceiver;
//		stream.ReadTimeout = 200; // Assigne le timeout de read à 16 pour environ 60 FPS (trame non événementielle)
		Debug.Log("Connection série effectuée !");
	}

//	void	dataReceiver(object sender, SerialDataReceivedEventArgs e)
//	{
//		SerialPort srlPort = (SerialPort) sender;
//		byte[] buf = new byte[srlPort.BytesToRead];
//		Debug.Log ("Data to read !");
//		srlPort.Read (buf, 0, buf.Length);
//		foreach (byte b in buf)
//		{
//			Debug.Log(b.ToString() + " ");
//		}
//	}

	void	connectToArduino()
	{
		if (stream != null)
		{
			if (stream.IsOpen)
			{
				stream.Close();
				Debug.LogWarning("Fermeture du port (déjà ouvert)");
			}
			else
			{
				createConnection ();
			}
		}
		else
		{
			createConnection ();
		}
	}

	public void sendByte(byte toSend)
	{
		byte[] dataToSend = new byte[1];
		sendBytes (dataToSend);
	}

	public void	sendBytes(byte[] bytes)
	{
		Debug.Log ("Sending byte !");
		stream.Write (bytes, 0, 1);
	}

	public int readByte()
	{
		int toReturn = stream.ReadByte ();
		return toReturn;
	}

	void	OnApplicationQuit()
	{
		stream.Close ();
	}
}
