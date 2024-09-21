using ClockServer;
using CoreRemoting;
using CoreRemoting.DependencyInjection;
using TimeServer;

using var server = new RemotingServer(new ServerConfig
{
    HostName = "localhost",
    NetworkPort = 9090,
    RegisterServicesAction = container =>
    {
        container.RegisterService<IStopwatch, Stopwatch>(ServiceLifetime.Singleton);
    },
});

server.Start();
            
Console.WriteLine("Server is running.");
Console.ReadLine();