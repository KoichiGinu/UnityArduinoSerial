using UnityEngine;
using System.Collections;

public class SendToArduino : MonoBehaviour
{
    public SerialHandler serialHandler;
    private float duration;

    private void Start()
    {
        //時間計測開始
        duration = 0;

        start = true;
    }

    void Update()
    {
        //フレーム書き換えごとに経過時間を累積
        duration += Time.deltaTime;

        //Arduinoに文字を送る
        serialHandler.Write("0");
    }
}