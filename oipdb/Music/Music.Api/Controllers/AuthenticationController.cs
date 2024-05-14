using MediatR;
using Microsoft.AspNetCore.Mvc;
using Music.Application.Authentication.Commands.Register;
using Music.Application.Authentication.Queries.Login;
using Music.Application.Services;
using Music.Contracts.Authentication;

namespace Music.Api.Controllers;

[Route("auth")]
public class AuthenticationController(ISender mediatr) : ApiController
{
    [HttpPost("register")]
    public async Task<IActionResult> Register(RegisterRequest request)
    {
        var registerResult =
            await mediatr.Send(new RegisterCommand(request.FirstName, request.LastName, request.Email,
                request.Password));

        return registerResult.Match(result => Ok(Map(result)), Problem);
    }

    private static AuthenticationResponse Map(AuthenticationResult result) =>
        new(result.User.Id, result.User.FirstName,
            result.User.LastName, result.Email, result.Token);

    [HttpPost("login")]
    public async Task<IActionResult> Login(LoginRequest request)
    {
        var loginResult = await mediatr.Send(new LoginQuery(request.Email, request.Password));

        return loginResult.Match(result => Ok(Map(result)), Problem);
    }
}