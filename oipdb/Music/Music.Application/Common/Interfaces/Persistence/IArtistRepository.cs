using Music.Domain.Artists;
using Music.Domain.Artists.ValueObjects;

namespace Music.Application.Common.Interfaces.Persistence;

public interface IArtistRepository
{
    Task AddAsync(Artist artist, CancellationToken cancellationToken);
    Task<bool> AnyAsync(Name name, CancellationToken cancellationToken);
    Task ChangeNameAsync(Artist artist, CancellationToken cancellationToken);
    Task<Artist?> SingleOrDefaultAsync(ArtistId id, CancellationToken cancellationToken);
    Task<List<Artist>> GetAllAsync(CancellationToken cancellationToken);
}