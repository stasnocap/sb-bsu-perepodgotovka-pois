using MapsterMapper;
using MediatR;
using Microsoft.AspNetCore.Mvc;
using Music.Application.Artists.Commands.ChangeArtistName;
using Music.Application.Artists.Commands.CreateArtist;
using Music.Application.Artists.Queries.FansAlsoLikeArtists;
using Music.Application.Artists.Queries.ListArtists;
using Music.Application.Artists.Queries.ListMostPopularArtists;
using Music.Contracts.Artists.Requests;
using Music.Contracts.Artists.Responses;

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
    
    [HttpGet("by-popularity")]
    public async Task<IActionResult> ListMostPopularArtists()
    {
        var query = new ListMostPopularArtistsQuery();

        var result = await _mediatr.Send(query, HttpContext.RequestAborted);

        return Ok(_mapper.Map<List<PopularArtistResponse>>(result));
    }
    
    [HttpGet("fans-also-like")]
    public async Task<IActionResult> FansAlsoLikeArtists(FansAlsoLikeArtistsRequest request)
    {
        var query = _mapper.Map<FansAlsoLikeArtistsQuery>(request);

        var result = await _mediatr.Send(query, HttpContext.RequestAborted);

        return Ok(_mapper.Map<List<FansAlsoLikeArtistResponse>>(result));
    }

    [HttpPost]
    public async Task<IActionResult> Create(CreateArtistRequest request)
    {
        var command = _mapper.Map<CreateArtistCommand>(request);

        var result = await _mediatr.Send(command, HttpContext.RequestAborted);

        return result.Match(r => Created((Uri?)null, r.Value), Problem);
    }

    [HttpPut]
    public async Task<IActionResult> ChangeName(ChangeArtistNameRequest request)
    {
        var command = _mapper.Map<ChangeArtistNameCommand>(request);

        var result = await _mediatr.Send(command, HttpContext.RequestAborted);

        return result.Match(r => Ok(r.Value), Problem);
    }
}