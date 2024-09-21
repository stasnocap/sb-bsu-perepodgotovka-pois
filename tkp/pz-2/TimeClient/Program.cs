using ClockServer;
using CoreRemoting;

using var client = new RemotingClient(new ClientConfig()
{
    ServerHostName = "localhost",
    ServerPort = 9090,
});

client.Connect();

// Create a proxy of the remote service, which behaves almost like a regular local object
var proxy = client.CreateProxy<IStopwatch>();

Console.WriteLine("Starting stopwatch... Press enter to stop.");

proxy.Start();

Console.ReadLine();

var elapsedMilliseconds = proxy.Stop();

Console.WriteLine($"Elapsed milliseconds: {elapsedMilliseconds}. Press enter to exit.");

Console.ReadLine();