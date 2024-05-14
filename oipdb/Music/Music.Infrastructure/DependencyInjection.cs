using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Music.Application.Common.Interfaces.Authentication;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Common.Interfaces.Services;
using Music.Infrastructure.Authentication;
using Music.Infrastructure.Persistence;
using Music.Infrastructure.Services;

namespace Music.Infrastructure;

public static class DependencyInjection
{
    public static IServiceCollection AddInfrastructure(this IServiceCollection services,
        IConfiguration configuration)
    {
        services.Configure<JwtSettings>(configuration.GetSection(JwtSettings.SectionName));
        
        services.AddSingleton<IJwtTokenGenerator, JwtTokenGenerator>();
        services.AddSingleton<IDateTimeProvider, DateTimeProvider>();

        services.AddScoped<IUserRepository, UserRepository>();
        return services;
    }
}