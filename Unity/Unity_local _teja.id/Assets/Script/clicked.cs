using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;
using System;
using System.Net.WebSockets;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using SocketIOClient;
using Newtonsoft.Json;
public class clicked : MonoBehaviour
{
    public GameObject button;
    public bool locked = false;
    // Start is called before the first frame update 
    SocketIO client;
    void Start()
    {
        button = GameObject.Find("button1");
        client = new SocketIO("http://te-ja.id:3003");
        client.On("data", args => Console.WriteLine(args.Text));
        client.ConnectAsync();
    }

    private async void Control(bool locks)
    {
        if (locks == true)
        {
            await client.EmitAsync("control", new { name = "M. As'ad Rosyadi", hwid = "BKV2010501", locks = "1",  deviceName = "Rumah",  });
        }
        else
        {
            await client.EmitAsync("control", new { name = "M. As'ad Rosyadi", hwid = "BKV2010501", locks = "0",  deviceName = "Rumah" });
        }
        //await client.EmitAsync("control", new { name = "M. As'ad Rosyadi", hwid = "BKV2010501", locks = locks,  deviceName ="Rumah"});
    }
    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if(Physics.Raycast(ray, out hit))
            {
                if(hit.collider.tag == "button")
                {
                    TextMesh textObject = GameObject.Find("text1").GetComponent<TextMesh>();
                    if (locked)
                    {
                        textObject.text = "Unlock";
                        float aX = button.transform.position.x;
                        float aZ = button.transform.position.z;
                        float aY = button.transform.position.y;
                        textObject.transform.position = new Vector3(aX - (0.38F * 140), aY, aZ + (0.3F * 45));
                        locked = !locked;
                        Control(locked);
                    } else
                    {
                        textObject.text = "Lock";
                        float aX = button.transform.position.x;
                        float aZ = button.transform.position.z;
                        float aY = button.transform.position.y;
                        textObject.transform.position = new Vector3(aX - (0.25F * 140), aY, aZ + (45 * 0.3F));
                        locked = !locked;
                        Control(locked);
                    }
                }
            }
        } else if (Input.touchCount > 0 && Input.touches[0].phase == TouchPhase.Began)
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.GetTouch(0).position);
            RaycastHit Hit;
            if (Physics.Raycast(ray, out Hit))
            {
                TextMesh textObject = GameObject.Find("text1").GetComponent<TextMesh>();
                if (locked)
                {
                    textObject.text = "Unlock";
                    float aX = button.transform.position.x;
                    float aZ = button.transform.position.z;
                    float aY = button.transform.position.y;
                    textObject.transform.position = new Vector3(aX - (0.38F * 140), aY, aZ + (0.3F * 45));
                    locked = !locked;
                    Control(locked);
                }
                else
                {
                    textObject.text = "Lock";
                    float aX = button.transform.position.x;
                    float aZ = button.transform.position.z;
                    float aY = button.transform.position.y;
                    textObject.transform.position = new Vector3(aX - (0.25F * 140), aY, aZ + (45 * 0.3F));
                    locked = !locked;
                    Control(locked);
                }
            }
        }
    }
}
