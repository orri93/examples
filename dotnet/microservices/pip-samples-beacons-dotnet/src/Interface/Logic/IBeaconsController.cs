using System.Threading.Tasks;
using PipSample.Beacons.Data.Version1;
using PipServices3.Commons.Data;

namespace PipSample.Beacons.Logic
{
  public interface IBeaconsController
  {
    Task<DataPage<BeaconV1>> GetBeaconAsync(string correlationId, FilterParams filter, PagingParams paging);

    Task<BeaconV1> GetBeaconByIdAsync(string correlationId, string id);

    Task<BeaconV1> GetBeaconByUdiAsync(string correlationId, string uid);

    Task<CenterObjectV1> CalculatePositionAsync(string correlationId, string siteId, string[] udis);

    Task<BeaconV1> CreateBeaconAsync(string correlationId, BeaconV1 beacon);

    Task<BeaconV1> UpdateBeaconAsync(string correlationId, BeaconV1 beacon);

    Task<BeaconV1> DeleteBeaconAsync(string correlationId, string id);
  }
}
