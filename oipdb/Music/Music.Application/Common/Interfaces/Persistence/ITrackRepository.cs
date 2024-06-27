using Music.Application.Tracks.Common;
using Music.Application.Tracks.Queries.ListMostPopularTracks;
using Music.Application.Tracks.Queries.ListRecommendedTracks;
using Music.Domain.Users.ValueObjects;

namespace Music.Application.Common.Interfaces.Persistence;

public interface ITrackRepository
{
    Task<List<PopularTrackResult>> ListMostPopularTracksAsync(CancellationToken cancellationToken);
    Task<List<RecommendedTrackResult>> ListRecommendedTracksAsync(UserId userId, CancellationToken cancellationToken);
    Task<List<RecommendedTrackResult>> DiscoverWeeklyAsync(UserId userId, CancellationToken cancellationToken);
}