using NetMQ;
using NetMQ.Sockets;

using (var client = new RequestSocket("@tcp://localhost:5556"))
{
    client.SendFrame("Hello from client A");
    string m2 = client.ReceiveFrameString();
    Console.WriteLine("From Server: {0}", m2);
}
