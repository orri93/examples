using NetMQ;
using NetMQ.Sockets;

using (var server = new ResponseSocket(">tcp://localhost:5556"))
{
    string m1 = server.ReceiveFrameString();
    Console.WriteLine("From Client: {0}", m1);
    server.SendFrame("Hi Back");
}
