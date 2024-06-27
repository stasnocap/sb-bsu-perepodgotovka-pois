using MapsterMapper;
using MediatR;
using Microsoft.AspNetCore.Mvc;
using Music.Application.Tracks.Queries.DiscoverWeekly;
using Music.Application.Tracks.Queries.ListMostPopularTracks;
using Music.Application.Tracks.Queries.ListRecommendedTracks;
using Music.Contracts.Tracks.Responses;

namespace Music.Api.Controllers;

[Route("[controller]")]
public class TracksController(ISender _mediatr, IMapper _mapper) : ApiController
{
    [HttpGet("by-popularity")]
    public async Task<IActionResult> ListMostPopularTracks()
    {
        var query = new ListMostPopularTracksQuery();

        var result = await _mediatr.Send(query, HttpContext.RequestAborted);

        return Ok(_mapper.Map<List<PopularTrackResponse>>(result));
    }
    
    [HttpGet("recommended")]
    public async Task<IActionResult> ListRecommendedTracks()
    {
        var query = new ListRecommendedTracksQuery();

        var result = await _mediatr.Send(query, HttpContext.RequestAborted);

        return Ok(_mapper.Map<List<RecommendedTrackResponse>>(result));
    }
    
    [HttpGet("discover-weekly")]
    public async Task<IActionResult> DiscoverWeekly()
    {
        var query = new DiscoverWeeklyQuery();

        var result = await _mediatr.Send(query, HttpContext.RequestAborted);

        return Ok(_mapper.Map<List<RecommendedTrackResponse>>(result));
    }
}