using MediatR;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Common.Interfaces.Services;
using Music.Application.Tracks.Common;

namespace Music.Application.Tracks.Queries.DiscoverWeekly;

public class DiscoverWeeklyQueryHandler(ITrackRepository _trackRepository, IUserContext _userContext) : IRequestHandler<DiscoverWeeklyQuery, List<RecommendedTrackResult>>
{
    public async Task<List<RecommendedTrackResult>> Handle(DiscoverWeeklyQuery request, CancellationToken cancellationToken)
    {
        var userId = _userContext.GetCurrentUserId();

        var result = await _trackRepository.DiscoverWeeklyAsync(userId, cancellationToken);

        return result;
    }
}