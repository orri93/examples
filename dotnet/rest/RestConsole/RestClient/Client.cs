using Newtonsoft.Json;
using RestClient.Model;
using RestLibrary;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace RestClient
{
    public class Client : IUserAccess
    {
        private const string UserAgent = "User-Agent";
        private const string UserAgentValue = "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";

        public User DoLogin(string userName, string password)
        {
            using (HttpClient httpClient = new HttpClient())
            {
                string url = String.Format("http://127.0.0.1:8888/login/{0}/{0}", userName, password);
                httpClient.DefaultRequestHeaders.Add(UserAgent, UserAgentValue);
                string response = httpClient.GetStringAsync(new Uri(url)).Result;
                UserMessage message = JsonConvert.DeserializeObject<UserMessage>(response);
                return message.User;
            }
        }
    }
}
