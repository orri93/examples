using RestLibrary;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace RestService
{
    public class Service : IUserAccess
    {
        [return: MessageParameter(Name = "User")]
        public User DoLogin(string userName, string password)
        {
            try
            {
                User user = new User();

                if (String.Equals(userName, "orri") && String.Equals(password, "orri"))
                {
                    user.UserName = userName;
                    user.Password = password;
                    user.FirstName = "Geirmundur";
                    user.LastName = "Sigurðsson";
                }

                return user;
            }
            catch(Exception)
            {
                return null;
            }
        }
    }
}
