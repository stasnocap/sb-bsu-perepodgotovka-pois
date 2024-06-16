using MediatR;
using Music.Application.Artists.Common;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.Artists;

namespace Music.Application.Artists.Queries.ListArtists;

public class ListArtistsQueryHandler(IArtistRepository _artistRepository) : IRequestHandler<ListArtistsQuery, List<ArtistResult>>
{
    public async Task<List<ArtistResult>> Handle(ListArtistsQuery request, CancellationToken cancellationToken)
    {
        var artists = await _artistRepository.GetAllAsync(cancellationToken);
        return artists
            .Select<Artist, ArtistResult>(a => new ArtistResult(a.Id.Value, a.Name.Value))
            .ToList();
    }
}