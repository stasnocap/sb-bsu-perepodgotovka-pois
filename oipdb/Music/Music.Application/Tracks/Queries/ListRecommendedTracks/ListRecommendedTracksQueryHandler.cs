using MediatR;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Common.Interfaces.Services;
using Music.Application.Tracks.Common;

namespace Music.Application.Tracks.Queries.ListRecommendedTracks;

public class ListRecommendedTracksQueryHandler(ITrackRepository _trackRepository, IUserContext _userContext) : IRequestHandler<ListRecommendedTracksQuery, List<RecommendedTrackResult>>
{
    public async Task<List<RecommendedTrackResult>> Handle(ListRecommendedTracksQuery request, CancellationToken cancellationToken)
    {
        var userId = _userContext.GetCurrentUserId();

        var result = await _trackRepository.ListRecommendedTracksAsync(userId, cancellationToken);

        return result;
    }
}