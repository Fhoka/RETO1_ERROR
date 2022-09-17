using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Runtime.Remoting.Messaging;
using TMPro;

enum TaskState
{
    INIT,
    WAIT_COMMANDS
}

public class Serial : MonoBehaviour
{
    private static TaskState taskState = TaskState.INIT;
    private SerialPort _serialPort;
    private byte[] buffer;
    public TextMeshProUGUI myText;
    private TextMeshProUGUI myTextCache;
    private int counter = 0;
    void Start()
    {
        _serialPort = new SerialPort();
        _serialPort.PortName = "/dev/ttyACM0";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;
        _serialPort.NewLine = "\n";
        _serialPort.Open();
        Debug.Log("Open Serial Port");
        buffer = new byte[128];
        myTextCache = myText;
    }

    void Update()
    {
        myText = myTextCache;
        myText.text = counter.ToString();
        counter++;
        
        switch (taskState)
        {
            case TaskState.INIT:
                taskState = TaskState.WAIT_COMMANDS;
                Debug.Log("WAIT COMMANDS");
                break;
            case TaskState.WAIT_COMMANDS:

                if (_serialPort.BytesToRead > 0)
                {
                    string response = _serialPort.ReadLine();
                    // response : 1,1\n
                    Debug.Log(response);
                }
                break;
            default:
                Debug.Log("State Error");
                break;
        }
    }

    public void ledON()
    {
        _serialPort.Write("ON\n");
    }
    
    public void ledOFF()
    {
        _serialPort.Write("OFF\n");
    }

    public void read()
    {
        _serialPort.Write("read\n");
    }
}
