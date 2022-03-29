import asyncio
from datetime import datetime, timedelta

from asyncua import Client

async def main():
  # url = "opc.tcp://metpfsexi:4840/"
  url = "opc.tcp://gospfsexi:4840/"
  # url = "opc.tcp://wt-mdt-eur-web-dsn:4840/"
  async with Client(url=url) as client:
    print("OPC UA Client created for", url)
    node = client.get_node('ns=4;s=Depth Tracking.BitPosition')
    print("Node Namespace Index:", node.nodeid.NamespaceIndex)
    print("Node Identifier:", node.nodeid.Identifier)

    start = datetime.utcnow()
    end = start - timedelta(days = 1)

    print("Start time:", start)
    print("End Time:", end)

    rrha = node.read_raw_history(start, end)

    data = await rrha
    # for i in range(len(data)):
    #   print("Value %d" % i)

if __name__ == "__main__":
  asyncio.run(main())
