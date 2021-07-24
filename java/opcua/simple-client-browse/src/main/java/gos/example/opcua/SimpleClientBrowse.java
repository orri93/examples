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

public class SimpleClientBrowse {
  private static final String DefaultEndpoint = "opc.tcp://localhost:4840";

  private final Logger logger = LoggerFactory.getLogger(getClass());

  public static void main(String[] args) {
    SimpleClientBrowse instance = new SimpleClientBrowse();
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
    String endpoint = DefaultEndpoint;
    System.out.println("Starting the Simple OPC UA Client Read Example");
    if (args.length > 0) {
      endpoint = args[0];
    }
    System.out.println("Connecting to " + endpoint);
    OpcUaClient client = OpcUaClient.create(endpoint);
    client.connect().get();
  }
}
