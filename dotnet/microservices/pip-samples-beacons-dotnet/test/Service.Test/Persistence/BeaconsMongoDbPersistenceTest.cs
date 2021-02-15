using System;
using System.Threading.Tasks;
using PipServices3.Commons.Config;
using PipServices3.Commons.Convert;
using Xunit;

namespace PipSample.Beacons.Persistence
{
  public class BeaconsMongoDbPersistenceTest : IDisposable
  {
    private bool _enabled = false;
    private BeaconsMongoDbPersistence _persistence;
    private BeaconsPersistenceFixture _fixture;

    public BeaconsMongoDbPersistenceTest()
    {
      var MONGO_ENABLED = Environment.GetEnvironmentVariable("MONGO_ENABLED") ?? "true";
      var MONGO_DB = Environment.GetEnvironmentVariable("MONGO_DB") ?? "test";
      var MONGO_COLLECTION = Environment.GetEnvironmentVariable("MONGO_COLLECTION") ?? "beacons";
      var MONGO_SERVICE_HOST = Environment.GetEnvironmentVariable("MONGO_SERVICE_HOST") ?? "localhost";
      var MONGO_SERVICE_PORT = Environment.GetEnvironmentVariable("MONGO_SERVICE_PORT") ?? "57017";
      var MONGO_SERVICE_URI = Environment.GetEnvironmentVariable("MONGO_SERVICE_URI");

      _enabled = BooleanConverter.ToBoolean(MONGO_ENABLED);

      if (_enabled)
      {
        var config = ConfigParams.FromTuples(
            "collection", MONGO_COLLECTION,
            "connection.database", MONGO_DB,
            "connection.host", MONGO_SERVICE_HOST,
            "connection.port", MONGO_SERVICE_PORT,
            "connection.uri", MONGO_SERVICE_URI
        );

        _persistence = new BeaconsMongoDbPersistence();
        _persistence.Configure(config);
        _persistence.OpenAsync(null).Wait();
        _persistence.ClearAsync(null).Wait();

        _fixture = new BeaconsPersistenceFixture(_persistence);
      }
    }

    public void Dispose()
    {
      if (_enabled)
        _persistence.CloseAsync(null).Wait();
    }

    [Fact]
    public async Task TestCrudOperationsAsync()
    {
      if (_enabled)
        await _fixture.TestCrudOperationsAsync();
    }

    [Fact]
    public async Task TestGetWithFiltersAsync()
    {
      if (_enabled)
        await _fixture.TestGetWithFiltersAsync();
    }
  }
}
