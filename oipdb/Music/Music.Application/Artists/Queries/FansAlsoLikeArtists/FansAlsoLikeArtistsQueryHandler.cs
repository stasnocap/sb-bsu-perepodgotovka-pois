using MediatR;
using Music.Application.Artists.Common;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Common.Interfaces.Services;

namespace Music.Application.Artists.Queries.FansAlsoLikeArtists;

public class FansAlsoLikeArtistsQueryHandler(IArtistRepository _artistRepository, IUserContext _userContext) : IRequestHandler<FansAlsoLikeArtistsQuery, List<FansAlsoLikeArtistResult>>
{
    public async Task<List<FansAlsoLikeArtistResult>> Handle(FansAlsoLikeArtistsQuery request, CancellationToken cancellationToken)
    {
        var userId = _userContext.GetCurrentUserId();

        var result = await _artistRepository.FansAlsoLikeArtistsAsync(request.ArtistId, userId, cancellationToken);

        return result;
    }
}