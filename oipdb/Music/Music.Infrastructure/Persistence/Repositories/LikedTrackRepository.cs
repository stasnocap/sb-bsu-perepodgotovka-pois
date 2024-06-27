using Dapper;
using Microsoft.Extensions.Configuration;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.LikedTracks;
using Music.Domain.Tracks.ValueObjects;
using Music.Domain.Users.ValueObjects;
using Music.Infrastructure.Persistence.Interceptors;

namespace Music.Infrastructure.Persistence.Repositories;

public class LikedTrackRepository(IConfiguration configuration, PublishDomainEventsInterceptor publishDomainEventsInterceptor) : BaseRepository(configuration, publishDomainEventsInterceptor), ILikedTrackRepository
{
    public async Task AddAsync(LikedTrack likedTrack, CancellationToken cancellationToken)
    {
        await BeginTransactionAsync(cancellationToken);

        const string sql = @"INSERT INTO ""LikedTracks"" (""TrackId"", ""UserId"") VALUES (@TrackId, @UserId);";

        await Connection.ExecuteAsync(sql, new
        {
            TrackId = likedTrack.TrackId.Value,
            UserId = likedTrack.UserId.Value,
        });

        await CommitAsync([likedTrack], cancellationToken);
    }

    public async Task<bool> AnyAsync(TrackId trackId, UserId userId, CancellationToken cancellationToken)
    {
        const string sql = @"SELECT EXISTS(SELECT 1 FROM ""LikedTracks"" WHERE ""TrackId""=@TrackId and ""UserId""=@UserId)";

        var any = (await Connection.QueryAsync<bool>(sql, new
            {
                TrackId = trackId.Value,
                UserId = userId.Value
            }))
            .SingleOrDefault();

        return any;
    }
}