using System.Reflection;
using Dapper;
using Microsoft.Extensions.Configuration;
using Music.Application.Artists.Common;
using Music.Application.Artists.Queries.FansAlsoLikeArtists;
using Music.Application.Artists.Queries.ListMostPopularArtists;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.Artists;
using Music.Domain.Artists.ValueObjects;
using Music.Domain.Users.ValueObjects;
using Music.Infrastructure.Persistence.Interceptors;

namespace Music.Infrastructure.Persistence.Repositories;

public class ArtistRepository(IConfiguration configuration, PublishDomainEventsInterceptor publishDomainEventsInterceptor) : BaseRepository(configuration, publishDomainEventsInterceptor), IArtistRepository
{
    public async Task AddAsync(Artist artist, CancellationToken cancellationToken)
    {
        await BeginTransactionAsync(cancellationToken);

        const string sql =
            @"INSERT INTO ""Artists""(""Id"", ""Name"") VALUES (@Id, @Name)";

        await Connection.ExecuteAsync(sql, new
        {
            Id = artist.Id.Value,
            Name = artist.Name.Value,
        });

        await CommitAsync([artist], cancellationToken);
    }

    public async Task<bool> AnyAsync(Name name, CancellationToken cancellationToken)
    {
        const string sql = @"SELECT EXISTS(SELECT 1 FROM ""Artists"" WHERE ""Name""=@Name)";
        
        var any = (await Connection.QueryAsync<bool>(sql, new { Name = name.Value }))
            .SingleOrDefault();
        
        return any;
    }

    public async Task ChangeNameAsync(Artist artist, CancellationToken cancellationToken)
    {
        const string sql = @"UPDATE ""Artists"" SET ""Name"" = @Name WHERE ""Id"" = @Id";

        await Connection.ExecuteAsync(sql, new
        {
            Id = artist.Id.Value,
            Name = artist.Name.Value,
        });
    }

    public async Task<Artist?> SingleOrDefaultAsync(ArtistId id, CancellationToken cancellationToken)
    {
        const string sql = @"SELECT * FROM ""Artists"" WHERE ""Id"" = @id";

        var artist = (await Connection.QueryAsync<Artist>(sql, [typeof(ArtistDto)], 
                objs => ((ArtistDto)objs[0]).ToArtist(), 
                new { Id = id.Value }))
            .SingleOrDefault();

        return artist;
    }

    public async Task<List<Artist>> GetAllAsync(CancellationToken cancellationToken)
    {
        const string sql = @"SELECT * FROM ""Artists""";
        
        var artists = (await Connection.QueryAsync<Artist>(sql, [typeof(ArtistDto)], 
            objs => ((ArtistDto)objs[0]).ToArtist()))
            .ToList();

        return artists;
    }

    public async Task<List<PopularArtistResult>> ListMostPopularArtistsAsync(CancellationToken cancellationToken)
    {
        const string sql = @"SELECT ""ArtistId"", ""Name"", count(*) AS ""Followers""
                             FROM ""Artists"" A
                                 JOIN ""Followers"" F on A.""Id"" = F.""ArtistId""
                             GROUP BY F.""ArtistId"", ""Name""
                             ORDER BY ""Followers"";";
        
        var artists = (await Connection.QueryAsync<PopularArtistResult>(sql)).ToList();

        return artists;
    }

    public async Task<List<FansAlsoLikeArtistResult>> FansAlsoLikeArtistsAsync(ArtistId artistId, UserId userId, CancellationToken cancellationToken)
    {
        const string sql = @"SELECT A.""Id"" AS ""ArtistId"", A.""Name"" AS ""ArtistName"" from fans_also_like_artists(@ArtistId, @UserId) A;";
        
        var artists = (await Connection.QueryAsync<FansAlsoLikeArtistResult>(sql, param: new { ArtistId = artistId.Value, UserId = userId.Value })).ToList();
    
        return artists;
    }

    private class ArtistDto
    {
        private static readonly ConstructorInfo Constructor =
            typeof(Artist).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];

        private static readonly ConstructorInfo IdConstructor =
            typeof(ArtistId).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];
        
        private static readonly ConstructorInfo NameConstructor =
            typeof(Name).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];
        
        public Guid Id { get; init; }
        public string Name { get; init; }

        public Artist ToArtist()
        {
            var userId = IdConstructor.Invoke([Id]);
            var firstName = NameConstructor.Invoke([Name]);
            var user = (Artist)Constructor.Invoke([userId, firstName]);
            return user;
        }
    }
}