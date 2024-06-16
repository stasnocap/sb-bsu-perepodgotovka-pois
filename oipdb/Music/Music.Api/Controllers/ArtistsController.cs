using MapsterMapper;
using MediatR;
using Microsoft.AspNetCore.Mvc;
using Music.Application.Artists.Commands.ChangeArtistName;
using Music.Application.Artists.Commands.CreateArtist;
using Music.Application.Artists.Queries.ListArtists;
using Music.Contracts.Artists;

namespace Music.Api.Controllers;

[Route("[controller]")]
public class ArtistsController(ISender _mediatr, IMapper _mapper) : ApiController
{
    [HttpGet]
    public async Task<IActionResult> ListArtists()
    {
        var query = new ListArtistsQuery();

        var result = await _mediatr.Send(query, HttpContext.RequestAborted);

        return Ok(_mapper.Map<List<ArtistResponse>>(result));
    }

    [HttpPost]
    public async Task<IActionResult> Create(CreateArtistRequest request)
    {
        var command = _mapper.Map<CreateArtistCommand>(request);

        var result = await _mediatr.Send(command, HttpContext.RequestAborted);

        return result.Match(r => Created((Uri?)null, r), Problem);
    }

    [HttpPut]
    public async Task<IActionResult> ChangeName(ChangeArtistNameRequest request)
    {
        var command = _mapper.Map<ChangeArtistNameCommand>(request);

        var result = await _mediatr.Send(command, HttpContext.RequestAborted);

        return result.Match(Ok, Problem);
    }
}