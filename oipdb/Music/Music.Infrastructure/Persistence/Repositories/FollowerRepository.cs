using Dapper;
using Microsoft.Extensions.Configuration;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.Artists.ValueObjects;
using Music.Domain.Followers;
using Music.Domain.Users.ValueObjects;
using Music.Infrastructure.Persistence.Interceptors;

namespace Music.Infrastructure.Persistence.Repositories;

public class FollowerRepository(IConfiguration configuration, PublishDomainEventsInterceptor publishDomainEventsInterceptor) : BaseRepository(configuration, publishDomainEventsInterceptor), IFollowerRepository
{
    public async Task AddAsync(Follower follower, CancellationToken cancellationToken)
    {
        await BeginTransactionAsync(cancellationToken);

        const string sql =
            @"INSERT INTO ""Followers""(""Id"", ""ArtistId"", ""UserId"") VALUES (@Id, @ArtistId, @UserId)";

        await Connection.ExecuteAsync(sql, new
        {
            Id = follower.Id.Value,
            ArtistId = follower.ArtistId.Value,
            UserId = follower.UserId.Value,
        });

        await CommitAsync([follower], cancellationToken);
    }

    public async Task<bool> IsAlreadyFollowed(ArtistId artistId, UserId userId)
    {
        const string sql = @"SELECT EXISTS(SELECT 1 FROM ""Followers"" WHERE ""ArtistId""=@ArtistId and ""UserId""=@UserId)";

        var any = (await Connection.QueryAsync<bool>(sql, new
            {
                ArtistId = artistId.Value,
                UserId = userId.Value,
            }))
            .SingleOrDefault();

        return any;
    }
}