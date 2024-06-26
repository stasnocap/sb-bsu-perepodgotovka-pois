﻿using System.Text;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Identity;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Options;
using Microsoft.IdentityModel.Tokens;
using Music.Application.Common.Interfaces.Authentication;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Common.Interfaces.Services;
using Music.Domain.Users;
using Music.Infrastructure.Authentication;
using Music.Infrastructure.Persistence;
using Music.Infrastructure.Persistence.Interceptors;
using Music.Infrastructure.Persistence.Repositories;
using Music.Infrastructure.Services;

namespace Music.Infrastructure;

public static class DependencyInjection
{
    public static IServiceCollection AddInfrastructure(this IServiceCollection services,
        IConfiguration configuration)
    {
        services.AddAuth(configuration);
        services.AddSingleton<IDateTimeProvider, DateTimeProvider>();
        services.AddHttpContextAccessor();
        services.AddScoped<IUserContext, UserContext>();

        services.AddScoped<PublishDomainEventsInterceptor>();
        services.AddScoped<IPasswordHasher<User>, PasswordHasher<User>>();
        services.AddScoped<IUserRepository, UserRepository>();
        services.AddScoped<IArtistRepository, ArtistRepository>();
        services.AddScoped<IFollowerRepository, FollowerRepository>();
        services.AddScoped<ILikedTrackRepository, LikedTrackRepository>();
        services.AddScoped<ITrackRepository, TrackRepository>();
        
        return services;
    }

    private static IServiceCollection AddAuth(this IServiceCollection services, IConfiguration configuration)
    {
        var jwtSettings = new JwtSettings();
        configuration.Bind(JwtSettings.SectionName, jwtSettings);

        services.AddSingleton(Options.Create(jwtSettings));
        services.AddSingleton<IJwtTokenGenerator, JwtTokenGenerator>();

        services.AddAuthentication(defaultScheme: JwtBearerDefaults.AuthenticationScheme)
            .AddJwtBearer(options => options.TokenValidationParameters = new TokenValidationParameters
            {
                ValidateIssuer = true,
                ValidateAudience = true,
                ValidateLifetime = true,
                ValidateIssuerSigningKey = true,
                ValidIssuer = jwtSettings.Issuer,
                ValidAudience = jwtSettings.Audience,
                IssuerSigningKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(jwtSettings.Secret))
            });

        return services;
    }
}