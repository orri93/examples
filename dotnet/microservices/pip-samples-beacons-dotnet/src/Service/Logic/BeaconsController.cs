﻿using System.Threading.Tasks;
using PipSample.Beacons.Data.Version1;
using PipSample.Beacons.Persistence;
using PipServices3.Commons.Commands;
using PipServices3.Commons.Config;
using PipServices3.Commons.Data;
using PipServices3.Commons.Refer;

namespace PipSample.Beacons.Logic
{
  public class BeaconController : IBeaconsController, IConfigurable, IReferenceable, ICommandable
  {
    private IBeaconsPersistence _persistence;
    private BeaconsCommandSet _commandSet;
    private string _param1 = "ABC";
    private int _param2 = 123;

    public BeaconsController()
    { }

    public void Configure(ConfigParams config)
    {
      _param1 = config.GetAsStringWithDefault("param1", _param1);
      _param2 = config.GetAsIntegerWithDefault("param2", _param2);

    }

    public void SetReferences(IReferences references)
    {
      _persistence = references.GetOneRequired<IBeaconsPersistence>(
          new Descriptor("beacons", "persistence", "*", "*", "1.0")
      );
    }

    public CommandSet GetCommandSet()
    {
      if (_commandSet == null)
        _commandSet = new BeaconsCommandSet(this);
      return _commandSet;
    }

    public async Task<DataPage<BeaconV1>> GetBeaconsAsync(
        string correlationId, FilterParams filter, PagingParams paging)
    {
      return await _persistence.GetPageByFilterAsync(correlationId, filter, paging);
    }

    public async Task<BeaconV1> GetBeaconByIdAsync(string correlationId, string id)
    {
      return await _persistence.GetOneByIdAsync(correlationId, id);
    }

    public async Task<BeaconV1> GetBeaconByUdiAsync(string correlationId, string udi)
    {
      return await _persistence.GetOneByUdiAsync(correlationId, udi);
    }

    public async Task<CenterObjectV1> CalculatePositionAsync(
        string correlationId, string siteId, string[] udis)
    {
      if (udis == null || udis.Length == 0) return null;

      var page = await this._persistence.GetPageByFilterAsync(
          correlationId,
          FilterParams.FromTuples("site_id", siteId, "udis", udis),
          null
      );

      var lat = 0.0;
      var lng = 0.0;
      var count = 0;

      foreach (var beacon in page.Data)
      {
        if (beacon.Center != null
            && beacon.Center.Type == "Point"
            && beacon.Center.Coordinates.Length > 1)
        {
          lng += beacon.Center.Coordinates[0];
          lat += beacon.Center.Coordinates[1];
          count += 1;
        }
      }

      if (count > 0)
      {
        return new CenterObjectV1
        {
          Type = "Point",
          Coordinates = new double[] { lng / count, lat / count }
        };
      }

      return null;
    }

    public async Task<BeaconV1> CreateBeaconAsync(string correlationId, BeaconV1 beacon)
    {
      beacon.Id = beacon.Id ?? IdGenerator.NextLong();
      beacon.Type = beacon.Type ?? BeaconTypeV1.Unknown;

      return await _persistence.CreateAsync(correlationId, beacon);
    }

    public async Task<BeaconV1> UpdateBeaconAsync(string correlationId, BeaconV1 beacon)
    {
      beacon.Type = beacon.Type ?? BeaconTypeV1.Unknown;

      return await _persistence.UpdateAsync(correlationId, beacon);
    }

    public async Task<BeaconV1> DeleteBeaconByIdAsync(string correlationId, string id)
    {
      return await _persistence.DeleteByIdAsync(correlationId, id);
    }
  }
}
