using MapsterMapper;
using MediatR;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Music.Application.Authentication.Commands.Register;
using Music.Application.Authentication.Queries.Login;
using Music.Contracts.Authentication;

namespace Music.Api.Controllers;

[Route("auth")]
[AllowAnonymous]
public class AuthenticationController(ISender mediatr, IMapper mapper) : ApiController
{
    [HttpPost("register")]
    public async Task<IActionResult> Register(RegisterRequest request)
    {
        var command = mapper.Map<RegisterCommand>(request);

        var result = await mediatr.Send(command);

        return result.Match(r => Ok(mapper.Map<AuthenticationResponse>(r)), Problem);
    }

    [HttpPost("login")]
    public async Task<IActionResult> Login(LoginRequest request)
    {
        var query = mapper.Map<LoginQuery>(request);

        var result = await mediatr.Send(query);

        return result.Match(r => Ok(mapper.Map<AuthenticationResponse>(r)), Problem);
    }
}