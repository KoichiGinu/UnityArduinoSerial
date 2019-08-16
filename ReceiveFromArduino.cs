using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

public class ReceiveFromArduino : MonoBehaviour
{
    //これをアタッチしたオブジェクトを格納
    public SerialHandler serialHandler;

    private float duration;
    private float[] data;

    // Use this for initialization
    void Start()
    {
        //信号を受信したときに、そのメッセージの処理を行う
        serialHandler.OnDataReceived += OnDataReceived;

        //時間計測開始
        duration = 0;
    }

    // Update is called once per frame
    void Update()
    {
        //フレーム書き換えごとに経過時間を累積
        duration += Time.deltaTime;

    }

    /*
	 * シリアルを受け取った時の処理
	 */
    void OnDataReceived(string message)
    {
        try
        {
            //Arduinoからの値をコンマ区切りでSensor[]にぶち込む
            string[] message = message.Split(',');

            if (message[0] == "HelloUnity")
            {
                //Arduinoから来た加速度センサの値をそのままぶち込んでいる
                for (int i = 0; i < int.Parse(message[1]); i++)
                {
                    data[i] = float.Parse(message[i + 2]);
                }
            }
        }
        catch (System.Exception e)
        {
            Debug.LogWarning(e.Message);
        }
    }
}