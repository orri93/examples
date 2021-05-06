using RestClient.GitHub;
using RestLibrary;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RestClient
{
    class Program
    {
        
        static void Main(string[] args)
        {
            Example.Execute();

            Client client = new Client();

            User user = client.DoLogin("orri", "orri");

            Console.WriteLine("First Name: {0}", user.FirstName);
            Console.WriteLine("Last Name: {0}", user.LastName);

            Console.ReadLine();
        }
    }
}
