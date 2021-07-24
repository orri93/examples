package gos.example.opcua;

import static org.eclipse.milo.opcua.stack.core.types.builtin.unsigned.Unsigned.uint;
import static org.eclipse.milo.opcua.stack.core.util.ConversionUtil.toList;

import java.util.List;
import java.util.concurrent.ExecutionException;

import org.eclipse.milo.opcua.sdk.client.OpcUaClient;
import org.eclipse.milo.opcua.stack.core.Identifiers;
import org.eclipse.milo.opcua.stack.core.UaException;
import org.eclipse.milo.opcua.stack.core.types.builtin.NodeId;
import org.eclipse.milo.opcua.stack.core.types.enumerated.BrowseDirection;
import org.eclipse.milo.opcua.stack.core.types.enumerated.BrowseResultMask;
import org.eclipse.milo.opcua.stack.core.types.enumerated.NodeClass;
import org.eclipse.milo.opcua.stack.core.types.structured.BrowseDescription;
import org.eclipse.milo.opcua.stack.core.types.structured.BrowseResult;
import org.eclipse.milo.opcua.stack.core.types.structured.ReferenceDescription;
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
    NodeId browseRoot = Identifiers.RootFolder;
    String endpoint = DefaultEndpoint;
    System.out.println("Starting the Simple OPC UA Client Read Example");
    if (args.length > 0) {
      endpoint = args[0];
    }
    if (args.length > 1) {
      browseRoot = NodeId.parseOrNull(args[1]);
      if (browseRoot == null) {
        System.err.println("Failed to parse '" + args[1] + "' as node id");
        browseRoot = Identifiers.RootFolder;
      } else {
        System.out.println("Plan to browse from node '" + args[1] + "'");
      }
    }
    System.out.println("Connecting to " + endpoint);
    OpcUaClient client = OpcUaClient.create(endpoint);
    client.connect().get();

    // start browsing at root folder
    browseNode("", client, browseRoot);
  }

  private void browseNode(String indent, OpcUaClient client, NodeId browseRoot) {
    BrowseDescription browse = new BrowseDescription(
      browseRoot,
      BrowseDirection.Forward,
      Identifiers.References,
      true,
      uint(NodeClass.Object.getValue() | NodeClass.Variable.getValue()),
      uint(BrowseResultMask.All.getValue())
    );

    try {
      BrowseResult browseResult = client.browse(browse).get();

      List<ReferenceDescription> references = toList(browseResult.getReferences());

      for (ReferenceDescription rd : references) {
        logger.info("{} Node={}", indent, rd.getBrowseName().getName());

      // recursively browse to children
      rd.getNodeId().toNodeId(client.getNamespaceTable())
        .ifPresent(nodeId -> browseNode(indent + "  ", client, nodeId));
      }
    } catch (InterruptedException | ExecutionException e) {
      logger.error("Browsing nodeId={} failed: {}", browseRoot, e.getMessage(), e);
    }
  }
}
