using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Threading.Tasks;

namespace RestLibrary
{
    [ServiceContract]
    public interface IUserAccess
    {
        [OperationContract]
        [WebInvoke(Method = "GET",
             ResponseFormat = WebMessageFormat.Json,
             BodyStyle = WebMessageBodyStyle.Wrapped,
             UriTemplate = "login/{username}/{password}")]
        [return: MessageParameter(Name = "User")]
        User DoLogin(string userName, string password);
    }
}
