﻿using System.Linq;
using System.Collections.Generic;
using System.Threading.Tasks;
using PipSample.Beacons.Data.Version1;
using PipServices3.Commons.Data;
using PipServices3.SqlServer.Persistence;

namespace PipSample.Beacons.Persistence
{
  public class BeaconsSqlServerPersistence : IdentifiableSqlServerPersistence<BeaconV1, string>, IBeaconsPersistence
  {
    public BeaconsSqlServerPersistence() : base("beacons")
    {
      AutoCreateObject("CREATE TABLE [beacons] ([id] VARCHAR(32), [site_id] VARCHAR(32), [type] VARCHAR(15), [udi] VARCHAR(25), [label] VARCHAR(50), [center] JSONB, [radius] REAL)");
      EnsureIndex("beacons_site_id", new Dictionary<string, bool> { { "site_id", true } }, new IndexOptions());
      this._maxPageSize = 1000;
    }

    private string ComposeFilter(FilterParams filter)
    {
      filter = filter ?? new FilterParams();

      var filters = new List<string>();

      var id = filter.GetAsNullableString("id");
      if (id != null)
        filters.Add("[id]='" + id + "'");

      var siteId = filter.GetAsNullableString("site_id");
      if (siteId != null)
        filters.Add("[site_id]='" + siteId + "'");

      var label = filter.GetAsNullableString("label");
      if (label != null)
        filters.Add("[label]='" + label + "'");

      var uid = filter.GetAsNullableString("uid");
      if (uid != null)
        filters.Add("[uid]='" + uid + "'");

      var tempUdis = filter.GetAsString("udis");
      var udis = tempUdis != null ? tempUdis.Split(',') : null;
      if (udis != null)
        filters.Add("[udi] IN ('" + string.Join("','", udis) + "')");

      return filters.Count > 0 ? string.Join(" AND ", filters.ToArray()) : null;
    }

    public async Task<DataPage<BeaconV1>> GetPageByFilterAsync(
         string correlationId, FilterParams filter, PagingParams paging)
    {
      return await GetPageByFilterAsync(correlationId, ComposeFilter(filter), paging, "[id]");
    }


    public async Task<BeaconV1> GetOneByUdiAsync(string correlationId, string udi)
    {
      var @params = new[] { udi };
      var query = "SELECT * FROM " + QuoteIdentifier(_tableName) + " WHERE [udi] = @param1";

      var result = (await ExecuteReaderAsync(query, @params)).FirstOrDefault();

      if (result == null)
      {
        _logger.Trace(correlationId, "Nothing found from {0} with udi = {1}", _tableName, udi);
        return default;
      }

      _logger.Trace(correlationId, "Retrieved from {0} with udi = {1}", _tableName, udi);

      var item = ConvertToPublic(result);

      return item;
    }
  }
}
