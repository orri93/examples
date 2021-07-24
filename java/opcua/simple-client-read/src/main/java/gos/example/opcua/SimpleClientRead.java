package gos.example.opcua;

import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

import com.google.common.collect.ImmutableList;

import org.eclipse.milo.opcua.sdk.client.OpcUaClient;
import org.eclipse.milo.opcua.sdk.client.nodes.UaVariableNode;
import org.eclipse.milo.opcua.stack.core.Identifiers;
import org.eclipse.milo.opcua.stack.core.UaException;
import org.eclipse.milo.opcua.stack.core.types.builtin.DataValue;
import org.eclipse.milo.opcua.stack.core.types.builtin.NodeId;
import org.eclipse.milo.opcua.stack.core.types.enumerated.ServerState;
import org.eclipse.milo.opcua.stack.core.types.enumerated.TimestampsToReturn;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class SimpleClientRead {
  private static final String DefaultEndpoint = "opc.tcp://localhost:4840";

  private final Logger logger = LoggerFactory.getLogger(getClass());

  public static void main(String[] args) {
    SimpleClientRead instance = new SimpleClientRead();
    try {
      instance.execute(args);
    } catch (UaException e) {
      e.printStackTrace();
    } catch (InterruptedException e) {
      e.printStackTrace();
    } catch (ExecutionException e) {
      e.printStackTrace();
    }
  }

  public void execute(String[] args) throws UaException, InterruptedException, ExecutionException {
    NodeId readNode = null;
    String endpoint = DefaultEndpoint;
    System.out.println("Starting the Simple OPC UA Client Read Example");
    if (args.length > 0) {
      endpoint = args[0];
    }
    if (args.length > 1) {
      readNode = NodeId.parseOrNull(args[1]);
      if (readNode == null) {
        System.err.println("Failed to parse '" + args[1] + "' as node id");
      } else {
        System.out.println("Plan to read from node '" + args[1] + "'");
      }
    }
    System.out.println("Connecting to " + endpoint);
    OpcUaClient client = OpcUaClient.create(endpoint);
    client.connect().get();

    UaVariableNode node = client.getAddressSpace().getVariableNode(Identifiers.Server_ServerStatus_StartTime);
    DataValue value = node.readValue();

    logger.info("StartTime={}", value.getValue().getValue());

    readServerStateAndTime(client).thenAccept(values -> {
      DataValue v0 = values.get(0);
      DataValue v1 = values.get(0);

      logger.info("State={}", ServerState.from((Integer) v0.getValue().getValue()));
      logger.info("CurrentTime={}", v1.getValue().getValue());
    });

    if (readNode != null) {
      value = client.readValue(0.0, TimestampsToReturn.Both, readNode).get();
      System.out.println("Value: " + value.getValue().toString());
    }
  }

  private CompletableFuture<List<DataValue>> readServerStateAndTime(OpcUaClient client) {
    List<NodeId> nodeIds = ImmutableList.of(
      Identifiers.Server_ServerStatus_State,
      Identifiers.Server_ServerStatus_CurrentTime);
    return client.readValues(0.0, TimestampsToReturn.Both, nodeIds);
  }
}
