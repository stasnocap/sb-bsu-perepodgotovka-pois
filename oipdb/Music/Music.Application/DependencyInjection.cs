﻿using Microsoft.Extensions.DependencyInjection;
using Music.Application.Services;

namespace Music.Application;

public static class DependencyInjection
{
    public static IServiceCollection AddApplication(this IServiceCollection services)
    {
        services.AddScoped<IAuthenticationService, AuthenticationService>();
        return services;
    }
}