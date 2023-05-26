using NetMQ;
using NetMQ.Sockets;

using (var client = new RequestSocket(">tcp://localhost:5556"))
{
    client.SendFrame("Hello from client B");
}
