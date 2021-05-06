using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace RestClient.GitHub
{
    public class Client : IRequestHandler
    {
        private const string UserAgent = "User-Agent";
        private const string UserAgentValue = "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";

        public string GetReleases(string url)
        {
            using (HttpClient httpClient = new HttpClient())
            {
                httpClient.DefaultRequestHeaders.Add(UserAgent, UserAgentValue);
                var respone = httpClient.GetStringAsync(new Uri(url)).Result;
                return respone;
            }
        }
    }
}
