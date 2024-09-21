using System.Net;
using System.Net.Sockets;
using System.Text;using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Options;
using TcpConfiguration;

var serviceProvider = BuildServiceProvider();

var tcpOptions = serviceProvider.GetRequiredService<IOptions<TcpOptions>>();

var ipEndPoint = new IPEndPoint(IPAddress.Parse(tcpOptions.Value.Host), tcpOptions.Value.Port);
TcpListener listener = new(ipEndPoint);

try
{    
    listener.Start();

    using TcpClient handler = await listener.AcceptTcpClientAsync();
    await using NetworkStream stream = handler.GetStream();

    var message = $"📅 {DateTime.Now} 🕛";
    var dateTimeBytes = Encoding.UTF8.GetBytes(message);
    await stream.WriteAsync(dateTimeBytes);

    Console.WriteLine($"Sent message: \"{message}\"");
}
finally
{
    listener.Stop();
}

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