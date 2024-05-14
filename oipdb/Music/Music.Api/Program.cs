using Microsoft.AspNetCore.Mvc.Infrastructure;
using Music.Api.Common.Errors;
using Music.Application;
using Music.Infrastructure;

var builder = WebApplication.CreateBuilder(args);
{
    builder.Services
        .AddApplication()
        .AddInfrastructure(builder.Configuration);
    
    builder.Services.AddControllers();
    
    builder.Services.AddSingleton<ProblemDetailsFactory, MusicProblemDetailsFactory>();
}

var app = builder.Build();
{
    app.UseExceptionHandler("/error");
    app.UseHttpsRedirection();
    app.MapControllers();
    app.Run();
}

