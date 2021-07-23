package gos.example.opcua;

import java.util.concurrent.ExecutionException;

import org.eclipse.milo.opcua.sdk.client.OpcUaClient;
import org.eclipse.milo.opcua.sdk.client.nodes.UaVariableNode;
import org.eclipse.milo.opcua.stack.core.Identifiers;
import org.eclipse.milo.opcua.stack.core.UaException;
import org.eclipse.milo.opcua.stack.core.types.builtin.DataValue;

public class SimpleClientRead {
  public static void main(String[] args) {
    SimpleClientRead instance = new SimpleClientRead();
    try {
      instance.execute();
    } catch (UaException e) {
      e.printStackTrace();
    } catch (InterruptedException e) {
      e.printStackTrace();
    } catch (ExecutionException e) {
      e.printStackTrace();
    }
  }

  public void execute() throws UaException, InterruptedException, ExecutionException {
    System.out.println("Starting the Simple OPC UA Client Read Example");
    OpcUaClient client = OpcUaClient.create("opc.tcp://localhost:4840");
    client.connect().get();

    UaVariableNode node = client.getAddressSpace().getVariableNode(Identifiers.Server_ServerStatus_StartTime);
    DataValue value = node.readValue();

    
  }
}
