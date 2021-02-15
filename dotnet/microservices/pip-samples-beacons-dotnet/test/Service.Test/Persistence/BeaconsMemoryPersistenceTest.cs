using System;
using System.Threading.Tasks;
using PipServices3.Commons.Config;
using Xunit;

namespace PipSample.Beacons.Persistence
{
  public class BeaconsMemoryPersistenceTest : IDisposable
  {
    public BeaconsMemoryPersistence _persistence;
    public BeaconsPersistenceFixture _fixture;

    public BeaconsMemoryPersistenceTest()
    {
      _persistence = new BeaconsMemoryPersistence();
      _persistence.Configure(new ConfigParams());

      _fixture = new BeaconsPersistenceFixture(_persistence);

      _persistence.OpenAsync(null).Wait();
    }

    public void Dispose()
    {
      _persistence.CloseAsync(null).Wait();
    }

    [Fact]
    public async Task TestCrudOperationsAsync()
    {
      await _fixture.TestCrudOperationsAsync();
    }

    [Fact]
    public async Task TestGetWithFiltersAsync()
    {
      await _fixture.TestGetWithFiltersAsync();
    }
  }
}
