using Music.Application.Artists.Common;
using Music.Application.Artists.Queries.FansAlsoLikeArtists;
using Music.Application.Artists.Queries.ListMostPopularArtists;
using Music.Domain.Artists;
using Music.Domain.Artists.ValueObjects;
using Music.Domain.Users.ValueObjects;

namespace Music.Application.Common.Interfaces.Persistence;

public interface IArtistRepository
{
    Task AddAsync(Artist artist, CancellationToken cancellationToken);
    Task<bool> AnyAsync(Name name, CancellationToken cancellationToken);
    Task ChangeNameAsync(Artist artist, CancellationToken cancellationToken);
    Task<Artist?> SingleOrDefaultAsync(ArtistId id, CancellationToken cancellationToken);
    Task<List<Artist>> GetAllAsync(CancellationToken cancellationToken);
    Task<List<PopularArtistResult>> ListMostPopularArtistsAsync(CancellationToken cancellationToken);
    Task<List<FansAlsoLikeArtistResult>> FansAlsoLikeArtistsAsync(ArtistId artistId, UserId userId, CancellationToken cancellationToken);
}