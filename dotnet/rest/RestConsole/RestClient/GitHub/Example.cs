using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RestClient.GitHub
{
    public static class Example
    {
        public const string BaseUrl = "https://api.github.com";
        public const string Url = BaseUrl + "/repos/restsharp/restsharp/releases";

        public static void Execute()
        {
            IRequestHandler client = new Client();

            string response = client.GetReleases(Url);

            var githubReleases = JsonConvert.DeserializeObject<List<GitHubRelease>>(response);

            foreach (var release in githubReleases)
            {
                Console.WriteLine("Release: {0}", release.Name);
                Console.WriteLine("Published: {0}", DateTime.Parse(release.PublishedAt));
            }
        }
    }
}
