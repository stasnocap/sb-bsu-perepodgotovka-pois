using Microsoft.AspNetCore.Mvc.Infrastructure;
using Music.Api.Common.Errors;
using Music.Api.Common.Mapping;

namespace Music.Api;

public static class DependencyInjection
{
    public static IServiceCollection AddPresentation(this IServiceCollection services)
    {
        services.AddControllers();
        services.AddSingleton<ProblemDetailsFactory, MusicProblemDetailsFactory>();
        services.AddMappings();
        return services;
    }
}