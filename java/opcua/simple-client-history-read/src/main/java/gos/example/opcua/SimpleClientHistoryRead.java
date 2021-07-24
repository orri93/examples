package gos.example.opcua;

import static org.eclipse.milo.opcua.stack.core.types.builtin.unsigned.Unsigned.uint;
import static org.eclipse.milo.opcua.stack.core.util.ConversionUtil.l;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

import org.eclipse.milo.opcua.sdk.client.OpcUaClient;
import org.eclipse.milo.opcua.stack.core.UaException;
import org.eclipse.milo.opcua.stack.core.types.builtin.ByteString;
import org.eclipse.milo.opcua.stack.core.types.builtin.DataValue;
import org.eclipse.milo.opcua.stack.core.types.builtin.DateTime;
import org.eclipse.milo.opcua.stack.core.types.builtin.NodeId;
import org.eclipse.milo.opcua.stack.core.types.builtin.QualifiedName;
import org.eclipse.milo.opcua.stack.core.types.builtin.StatusCode;
import org.eclipse.milo.opcua.stack.core.types.enumerated.TimestampsToReturn;
import org.eclipse.milo.opcua.stack.core.types.structured.HistoryData;
import org.eclipse.milo.opcua.stack.core.types.structured.HistoryReadDetails;
import org.eclipse.milo.opcua.stack.core.types.structured.HistoryReadRequest;
import org.eclipse.milo.opcua.stack.core.types.structured.HistoryReadResponse;
import org.eclipse.milo.opcua.stack.core.types.structured.HistoryReadResult;
import org.eclipse.milo.opcua.stack.core.types.structured.HistoryReadValueId;
import org.eclipse.milo.opcua.stack.core.types.structured.ReadRawModifiedDetails;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class SimpleClientHistoryRead {
  private static final String DefaultEndpoint = "opc.tcp://localhost:4840";

  private final Logger logger = LoggerFactory.getLogger(getClass());

  public static void main(String[] args) {
    SimpleClientHistoryRead instance = new SimpleClientHistoryRead();
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

    HistoryReadDetails historyReadDetails = new ReadRawModifiedDetails(
      false,
      DateTime.MIN_VALUE,
      DateTime.now(),
      uint(0),
      true);

    List<HistoryReadValueId> nodesToRead = new ArrayList<>();

    HistoryReadValueId historyReadValueId = new HistoryReadValueId(
      new NodeId(3, "Counter"),
      null,
      QualifiedName.NULL_VALUE,
      ByteString.NULL_VALUE);
    nodesToRead.add(historyReadValueId);

    if (readNode != null) {
      HistoryReadValueId historyReadNode = new HistoryReadValueId(
        readNode,
        null,
        QualifiedName.NULL_VALUE,
        ByteString.NULL_VALUE);
        nodesToRead.add(historyReadNode);
    }

    HistoryReadResponse historyReadResponse = client.historyRead(
      historyReadDetails,
      TimestampsToReturn.Both,
      false,
      nodesToRead).get();
    
    HistoryReadResult[] historyReadResults = historyReadResponse.getResults();

    if (historyReadResults != null) {
      HistoryReadResult historyReadResult = historyReadResults[0];
      StatusCode statusCode = historyReadResult.getStatusCode();

      if (statusCode.isGood()) {
        HistoryData historyData = (HistoryData) historyReadResult.getHistoryData().decode(
          client.getStaticSerializationContext());

        List<DataValue> dataValues = l(historyData.getDataValues());

        dataValues.forEach(v -> System.out.println("value=" + v));
      } else {
        System.out.println("History read failed: " + statusCode);
      }
    }
  }
}
