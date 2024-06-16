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
public class AuthenticationController(ISender _mediatr, IMapper _mapper) : ApiController
{
    [HttpPost("register")]
    public async Task<IActionResult> Register(RegisterRequest request)
    {
        var command = _mapper.Map<RegisterCommand>(request);

        var result = await _mediatr.Send(command, HttpContext.RequestAborted);

        return result.Match(r => Created((Uri?)null, _mapper.Map<AuthenticationResponse>(r)), Problem);
    }

    [HttpPost("login")]
    public async Task<IActionResult> Login(LoginRequest request)
    {
        var query = _mapper.Map<LoginQuery>(request);

        var result = await _mediatr.Send(query, HttpContext.RequestAborted);

        return result.Match(r => Ok(_mapper.Map<AuthenticationResponse>(r)), Problem);
    }
}