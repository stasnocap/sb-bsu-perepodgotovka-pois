using Microsoft.Extensions.DependencyInjection;

namespace TcpConfiguration;

public static class TcpExtensions
{
    public static IServiceCollection AddTcpConfiguration(this IServiceCollection services)
    {
        services.AddOptionsWithValidateOnStart<TcpOptions>()
            .BindConfiguration(nameof(TcpOptions));

        return services;
    }
}