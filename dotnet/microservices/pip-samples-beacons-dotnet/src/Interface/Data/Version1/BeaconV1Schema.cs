using PipServices3.Commons.Convert;
using PipServices3.Commons.Validate;

namespace PipSample.Beacons.Data.Version1
{
  public class BeaconV1Schema : ObjectSchema
  {
    public BeaconV1Schema()
    {
      base.WithOptionalProperty("id", TypeCode.String);
      base.WithRequiredProperty("site_id", TypeCode.String);
      base.WithOptionalProperty("type", TypeCode.String);
      base.WithRequiredProperty("uid", TypeCode.String);
      base.WithOptionalProperty("label", TypeCode.String);
      base.WithOptionalProperty("center", null);
      base.WithOptionalProperty("radius", TypeCode.Double);
    }
  }
}
