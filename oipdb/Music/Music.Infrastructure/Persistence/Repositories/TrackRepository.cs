using Dapper;
using Microsoft.Extensions.Configuration;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Tracks.Common;
using Music.Application.Tracks.Queries.ListMostPopularTracks;
using Music.Application.Tracks.Queries.ListRecommendedTracks;
using Music.Domain.Users.ValueObjects;
using Music.Infrastructure.Persistence.Interceptors;

namespace Music.Infrastructure.Persistence.Repositories;

public class TrackRepository(IConfiguration configuration, PublishDomainEventsInterceptor publishDomainEventsInterceptor) : BaseRepository(configuration, publishDomainEventsInterceptor), ITrackRepository
{
    public async Task<List<PopularTrackResult>> ListMostPopularTracksAsync(CancellationToken cancellationToken)
    {
        const string sql = @"SELECT ""TrackId"", ""Name"" AS ""TrackName"", count(*) AS ""Likes""
                             FROM ""Tracks"" T
                                      JOIN public.""LikedTracks"" LT on T.""Id"" = LT.""TrackId""
                             GROUP BY ""TrackId"", ""Name""
                             ORDER BY ""Likes"";";

        var tracks = (await Connection.QueryAsync<PopularTrackResult>(sql)).ToList();

        return tracks;
    }

    public async Task<List<RecommendedTrackResult>> ListRecommendedTracksAsync(UserId userId, CancellationToken cancellationToken)
    {
        const string sql = @"SELECT * FROM recommended_tracks(@UserId);";

        var tracks = (await Connection.QueryAsync<RecommendedTrackResult>(sql, new { UserId = userId.Value })).ToList();

        return tracks;
    }
    
    public async Task<List<RecommendedTrackResult>> DiscoverWeeklyAsync(UserId userId, CancellationToken cancellationToken)
    {
        const string sql = @"SELECT * FROM recommended_tracks(@UserId, current_timestamp - INTERVAL '7 days');";

        var tracks = (await Connection.QueryAsync<RecommendedTrackResult>(sql, new { UserId = userId.Value })).ToList();

        return tracks;
    }
}