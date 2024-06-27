using MediatR;
using Music.Application.Artists.Common;
using Music.Application.Common.Interfaces.Persistence;

namespace Music.Application.Artists.Queries.ListMostPopularArtists;

public class ListMostPopularArtistsQueryHandler(IArtistRepository _artistRepository) : IRequestHandler<ListMostPopularArtistsQuery, List<PopularArtistResult>>
{
    public async Task<List<PopularArtistResult>> Handle(ListMostPopularArtistsQuery request, CancellationToken cancellationToken)
    {
        var result = await _artistRepository.ListMostPopularArtistsAsync(cancellationToken);
        
        return result;
    }
}