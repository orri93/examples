import asyncio
import logging

from asyncua import Client

_logger = logging.getLogger('asyncua')

async def main():
  # url = "opc.tcp://metpfsexi:4840/"
  url = "opc.tcp://gospfsexi:4840/"
  # url = "opc.tcp://wt-mdt-eur-web-dsn:4840/"
  async with Client(url=url) as client:
    _logger.info("Root node is: %r", client.nodes.root)

    node = client.get_node('ns=2;s=Depth Tracking.BitPosition')
    value = await node.read_value()

    _logger.info("Value is: %r", value)

if __name__ == "__main__":
  logging.basicConfig(level=logging.INFO)
  asyncio.run(main())
