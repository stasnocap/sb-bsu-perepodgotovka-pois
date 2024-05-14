using Microsoft.AspNetCore.Mvc;
using Music.Application.Services;
using Music.Contracts.Authentication;

namespace Music.Api.Controllers;

[Route("auth")]
public class AuthenticationController(IAuthenticationService authenticationService) : ApiController
{
    [HttpPost("register")]
    public IActionResult Register(RegisterRequest request)
    {
        var registerResult =
            authenticationService.Register(request.FirstName, request.LastName, request.Email, request.Password);

        return registerResult.Match(result => Ok(Map(result)), Problem);
    }

    private static AuthenticationResponse Map(AuthenticationResult result) =>
        new(result.User.Id, result.User.FirstName,
            result.User.LastName, result.Email, result.Token);

    [HttpPost("login")]
    public IActionResult Login(LoginRequest request)
    {
        var loginResult = authenticationService.Login(request.Email, request.Password);

        return loginResult.Match(result => Ok(Map(result)), Problem);
    }
}