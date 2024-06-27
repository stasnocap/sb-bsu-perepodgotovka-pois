using MapsterMapper;
using MediatR;
using Microsoft.AspNetCore.Mvc;
using Music.Application.Followers.Commands.CreateFollower;
using Music.Contracts.Followers;

namespace Music.Api.Controllers;

[Route("[controller]")]
public class FollowersController(ISender _mediatr, IMapper _mapper) : ApiController
{
    [HttpPost]
    public async Task<IActionResult> Create(CreateFollowerRequest request)
    {
        var command = _mapper.Map<CreateFollowerCommand>(request);

        var result = await _mediatr.Send(command, HttpContext.RequestAborted);

        return result.Match(r => Created((Uri?)null, r.Value), Problem);
    }
}