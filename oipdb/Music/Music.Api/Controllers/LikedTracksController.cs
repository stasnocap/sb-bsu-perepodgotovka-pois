using MapsterMapper;
using MediatR;
using Microsoft.AspNetCore.Mvc;
using Music.Application.LikedTracks.Commands;
using Music.Contracts.LikedTracks;

namespace Music.Api.Controllers;

[Route("[controller]")]
public class LikedTracksController(ISender _mediatr, IMapper _mapper) : ApiController
{
    [HttpPost]
    public async Task<IActionResult> Create(LikeTrackRequest request)
    {
        var command = _mapper.Map<LikeTrackCommand>(request);

        var result = await _mediatr.Send(command, HttpContext.RequestAborted);

        return result.Match(r => Created((Uri?)null, r.Value), Problem);
    }
}