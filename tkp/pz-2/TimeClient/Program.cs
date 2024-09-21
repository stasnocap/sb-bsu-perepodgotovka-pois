using System.Net;
using System.Net.Sockets;
using System.Text;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Options;
using TcpConfiguration;

var serviceProvider = BuildServiceProvider();

var tcpOptions = serviceProvider.GetRequiredService<IOptions<TcpOptions>>();

var ipEndPoint = new IPEndPoint(IPAddress.Parse(tcpOptions.Value.Host), tcpOptions.Value.Port);

using TcpClient client = new();
await client.ConnectAsync(ipEndPoint);
await using NetworkStream stream = client.GetStream();

var buffer = new byte[1_024];
int received = await stream.ReadAsync(buffer);

var message = Encoding.UTF8.GetString(buffer, 0, received);
Console.WriteLine($"Message received: \"{message}\"");

Console.ReadLine();

static ServiceProvider BuildServiceProvider()
{
    var services = new ServiceCollection();

    services.AddSingleton<IConfiguration>(new ConfigurationBuilder()
        .AddJsonFile("appsettings.json")
        .Build());

    services.AddTcpConfiguration();

    return services.BuildServiceProvider();
}